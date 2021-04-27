#include "xmc1100.h"
#include "scu.h"
#include "usic.h"

// Serial inputs from the pins to the protocol processor:
//   DX0,DX3,DX4,DX5 input pins (DX0 for uart, pin select is DXnCR.DSEL).
//   DX1              clock input
//   DX2              control input
// Which feed into registers:
//   RBUF             for byte by byte receive
//   OUTR             for optional FIFO receive

// Serial outputs from the output stage to the pins:
//   DOUT0 ... DOUT3  data out (uart uses DOUT0)
// Which are fed from registers:
//   TBUFx            for byte by byte transmit (includes TCI in register addr)
//   INx & BYP        for optional FIFO transmit (INx includes TCI)

// Interrupt registers:
//   CCR   enables general interrupts
//   INPR  routes general events to usic sr interrupts
//   PSR   indicates the cause of the interrupt
//   PSCR  is the bit clear register for PSR
// General interrupts (with flag and enable+route):
//   Transmit Buffer  TBIF  CCR.TBIEN+INPR.TBINP
//   Receive Buffer   RSIF  CCR.RSIEN+INPR.TBINP (shared with transmit)
//   Transmit Shift   TSIF  CCR.TSIEN+INPR.TSINP
//   Standard Receive RIF   CCR.RIEN+INPR.RINP
//   Alt. Receive     AIF   CCR.RIEN+INPR.RINP
//   Data Lost        DLIF  CCR.DLIEN+INPR.PINP (shared with protocol spec)
//   Baud Rate Gen    BRGIF CCR.BRGIEN+INPR.PINP (shared with protocol spec)
// UART specific interrupts:
//   TX Frame Finish  TFF   PCR.FFIEN
//   RX Frame Finish  RFF
//   Collision Detect COL   PCR.CDEN
//   Syn Break Detect SBD   PCR.SBIEN
//   RX Noise Detect  RNS   PCR.RNIEN
//   Format Err 0     FER0  PCR.FEIEN
//   Format Err 1     FER1
// FIFO interrupts:
//   TRBSR indicates the cause of the interrupt
//   Standard Tx FIFO event  STBI  TBCTR.STBIEN+TBCTR.STBINP
//   Tx FIFO error event     TBERI TBCTR.SRBIEN+TBCTR.ATBINP
//   Standard Rx FIFO event  SRBI  RBCTR.SRBIEN+RBCTR.SRBINP
//   Alternate Rx FIFO event ARBI  RBCTR.ARBIEN+RBCTR.ARBINP
//   Rx FIFO error event     RBERI RBCTR.RBERIEN+RBCTR.ARBINP

#define TXBUFF_LEN 128
static unsigned short ch0TxBuff[TXBUFF_LEN];
static unsigned int ch0TxBuffStart = 0;
static unsigned int ch0TxBuffEnd = 0;

static const char hex_digits[] = "0123456789abcdef";

void toHex(const unsigned int val, char *buff) {
        unsigned int index;

        for (index = 0; index < 8; index++) {
                unsigned int x = (val >> (4 * (7 - index)));
                buff[index] = hex_digits[(x & 0x0f)];
        }
        buff[index] = '\0';
}

void toHexShort(const unsigned int val, char *buff) {
        unsigned int index;

        for (index = 0; index < 4; index++) {
                unsigned int x = (val >> (4 * (3 - index)));
                buff[index] = hex_digits[(x & 0x0f)];
        }
        buff[index] = '\0';
}

unsigned int usicEnable(void) {
	// Clear gating of USIC in SCU_CGATCLR0
	if (scuUngatePeripheralClock(CGATCLR0_USIC0)) {
		return 1;
	}

	// Check module identification
	// This is not available before peripheral clock starts.
	if ((USIC0_ID >> 8) != 0x0000AAC0) {
		return 1;
	}

	return 0;
}

const unsigned int usicChannelBase(const int channel) {
	switch(channel) {
	case 0:
		return USIC0_CH0_BASE;
	case 1:
		return USIC0_CH1_BASE;
	}
	return 0;
}

static void usicConfigureSSCMaster(const unsigned int cbase) {
	// Configure USIC channel 1 as an SSC master using pins:
	//   DX0 input: P0.6 (USIC0_CH1.DX0C)
	//   DOUT0 output: P0.7 (P0.7 ALT7)
	//   SCLKOUT output: P0.8 (P0.8 ALT7)
	//   CS SELO0 output: P0.9 (P0.9 ALT7)
	// Channel 1 XMC2Go available pins:
	//   DX0 input is available on P0.6, P0.7, P2.10, P2.11
	//   DOUT0 is available on P0.6, P0.7, P2.10, P2.11
	//   SCLKOUT is available on P0.8, P2.11
	//   CS SELO0 is available on P0.0 or P0.9
	//   No other CS SELO? line is exposed.

	// Baud rate config for SCLK.
	// fsclk = fsys(32MHz) * (STEP/1024) * 1/2 * 1/(PDIV + 1)
	// using scripts/serial_solver.py we find a good fractional solution
	// that provides exactly 100K and 400k baud fsclk values:
	// step=0x300 PCTQ=1 PDIV=0x77 100000  PDIV=13 400000
	// Max baud rate for these values is 1.2M.
	// Unlike ASC mode DCTQ only effects a couple of idle periods.
	// Fractional mode, STEP=0x300 (fFD = 32MHz * (0x300/0x3FF) = 24MHz)
	USIC0_FDR(cbase) = 0x00008300;
	USIC0_BRG(cbase) = (1 << 30) |      // SCLKCFG = 01 (SCLK passive high)
	                   (0x000B << 16) | // PDIV (fPDIV = fPPP / 12 (2MHz))
	                   (1 << 10) |      // DCTQ = 0x01 (2 time quanta)
	                   (1 << 8) |       // PCTQ = 0x01 (tQ = 2/fPPP 2/2MHz)
	                   (0 << 6) |       // CTQSEL = 1 (fCTQIN = fPDIV)
	                   (0 << 4) |       // PPPEN = 0 (fPPP = fPIN (24MHz))
	                   (0 << 0);        // CLKSEL = 0 (fPIN = fFD (24MHz))

	// Shift control register.
	// FLE is overridden by TCI[4:0] due to TCSR.FLEMD being set below,
	// ie writing to USIC0_TBUF[15] sets it to 15.
	USIC0_SCTR(cbase) = ((16-1) << 24) | // SCTR.WLE (word length)
	                    ((16-1) << 16) | // SCTR.FLE (frame length)
	                    (1 << 8) | // SCTR.TRM (1: shift idle at 1)
	                    (0 << 6) | // SCTR.DOCFG (0: DOUTx not inverted)
	                    (0 << 4) | // SCTR.HPCDIR (0: hwcontrol=input
	                    (0 << 2) | // SCTR.DSM (0: one bit at a time)
	                    (1 << 1) | // SCTR.PDL (1: passive data level 1)
	                    (1 << 0);  // SCTR.SDIR (1: shift MSB first)

	// Transmission control and status register.
	USIC0_TCSR(cbase) = (1 << 10) | // TCSR.TDEN (01: TBUFx valid if TDV)
	                    (1 << 8)  | // TCSR.TDSSM (1: invalidate sent data)
	                    (1 << 2);   // TCSR.FLEMD (1: TBUFx sets frame len)
	                    //(1 << 1); // TCSR.SELMD (1: TBUFx selects CS)
	                    //(1 << 0); // TCSR.WLEMD (1: TBUFx sets word len)

	// SSC Protocol Control Register.
	USIC0_PCR(cbase) = (1 << 16) | // PCR.SELO (1: SELO0 can be used)
	                   (0 << 8) | // PCR.DCTQ1 (0: 1/fctqin)
	                   (0 << 6) | // PCR.PCTQ1 (0: 1/fctqin)
	                   (2 << 4) | // PCR.CTQSEL1 (2: fctqin = fsclk)
	                   (0 << 3) | // PCR.FEM (0: Frame ends when TX ends)
	                   (1 << 2) | // PCR.SELINV (1: CS is active low)
	                   (1 << 1) | // PCR.SELCTR (1: direct select mode)
	                   (1 << 0);  // PCR.MSLSEN (1: master use slave select)

	// No FIFO buffering.
	USIC0_RBCTR(cbase) = 0;

	// DX0 data input.
	USIC0_DX0CR(cbase) = (0 << 8) | // DX0CR.DPOL (0: signal isnt inverted)
	                     (1 << 4) | // DX0CR.INSW (1: no PPU processing)
	                     (2 << 0);  // DX0CR.DSEL = DXnC (P0.6)
	// DX1 clock input (to data shift unit).
	// PPP provides clock for data shift unit because INSW and DCEN are 0.
	USIC0_DX1CR(cbase) = 0;
	// DX2 chip select input (to data shift unit).
	// Not used in master mode, PPP provides select and delay for the DSU.
	USIC0_DX2CR(cbase) = 0;
}

static void usicConfigureASC(const unsigned int cbase) {
	// For clock = 32MHz:
	// Fractional mode, STEP=0x24E
	// PDIV=0004, DCTQ=15, PCTQ=1 (PDIV=4 for 115200 baud,
	//                             PDIV=3B for 9600)
	USIC0_FDR(cbase) = 0x0000824E;
	USIC0_BRG(cbase) = (0x0004 << 16) | (15 << 10) | (1<<8);
	// 8 bits, active high, passive high
	// USIC0_SCTR(cbase) = 0x07070102;
	USIC0_SCTR(cbase) = ((8-1) << 24) | // SCTR.WLE (word length)
	                    ((8-1) << 16) | // SCTR.FLE (frame length)
	                    (1 << 8) | // SCTR.TRM (1: shift idle at 1)
	                    (0 << 6) | // SCTR.DOCFG (0: DOUTx not inverted)
	                    (0 << 4) | // SCTR.HPCDIR (0: hwcontrol=input
	                    (0 << 2) | // SCTR.DSM (0: one bit at a time)
	                    (1 << 1) | // SCTR.PDL (1: passive data level 1)
	                    (0 << 0); // SCTR.SDIR (0: shift LSB first)
	// TDSSM=1: TBUF is considered invalid when moved to shift reg
	// TDEN=1:  TBUF is considered valid when it gets assigned
	USIC0_TCSR(cbase) = 0x00000500;  // TDSSM=1, TDEN=01
	// majority bit decision, 1 stop, sample at 9
	USIC0_PCR(cbase) = (9 << 8) | 1;
	// TODO: This is only correct for CH0 to the XMC2Go pins.
	USIC0_DX3CR(cbase) = 0x00000000;  // DX3 DXnA selected (P2.2)
	USIC0_DX0CR(cbase) = 0x00000006;  // DX0 DXnG selected, fPeriph
}

static void usicConfigureIIC(const unsigned int cbase) {
	;
}

unsigned int usicConfigure(int channel, int protocol) {
	const unsigned int cbase = usicChannelBase(channel);
	if (cbase == 0)
		return 0;

	if (usicEnable())
		return 0;

	// Enable USIC module clock and functionality.
	// Module enable (+moden write)
	USIC0_KSCFG(cbase) = BIT1 | BIT0;
	// Set channel operating mode to disabled, idle.
	USIC0_CCR(cbase) = USIC_PROTO_DISABLED;

	// Protocol specific settings.
	unsigned int proto_available = BIT6 | BIT7; // RB, TB buffers
	unsigned int ccr_enable = 0;
	switch(protocol) {
	case USIC_PROTO_SSC:
		proto_available |= BIT0;
		// SSC
		ccr_enable = USIC_PROTO_SSC;
		usicConfigureSSCMaster(cbase);
		break;
	case USIC_PROTO_ASC:
		proto_available |= BIT1;
		// ASC, no hardware control, no parity.
		ccr_enable = USIC_PROTO_ASC;
		usicConfigureASC(cbase);
		break;
	case USIC_PROTO_IIC:
		proto_available |= BIT2;
		// IIC, parity must be disabled.
		ccr_enable = USIC_PROTO_IIC;
		usicConfigureIIC(cbase);
		break;
	default:
		return 0;
	}

	// Check that the protocol is supported on this channel.
	if ((USIC0_CCFG(cbase) & proto_available) != proto_available) {
		return 0;
	}

	// Use default interrupt routing.
	USIC0_INPR(cbase) = 0;

	// Enable the protocol unit.
	USIC0_CCR(cbase) = ccr_enable;

	return cbase;
}

// Input character handler, may be overridden by the user.
void __attribute__((weak)) usicCh0Receive(unsigned int val) {
	val = val & 0xFF;
	USIC0_IN(USIC0_CH0_BASE)[0] = val;
	if ((unsigned char)val == '\r') {
		USIC0_IN(USIC0_CH0_BASE)[0] = '\n';
	}
}

// Output done check, may be overridden by user.
unsigned int __attribute__((weak)) usicCh0TransmitDone(void) {
	if (ch0TxBuffStart >= ch0TxBuffEnd) {
		ch0TxBuffStart = ch0TxBuffEnd = 0;
		return 1;
	}
	return 0;
}

// Output character handler, may be overridden by user.
unsigned short __attribute__((weak)) usicCh0Transmit(void) {
	if (ch0TxBuffStart < ch0TxBuffEnd) {
		return ch0TxBuff[ch0TxBuffStart++];
	} else {
		return '?';
	}
}

// Send one byte via the callbacks above.
void usicSendCh0Byte(void) {
	// Transmit a byte if we have one to send.
	if (!(usicCh0TransmitDone && usicCh0TransmitDone())) {
		if (usicCh0Transmit) {
			USIC0_IN(USIC0_CH0_BASE)[0] = usicCh0Transmit();
		} else {
			USIC0_IN(USIC0_CH0_BASE)[0] = 'x';
		}
	}
}

// Interface for sending data via the callbacks above.
void usicSendCh0(void) {
	// Enable the TX interrupt and transmit the first byte.
	USIC0_TBCTR(USIC0_CH0_BASE) |= BIT30;
	usicSendCh0Byte();
}

// Interface for sending a string using the default callbacks.
void usicBufferedSendCh0(const char *msg) {
	unsigned int i, pos;
	pos = ch0TxBuffEnd;
	for(i=0; (msg[i] != '\0') && (pos < TXBUFF_LEN); i++, pos++) {
		ch0TxBuff[pos] = msg[i];
	}
	ch0TxBuffEnd = pos;
	usicSendCh0();
}

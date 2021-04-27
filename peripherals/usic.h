// Support for the XMC1100 USIC (universal serial interface channel)

#ifndef PERIPHERALS_USIC_H
#define PERIPHERALS_USIC_H

enum usic_protocols {
        USIC_PROTO_DISABLED = 0,
        USIC_PROTO_SSC = 1,
        USIC_PROTO_ASC = 2,
        USIC_PROTO_IIS = 3,
        USIC_PROTO_IIC = 4,
};

unsigned int usicEnable(void);
// Eg. usicConfigure(0, USIC_PROTO_ASC);
unsigned int usicConfigure(int channel, int protocol);

// Internal helper.
const unsigned int usicChannelBase(const int channel);

void usicSendCh0(void);

// Callbacks used by usicSendCh0 to get next byte to send.
// Output done check, default may be overridden by user.
extern unsigned int usicCh0TransmitDone(void);
// Output character handler, default may be overridden by user.
extern unsigned short usicCh0Transmit(void);
// Input character handler, default may be overridden by the user.
// The default echoes received characters back to output.
extern void usicCh0Receive(unsigned int);

// Interfaces for sending data via the callbacks above.
void usicSendCh0Byte(void);
void usicSendCh0(void);
// Interface for sending a string using the default callbacks.
void usicBufferedSendCh0(const char *msg);

void toHex(const unsigned int val, char *buff);
void toHexShort(const unsigned int val, char *buff);

#define USIC0_ID            REGISTER_32(USIC0_CH0_BASE + 0x08)

#define USIC0_CCFG(cbase)   REGISTER_32(cbase + 0x004)

#define USIC0_KSCFG(cbase)  REGISTER_32(cbase + 0x00c)
#define USIC0_FDR(cbase)    REGISTER_32(cbase + 0x010)
#define USIC0_BRG(cbase)    REGISTER_32(cbase + 0x014)
#define USIC0_INPR(cbase)   REGISTER_32(cbase + 0x018)
#define USIC0_DX0CR(cbase)  REGISTER_32(cbase + 0x01c)
#define USIC0_DX1CR(cbase)  REGISTER_32(cbase + 0x020)
#define USIC0_DX2CR(cbase)  REGISTER_32(cbase + 0x024)
#define USIC0_DX3CR(cbase)  REGISTER_32(cbase + 0x028)
#define USIC0_DX4CR(cbase)  REGISTER_32(cbase + 0x02c)
#define USIC0_DX5CR(cbase)  REGISTER_32(cbase + 0x030)
#define USIC0_SCTR(cbase)   REGISTER_32(cbase + 0x034)
#define USIC0_TCSR(cbase)   REGISTER_32(cbase + 0x038)
#define USIC0_PCR(cbase)    REGISTER_32(cbase + 0x03c)
#define USIC0_CCR(cbase)    REGISTER_32(cbase + 0x040)
#define USIC0_CMTR(cbase)   REGISTER_32(cbase + 0x044)
#define USIC0_PSR(cbase)    REGISTER_32(cbase + 0x048)
#define USIC0_PSCR(cbase)   REGISTER_32(cbase + 0x04c)

#define USIC0_RBUFSR(cbase)       REGISTER_32(cbase + 0x050)
#define USIC0_RBUF(cbase)         REGISTER_32(cbase + 0x054)
#define USIC0_RBUFD(cbase)        REGISTER_32(cbase + 0x058)
#define USIC0_RBUF0(cbase)        REGISTER_32(cbase + 0x05c)
#define USIC0_RBUF1(cbase)        REGISTER_32(cbase + 0x060)
#define USIC0_RBUF01SR(cbase)     REGISTER_32(cbase + 0x064)
#define USIC0_FMR(cbase)          REGISTER_32(cbase + 0x068)

// USIC0_TBUF IS AN ARRAY OF 32 WORDS (INDEX 0 TO 31)
#define USIC0_TBUF(cbase)         PTR_32(cbase + 0x080)

#define USIC0_BYP(cbase)          REGISTER_32(cbase + 0x100)
#define USIC0_BYPCR(cbase)        REGISTER_32(cbase + 0x104)
#define USIC0_TBCTR(cbase)        REGISTER_32(cbase + 0x108)
#define USIC0_RBCTR(cbase)        REGISTER_32(cbase + 0x10c)
#define USIC0_TRBPTR(cbase)       REGISTER_32(cbase + 0x110)
#define USIC0_TRBSR(cbase)        REGISTER_32(cbase + 0x114)
#define USIC0_TRBSCR(cbase)       REGISTER_32(cbase + 0x118)
#define USIC0_OUTR(cbase)         REGISTER_32(cbase + 0x11c)
#define USIC0_OUTDR(cbase)        REGISTER_32(cbase + 0x120)

// USIC_IN IS AN ARRAY OF 32 WORDS (INDEX 0 TO 31)
#define USIC0_IN(cbase)           PTR_32(cbase + 0x180)

#endif

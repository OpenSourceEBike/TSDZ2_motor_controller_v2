<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="UART" URI="http://resources/4.1.14/app/UART/0" description="UART APP configures a USIC channel to perform &#xA;transmit &amp; receive operations using UART protocol." mode="NOTSHARABLE" version="4.1.14" minDaveVersion="4.0.0" instanceLabel="UART_0" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="dx0_input_stage" URI="http://resources/4.1.14/app/UART/0/vs_uart_dx0ins" hwSignal="dx0ins" hwResource="//@hwResources.0"/>
  <virtualSignals name="dx3_input_stage" URI="http://resources/4.1.14/app/UART/0/vs_uart_dx3ins" hwSignal="dx3ins" hwResource="//@hwResources.0"/>
  <virtualSignals name="dout0_output" URI="http://resources/4.1.14/app/UART/0/vs_uart_dout0" hwSignal="dout0" hwResource="//@hwResources.0"/>
  <virtualSignals name="rxd_pin" URI="http://resources/4.1.14/app/UART/0/vs_uart_rxpad" hwSignal="pad" hwResource="//@hwResources.1" visible="true"/>
  <virtualSignals name="txd_pin" URI="http://resources/4.1.14/app/UART/0/vs_uart_txpad" hwSignal="pad" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="event_transmit_buffer" URI="http://resources/4.1.14/app/UART/0/vs_uart_std_tx_int" hwSignal="transmit_buffer_int" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="event_std_receive" URI="http://resources/4.1.14/app/UART/0/vs_uart_std_rx_int" hwSignal="standard_receive_int" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="event_alt_receive" URI="http://resources/4.1.14/app/UART/0/vs_uart_alt_rx_int" hwSignal="alternate_receive_int" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="event_protocol" URI="http://resources/4.1.14/app/UART/0/vs_uart_proto_specfic_int" hwSignal="protocol_specific_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="event_fifo_transmit" URI="http://resources/4.1.14/app/UART/0/vs_uart_fifo_tx_int" hwSignal="standard_transmit_buffer_int" hwResource="//@hwResources.0"/>
  <virtualSignals name="event_fifo_std_receive" URI="http://resources/4.1.14/app/UART/0/vs_uart_fifo_rx_int" hwSignal="standard_receive_buffer_int" hwResource="//@hwResources.0"/>
  <virtualSignals name="event_fifo_alt_receive" URI="http://resources/4.1.14/app/UART/0/vs_uart_fifo_alt_rx_int" hwSignal="alternate_receive_buffer_int" hwResource="//@hwResources.0"/>
  <virtualSignals name="sr_transmit" URI="http://resources/4.1.14/app/UART/0/vs_interrupt_uart_tx" hwSignal="signal_in" hwResource="//@hwResources.3"/>
  <virtualSignals name="sr_receive" URI="http://resources/4.1.14/app/UART/0/vs_interrupt_uart_rx" hwSignal="signal_in" hwResource="//@hwResources.4"/>
  <virtualSignals name="sr_protocol_events" URI="http://resources/4.1.14/app/UART/0/vs_interrupt_uart_error" hwSignal="signal_in" hwResource="//@hwResources.5" required="false"/>
  <virtualSignals name="source_trigger" URI="http://resources/4.1.14/app/UART/0/vs_src_trigger_dlr_rx_in" hwSignal="in" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="destination_trigger" URI="http://resources/4.1.14/app/UART/0/vs_dst_trigger_dlr_tx_in" hwSignal="in" hwResource="//@hwResources.8" required="false"/>
  <virtualSignals name="dlr_out" URI="http://resources/4.1.14/app/UART/0/vs_src_trigger_dlr_rx_out" hwSignal="out" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="dlr_out" URI="http://resources/4.1.14/app/UART/0/vs_dst_trigger_dlr_tx_out" hwSignal="out" hwResource="//@hwResources.8" required="false"/>
  <virtualSignals name="DMA Transfer complete event" URI="http://resources/4.1.14/app/UART/0/vs_dma_interrupt_tx" hwSignal="dma_int" hwResource="//@hwResources.6" required="false"/>
  <virtualSignals name="DMA Transfer complete event" URI="http://resources/4.1.14/app/UART/0/vs_dma_interrupt_rx" hwSignal="dma_int" hwResource="//@hwResources.7" required="false"/>
  <virtualSignals name="Destination request" URI="http://resources/4.1.14/app/UART/0/vs_dma_ch_dst_req_tx" hwSignal="dest_req" hwResource="//@hwResources.6" required="false"/>
  <virtualSignals name="Source request" URI="http://resources/4.1.14/app/UART/0/vs_dma_ch_src_req_rx" hwSignal="src_req" hwResource="//@hwResources.7" required="false"/>
  <virtualSignals name="Receive Pin_signal" URI="http://resources/4.1.14/app/UART/0/__pin_vs_uart_rxpad" hwSignal="pin" hwResource="//@hwResources.10"/>
  <virtualSignals name="Transmit Pin_signal" URI="http://resources/4.1.14/app/UART/0/__pin_vs_uart_txpad" hwSignal="pin" hwResource="//@hwResources.11"/>
  <requiredApps URI="http://resources/4.1.14/app/UART/0/appres_clock" requiredAppName="CLOCK_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CLOCK_XMC1/v4_0_26/CLOCK_XMC1_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.1.14/app/UART/0/appres_cpu" requiredAppName="CPU_CTRL_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CPU_CTRL_XMC1/v4_0_12/CPU_CTRL_XMC1_0.app#/"/>
  </requiredApps>
  <hwResources name="Channel" URI="http://resources/4.1.14/app/UART/0/hwres_usic_ch" resourceGroupUri="peripheral/usic/*/channel/*" mResGrpUri="peripheral/usic/*/channel/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/USIC0/USIC0_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="Receive Pin" URI="http://resources/4.1.14/app/UART/0/hwres_port_pad_uart_rx" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.14"/>
  </hwResources>
  <hwResources name="Transmit Pin" URI="http://resources/4.1.14/app/UART/0/hwres_port_pad_uart_tx" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.19"/>
  </hwResources>
  <hwResources name="NVIC Node Tx" URI="http://resources/4.1.14/app/UART/0/hwres_nvic_node_tx" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CPU/CPU_0.dd#//@provided.3"/>
  </hwResources>
  <hwResources name="NVIC Node Rx" URI="http://resources/4.1.14/app/UART/0/hwres_nvic_node_rx" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CPU/CPU_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="NVIC Node Error" URI="http://resources/4.1.14/app/UART/0/hwres_nvic_node_error" resourceGroupUri="" required="false" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*"/>
  <hwResources name="DMA channel Tx" URI="http://resources/4.1.14/app/UART/0/hwres_dma_ch_tx" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/sv0/0/ch/*">
    <solverVarMap index="1">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="1">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="DMA channel Rx" URI="http://resources/4.1.14/app/UART/0/hwres_dma_ch_rx" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/sv0/0/ch/*">
    <solverVarMap index="1">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="1">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="DLR channel Tx" URI="http://resources/4.1.14/app/UART/0/hwres_dlr_ch_tx" resourceGroupUri="" required="false" mResGrpUri="peripheral/dlr/0/ch/*"/>
  <hwResources name="DLR channel Rx" URI="http://resources/4.1.14/app/UART/0/hwres_dlr_ch_rx" resourceGroupUri="" required="false" mResGrpUri="peripheral/dlr/0/ch/*"/>
  <hwResources name="Receive Pin" URI="http://resources/4.1.14/app/UART/0/__pin_hwres_port_pad_uart_rx" resourceGroupUri="devicepackage/0/23" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.6"/>
  </hwResources>
  <hwResources name="Transmit Pin" URI="http://resources/4.1.14/app/UART/0/__pin_hwres_port_pad_uart_tx" resourceGroupUri="devicepackage/0/24" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.16"/>
  </hwResources>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_rxpad/http://resources/4.1.14/app/UART/0/vs_uart_dx0ins" systemDefined="true" sourceSignal="rxd_pin" targetSignal="dx0_input_stage" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_dout0/http://resources/4.1.14/app/UART/0/vs_uart_txpad" systemDefined="true" sourceSignal="dout0_output" targetSignal="txd_pin" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.4"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_txpad/http://resources/4.1.14/app/UART/0/vs_uart_dx0ins" systemDefined="true" sourceSignal="txd_pin" targetSignal="dx0_input_stage" required="false" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_dout0/http://resources/4.1.14/app/UART/0/vs_uart_dx0ins" systemDefined="true" sourceSignal="dout0_output" targetSignal="dx0_input_stage" required="false" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_std_tx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_tx" systemDefined="true" sourceSignal="event_transmit_buffer" targetSignal="sr_transmit" required="false" srcVirtualSignal="//@virtualSignals.5" targetVirtualSignal="//@virtualSignals.12"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_std_rx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_rx" systemDefined="true" sourceSignal="event_std_receive" targetSignal="sr_receive" required="false" srcVirtualSignal="//@virtualSignals.6" targetVirtualSignal="//@virtualSignals.13"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_alt_rx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_rx" systemDefined="true" sourceSignal="event_alt_receive" targetSignal="sr_receive" required="false" srcVirtualSignal="//@virtualSignals.7" targetVirtualSignal="//@virtualSignals.13"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_fifo_tx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_tx" systemDefined="true" sourceSignal="event_fifo_transmit" targetSignal="sr_transmit" srcVirtualSignal="//@virtualSignals.9" targetVirtualSignal="//@virtualSignals.12"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_fifo_rx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_rx" systemDefined="true" sourceSignal="event_fifo_std_receive" targetSignal="sr_receive" srcVirtualSignal="//@virtualSignals.10" targetVirtualSignal="//@virtualSignals.13"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_fifo_alt_rx_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_rx" systemDefined="true" sourceSignal="event_fifo_alt_receive" targetSignal="sr_receive" srcVirtualSignal="//@virtualSignals.11" targetVirtualSignal="//@virtualSignals.13"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_proto_specfic_int/http://resources/4.1.14/app/UART/0/vs_interrupt_uart_error" systemDefined="true" sourceSignal="event_protocol" targetSignal="sr_protocol_events" required="false" srcVirtualSignal="//@virtualSignals.8" targetVirtualSignal="//@virtualSignals.14"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_rxpad/http://resources/4.1.14/app/UART/0/__pin_vs_uart_rxpad" systemDefined="true" sourceSignal="rxd_pin" targetSignal="Receive Pin_signal" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.23"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/__pin_vs_uart_rxpad/http://resources/4.1.14/app/UART/0/vs_uart_rxpad" systemDefined="true" sourceSignal="Receive Pin_signal" targetSignal="rxd_pin" srcVirtualSignal="//@virtualSignals.23" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/vs_uart_txpad/http://resources/4.1.14/app/UART/0/__pin_vs_uart_txpad" systemDefined="true" sourceSignal="txd_pin" targetSignal="Transmit Pin_signal" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.24"/>
  <connections URI="http://resources/4.1.14/app/UART/0/http://resources/4.1.14/app/UART/0/__pin_vs_uart_txpad/http://resources/4.1.14/app/UART/0/vs_uart_txpad" systemDefined="true" sourceSignal="Transmit Pin_signal" targetSignal="txd_pin" srcVirtualSignal="//@virtualSignals.24" targetVirtualSignal="//@virtualSignals.4"/>
</ResourceModel:App>

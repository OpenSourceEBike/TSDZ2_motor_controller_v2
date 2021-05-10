<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="CLOCK_XMC1" URI="http://resources/4.0.26/app/CLOCK_XMC1/0" description="CLOCK_XMC1 APP configures System and Peripheral Clocks." version="4.0.26" minDaveVersion="4.0.0" instanceLabel="CLOCK_XMC1_0" appLabel="">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../UART/v4_1_14/UART_0.app#//@requiredApps.0"/>
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@requiredApps.0"/>
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../GLOBAL_ADC/v4_0_22/GLOBAL_ADC_0.app#//@requiredApps.0"/>
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#//@requiredApps.0"/>
  <properties singleton="true" provideInit="true" sharable="true"/>
  <virtualSignals name="clk_dco2_output" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_dco_clkout" hwSignal="clkout" hwResource="//@hwResources.0"/>
  <virtualSignals name="clk_rtc" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_frtc" hwSignal="frtc" hwResource="//@hwResources.1"/>
  <virtualSignals name="clk_dco2_output" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_dco2_clk" hwSignal="dco2_clk" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="clk_osc_lp_output" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_lp_clk" hwSignal="osc_lp_clk" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="clk_hp_xtal1_input" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_hp_xtal1" hwSignal="osc_hp_xtal1" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="clk_hp_xtal2_input" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_hp_xtal2" hwSignal="osc_hp_xtal2" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="clk_lp_xtal1_input" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_lp_xtal1" hwSignal="osc_lp_xtal1" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="clk_lp_xtal2_input" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_lp_xtal2" hwSignal="osc_lp_xtal2" hwResource="//@hwResources.1" required="false" visible="true"/>
  <requiredApps URI="http://resources/4.0.26/app/CLOCK_XMC1/0/appres_global_scu" requiredAppName="GLOBAL_SCU_XMC1" required="false" requiringMode="SHARABLE"/>
  <hwResources name="DCO CLOCK" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_dco" resourceGroupUri="peripheral/scu/0/dco/*" mResGrpUri="peripheral/scu/0/dco/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="CLOCK CONTROL UNIT" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_clkcntrlunit" resourceGroupUri="peripheral/scu/0/ccu/config" mResGrpUri="peripheral/scu/0/ccu/config">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.1"/>
  </hwResources>
  <hwResources name="osc_hp_xtal1" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_port_pad_osc_hp_xtal1" resourceGroupUri="" required="false" mResGrpUri="port/p/0/pad/10"/>
  <hwResources name="osc_hp_xtal2" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_port_pad_osc_hp_xtal2" resourceGroupUri="" required="false" mResGrpUri="port/p/0/pad/11"/>
  <hwResources name="osc_rtc_xtal1" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_port_pad_osc_rtc_xtal1" resourceGroupUri="" required="false" mResGrpUri="port/p/0/pad/8"/>
  <hwResources name="osc_rtc_xtal2" URI="http://resources/4.0.26/app/CLOCK_XMC1/0/hwres_port_pad_osc_rtc_xtal2" resourceGroupUri="" required="false" mResGrpUri="port/p/0/pad/9"/>
  <connections URI="http://resources/4.0.26/app/CLOCK_XMC1/0/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_dco_clkout/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_frtc" systemDefined="true" sourceSignal="clk_dco2_output" targetSignal="clk_rtc" srcVirtualSignal="//@virtualSignals.0" targetVirtualSignal="//@virtualSignals.1"/>
  <connections URI="http://resources/4.0.26/app/CLOCK_XMC1/0/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_dco2_clk/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_frtc" systemDefined="true" sourceSignal="clk_dco2_output" targetSignal="clk_rtc" required="false" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.1"/>
  <connections URI="http://resources/4.0.26/app/CLOCK_XMC1/0/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_osc_lp_clk/http://resources/4.0.26/app/CLOCK_XMC1/0/vs_frtc" systemDefined="true" sourceSignal="clk_osc_lp_output" targetSignal="clk_rtc" required="false" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.1"/>
</ResourceModel:App>

<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="ADC_QUEUE" URI="http://resources/4.0.20/app/ADC_QUEUE/0" description="Provides configurations for queue request source of VADC" mode="NOTSHARABLE" version="4.0.20" minDaveVersion="4.0.0" instanceLabel="ADC_QUEUE_0" appLabel="" containingProxySignal="true">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@requiredApps.0"/>
  <properties provideInit="true" sharable="true"/>
  <virtualSignals name="queue_to_global" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_queueglobal" hwSignal="global_signal" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="queue_select" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" hwSignal="select" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.10"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.11"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.12"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.14"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.15"/>
  </virtualSignals>
  <virtualSignals name="group_selection" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_queue2config" hwSignal="req" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="trigger_input" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_greqtr0sel" hwSignal="greqtr0sel" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_2/PMSM_FOC_0.app#//@connections.45"/>
  </virtualSignals>
  <virtualSignals name="gating_input" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_greqgt0sel" hwSignal="greqgt0sel" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="event_queue_source" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_sourceevent" hwSignal="sev" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="class_select" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_classselect_out" hwSignal="class_sel" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="iclass_select" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_iclass2channel" hwSignal="ch_class_sel" hwResource="//@hwResources.1" visible="true"/>
  <virtualSignals name="queue_iclass_select" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_classselect_in" hwSignal="queue_class_sel" hwResource="//@hwResources.1"/>
  <virtualSignals name="sr_interrupt_signal" URI="http://resources/4.0.20/app/ADC_QUEUE/0/vs_signal_src" hwSignal="signal_in" hwResource="//@hwResources.2" required="false" visible="true"/>
  <requiredApps URI="http://resources/4.0.20/app/ADC_QUEUE/0/appres_global_adc" requiredAppName="GLOBAL_ADC" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_ADC/v4_0_16/GLOBAL_ADC_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.0.20/app/ADC_QUEUE/0/appres_cpu" requiredAppName="CPU_CTRL_XMC1" required="false" requiringMode="SHARABLE"/>
  <hwResources name="Queue" URI="http://resources/4.0.20/app/ADC_QUEUE/0/hwres_vadc_queue" resourceGroupUri="peripheral/vadc/*/group/*/queue" mResGrpUri="peripheral/vadc/*/group/*/queue">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.1"/>
  </hwResources>
  <hwResources name="Queue Class" URI="http://resources/4.0.20/app/ADC_QUEUE/0/hwres_vadc_qgrpclass" resourceGroupUri="peripheral/vadc/*/group/*/class/*" mResGrpUri="peripheral/vadc/*/group/*/class/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="Source Event Interrupt" URI="http://resources/4.0.20/app/ADC_QUEUE/0/hwres_nvicnode_srcevt" resourceGroupUri="" required="false" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*"/>
  <connections URI="http://resources/4.0.20/app/ADC_QUEUE/0/http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_sourceevent/http://resources/4.0.20/app/ADC_QUEUE/0/vs_signal_src" systemDefined="true" sourceSignal="event_queue_source" targetSignal="sr_interrupt_signal" required="false" srcVirtualSignal="//@virtualSignals.5" targetVirtualSignal="//@virtualSignals.9"/>
  <connections URI="http://resources/4.0.20/app/ADC_QUEUE/0/http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_classselect_out/http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_classselect_in" systemDefined="true" sourceSignal="class_select" targetSignal="queue_iclass_select" srcVirtualSignal="//@virtualSignals.6" targetVirtualSignal="//@virtualSignals.8"/>
  <connections URI="http://resources/4.0.20/app/ADC_QUEUE/0/http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_to_global_signal/http://resources/4.0.20/app/ADC_QUEUE/0/vs_adc_queue_queueglobal" systemDefined="true" sourceSignal="global_signal" targetSignal="queue_to_global" targetVirtualSignal="//@virtualSignals.0" proxySrcVirtualSignalUri="http://resources/4.0.16/app/GLOBAL_ADC/0/vs_global_adc_global" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_ADC/v4_0_16/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_ADC/v4_0_16/GLOBAL_ADC_0.app#//@virtualSignals.0"/>
  </connections>
</ResourceModel:App>

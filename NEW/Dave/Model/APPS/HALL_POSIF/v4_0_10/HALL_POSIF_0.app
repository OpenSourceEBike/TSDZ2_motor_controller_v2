<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="HALL_POSIF" URI="http://resources/4.0.10/app/HALL_POSIF/0" description="To get the &#xA; motor position and speed using &#xA; hall sensors separated at 120 degrees.&#xA; It supports 2-hall and 3-hall configuration." version="4.0.10" minDaveVersion="4.0.0" instanceLabel="HALL_POSIF_0" appLabel="" containingProxySignal="true">
  <properties provideInit="true" sharable="true"/>
  <virtualSignals name="hall_1" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input0" hwSignal="ipos0" hwResource="//@hwResources.0"/>
  <virtualSignals name="hall_2" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input1" hwSignal="ipos1" hwResource="//@hwResources.0"/>
  <virtualSignals name="hall_3" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input2" hwSignal="ipos2" hwResource="//@hwResources.0"/>
  <virtualSignals name="hall_pattern_sample_delay" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pifhsd" hwSignal="pifhsd" hwResource="//@hwResources.0"/>
  <virtualSignals name="wrong_hall_event_emulation" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pifewhe" hwSignal="pifewhe" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="hall_input_edge_detection_trigger" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out0" hwSignal="out0" hwResource="//@hwResources.0"/>
  <virtualSignals name="corret_hall_output" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out1" hwSignal="out1" hwResource="//@hwResources.0"/>
  <virtualSignals name="wrong_hall_output" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out2" hwSignal="out2" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="stop" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out3" hwSignal="out3" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="multichannel_pattern_update" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out4" hwSignal="out4" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="syncstart" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out5" hwSignal="out5" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="event_wrong_hall" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_whee" hwSignal="whee" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="event_hall_input_update" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_hiee" hwSignal="hiee" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="event_correct_hall" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_chee" hwSignal="chee" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="multichannel_pattern_update_trigger" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_ps" hwSignal="ps" hwResource="//@hwResources.5" visible="true"/>
  <virtualSignals name="phase_delay_slice_global_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_globalsignal" hwSignal="global_signal" hwResource="//@hwResources.4"/>
  <virtualSignals name="capture_slice_global_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_globalsignal" hwSignal="global_signal" hwResource="//@hwResources.5"/>
  <virtualSignals name="phase_delay_slice_status" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_st0" hwSignal="st" hwResource="//@hwResources.4"/>
  <virtualSignals name="event_phase_delay_slice_period_match" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_periodmatch" hwSignal="pmus_omds" hwResource="//@hwResources.4" visible="true"/>
  <virtualSignals name="event_pattern_update" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_compmatch" hwSignal="cmds_cmus" hwResource="//@hwResources.5" visible="true"/>
  <virtualSignals name="event_speed_capture" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_capture" hwSignal="e0as" hwResource="//@hwResources.5" visible="true"/>
  <virtualSignals name="phase_delay_slice_external_start_input_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_gp0unsync" hwSignal="gp0_unsync" hwResource="//@hwResources.4"/>
  <virtualSignals name="external_capture_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_gp0unsync" hwSignal="gp0_unsync" hwResource="//@hwResources.5"/>
  <virtualSignals name="hall_1_pad" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall1" hwSignal="pad" hwResource="//@hwResources.1"/>
  <virtualSignals name="hall_2_pad" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall2" hwSignal="pad" hwResource="//@hwResources.2"/>
  <virtualSignals name="hall_3_pad" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall3" hwSignal="pad" hwResource="//@hwResources.3"/>
  <virtualSignals name="hall_1_event_generation_signal_a" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall1" hwSignal="a" hwResource="//@hwResources.6" required="false"/>
  <virtualSignals name="hall_2_event_generation_signal_a" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall2" hwSignal="a" hwResource="//@hwResources.7" required="false"/>
  <virtualSignals name="hall_3_event_generation_signal_a" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall3" hwSignal="a" hwResource="//@hwResources.8" required="false"/>
  <virtualSignals name="hall_1_event_generation_flag_status" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall1" hwSignal="fl" hwResource="//@hwResources.6" required="false"/>
  <virtualSignals name="hall_2_event_generation_flag_status" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall2" hwSignal="fl" hwResource="//@hwResources.7" required="false"/>
  <virtualSignals name="hall_3_event_generation_flag_status" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall3" hwSignal="fl" hwResource="//@hwResources.8" required="false"/>
  <virtualSignals name="hall_1_event_detection_in" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall1" hwSignal="pdin" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="hall_2_event_detection_in" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall2" hwSignal="pdin" hwResource="//@hwResources.10" required="false"/>
  <virtualSignals name="hall_3_event_detection_in" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall3" hwSignal="pdin" hwResource="//@hwResources.11" required="false"/>
  <virtualSignals name="hall_1_event_detection_out" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall1" hwSignal="pdout" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="hall_2_event_detection_out" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall2" hwSignal="pdout" hwResource="//@hwResources.10" required="false"/>
  <virtualSignals name="hall_3_event_detection_out" URI="http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall3" hwSignal="pdout" hwResource="//@hwResources.11" required="false"/>
  <virtualSignals name="Hall 1_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall1" hwSignal="pin" hwResource="//@hwResources.12"/>
  <virtualSignals name="Hall 2_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall2" hwSignal="pin" hwResource="//@hwResources.13"/>
  <virtualSignals name="Hall 3_signal" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall3" hwSignal="pin" hwResource="//@hwResources.14"/>
  <requiredApps URI="http://resources/4.0.10/app/HALL_POSIF/0/appres_global_posif_0" requiredAppName="GLOBAL_POSIF" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_POSIF/v4_0_18/GLOBAL_POSIF_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.0.10/app/HALL_POSIF/0/appres_global_ccu4_0" requiredAppName="GLOBAL_CCU4" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#/"/>
  </requiredApps>
  <hwResources name="POSIF Hall" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_posif_hsc_qd_0" resourceGroupUri="peripheral/posif/*/posif/hsc_qd" mResGrpUri="peripheral/posif/*/posif/hsc_qd">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/POSIF0/POSIF0_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="Hall 1" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_port_pad_1" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port1/Port1_1.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="Hall 2" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_port_pad_2" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port1/Port1_1.dd#//@provided.15"/>
  </hwResources>
  <hwResources name="Hall 3" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_port_pad_3" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port1/Port1_1.dd#//@provided.11"/>
  </hwResources>
  <hwResources name="Hall Event Blanking CC4 Slice" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_ccu4_slice0" resourceGroupUri="peripheral/ccu4/*/cc4/*" mResGrpUri="peripheral/ccu4/*/cc4/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU40/CCU40_0.dd#//@provided.3"/>
  </hwResources>
  <hwResources name="Capture CC4 Slice" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_ccu4_slice1" resourceGroupUri="peripheral/ccu4/*/cc4/*" mResGrpUri="peripheral/ccu4/*/cc4/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU40/CCU40_0.dd#//@provided.14"/>
  </hwResources>
  <hwResources name="ETL 1" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_ers_etl_1" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ers_etl/*"/>
  <hwResources name="ETL 2" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_ers_etl_2" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ers_etl/*"/>
  <hwResources name="ETL 3" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_ers_etl_3" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ers_etl/*"/>
  <hwResources name="OGU 1" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_eru_ogu_1" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ogu/*"/>
  <hwResources name="OGU 2" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_eru_ogu_2" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ogu/*"/>
  <hwResources name="OGU 3" URI="http://resources/4.0.10/app/HALL_POSIF/0/hwres_eru_ogu_3" resourceGroupUri="" required="false" mResGrpUri="peripheral/eru/*/ogu/*"/>
  <hwResources name="Hall 1" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_hwres_port_pad_1" resourceGroupUri="devicepackage/0/*" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="Hall 2" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_hwres_port_pad_2" resourceGroupUri="devicepackage/0/*" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.2"/>
  </hwResources>
  <hwResources name="Hall 3" URI="http://resources/4.0.10/app/HALL_POSIF/0/__pin_hwres_port_pad_3" resourceGroupUri="devicepackage/0/*" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.3"/>
  </hwResources>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_global_ccu4_globalsignal/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_globalsignal" systemDefined="true" sourceSignal="ccu4_global" targetSignal="phase_delay_slice_global_signal" targetVirtualSignal="//@virtualSignals.15" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU4/0/vs_global_ccu4_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_global_ccu4_globalsignal/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_globalsignal" systemDefined="true" sourceSignal="ccu4_global" targetSignal="capture_slice_global_signal" targetVirtualSignal="//@virtualSignals.16" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU4/0/vs_global_ccu4_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU4/v4_1_14/GLOBAL_CCU4_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_st0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pifhsd" systemDefined="true" sourceSignal="phase_delay_slice_status" targetSignal="hall_pattern_sample_delay" srcVirtualSignal="//@virtualSignals.17" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice0_gp0unsync" systemDefined="true" sourceSignal="hall_input_edge_detection_trigger" targetSignal="phase_delay_slice_external_start_input_signal" srcVirtualSignal="//@virtualSignals.5" targetVirtualSignal="//@virtualSignals.21"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_out1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_slice1_gp0unsync" systemDefined="true" sourceSignal="corret_hall_output" targetSignal="external_capture_signal" srcVirtualSignal="//@virtualSignals.6" targetVirtualSignal="//@virtualSignals.22"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input0" systemDefined="true" sourceSignal="hall_1_pad" targetSignal="hall_1" srcVirtualSignal="//@virtualSignals.23" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall2/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input1" systemDefined="true" sourceSignal="hall_2_pad" targetSignal="hall_2" srcVirtualSignal="//@virtualSignals.24" targetVirtualSignal="//@virtualSignals.1"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall3/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input2" systemDefined="true" sourceSignal="hall_3_pad" targetSignal="hall_3" srcVirtualSignal="//@virtualSignals.25" targetVirtualSignal="//@virtualSignals.2"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall1" systemDefined="true" sourceSignal="hall_1_pad" targetSignal="hall_1_event_generation_signal_a" required="false" srcVirtualSignal="//@virtualSignals.23" targetVirtualSignal="//@virtualSignals.26"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall2/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall2" systemDefined="true" sourceSignal="hall_2_pad" targetSignal="hall_2_event_generation_signal_a" required="false" srcVirtualSignal="//@virtualSignals.24" targetVirtualSignal="//@virtualSignals.27"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall3/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_input_a_hall3" systemDefined="true" sourceSignal="hall_3_pad" targetSignal="hall_3_event_generation_signal_a" required="false" srcVirtualSignal="//@virtualSignals.25" targetVirtualSignal="//@virtualSignals.28"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall1" systemDefined="true" sourceSignal="hall_1_event_generation_flag_status" targetSignal="hall_1_event_detection_in" required="false" srcVirtualSignal="//@virtualSignals.29" targetVirtualSignal="//@virtualSignals.32"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall2/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall2" systemDefined="true" sourceSignal="hall_2_event_generation_flag_status" targetSignal="hall_2_event_detection_in" required="false" srcVirtualSignal="//@virtualSignals.30" targetVirtualSignal="//@virtualSignals.33"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventgen_flagstatus_hall3/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdin_hall3" systemDefined="true" sourceSignal="hall_3_event_generation_flag_status" targetSignal="hall_3_event_detection_in" required="false" srcVirtualSignal="//@virtualSignals.31" targetVirtualSignal="//@virtualSignals.34"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input0" systemDefined="true" sourceSignal="hall_1_event_detection_out" targetSignal="hall_1" required="false" srcVirtualSignal="//@virtualSignals.35" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall2/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input1" systemDefined="true" sourceSignal="hall_2_event_detection_out" targetSignal="hall_2" required="false" srcVirtualSignal="//@virtualSignals.36" targetVirtualSignal="//@virtualSignals.1"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_eventdet_pdout_hall3/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_input2" systemDefined="true" sourceSignal="hall_3_event_detection_out" targetSignal="hall_3" required="false" srcVirtualSignal="//@virtualSignals.37" targetVirtualSignal="//@virtualSignals.2"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall1/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall1" systemDefined="true" sourceSignal="hall_1_pad" targetSignal="Hall 1_signal" srcVirtualSignal="//@virtualSignals.23" targetVirtualSignal="//@virtualSignals.38"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall1/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall1" systemDefined="true" sourceSignal="Hall 1_signal" targetSignal="hall_1_pad" srcVirtualSignal="//@virtualSignals.38" targetVirtualSignal="//@virtualSignals.23"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall2/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall2" systemDefined="true" sourceSignal="hall_2_pad" targetSignal="Hall 2_signal" srcVirtualSignal="//@virtualSignals.24" targetVirtualSignal="//@virtualSignals.39"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall2/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall2" systemDefined="true" sourceSignal="Hall 2_signal" targetSignal="hall_2_pad" srcVirtualSignal="//@virtualSignals.39" targetVirtualSignal="//@virtualSignals.24"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall3/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall3" systemDefined="true" sourceSignal="hall_3_pad" targetSignal="Hall 3_signal" srcVirtualSignal="//@virtualSignals.25" targetVirtualSignal="//@virtualSignals.40"/>
  <connections URI="http://resources/4.0.10/app/HALL_POSIF/0/http://resources/4.0.10/app/HALL_POSIF/0/__pin_vs_hall_posif_pad_hall3/http://resources/4.0.10/app/HALL_POSIF/0/vs_hall_posif_pad_hall3" systemDefined="true" sourceSignal="Hall 3_signal" targetSignal="hall_3_pad" srcVirtualSignal="//@virtualSignals.40" targetVirtualSignal="//@virtualSignals.25"/>
</ResourceModel:App>

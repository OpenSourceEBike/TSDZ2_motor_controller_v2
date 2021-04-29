<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="PWM_SVM" URI="http://resources/4.0.30/app/PWM_SVM/0" description="Generates 3-phase space vector pulse width modulated &#xA;outputs using CCU8. It supports symmetric &#xA; 7-segment/5-segment SVM algorithm." mode="NOTSHARABLE" version="4.0.30" minDaveVersion="4.0.0" instanceLabel="PWM_SVM_0" appLabel="" containingProxySignal="true">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../PMSM_FOC/v4_2_14/PMSM_FOC_0.app#//@requiredApps.4"/>
  <properties provideInit="true" sharable="true"/>
  <virtualSignals name="ph_u_global_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phu" hwSignal="global_signal" hwResource="//@hwResources.0"/>
  <virtualSignals name="ph_v_global_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phv" hwSignal="global_signal" hwResource="//@hwResources.1"/>
  <virtualSignals name="ph_w_global_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phw" hwSignal="global_signal" hwResource="//@hwResources.2"/>
  <virtualSignals name="adc_trigger_global_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_currenttrig" hwSignal="global_signal" hwResource="//@hwResources.3"/>
  <virtualSignals name="ph_u_external_start" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phu" hwSignal="gp0_unsync" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="ph_v_external_start" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phv" hwSignal="gp0_unsync" hwResource="//@hwResources.1" visible="true"/>
  <virtualSignals name="ph_w_external_start" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phw" hwSignal="gp0_unsync" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="current_trigger_external_start" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_currenttrig" hwSignal="gp0_unsync" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="ph_u_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phu" hwSignal="gp2_unsync" hwResource="//@hwResources.0"/>
  <virtualSignals name="ph_v_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phv" hwSignal="gp2_unsync" hwResource="//@hwResources.1"/>
  <virtualSignals name="ph_w_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phw" hwSignal="gp2_unsync" hwResource="//@hwResources.2"/>
  <virtualSignals name="trigger_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_currenttrig" hwSignal="gp2_unsync" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="event_ph_u_period/one_match" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_phu" hwSignal="pmus_omds" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_14/PMSM_FOC_0.app#//@connections.0"/>
  </virtualSignals>
  <virtualSignals name="event_ph_v_period/one_match" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_phv" hwSignal="pmus_omds" hwResource="//@hwResources.1" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_14/PMSM_FOC_0.app#//@connections.2"/>
  </virtualSignals>
  <virtualSignals name="event_ph_w_period/one_match" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_phw" hwSignal="pmus_omds" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="adc_trigger_period/one_match" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_currenttrig" hwSignal="pmus_omds" hwResource="//@hwResources.3" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_14/PMSM_FOC_0.app#//@connections.45"/>
  </virtualSignals>
  <virtualSignals name="event_ph_u_compare_match_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_phu" hwResource="//@hwResources.0" visible="true" solverVariableName="sv0" solverVariableValue="cmd1s_cmu1s"/>
  <virtualSignals name="event_ph_v_compare_match_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_phv" hwResource="//@hwResources.1" visible="true" solverVariableName="sv1" solverVariableValue="cmd1s_cmu1s"/>
  <virtualSignals name="event_ph_w_compare_match_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_phw" hwResource="//@hwResources.2" visible="true" solverVariableName="sv2" solverVariableValue="cmd1s_cmu1s"/>
  <virtualSignals name="event_ph_v_compare_match_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_op_cmds_cmus_cmpch1_phv" hwResource="//@hwResources.0" required="false" visible="true" solverVariableName="sv1" solverVariableValue=""/>
  <virtualSignals name="event_ph_w_compare_match_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_op_cmds_cmus_cmpch1_phw" hwResource="//@hwResources.1" required="false" visible="true" solverVariableName="sv2" solverVariableValue=""/>
  <virtualSignals name="event_current_trigger_compare_match1_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_currenttrig" hwSignal="cmd1s_cmu1s" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="event_ph_u_compare_match2_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_phu" hwSignal="cmd2s_cmu2s" hwResource="//@hwResources.0" required="false" visible="true"/>
  <virtualSignals name="event_ph_v_compare_match2_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_phv" hwSignal="cmd2s_cmu2s" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="event_ph_w_compare_match2_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_phw" hwSignal="cmd2s_cmu2s" hwResource="//@hwResources.2" required="false" visible="true"/>
  <virtualSignals name="event_current_trigger_compare_match2_up/down" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_currenttrig" hwSignal="cmd2s_cmu2s" hwResource="//@hwResources.3" required="false" visible="true"/>
  <virtualSignals name="event_ph_u_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_e2as_phu" hwSignal="e2as" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PMSM_FOC/v4_2_14/PMSM_FOC_0.app#//@connections.1"/>
  </virtualSignals>
  <virtualSignals name="event_ph_v_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_e2as_phv" hwSignal="e2as" hwResource="//@hwResources.1" visible="true"/>
  <virtualSignals name="event_ph_w_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_e2as_phw" hwSignal="e2as" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="event_trigger_trap" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_e2as_currenttrig" hwSignal="e2as" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="ph_u_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_sta_phu" hwResource="//@hwResources.0" visible="true" solverVariableName="sv3" solverVariableValue="sta"/>
  <virtualSignals name="ph_v_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_sta_phv" hwResource="//@hwResources.1" visible="true" solverVariableName="sv4" solverVariableValue="sta"/>
  <virtualSignals name="ph_w_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_sta_phw" hwResource="//@hwResources.2" visible="true" solverVariableName="sv5" solverVariableValue="sta"/>
  <virtualSignals name="ph_v_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_op_sta_phv" hwResource="//@hwResources.0" required="false" visible="true" solverVariableName="sv4" solverVariableValue=""/>
  <virtualSignals name="ph_w_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_op_sta_phw" hwResource="//@hwResources.1" required="false" visible="true" solverVariableName="sv5" solverVariableValue=""/>
  <virtualSignals name="adc_trigger_ch_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_sta_currenttrig" hwSignal="sta" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="ph_u_ch2_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_stb_phu" hwSignal="stb" hwResource="//@hwResources.0" required="false" visible="true"/>
  <virtualSignals name="ph_v_ch2_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_stb_phv" hwSignal="stb" hwResource="//@hwResources.1" required="false" visible="true"/>
  <virtualSignals name="ph_w_ch2_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_stb_phw" hwSignal="stb" hwResource="//@hwResources.2" required="false" visible="true"/>
  <virtualSignals name="adc_trigger_ch2_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_stb_currenttrig" hwSignal="stb" hwResource="//@hwResources.3" required="false" visible="true"/>
  <virtualSignals name="ph_u_slice_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_st_phu" hwSignal="st" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="ph_v_slice_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_st_phv" hwSignal="st" hwResource="//@hwResources.1" visible="true"/>
  <virtualSignals name="ph_w_slice_status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_st_phw" hwSignal="st" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="trigger_slice Status" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_st_currenttrig" hwSignal="st" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="ph_u_high" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phu" hwResource="//@hwResources.0" solverVariableName="sv6" solverVariableValue="out0"/>
  <virtualSignals name="ph_v_high" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phv" hwResource="//@hwResources.1" solverVariableName="sv7" solverVariableValue="out0"/>
  <virtualSignals name="ph_w_high" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phw" hwResource="//@hwResources.2" solverVariableName="sv8" solverVariableValue="out0"/>
  <virtualSignals name="ph_v_high" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_op_phv" hwResource="//@hwResources.0" required="false" solverVariableName="sv7" solverVariableValue=""/>
  <virtualSignals name="ph_w_high" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_op_phw" hwResource="//@hwResources.1" required="false" solverVariableName="sv8" solverVariableValue=""/>
  <virtualSignals name="ph_u_low" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phu" hwResource="//@hwResources.0" solverVariableName="sv9" solverVariableValue="out1"/>
  <virtualSignals name="ph_v_low" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phv" hwResource="//@hwResources.1" solverVariableName="sv10" solverVariableValue="out1"/>
  <virtualSignals name="ph_w_low" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phw" hwResource="//@hwResources.2" solverVariableName="sv11" solverVariableValue="out1"/>
  <virtualSignals name="ph_v_low" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_op_phv" hwResource="//@hwResources.0" required="false" solverVariableName="sv10" solverVariableValue=""/>
  <virtualSignals name="ph_w_low" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_op_phw" hwResource="//@hwResources.1" required="false" solverVariableName="sv11" solverVariableValue=""/>
  <virtualSignals name="ph_u_high_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_high" hwSignal="pad" hwResource="//@hwResources.4"/>
  <virtualSignals name="ph_u_low_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_low" hwSignal="pad" hwResource="//@hwResources.5"/>
  <virtualSignals name="ph_v_high_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_high" hwSignal="pad" hwResource="//@hwResources.6"/>
  <virtualSignals name="ph_v_low_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_low" hwSignal="pad" hwResource="//@hwResources.7"/>
  <virtualSignals name="ph_w_high_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_high" hwSignal="pad" hwResource="//@hwResources.8"/>
  <virtualSignals name="ph_w_low_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_low" hwSignal="pad" hwResource="//@hwResources.9"/>
  <virtualSignals name="trap_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap" hwSignal="pad" hwResource="//@hwResources.10"/>
  <virtualSignals name="inverter_enable_pad" URI="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_inverter" hwSignal="pad" hwResource="//@hwResources.11"/>
  <virtualSignals name="PhaseU_High Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_high" hwSignal="pin" hwResource="//@hwResources.12"/>
  <virtualSignals name="PhaseV_High Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_high" hwSignal="pin" hwResource="//@hwResources.13"/>
  <virtualSignals name="PhaseW_High Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_high" hwSignal="pin" hwResource="//@hwResources.14"/>
  <virtualSignals name="PhaseU_Low Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_low" hwSignal="pin" hwResource="//@hwResources.15"/>
  <virtualSignals name="PhaseV_Low Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_low" hwSignal="pin" hwResource="//@hwResources.16"/>
  <virtualSignals name="PhaseW_Low Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_low" hwSignal="pin" hwResource="//@hwResources.17"/>
  <virtualSignals name="Trap Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_trap" hwSignal="pin" hwResource="//@hwResources.18"/>
  <virtualSignals name="Inverter Enable Pin_signal" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_inverter" hwSignal="pin" hwResource="//@hwResources.19"/>
  <requiredApps URI="http://resources/4.0.30/app/PWM_SVM/0/appres_global_ccu8_app0" requiredAppName="GLOBAL_CCU8" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#/"/>
  </requiredApps>
  <hwResources name="PhU Slice" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_ccu8_config_a" resourceGroupUri="peripheral/ccu8/*/cc8/*" mResGrpUri="peripheral/ccu8/*/cc8/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU80/CCU80_0.dd#//@provided.42"/>
  </hwResources>
  <hwResources name="PhV Slice" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_ccu8_config_b" resourceGroupUri="peripheral/ccu8/*/cc8/*" mResGrpUri="peripheral/ccu8/*/cc8/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU80/CCU80_0.dd#//@provided.14"/>
  </hwResources>
  <hwResources name="PhW Slice" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_ccu8_config_c" resourceGroupUri="peripheral/ccu8/*/cc8/*" mResGrpUri="peripheral/ccu8/*/cc8/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU80/CCU80_0.dd#//@provided.28"/>
  </hwResources>
  <hwResources name="CCU8 ADC trigger Slice" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_ccu8_config_d" resourceGroupUri="peripheral/ccu8/*/cc8/*" mResGrpUri="peripheral/ccu8/*/cc8/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU80/CCU80_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="PhaseU_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phuhigh" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.27"/>
  </hwResources>
  <hwResources name="PhaseU_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phulow" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.41"/>
  </hwResources>
  <hwResources name="PhaseV_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phvhigh" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.45"/>
  </hwResources>
  <hwResources name="PhaseV_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phvlow" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.37"/>
  </hwResources>
  <hwResources name="PhaseW_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phwhigh" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.49"/>
  </hwResources>
  <hwResources name="PhaseW_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_phwlow" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.32"/>
  </hwResources>
  <hwResources name="Trap Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_trap" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port0/Port0_0.dd#//@provided.10"/>
  </hwResources>
  <hwResources name="Inverter Enable Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/hwres_port_pad_inverterenable" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port1/Port1_1.dd#//@provided.6"/>
  </hwResources>
  <hwResources name="PhaseU_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phuhigh" resourceGroupUri="devicepackage/0/17" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.14"/>
  </hwResources>
  <hwResources name="PhaseV_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phvhigh" resourceGroupUri="devicepackage/0/19" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.17"/>
  </hwResources>
  <hwResources name="PhaseW_High Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phwhigh" resourceGroupUri="devicepackage/0/27" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.20"/>
  </hwResources>
  <hwResources name="PhaseU_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phulow" resourceGroupUri="devicepackage/0/18" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.18"/>
  </hwResources>
  <hwResources name="PhaseV_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phvlow" resourceGroupUri="devicepackage/0/20" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.21"/>
  </hwResources>
  <hwResources name="PhaseW_Low Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_phwlow" resourceGroupUri="devicepackage/0/28" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.19"/>
  </hwResources>
  <hwResources name="Trap Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_trap" resourceGroupUri="devicepackage/0/*" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.13"/>
  </hwResources>
  <hwResources name="Inverter Enable Pin" URI="http://resources/4.0.30/app/PWM_SVM/0/__pin_hwres_port_pad_inverterenable" resourceGroupUri="devicepackage/0/*" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.1"/>
  </hwResources>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_global/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phu" systemDefined="true" sourceSignal="ccu8_global" targetSignal="ph_u_global_signal" targetVirtualSignal="//@virtualSignals.0" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_global/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phv" systemDefined="true" sourceSignal="ccu8_global" targetSignal="ph_v_global_signal" targetVirtualSignal="//@virtualSignals.1" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_global/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_phw" systemDefined="true" sourceSignal="ccu8_global" targetSignal="ph_w_global_signal" targetVirtualSignal="//@virtualSignals.2" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_global/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_globalsignal_currenttrig" systemDefined="true" sourceSignal="ccu8_global" targetSignal="adc_trigger_global_signal" targetVirtualSignal="//@virtualSignals.3" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_globalsignal" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.0"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phu/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_high" systemDefined="true" sourceSignal="ph_u_high" targetSignal="ph_u_high_pad" srcVirtualSignal="//@virtualSignals.44" targetVirtualSignal="//@virtualSignals.54"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phv/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_high" systemDefined="true" sourceSignal="ph_v_high" targetSignal="ph_v_high_pad" srcVirtualSignal="//@virtualSignals.45" targetVirtualSignal="//@virtualSignals.56"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_phw/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_high" systemDefined="true" sourceSignal="ph_w_high" targetSignal="ph_w_high_pad" srcVirtualSignal="//@virtualSignals.46" targetVirtualSignal="//@virtualSignals.58"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_op_phv/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_high" systemDefined="true" sourceSignal="ph_v_high" targetSignal="ph_v_high_pad" required="false" srcVirtualSignal="//@virtualSignals.47" targetVirtualSignal="//@virtualSignals.56"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out0_op_phw/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_high" systemDefined="true" sourceSignal="ph_w_high" targetSignal="ph_w_high_pad" required="false" srcVirtualSignal="//@virtualSignals.48" targetVirtualSignal="//@virtualSignals.58"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phu/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_low" systemDefined="true" sourceSignal="ph_u_low" targetSignal="ph_u_low_pad" srcVirtualSignal="//@virtualSignals.49" targetVirtualSignal="//@virtualSignals.55"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phv/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_low" systemDefined="true" sourceSignal="ph_v_low" targetSignal="ph_v_low_pad" srcVirtualSignal="//@virtualSignals.50" targetVirtualSignal="//@virtualSignals.57"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_phw/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_low" systemDefined="true" sourceSignal="ph_w_low" targetSignal="ph_w_low_pad" srcVirtualSignal="//@virtualSignals.51" targetVirtualSignal="//@virtualSignals.59"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_op_phv/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_low" systemDefined="true" sourceSignal="ph_v_low" targetSignal="ph_v_low_pad" required="false" srcVirtualSignal="//@virtualSignals.52" targetVirtualSignal="//@virtualSignals.57"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_out1_op_phw/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_low" systemDefined="true" sourceSignal="ph_w_low" targetSignal="ph_w_low_pad" required="false" srcVirtualSignal="//@virtualSignals.53" targetVirtualSignal="//@virtualSignals.59"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phu" systemDefined="true" sourceSignal="trap_pad" targetSignal="ph_u_trap" srcVirtualSignal="//@virtualSignals.60" targetVirtualSignal="//@virtualSignals.8"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phv" systemDefined="true" sourceSignal="trap_pad" targetSignal="ph_v_trap" srcVirtualSignal="//@virtualSignals.60" targetVirtualSignal="//@virtualSignals.9"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp2_unsync_phw" systemDefined="true" sourceSignal="trap_pad" targetSignal="ph_w_trap" srcVirtualSignal="//@virtualSignals.60" targetVirtualSignal="//@virtualSignals.10"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_gsc_enable/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phu" systemDefined="true" sourceSignal="ccu8_global_start" targetSignal="ph_u_external_start" targetVirtualSignal="//@virtualSignals.4" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_gsc_enable" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_gsc_enable/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phv" systemDefined="true" sourceSignal="ccu8_global_start" targetSignal="ph_v_external_start" targetVirtualSignal="//@virtualSignals.5" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_gsc_enable" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_gsc_enable/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_phw" systemDefined="true" sourceSignal="ccu8_global_start" targetSignal="ph_w_external_start" targetVirtualSignal="//@virtualSignals.6" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_gsc_enable" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_global_ccu8_gsc_enable/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_gp0_unsync_currenttrig" systemDefined="true" sourceSignal="ccu8_global_start" targetSignal="current_trigger_external_start" targetVirtualSignal="//@virtualSignals.7" proxySrcVirtualSignalUri="http://resources/4.1.14/app/GLOBAL_CCU8/0/vs_global_ccu8_gsc_enable" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
    <srcVirtualSignal href="../../GLOBAL_CCU8/v4_1_14/GLOBAL_CCU8_0.app#//@virtualSignals.2"/>
  </connections>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_high/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_high" systemDefined="true" sourceSignal="ph_u_high_pad" targetSignal="PhaseU_High Pin_signal" srcVirtualSignal="//@virtualSignals.54" targetVirtualSignal="//@virtualSignals.62"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_high/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_high" systemDefined="true" sourceSignal="PhaseU_High Pin_signal" targetSignal="ph_u_high_pad" srcVirtualSignal="//@virtualSignals.62" targetVirtualSignal="//@virtualSignals.54"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_high/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_high" systemDefined="true" sourceSignal="ph_v_high_pad" targetSignal="PhaseV_High Pin_signal" srcVirtualSignal="//@virtualSignals.56" targetVirtualSignal="//@virtualSignals.63"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_high/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_high" systemDefined="true" sourceSignal="PhaseV_High Pin_signal" targetSignal="ph_v_high_pad" srcVirtualSignal="//@virtualSignals.63" targetVirtualSignal="//@virtualSignals.56"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_high/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_high" systemDefined="true" sourceSignal="ph_w_high_pad" targetSignal="PhaseW_High Pin_signal" srcVirtualSignal="//@virtualSignals.58" targetVirtualSignal="//@virtualSignals.64"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_high/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_high" systemDefined="true" sourceSignal="PhaseW_High Pin_signal" targetSignal="ph_w_high_pad" srcVirtualSignal="//@virtualSignals.64" targetVirtualSignal="//@virtualSignals.58"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_low/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_low" systemDefined="true" sourceSignal="ph_u_low_pad" targetSignal="PhaseU_Low Pin_signal" srcVirtualSignal="//@virtualSignals.55" targetVirtualSignal="//@virtualSignals.65"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phu_low/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phu_low" systemDefined="true" sourceSignal="PhaseU_Low Pin_signal" targetSignal="ph_u_low_pad" srcVirtualSignal="//@virtualSignals.65" targetVirtualSignal="//@virtualSignals.55"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_low/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_low" systemDefined="true" sourceSignal="ph_v_low_pad" targetSignal="PhaseV_Low Pin_signal" srcVirtualSignal="//@virtualSignals.57" targetVirtualSignal="//@virtualSignals.66"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phv_low/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phv_low" systemDefined="true" sourceSignal="PhaseV_Low Pin_signal" targetSignal="ph_v_low_pad" srcVirtualSignal="//@virtualSignals.66" targetVirtualSignal="//@virtualSignals.57"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_low/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_low" systemDefined="true" sourceSignal="ph_w_low_pad" targetSignal="PhaseW_Low Pin_signal" srcVirtualSignal="//@virtualSignals.59" targetVirtualSignal="//@virtualSignals.67"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_phw_low/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_phw_low" systemDefined="true" sourceSignal="PhaseW_Low Pin_signal" targetSignal="ph_w_low_pad" srcVirtualSignal="//@virtualSignals.67" targetVirtualSignal="//@virtualSignals.59"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_trap" systemDefined="true" sourceSignal="trap_pad" targetSignal="Trap Pin_signal" srcVirtualSignal="//@virtualSignals.60" targetVirtualSignal="//@virtualSignals.68"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_trap/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_trap" systemDefined="true" sourceSignal="Trap Pin_signal" targetSignal="trap_pad" srcVirtualSignal="//@virtualSignals.68" targetVirtualSignal="//@virtualSignals.60"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_inverter/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_inverter" systemDefined="true" sourceSignal="inverter_enable_pad" targetSignal="Inverter Enable Pin_signal" srcVirtualSignal="//@virtualSignals.61" targetVirtualSignal="//@virtualSignals.69"/>
  <connections URI="http://resources/4.0.30/app/PWM_SVM/0/http://resources/4.0.30/app/PWM_SVM/0/__pin_vs_pwm_svm_pin_inverter/http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pin_inverter" systemDefined="true" sourceSignal="Inverter Enable Pin_signal" targetSignal="inverter_enable_pad" srcVirtualSignal="//@virtualSignals.69" targetVirtualSignal="//@virtualSignals.61"/>
</ResourceModel:App>

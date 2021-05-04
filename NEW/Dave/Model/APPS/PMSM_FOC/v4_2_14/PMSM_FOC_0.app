<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="PMSM_FOC" URI="http://resources/4.2.14/app/PMSM_FOC/0" description="Supports sensorless field oriented control (FOC) &#xA; for permanent magnet synchronous motor(PMSM)." mode="NOTSHARABLE" version="4.2.14" minDaveVersion="4.0.0" instanceLabel="PMSM_FOC_0" appLabel="" containingProxySignal="true">
  <properties singleton="true" provideInit="true"/>
  <virtualSignals name="i_phase_u" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1" hwSignal="gch" hwResource="//@hwResources.0"/>
  <virtualSignals name="i_phase_u_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_sel" hwSignal="select" hwResource="//@hwResources.0"/>
  <virtualSignals name="i_phase_u_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_ressel" hwSignal="res_sel" hwResource="//@hwResources.0"/>
  <virtualSignals name="v_dc_link" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2" hwSignal="gch" hwResource="//@hwResources.1"/>
  <virtualSignals name="v_dc_link_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_sel" hwSignal="select" hwResource="//@hwResources.1"/>
  <virtualSignals name="v_dc_link_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_ressel" hwSignal="res_sel" hwResource="//@hwResources.1"/>
  <virtualSignals name="analog_speed_input" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3" hwSignal="gch" hwResource="//@hwResources.2"/>
  <virtualSignals name="analog_speed_input_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_sel" hwSignal="select" hwResource="//@hwResources.2"/>
  <virtualSignals name="analog_speed_input_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_ressel" hwSignal="res_sel" hwResource="//@hwResources.2"/>
  <virtualSignals name="user_defined" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4" hwSignal="gch" hwResource="//@hwResources.3"/>
  <virtualSignals name="user_defined_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_sel" hwSignal="select" hwResource="//@hwResources.3"/>
  <virtualSignals name="user_defined_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_ressel" hwSignal="res_sel" hwResource="//@hwResources.3"/>
  <virtualSignals name="i_phase_v" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5" hwSignal="gch" hwResource="//@hwResources.4"/>
  <virtualSignals name="i_phase_v_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_sel" hwSignal="select" hwResource="//@hwResources.4"/>
  <virtualSignals name="i_phase_v_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_ressel" hwSignal="res_sel" hwResource="//@hwResources.4"/>
  <virtualSignals name="i_phase_w" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6" hwSignal="gch" hwResource="//@hwResources.5"/>
  <virtualSignals name="i_phase_w_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_sel" hwSignal="select" hwResource="//@hwResources.5"/>
  <virtualSignals name="i_phase_w_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_ressel" hwSignal="res_sel" hwResource="//@hwResources.5"/>
  <virtualSignals name="i_dc_link" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7" hwSignal="gch" hwResource="//@hwResources.6"/>
  <virtualSignals name="i_dc_link_channel_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_sel" hwSignal="select" hwResource="//@hwResources.6"/>
  <virtualSignals name="i_dc_link_result_select" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_ressel" hwSignal="res_sel" hwResource="//@hwResources.6"/>
  <virtualSignals name="i_phase_u_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_res" hwSignal="res_sel" hwResource="//@hwResources.14"/>
  <virtualSignals name="v_dc_link_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_res" hwSignal="res_sel" hwResource="//@hwResources.15"/>
  <virtualSignals name="analog_speed_input_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_res" hwSignal="res_sel" hwResource="//@hwResources.16"/>
  <virtualSignals name="user_defined_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_res" hwSignal="res_sel" hwResource="//@hwResources.17"/>
  <virtualSignals name="i_phase_v_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_res" hwSignal="res_sel" hwResource="//@hwResources.18"/>
  <virtualSignals name="i_phase_w_result" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_res" hwSignal="res_sel" hwResource="//@hwResources.19"/>
  <virtualSignals name="i_dc_link_result0" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_res" hwSignal="res_sel" hwResource="//@hwResources.20"/>
  <virtualSignals name="i_dc_link_result1" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch8_res" hwSignal="res_sel" hwResource="//@hwResources.21"/>
  <virtualSignals name="i_dc_link_result2" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch9_res" hwSignal="res_sel" hwResource="//@hwResources.22"/>
  <virtualSignals name="i_dc_link_result3" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch10_res" hwSignal="res_sel" hwResource="//@hwResources.23"/>
  <virtualSignals name="i_phase_u_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_io" hwSignal="pad" hwResource="//@hwResources.7"/>
  <virtualSignals name="v_dc_link_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_io" hwSignal="pad" hwResource="//@hwResources.8"/>
  <virtualSignals name="analog_speed_input_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_io" hwSignal="pad" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="user_defined_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_io" hwSignal="pad" hwResource="//@hwResources.10" required="false"/>
  <virtualSignals name="i_phase_v_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_io" hwSignal="pad" hwResource="//@hwResources.11"/>
  <virtualSignals name="i_phase_w_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_io" hwSignal="pad" hwResource="//@hwResources.12"/>
  <virtualSignals name="i_dc_link_pad" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_io" hwSignal="pad" hwResource="//@hwResources.13" required="false"/>
  <virtualSignals name="sr_fast_control_loop" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_fcl_nvicsignal_in" hwSignal="signal_in" hwResource="//@hwResources.24" visible="true"/>
  <virtualSignals name="sr_trap_one_match" URI="http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_trap_nvicsignal_in" hwSignal="signal_in" hwResource="//@hwResources.25" visible="true"/>
  <virtualSignals name="i_phase_u Pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch1_io" hwSignal="pin" hwResource="//@hwResources.26"/>
  <virtualSignals name="i_phase_v Pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch5_io" hwSignal="pin" hwResource="//@hwResources.27"/>
  <virtualSignals name="i_phase_w Pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch6_io" hwSignal="pin" hwResource="//@hwResources.28"/>
  <virtualSignals name="i_dc_link pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch7_io" hwSignal="pin" hwResource="//@hwResources.29"/>
  <virtualSignals name="v_dc_link Pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch2_io" hwSignal="pin" hwResource="//@hwResources.30"/>
  <virtualSignals name="analog_speed_input pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch3_io" hwSignal="pin" hwResource="//@hwResources.31"/>
  <virtualSignals name="user_defined pin_signal" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch4_io" hwSignal="pin" hwResource="//@hwResources.32"/>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_queue_a" requiredAppName="ADC_QUEUE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_queue_b" requiredAppName="ADC_QUEUE" required="false"/>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_queue_c" requiredAppName="ADC_QUEUE" required="false"/>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_queue_d" requiredAppName="ADC_QUEUE" required="false"/>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_pwm_svm" requiredAppName="PWM_SVM">
    <downwardMapList xsi:type="ResourceModel:App" href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#/"/>
  </requiredApps>
  <requiredApps URI="http://resources/4.2.14/app/PMSM_FOC/0/appres_cpu" requiredAppName="CPU_CTRL_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CPU_CTRL_XMC1/v4_0_12/CPU_CTRL_XMC1_0.app#/"/>
  </requiredApps>
  <hwResources name="i_phase_u" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan1" resourceGroupUri="peripheral/vadc/0/group/*/ch/*" mResGrpUri="peripheral/vadc/0/group/*/ch/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.77"/>
  </hwResources>
  <hwResources name="v_dc_link" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan2" resourceGroupUri="peripheral/vadc/0/group/*/ch/*" mResGrpUri="peripheral/vadc/0/group/*/ch/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.82"/>
  </hwResources>
  <hwResources name="analog_speed_input" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan3" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/group/*/ch/*"/>
  <hwResources name="user_defined" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan4" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/group/*/ch/*"/>
  <hwResources name="i_phase_v" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan5" resourceGroupUri="peripheral/vadc/0/group/*/ch/*" mResGrpUri="peripheral/vadc/0/group/*/ch/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.66"/>
  </hwResources>
  <hwResources name="i_phase_w" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan6" resourceGroupUri="peripheral/vadc/0/group/*/ch/*" mResGrpUri="peripheral/vadc/0/group/*/ch/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.72"/>
  </hwResources>
  <hwResources name="i_dc_link" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_adcchan7" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/group/*/ch/*"/>
  <hwResources name="i_phase_u Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_a_pin" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port2/Port2_2.dd#//@provided.29"/>
  </hwResources>
  <hwResources name="v_dc_link Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_b_pin" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port2/Port2_2.dd#//@provided.34"/>
  </hwResources>
  <hwResources name="analog_speed_input pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_c_pin" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="user_defined pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_d_pin" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="i_phase_v Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_e_pin" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port2/Port2_2.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="i_phase_w Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_f_pin" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/Port2/Port2_2.dd#//@provided.8"/>
  </hwResources>
  <hwResources name="i_dc_link pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_chan_g_pin" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="i_phase_u Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result1" resourceGroupUri="peripheral/vadc/0/group/*/result/*" mResGrpUri="peripheral/vadc/0/group/*/result/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.54"/>
  </hwResources>
  <hwResources name="v_dc_link Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result2" resourceGroupUri="peripheral/vadc/0/group/*/result/*" mResGrpUri="peripheral/vadc/0/group/*/result/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.62"/>
  </hwResources>
  <hwResources name="analog_speed_input Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result3" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/group/*/result/*"/>
  <hwResources name="user_defined Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result4" resourceGroupUri="" required="false" mResGrpUri="peripheral/vadc/0/group/*/result/*"/>
  <hwResources name="i_phase_v Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result5" resourceGroupUri="peripheral/vadc/0/group/*/result/*" mResGrpUri="peripheral/vadc/0/group/*/result/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.52"/>
  </hwResources>
  <hwResources name="i_phase_w Result" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result6" resourceGroupUri="peripheral/vadc/0/group/*/result/*" mResGrpUri="peripheral/vadc/0/group/*/result/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/VADC/VADC_0.dd#//@provided.49"/>
  </hwResources>
  <hwResources name="i_dc_link Result0" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result7" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv0/sv1/sv2">
    <solverVarMap index="4">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv1" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv2" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv0" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv1" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv2" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="i_dc_link Result1" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result8" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv3/sv4/sv5">
    <solverVarMap index="4">
      <value variableName="sv3" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv4" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv5" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv3" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv4" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv5" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="i_dc_link Result2" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result9" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv6/sv7/sv8">
    <solverVarMap index="4">
      <value variableName="sv6" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv7" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv8" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv6" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv7" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv8" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="i_dc_link Result3" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_result10" resourceGroupUri="" required="false" solverVariable="true" mResGrpUri="peripheral/vadc/0/group/sv9/sv10/sv11">
    <solverVarMap index="4">
      <value variableName="sv9" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv10" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv11" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="4">
      <value variableName="sv9" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv10" solverValue=""/>
    </solverVarMap>
    <solverVarMap index="6">
      <value variableName="sv11" solverValue=""/>
    </solverVarMap>
  </hwResources>
  <hwResources name="FCL nvic node" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_fcl_nvicnode" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CPU/CPU_0.dd#//@provided.6"/>
  </hwResources>
  <hwResources name="Trap/Phase V one match nvic node" URI="http://resources/4.2.14/app/PMSM_FOC/0/hwres_trap_nvicnode" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CPU/CPU_0.dd#//@provided.8"/>
  </hwResources>
  <hwResources name="i_phase_u Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_a_pin" resourceGroupUri="devicepackage/0/6" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.11"/>
  </hwResources>
  <hwResources name="i_phase_v Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_e_pin" resourceGroupUri="devicepackage/0/7" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.10"/>
  </hwResources>
  <hwResources name="i_phase_w Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_f_pin" resourceGroupUri="devicepackage/0/8" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.9"/>
  </hwResources>
  <hwResources name="i_dc_link pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_g_pin" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="v_dc_link Pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_b_pin" resourceGroupUri="devicepackage/0/1" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.22"/>
  </hwResources>
  <hwResources name="analog_speed_input pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_c_pin" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <hwResources name="user_defined pin" URI="http://resources/4.2.14/app/PMSM_FOC/0/__pin_hwres_chan_d_pin" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phu_periodmatch/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_fcl_nvicsignal_in" systemDefined="true" sourceSignal="event_ph_u_period/one_match" targetSignal="sr_fast_control_loop" targetVirtualSignal="//@virtualSignals.38" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_phu" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.12"/>
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.12"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phu_trap/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_trap_nvicsignal_in" systemDefined="true" sourceSignal="event_ph_u_trap" targetSignal="sr_trap_one_match" required="false" targetVirtualSignal="//@virtualSignals.39" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_e2as_phu" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.26"/>
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.26"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phv_periodmatch/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_trap_nvicsignal_in" systemDefined="true" sourceSignal="event_ph_v_period/one_match" targetSignal="sr_trap_one_match" targetVirtualSignal="//@virtualSignals.39" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_phv" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.13"/>
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.13"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1" systemDefined="true" sourceSignal="i_phase_u_pad" targetSignal="i_phase_u" srcVirtualSignal="//@virtualSignals.31" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5" systemDefined="true" sourceSignal="i_phase_v_pad" targetSignal="i_phase_v" srcVirtualSignal="//@virtualSignals.35" targetVirtualSignal="//@virtualSignals.12"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6" systemDefined="true" sourceSignal="i_phase_w_pad" targetSignal="i_phase_w" srcVirtualSignal="//@virtualSignals.36" targetVirtualSignal="//@virtualSignals.15"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7" systemDefined="true" sourceSignal="i_dc_link_pad" targetSignal="i_dc_link" required="false" srcVirtualSignal="//@virtualSignals.37" targetVirtualSignal="//@virtualSignals.18"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2" systemDefined="true" sourceSignal="v_dc_link_pad" targetSignal="v_dc_link" srcVirtualSignal="//@virtualSignals.32" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3" systemDefined="true" sourceSignal="analog_speed_input_pad" targetSignal="analog_speed_input" required="false" srcVirtualSignal="//@virtualSignals.33" targetVirtualSignal="//@virtualSignals.6"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4" systemDefined="true" sourceSignal="user_defined_pad" targetSignal="user_defined" required="false" srcVirtualSignal="//@virtualSignals.34" targetVirtualSignal="//@virtualSignals.9"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="i_phase_u_channel_select" targetVirtualSignal="//@virtualSignals.1" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="i_phase_v_channel_select" targetVirtualSignal="//@virtualSignals.13" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="i_phase_w_channel_select" targetVirtualSignal="//@virtualSignals.16" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="i_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.19" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="v_dc_link_channel_select" targetVirtualSignal="//@virtualSignals.4" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="analog_speed_input_channel_select" required="false" targetVirtualSignal="//@virtualSignals.7" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue12channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_sel" systemDefined="true" sourceSignal="queue_select" targetSignal="user_defined_channel_select" required="false" targetVirtualSignal="//@virtualSignals.10" proxySrcVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_queue2channel" containingProxySignal="true">
    <srcVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_sel" systemDefined="true" targetSignal="i_phase_u_channel_select" required="false" targetVirtualSignal="//@virtualSignals.1" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_sel" systemDefined="true" targetSignal="i_phase_v_channel_select" required="false" targetVirtualSignal="//@virtualSignals.13" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_sel" systemDefined="true" targetSignal="i_phase_w_channel_select" required="false" targetVirtualSignal="//@virtualSignals.16" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_sel" systemDefined="true" targetSignal="i_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.19" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_sel" systemDefined="true" targetSignal="v_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.4" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_sel" systemDefined="true" targetSignal="analog_speed_input_channel_select" required="false" targetVirtualSignal="//@virtualSignals.7" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue22channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_sel" systemDefined="true" targetSignal="user_defined_channel_select" required="false" targetVirtualSignal="//@virtualSignals.10" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_sel" systemDefined="true" targetSignal="i_phase_u_channel_select" required="false" targetVirtualSignal="//@virtualSignals.1" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_sel" systemDefined="true" targetSignal="i_phase_v_channel_select" required="false" targetVirtualSignal="//@virtualSignals.13" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_sel" systemDefined="true" targetSignal="i_phase_w_channel_select" required="false" targetVirtualSignal="//@virtualSignals.16" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_sel" systemDefined="true" targetSignal="i_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.19" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_sel" systemDefined="true" targetSignal="v_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.4" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_sel" systemDefined="true" targetSignal="analog_speed_input_channel_select" required="false" targetVirtualSignal="//@virtualSignals.7" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue32channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_sel" systemDefined="true" targetSignal="user_defined_channel_select" required="false" targetVirtualSignal="//@virtualSignals.10" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_sel" systemDefined="true" targetSignal="i_phase_u_channel_select" required="false" targetVirtualSignal="//@virtualSignals.1" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_sel" systemDefined="true" targetSignal="i_phase_v_channel_select" required="false" targetVirtualSignal="//@virtualSignals.13" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_sel" systemDefined="true" targetSignal="i_phase_w_channel_select" required="false" targetVirtualSignal="//@virtualSignals.16" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_sel" systemDefined="true" targetSignal="i_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.19" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_sel" systemDefined="true" targetSignal="v_dc_link_channel_select" required="false" targetVirtualSignal="//@virtualSignals.4" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_sel" systemDefined="true" targetSignal="analog_speed_input_channel_select" required="false" targetVirtualSignal="//@virtualSignals.7" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_queue42channel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_sel" systemDefined="true" targetSignal="user_defined_channel_select" required="false" targetVirtualSignal="//@virtualSignals.10" containingProxySignal="true"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_res" systemDefined="true" sourceSignal="i_phase_u_result_select" targetSignal="i_phase_u_result" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.21"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_res" systemDefined="true" sourceSignal="i_phase_v_result_select" targetSignal="i_phase_v_result" srcVirtualSignal="//@virtualSignals.14" targetVirtualSignal="//@virtualSignals.25"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_res" systemDefined="true" sourceSignal="i_phase_w_result_select" targetSignal="i_phase_w_result" srcVirtualSignal="//@virtualSignals.17" targetVirtualSignal="//@virtualSignals.26"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_res" systemDefined="true" sourceSignal="v_dc_link_result_select" targetSignal="v_dc_link_result" srcVirtualSignal="//@virtualSignals.5" targetVirtualSignal="//@virtualSignals.22"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_res" systemDefined="true" sourceSignal="analog_speed_input_result_select" targetSignal="analog_speed_input_result" required="false" srcVirtualSignal="//@virtualSignals.8" targetVirtualSignal="//@virtualSignals.23"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_res" systemDefined="true" sourceSignal="user_defined_result_select" targetSignal="user_defined_result" required="false" srcVirtualSignal="//@virtualSignals.11" targetVirtualSignal="//@virtualSignals.24"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_ressel/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_res" systemDefined="true" sourceSignal="i_dc_link_result_select" targetSignal="i_dc_link_result0" required="false" srcVirtualSignal="//@virtualSignals.20" targetVirtualSignal="//@virtualSignals.27"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phasecurrent_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_a" systemDefined="true" sourceSignal="adc_trigger_period/one_match" targetSignal="trigger_input" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_currenttrig" proxyTargetVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_greqtr0sel" containingProxySignal="true">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.15"/>
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.3"/>
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.15"/>
    <targetVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.3"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phasecurrent_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_b" systemDefined="true" sourceSignal="adc_trigger_period/one_match" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.15"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phasecurrent_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_c" systemDefined="true" sourceSignal="adc_trigger_period/one_match" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.15"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_phasecurrent_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_d" systemDefined="true" sourceSignal="adc_trigger_period/one_match" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_pmus_omds_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.15"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch1_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_a" systemDefined="true" sourceSignal="event_current_trigger_compare_match1_up/down" targetSignal="trigger_input" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_currenttrig" proxyTargetVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_greqtr0sel" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.21"/>
    <targetVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.3"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch2_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_a" systemDefined="true" sourceSignal="event_current_trigger_compare_match2_up/down" targetSignal="trigger_input" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_currenttrig" proxyTargetVirtualSignalUri="http://resources/4.0.22/app/ADC_QUEUE/0/vs_adc_queue_greqtr0sel" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.25"/>
    <targetVirtualSignal href="../../ADC_QUEUE/v4_0_22/ADC_QUEUE_0.app#//@virtualSignals.3"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch1_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_b" systemDefined="true" sourceSignal="event_current_trigger_compare_match1_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.21"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch2_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_b" systemDefined="true" sourceSignal="event_current_trigger_compare_match2_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.25"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch1_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_c" systemDefined="true" sourceSignal="event_current_trigger_compare_match1_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.21"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch2_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_c" systemDefined="true" sourceSignal="event_current_trigger_compare_match2_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.25"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch1_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_d" systemDefined="true" sourceSignal="event_current_trigger_compare_match1_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch1_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.21"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_svm_dclink_current_cmpch2_trigger/http://resources/4.2.14/app/PMSM_FOC/0/vs_adc_queue_trigsel_d" systemDefined="true" sourceSignal="event_current_trigger_compare_match2_up/down" required="false" proxySrcVirtualSignalUri="http://resources/4.0.30/app/PWM_SVM/0/vs_pwm_svm_cmds_cmus_cmpch2_currenttrig" containingProxySignal="true">
    <srcVirtualSignal href="../../PWM_SVM/v4_0_30/PWM_SVM_0.app#//@virtualSignals.25"/>
  </connections>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch1_io" systemDefined="true" sourceSignal="i_phase_u_pad" targetSignal="i_phase_u Pin_signal" srcVirtualSignal="//@virtualSignals.31" targetVirtualSignal="//@virtualSignals.40"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch1_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch1_io" systemDefined="true" sourceSignal="i_phase_u Pin_signal" targetSignal="i_phase_u_pad" srcVirtualSignal="//@virtualSignals.40" targetVirtualSignal="//@virtualSignals.31"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch5_io" systemDefined="true" sourceSignal="i_phase_v_pad" targetSignal="i_phase_v Pin_signal" srcVirtualSignal="//@virtualSignals.35" targetVirtualSignal="//@virtualSignals.41"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch5_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch5_io" systemDefined="true" sourceSignal="i_phase_v Pin_signal" targetSignal="i_phase_v_pad" srcVirtualSignal="//@virtualSignals.41" targetVirtualSignal="//@virtualSignals.35"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch6_io" systemDefined="true" sourceSignal="i_phase_w_pad" targetSignal="i_phase_w Pin_signal" srcVirtualSignal="//@virtualSignals.36" targetVirtualSignal="//@virtualSignals.42"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch6_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch6_io" systemDefined="true" sourceSignal="i_phase_w Pin_signal" targetSignal="i_phase_w_pad" srcVirtualSignal="//@virtualSignals.42" targetVirtualSignal="//@virtualSignals.36"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch7_io" systemDefined="true" sourceSignal="i_dc_link_pad" targetSignal="i_dc_link pin_signal" srcVirtualSignal="//@virtualSignals.37" targetVirtualSignal="//@virtualSignals.43"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch7_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch7_io" systemDefined="true" sourceSignal="i_dc_link pin_signal" targetSignal="i_dc_link_pad" srcVirtualSignal="//@virtualSignals.43" targetVirtualSignal="//@virtualSignals.37"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch2_io" systemDefined="true" sourceSignal="v_dc_link_pad" targetSignal="v_dc_link Pin_signal" srcVirtualSignal="//@virtualSignals.32" targetVirtualSignal="//@virtualSignals.44"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch2_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch2_io" systemDefined="true" sourceSignal="v_dc_link Pin_signal" targetSignal="v_dc_link_pad" srcVirtualSignal="//@virtualSignals.44" targetVirtualSignal="//@virtualSignals.32"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch3_io" systemDefined="true" sourceSignal="analog_speed_input_pad" targetSignal="analog_speed_input pin_signal" srcVirtualSignal="//@virtualSignals.33" targetVirtualSignal="//@virtualSignals.45"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch3_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch3_io" systemDefined="true" sourceSignal="analog_speed_input pin_signal" targetSignal="analog_speed_input_pad" srcVirtualSignal="//@virtualSignals.45" targetVirtualSignal="//@virtualSignals.33"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_io/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch4_io" systemDefined="true" sourceSignal="user_defined_pad" targetSignal="user_defined pin_signal" srcVirtualSignal="//@virtualSignals.34" targetVirtualSignal="//@virtualSignals.46"/>
  <connections URI="http://resources/4.2.14/app/PMSM_FOC/0/http://resources/4.2.14/app/PMSM_FOC/0/__pin_vs_pmsm_foc_adcch4_io/http://resources/4.2.14/app/PMSM_FOC/0/vs_pmsm_foc_adcch4_io" systemDefined="true" sourceSignal="user_defined pin_signal" targetSignal="user_defined_pad" srcVirtualSignal="//@virtualSignals.46" targetVirtualSignal="//@virtualSignals.34"/>
</ResourceModel:App>

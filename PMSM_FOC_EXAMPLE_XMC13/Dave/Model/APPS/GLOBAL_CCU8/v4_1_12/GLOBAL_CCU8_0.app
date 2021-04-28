<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="GLOBAL_CCU8" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0" description="Initializes CCU8 Global Register Set." version="4.1.12" minDaveVersion="4.0.0" instanceLabel="GLOBAL_CCU8_0" appLabel="">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@requiredApps.0"/>
  <properties provideInit="true" sharable="true"/>
  <virtualSignals name="ccu8_global" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/vs_global_ccu8_globalsignal" hwSignal="global_signal" hwResource="//@hwResources.0">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.0"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.1"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.2"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.3"/>
  </virtualSignals>
  <virtualSignals name="clock_ccu" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/vs_global_ccu8_clk" hwSignal="clk" hwResource="//@hwResources.0"/>
  <virtualSignals name="ccu8_global_start" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/vs_global_ccu8_gsc_enable" hwSignal="gsc_enable" hwResource="//@hwResources.1" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.17"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.18"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.19"/>
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../PWM_SVM/v4_0_18/PWM_SVM_0.app#//@connections.20"/>
  </virtualSignals>
  <requiredApps URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/appres_clock" requiredAppName="CLOCK_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CLOCK_XMC1/v4_0_18/CLOCK_XMC1_0.app#/"/>
  </requiredApps>
  <hwResources name="Global" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/hwres_peripheral_ccu8_global" resourceGroupUri="peripheral/ccu8/sv0/global" solverVariable="true" mResGrpUri="peripheral/ccu8/sv0/global">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/CCU80/CCU80_0.dd#//@provided.0"/>
    <solverVarMap index="2">
      <value variableName="sv0" solverValue="0"/>
    </solverVarMap>
    <solverVarMap index="2">
      <value variableName="sv0" solverValue="0"/>
    </solverVarMap>
  </hwResources>
  <hwResources name="CCU8 sync start" URI="http://resources/4.1.12/app/GLOBAL_CCU8/0/hwres_peripheral_scu_gcu_ccu8_global_enable" resourceGroupUri="peripheral/scu/*/gcu/ccu8_global_enable/sv0" solverVariable="true" mResGrpUri="peripheral/scu/*/gcu/ccu8_global_enable/sv0">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.2"/>
    <solverVarMap index="5">
      <value variableName="sv0" solverValue="0"/>
    </solverVarMap>
    <solverVarMap index="5">
      <value variableName="sv0" solverValue="0"/>
    </solverVarMap>
  </hwResources>
</ResourceModel:App>

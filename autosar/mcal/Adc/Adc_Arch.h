/**
 * @file    Adc_Arch.h
 * @brief   **Adc Architecture Driver**
 * @author  Naim Leon
 *
 * Adc driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Adc driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef ADC_ARCH_H__
#define ADC_ARCH_H__

#include "Adc_Types.h"

void Adc_Arch_Init( Adc_HwUnit *HwUnit, const Adc_ConfigType *ConfigPtr );
Std_ReturnType Adc_Arch_SetupResultBuffer( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
void Adc_Arch_DeInit( Adc_HwUnit *HwUnit );
void Adc_Arch_StartGroupConversion( Adc_HwUnit *HwUnit, Adc_GroupType Group );
void Adc_Arch_StopGroupConversion( Adc_HwUnit *HwUnit, Adc_GroupType Group );
Std_ReturnType Adc_Arch_ReadGroup( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
void Adc_Arch_EnableHardwareTrigger( Adc_HwUnit *HwUnit, Adc_GroupType Group );
void Adc_Arch_DisableHardwareTrigger( Adc_HwUnit *HwUnit, Adc_GroupType Group );
void Adc_Arch_EnableGroupNotification( Adc_HwUnit *HwUnit, Adc_GroupType Group );
void Adc_Arch_DisableGroupNotification( Adc_HwUnit *HwUnit, Adc_GroupType Group );
Adc_StatusType Adc_Arch_GetGroupStatus( Adc_HwUnit *HwUnit, Adc_GroupType Group );
Adc_StreamNumSampleType Adc_Arch_GetStreamLastPointer( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr );
void Adc_Arch_GetVersionInfo( Adc_HwUnit *HwUnit, Std_VersionInfoType *versioninfo );
Std_ReturnType Adc_Arch_SetPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_Arch_GetCurrentPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_Arch_GetTargetPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_Arch_PreparePowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result );

#endif
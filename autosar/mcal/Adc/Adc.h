/**
 * @file    Adc.h
 * @brief   **ADC Driver**
 * @author  Naim Leon
 *
 * The ADC module provides the functionality API and the configuration of the AUTOSAR Basic
 * Software module ADC Driver. The ADC driver is targeting Successive Approximation ADC Hardware.
 * Delta Sigma ADC conversion use cases are out of scope of this module.
 *
 */
#ifndef ADC_H__
#define ADC_H__

#include "Adc_Cfg.h"
#include "Adc_Types.h"

void Adc_Init( const Adc_ConfigType *ConfigPtr );
Std_ReturnType Adc_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
#if ADC_DEINIT_API == STD_ON
void Adc_DeInit( void );
#endif
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON
void Adc_StartGroupConversion( Adc_GroupType Group );
#endif
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON
void Adc_StopGroupConversion( Adc_GroupType Group );
#endif
#if ADC_READ_GROUP_API == STD_ON
Std_ReturnType Adc_ReadGroup( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
#endif
#if ADC_HW_TRIGGER_API == STD_ON
void Adc_EnableHardwareTrigger( Adc_GroupType Group );
#endif
#if ADC_HW_TRIGGER_API == STD_ON
void Adc_DisableHardwareTrigger( Adc_GroupType Group );
#endif
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON
void Adc_EnableGroupNotification( Adc_GroupType Group );
#endif
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON
void Adc_DisableGroupNotification( Adc_GroupType Group );
#endif
Adc_StatusType Adc_GetGroupStatus( Adc_GroupType Group );
Adc_StreamNumSampleType Adc_GetStreamLastPointer( Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr );
void Adc_GetVersionInfo( Std_VersionInfoType *versioninfo );
Std_ReturnType Adc_SetPowerState( Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_GetCurrentPowerState( Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_GetTargetPowerState( Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_PreparePowerState( Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result );

#endif /* ADC_H__ */
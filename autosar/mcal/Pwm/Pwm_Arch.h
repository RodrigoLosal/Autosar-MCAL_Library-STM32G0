/**
 * @file    Pwm_Arch.c
 * @brief   **Pwm Architecture Driver**
 * @author  Jazmin Melendrez
 *
 * Pwm driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Pwm driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef PWM_ARCH_H__
#define PWM_ARCH_H__

#include "Pwm_Types.h"

void Pwm_Arch_Init( Pwm_HwUnit *HwUnit, const Pwm_ConfigType *Config );
void Pwm_Arch_DeInit( Pwm_HwUnit *HwUnit );
void Pwm_Arch_SetDutyCycle( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, uint16 DutyCycle );
void Pwm_Arch_SetPeriodAndDuty( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle );
void Pwm_Arch_SetOutputToIdle( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber );
Pwm_OutputStateType Pwm_Arch_GetOutputState( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber );
void Pwm_Arch_DisableNotification( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber );
void Pwm_Arch_EnableNotification( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification );
Std_ReturnType Pwm_Arch_SetPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_Arch_GetCurrentPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_Arch_GetTargetPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_Arch_PreparePowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result );
void Pwm_Arch_GetVersionInfo( Pwm_HwUnit *HwUnit, Std_VersionInfoType *versioninfo );

#endif
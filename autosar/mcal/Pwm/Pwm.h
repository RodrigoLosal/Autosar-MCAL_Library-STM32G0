/**
 * @file    Pwm.h
 * @brief   **Pwm Driver header**
 * @author  Jazmin Melendrez
 *
 * The driver provides functions for initialization and control of the microcontroller internal
 * PWM stage (pulse width modulation). The PWM module generates pulses with variable pulse width.
 * It allows the selection of the duty cycle and the signal period time.
 */
#ifndef PWM_H__
#define PWM_H__

#include "Pwm_Cfg.h"

void Pwm_Init( const Pwm_ConfigType *ConfigPtr );
#if PWM_DE_INIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_DeInit( void );
#endif
#if PWM_SET_DUTY_CYCLE == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_SetDutyCycle( Pwm_ChannelType ChannelNumber, uint16 DutyCycle );
#endif
#if PWM_SET_PERIOD_AND_DUTY == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle );
#endif
#if PWM_SET_OUTPUT_TO_IDLE == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_SetOutputToIdle( Pwm_ChannelType ChannelNumber );
#endif
#if PWM_GET_OUTPUT_STATE == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Pwm_OutputStateType Pwm_GetOutputState( Pwm_ChannelType ChannelNumber );
#endif
#if PWM_NOTIFICATION_SUPPORTED == STD_OFF /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_DisableNotification( Pwm_ChannelType ChannelNumber );
#endif
#if PWM_NOTIFICATION_SUPPORTED == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_EnableNotification( Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification );
#endif
Std_ReturnType Pwm_SetPowerState( Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_GetCurrentPowerState( Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_GetTargetPowerState( Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result );
Std_ReturnType Pwm_PreparePowerState( Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result );
#if PWM_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Pwm_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#endif
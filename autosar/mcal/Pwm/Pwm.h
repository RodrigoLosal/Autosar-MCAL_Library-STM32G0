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

/**
 * @defgroup PWM_Ids Pwm Id number for module and each API
 *
 * @{ */
#define PWM_ID_INIT                     0x00u /*!< Pwm_Init() api service id */
#define PWM_ID_DE_INIT                  0x01u /*!< Pwm_DeInit() api service id */
#define PWM_ID_SET_DUTY_CYCLE           0x02u /*!< Pwm_SetDutyCycle() api service id */
#define PWM_ID_SET_PERIOD_AND_DUTY      0x03u /*!< Pwm_SetPeridoAndDuty() api service id */
#define PWM_ID_SET_OUTPUT_TO_IDLE       0x04u /*!< Pwm_SetOutputToIdle() api service id */
#define PWM_ID_GET_OUTPUT_STATE         0x05u /*!< Pwm_GetOutputState() api service id */
#define PWM_ID_DISABLE_NOTIFICATION     0x06u /*!< Pwm_DisableNotification() api service id */
#define PWM_ID_ENABLE_NOTIFICATION      0x07u /*!< Pwm_EnableNotification() api service id */
#define PWM_ID_GET_CURRENT_POWER_STATE  0x0au /*!< Pwm_GetCurrentPowerState() api service id */
#define PWM_ID_GET_TARGET_POWER_STATE   0x0bu /*!< Pwm_GetTargetPowerState() api service id */
#define PWM_ID_PREPARE_POWER_STATE      0x0cu /*!< Pwm_PreparePowerState() api service id */
#define PWM_ID_GET_VERSION_INFO         0x08u /*!< Pwm_GetVersionInfo() api service id */
/**
 * @} */

/**
 * @defgroup PWM_Error_Type Pwm Developtment Error Types
 *
 * @{ */
#define PWM_E_INIT_FAILED               0x10u /*!< API Pwm_Init service called with wrong parameter */
#define PWM_E_UNINIT                    0x11u /*!< API service used without module initialization */
#define PWM_E_PARAM_CHANNEL             0x12u /*!< API service used with an invalid channel Identifier */
#define PWM_E_PERIOD_UNCHANGEABLE       0x13u /*!< Usage of unauthorized PWM service on PWM channel configured a fixed period */
#define PWM_E_ALREADY_INITIALIZED       0x14u /*!< API Pwm_Init service called while the PWM driver has already been initialised */
#define PWM_E_PARAM_POINTER             0x15u /*!< API Pwm_GetVersionInfo is called with a NULL parameter. */
#define PWM_E_POWER_STATE_NOT_SUPPORTED 0x17u /*!< The requested power state is not supported by the PWM module. */
#define PWM_E_TRANSITION_NOT_POSSIBLE   0x18u /*!< The requested power state is not reachable from the current one. */
#define PWM_E_PERIPHERAL_NOT_PREPARED   0x19u /*!< PWM_E_PERIPHERAL_NOT_PREPARED. */
#define PWM_E_NOT_DISENGAGED            0x16u /*!< API Pwm_SetPowerState is called while the PWM module is still in use.*/
/**
 * @} */

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
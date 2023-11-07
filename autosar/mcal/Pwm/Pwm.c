/**
 * @file    Pwm.c
 * @brief   **Pwm Driver**
 * @author  Jazmín Melendrez
 *
 * The driver provides functions for initialization and control of the microcontroller internal
 * PWM stage (pulse width modulation). The PWM module generates pulses with variable pulse width.
 * It allows the selection of the duty cycle and the signal period time.
 */
#include "Std_Types.h"
#include "Pwm_Cfg.h"
#include "Pwm.h"

/**
 * @brief    **Pwm Initialization**
 *
 * Service for PWM initialization.
 *
 * @param    ConfigPtr Pointer to driver configuration
 *
 * @reqs    SWS_Pwm_00095
 */
void Pwm_Init( const Pwm_ConfigType *ConfigPtr )
{
}

/**
 * @brief    **Pwm Deinitialization**
 *
 * This function de-initializes the Pwm module.
 *
 * @reqs    SWS_Pwm_00096
 */
void Pwm_DeInit( void )
{
}

/**
 * @brief    **Pwm Set Duty Cycle**
 *
 * This function sets the duty cycle of the PWM channel.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param     DutyCycle Min=0x0000 Max=0x8000
 *
 * @reqs    SWS_Pwm_91000
 */
void Pwm_SetDutyCycle( Pwm_ChannelType ChannelNumber, uint16 DutyCycle )
{
}

/**
 * @brief    **Pwm Set Period and Duty**
 *
 * This function sets the period and the duty cycle of a PWM channel.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param    Period Period of the PWM signal
 * @param     DutyCycle Min=0x0000 Max=0x8000
 *
 * @reqs    SWS_Pwm_91001
 */
void Pwm_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle )
{
}

/**
 * @brief    **Pwm Set Output To Idle**
 *
 * This function sets the PWM output to the configured Idle state.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @reqs    SWS_Pwm_91002
 */
void Pwm_SetOutputToIdle( Pwm_ChannelType ChannelNumber )
{
}

/**
 * @brief    **Pwm Get Output State**
 *
 * Function to read the internal state of the PWM output signal.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @retval  PWM_HIGH: The PWM output state is high
 *          PWM_LOW: The PWM output state is low
 *
 * @reqs    SWS_Pwm_00100
 */
Pwm_OutputStateType Pwm_GetOutputState( Pwm_ChannelType ChannelNumber )
{
}

/**
 * @brief    **Pwm Disable Notification**
 *
 * Function to disable the PWM signal edge notification.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @reqs    SWS_Pwm_91003
 */
void Pwm_DisableNotification( Pwm_ChannelType ChannelNumber )
{
}

/**
 * @brief    **Pwm Enable Notification**
 *
 * Function to enable the PWM signal edge notification according to notification parameter.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param    Notification Type of notification PWM_RISING_EDGE or PWM_FALLING_EDGE or PWM_BOTH_EDGES.
 *
 * @reqs    SWS_Pwm_91004
 */
void Pwm_EnableNotification( Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification )
{
}

/**
 * @brief    **Pwm Set Power State**
 *
 * This function configures the Pwm module so that it enters the already prepared power state,
 * chosen between a predefined set of configured ones.
 *
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED:Power state change executed.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *                  PWM_SEQUENCE_ERROR: wrong API call sequence.
 *                  PWM_HW_FAILURE: the HW module has a failure which prevents it to enter the
 *                  required power state
 * @retval  E_OK: Power Mode changed
 *          E_NOT_OK: request rejected
 *
 * @reqs    SWS_Pwm_00166
 */
Std_ReturnType Pwm_SetPowerState( Pwm_PowerStateRequestResultType *Result )
{
}

/**
 * @brief    **Pwm Get Current Power State**
 *
 *This API returns the current power state of the PWM HW unit.
 *
 * @param    CurrentPowerState The current power mode of the PWM HW Unit is returned in this parameter
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED: Current power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Pwm_00177
 */
Std_ReturnType Pwm_GetCurrentPowerState( Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result )
{
}

/**
 * @brief    **Pwm Get Target Power State**
 *
 *This API returns the Target power state of the PWM HW unit.
 *
 * @param    TargetPowerState The Target power mode of the PWM HW Unit is returned in this parameter.
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED:Target power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Pwm_00180
 */
Std_ReturnType Pwm_GetTargetPowerState( Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result )
{
}

/**
 * @brief    **Pwm Prepare Power State**
 *
 *This API starts the needed process to allow the PWM HW module to enter the requested power state.
 *
 * @param    PowerState The Target power mode of the PWM HW Unit is returned in this parameter.
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED: PWM Module
 *                  power state preparation was started.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *                  PWM_SEQUENCE_ERROR: wrong API call sequence (Current Power State = Target Power State).
 *                  PWM_POWER_STATE_NOT_SUPP: PWM Module does not support the requested power state.
 *                  PWM_TRANS_NOT_POSSIBLE: PWM Module cannot transition directly from the current
 *                  power state to the requested power state or the HW peripheral is still busy
 * @retval  E_OK: Preparation process started
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Pwm_00183
 */
Std_ReturnType Pwm_PreparePowerState( Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result )
{
}

/**
 * @brief    **Pwm Get Version Info**
 *
 *This function returns the version information of this module.
 *
 * @param    versioninfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Pwm_00103
 */
void Pwm_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
}
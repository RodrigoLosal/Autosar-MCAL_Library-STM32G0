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
#include "Std_Types.h"
#include "Pwm_Cfg.h"
#include "Pwm_Arch.h"
#include "Bfx.h"

/**
 * @brief    **Pwm low level Initialization**
 *
 * This function initialize all internals variables and the used PWM structure of the
 * microcontroller according to the parameters specified in ConfigPtr and HwUnit.
 * Furthermore disable all notifications.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Config Pointer to driver configuration
 */
void Pwm_Arch_Init( Pwm_HwUnit *HwUnit, const Pwm_ConfigType *Config )
{
    (void)HwUnit;
    (void)Config;
}

/**
 * @brief    **Pwm low level Deinitialization**
 *
 * This function de-initializes the Pwm module.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 */
void Pwm_Arch_DeInit( Pwm_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief    **Pwm low level Set Duty Cycle**
 *
 * This function sets the duty cycle of the PWM channel.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param     DutyCycle Min=0x0000 Max=0x8000
 */
void Pwm_Arch_SetDutyCycle( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, uint16 DutyCycle )
{
    (void)HwUnit;
    (void)ChannelNumber;
    (void)DutyCycle;
}

/**
 * @brief    **Pwm low level Set Period and Duty**
 *
 * This function sets the period and the duty cycle of a PWM channel.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param    Period Period of the PWM signal
 * @param     DutyCycle Min=0x0000 Max=0x8000
 */
void Pwm_Arch_SetPeriodAndDuty( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle )
{
    (void)HwUnit;
    (void)ChannelNumber;
    (void)Period;
    (void)DutyCycle;
}

/**
 * @brief    **Pwm low level Set Output To Idle**
 *
 * This function sets the PWM output to the configured Idle state.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 */
void Pwm_Arch_SetOutputToIdle( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber )
{
    (void)HwUnit;
    (void)ChannelNumber;
}

/**
 * @brief    **Pwm low level Get Output State**
 *
 * Function to read the internal state of the PWM output signal.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @retval  PWM_HIGH: The PWM output state is high
 *          PWM_LOW: The PWM output state is low
 */
Pwm_OutputStateType Pwm_Arch_GetOutputState( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber )
{
    (void)HwUnit;
    (void)ChannelNumber;
    return E_NOT_OK;
}

/**
 * @brief    **Pwm low level Disable Notification**
 *
 * Function to disable the PWM signal edge notification.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 */
void Pwm_Arch_DisableNotification( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber )
{
    (void)HwUnit;
    (void)ChannelNumber;
}

/**
 * @brief    **Pwm low level Enable Notification**
 *
 * Function to enable the PWM signal edge notification according to notification parameter.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param    Notification Type of notification PWM_RISING_EDGE or PWM_FALLING_EDGE or PWM_BOTH_EDGES.
 */
void Pwm_Arch_EnableNotification( Pwm_HwUnit *HwUnit, Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification )
{
    (void)HwUnit;
    (void)ChannelNumber;
    (void)Notification;
}

/**
 * @brief    **Pwm low level Set Power State**
 *
 * This function configures the Pwm module so that it enters the already prepared power state,
 * chosen between a predefined set of configured ones.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED:Power state change executed.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *                  PWM_SEQUENCE_ERROR: wrong API call sequence.
 *                  PWM_HW_FAILURE: the HW module has a failure which prevents it to enter the
 *                  required power state
 *
 * @retval  E_OK: Power Mode changed
 *          E_NOT_OK: request rejected
 */
Std_ReturnType Pwm_Arch_SetPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)Result;
    return E_NOT_OK;
}

/**
 * @brief    **Pwm low level Get Current Power State**
 *
 * This function provides the current power state of a specified PWM hardware unit.
 *
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    CurrentPowerState The current power mode of the PWM HW Unit is returned in this parameter
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED: Current power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 */
Std_ReturnType Pwm_Arch_GetCurrentPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)CurrentPowerState;
    (void)Result;
    return E_NOT_OK;
}

/**
 * @brief    **Pwm low level Get Target Power State**
 *
 * The API returns the requested power state of the HW unit. This shall coincide with the
 * current power state if no transition is ongoing.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    TargetPowerState The Target power mode of the PWM HW Unit is returned in this parameter.
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED:Target power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 */
Std_ReturnType Pwm_Arch_GetTargetPowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)TargetPowerState;
    (void)Result;
    return E_NOT_OK;
}

/**
 * @brief    **Pwm low level Prepare Power State**
 *
 * This API starts the needed process to allow the PWM HW module to enter the requested power state.
 * Initiates all actions needed to enable a HW module to enter the target power state.
 *
 * @param    HwUnit Pointer to the hardware unit configuration.
 * @param    PowerState The Target power mode of the PWM HW Unit is returned in this parameter.
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED: PWM Module
 *                  power state preparation was started.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *                  PWM_SEQUENCE_ERROR: wrong API call sequence (Current Power State = Target Power State).
 *                  PWM_POWER_STATE_NOT_SUPP: PWM Module does not support the requested power state.
 *                  PWM_TRANS_NOT_POSSIBLE: PWM Module cannot transition directly from the current
 *                  power state to the requested power state or the HW peripheral is still busy
 *
 * @retval  E_OK: Preparation process started
 *          E_NOT_OK: Service is rejected
 */
Std_ReturnType Pwm_Arch_PreparePowerState( Pwm_HwUnit *HwUnit, Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)PowerState;
    (void)Result;
    return E_NOT_OK;
}

/**
 * @brief    **Pwm low level Get Version Info**
 *
 * This function returns the version information of this module.
 *
 * @param    versioninfo Pointer to where to store the version information of this module.
 */
void Pwm_Arch_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void)versioninfo;
}

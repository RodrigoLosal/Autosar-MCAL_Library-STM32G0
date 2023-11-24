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
#include "Pwm.h"
#include "Pwm_Arch.h"

/**
 * @defgroup These definitions set the minimum and maximum channel numbers for PWM operations.
 *
 * @{ */
#define PWM_CHANNEL_MIN 1 /*!< Minimum valid PWM channel number.  */
#define PWM_CHANNEL_MAX 2 /*!< Maximum valid PWM channel number.  */
/**
 * @} */

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Pwm_Cfg.h */
#if PWM_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
static Pwm_HwUnit HwUnit_Pwm =
{
.HwUnitState       = PWM_NOT_INIT, /*!< Pwm hardware unit state */
.Config            = NULL_PTR,
.Pwm_ChannelClass  = PWM_VARIABLE_PERIOD,
.Pwm_channelNumber = PWM_CHANNEL_MAX };

/* clang-format on */

/**
 * @brief    **Pwm Initialization**
 *
 * Service for PWM initialization.
 *
 * @param    ConfigPtr Pointer to driver configuration
 *
 * @reqs    SWS_Pwm_00095, SWS_Pwm_00018, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_Init( const Pwm_ConfigType *ConfigPtr )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_INIT )
    {
        /* If development error detection for the Pwm module is enabled:
        calling the routine Pwm_Init while the PWM driver and hardware
        are already initialized will cause a development error PWM_E_ALREADY_INITIALIZED.
        The desired functionality shall be left without any action. */
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_INIT, PWM_E_ALREADY_INITIALIZED );
    }
    else
    {
        Pwm_Arch_Init( &HwUnit_Pwm, ConfigPtr );
        HwUnit_Pwm.Config      = ConfigPtr;
        HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;
    }
}

/**
 * @brief    **Pwm Deinitialization**
 *
 * This function de-initializes the Pwm module.
 *
 * @reqs    SWS_Pwm_00096, SWS_Pwm_00117, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_DeInit( void )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_DE_INIT, PWM_E_UNINIT );
    }
    else
    {
        Pwm_Arch_DeInit( &HwUnit_Pwm );
    }
}

/**
 * @brief    **Pwm Set Duty Cycle**
 *
 * This function sets the duty cycle of the PWM channel.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param     DutyCycle Min=0x0000 Max=0x8000
 *
 * @reqs    SWS_Pwm_91000, SWS_Pwm_00117, SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_SetDutyCycle( Pwm_ChannelType ChannelNumber, uint16 DutyCycle )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_DUTY_CYCLE, PWM_E_UNINIT );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_DUTY_CYCLE, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        Pwm_Arch_SetDutyCycle( &HwUnit_Pwm, ChannelNumber, DutyCycle );
    }
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
 * @reqs    SWS_Pwm_91001, SWS_Pwm_00117, SWS_Pwm_00045, SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_PERIOD_AND_DUTY, PWM_E_UNINIT );
    }
    else if( HwUnit_Pwm.Pwm_ChannelClass != PWM_VARIABLE_PERIOD )
    {
        /*If development error detection for the Pwm module is
        enabled: The API Pwm_SetPeriodAndDuty() shall check if the given PWM
        channel is of the channel class type PWM_VARIABLE_PERIOD. If this is not the case
        the development error PWM_E_PERIOD_UNCHANGEABLE shall be called.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_PERIOD_AND_DUTY, PWM_E_PERIOD_UNCHANGEABLE );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_PERIOD_AND_DUTY, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        Pwm_Arch_SetPeriodAndDuty( &HwUnit_Pwm, ChannelNumber, Period, DutyCycle );
    }
}

/**
 * @brief    **Pwm Set Output To Idle**
 *
 * This function sets the PWM output to the configured Idle state.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @reqs    SWS_Pwm_91002, SWS_Pwm_00117 SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_SetOutputToIdle( Pwm_ChannelType ChannelNumber )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_OUTPUT_TO_IDLE, PWM_E_UNINIT );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_OUTPUT_TO_IDLE, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        Pwm_Arch_SetOutputToIdle( &HwUnit_Pwm, ChannelNumber );
    }
}

/**
 * @brief    **Pwm Get Output State**
 *
 * Function to read the internal state of the PWM output signal.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @retval  PWM_HIGH: The PWM output state is high
 *          PWM_LOW: The PWM output state is low
 *
 * @reqs    SWS_Pwm_00100, SWS_Pwm_00117 SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
Pwm_OutputStateType Pwm_GetOutputState( Pwm_ChannelType ChannelNumber )
{
    Pwm_OutputStateType outputState = PWM_HIGH;

    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_GET_OUTPUT_STATE, PWM_E_UNINIT );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_GET_OUTPUT_STATE, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        outputState = Pwm_Arch_GetOutputState( &HwUnit_Pwm, ChannelNumber );
    }
    return outputState;
}

/**
 * @brief    **Pwm Disable Notification**
 *
 * Function to disable the PWM signal edge notification.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 *
 * @reqs    SWS_Pwm_91003, SWS_Pwm_00117 SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_DisableNotification( Pwm_ChannelType ChannelNumber )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_DISABLE_NOTIFICATION, PWM_E_UNINIT );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_DISABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        Pwm_Arch_DisableNotification( &HwUnit_Pwm, ChannelNumber );
    }
}

/**
 * @brief    **Pwm Enable Notification**
 *
 * Function to enable the PWM signal edge notification according to notification parameter.
 *
 * @param    ChannelNumber Numeric identifier of the PWM
 * @param    Notification Type of notification PWM_RISING_EDGE or PWM_FALLING_EDGE or PWM_BOTH_EDGES.
 *
 * @reqs    SWS_Pwm_91004, SWS_Pwm_00117 SWS_Pwm_00047, SWS_Pwm_10051, SWS_Pwm_20051
 */
void Pwm_EnableNotification( Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification )
{
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_ENABLE_NOTIFICATION, PWM_E_UNINIT );
    }
    else if( ( ChannelNumber > HwUnit_Pwm.Pwm_channelNumber ) || ( ChannelNumber < PWM_CHANNEL_MIN ) )
    {
        /*If development error detection for the Pwm module is enabled:
        the PWM functions shall check the parameter ChannelNumber and raise
        development error PWM_E_PARAM_CHANNEL if the parameter ChannelNumber is
        invalid.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_ENABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL );
    }
    else
    {
        Pwm_Arch_EnableNotification( &HwUnit_Pwm, ChannelNumber, Notification );
    }
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
 *
 * @retval  E_OK: Power Mode changed
 *          E_NOT_OK: request rejected
 *
 * @reqs    SWS_Pwm_00166, SWS_Pwm_00117
 */
Std_ReturnType Pwm_SetPowerState( Pwm_PowerStateRequestResultType *Result )
{
    Std_ReturnType returnValue = E_NOT_OK;
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_SET_POWER_STATE, PWM_E_UNINIT );
    }
    else
    {
        returnValue = Pwm_Arch_SetPowerState( &HwUnit_Pwm, Result );
    }
    return returnValue;
}

/**
 * @brief    **Pwm Get Current Power State**
 *
 * This API returns the current power state of the PWM HW unit.
 *
 * @param    CurrentPowerState The current power mode of the PWM HW Unit is returned in this parameter
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED: Current power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Pwm_00177, SWS_Pwm_00117
 */
Std_ReturnType Pwm_GetCurrentPowerState( Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result )
{
    Std_ReturnType returnValue = E_NOT_OK;
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_GET_CURRENT_POWER_STATE, PWM_E_UNINIT );
    }
    else
    {
        returnValue = Pwm_Arch_GetCurrentPowerState( &HwUnit_Pwm, CurrentPowerState, Result );
    }
    return returnValue;
}

/**
 * @brief    **Pwm Get Target Power State**
 *
 * This API returns the Target power state of the PWM HW unit.
 *
 * @param    TargetPowerState The Target power mode of the PWM HW Unit is returned in this parameter.
 * @param    Result If the API returns E_OK: PWM_SERVICE_ACCEPTED:Target power mode was returned.
 *                  If the API returns E_NOT_OK: PWM_NOT_INIT: PWM Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Pwm_00180, SWS_Pwm_00117
 */
Std_ReturnType Pwm_GetTargetPowerState( Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result )
{
    Std_ReturnType returnValue = E_NOT_OK;
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_GET_TARGET_POWER_STATE, PWM_E_UNINIT );
    }
    else
    {
        returnValue = Pwm_Arch_GetTargetPowerState( &HwUnit_Pwm, TargetPowerState, Result );
    }
    return returnValue;
}

/**
 * @brief    **Pwm Prepare Power State**
 *
 * This API starts the needed process to allow the PWM HW module to enter the requested power state.
 *
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
 *
 * @reqs    SWS_Pwm_00183, SWS_Pwm_00117
 */
Std_ReturnType Pwm_PreparePowerState( Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result )
{
    Std_ReturnType returnValue = E_NOT_OK;
    if( HwUnit_Pwm.HwUnitState == PWM_STATE_UNINIT )
    {
        /*If development error detection for the Pwm module is enabled:
        if any function (except Pwm_Init) is called before Pwm_Init has been called, the
        called function shall raise development error PWM_E_UNINIT.*/
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_PREPARE_POWER_STATE, PWM_E_UNINIT );
    }
    else
    {
        returnValue = Pwm_Arch_PreparePowerState( &HwUnit_Pwm, PowerState, Result );
    }
    return returnValue;
}

/**
 * @brief    **Pwm Get Version Info**
 *
 * This function returns the version information of this module.
 *
 * @param    versioninfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Pwm_00103, SWS_Pwm_00117
 */
void Pwm_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /* If development error detection for the Pwm module is enabled:
        The function Pwm_GetVersionInfo shall raise the error PWM_E_PARAM_POINTER if the parameter
        versionInfo is a null pointer */
        Det_ReportError( PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ID_GET_VERSION_INFO, PWM_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = PWM_MODULE_ID;
        versioninfo->vendorID         = PWM_VENDOR_ID;
        versioninfo->sw_major_version = PWM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = PWM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = PWM_SW_PATCH_VERSION;
    }
}

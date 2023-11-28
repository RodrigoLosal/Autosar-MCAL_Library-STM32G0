/**
 * @file    Adc.c
 * @brief   **Adc Driver**
 * @author  Naim Leon
 *
 * The ADC module provides the functionality API and the configuration of the AUTOSAR Basic
 * Software module ADC Driver. The ADC driver is targeting Successive Approximation ADC Hardware.
 * Delta Sigma ADC conversion use cases are out of scope of this module.
 */
#include "Std_Types.h"
#include "Adc.h"
#include "Adc_Arch.h"
#include "Adc_Cfg.h"

#if ADC_DEV_ERROR_DETECT == FALSE
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief  Variable for the initial value of the Adc configuration array.
 */
/* clang-format off */
static Adc_HwUnit HwUnit_Adc =
{
    .Config = NULL_PTR,
};
/* clang-format on */

/**
 * @brief  Variable with the initial value of the Adc Det struct.
 */
static Adc_Det_Str Det_Adc =
{
    .Adc_InitState = FALSE,
    .Adc_ModuleID = ADC_MODULE_ID,
    .Adc_SetupResultBuffer = FALSE
};

/**
 * @brief    **ADC Initialization**
 *
 * This function Initializes the ADC hardware units and driver.
 *
 * @param    ConfigPtr Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 *
 * @reqs    SWS_Adc_00365
 */
void Adc_Init( const Adc_ConfigType *ConfigPtr )
{
    if( Det_Adc.Adc_InitState == TRUE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ID_INIT, ADC_E_ALREADY_INITIALIZED );
    }
    else
    {
        Adc_Arch_Init( &HwUnit_Adc, ConfigPtr );
        Det_Adc.Adc_InitState = TRUE;
        HwUnit_Adc.Config = ConfigPtr;
    }
}

/**
 * @brief    **ADC Result Buffer**
 *
 * This function initializes ADC driver with the group specific result buffer start address where
 * the conversion results will be stored. The application has to ensure that the application
 * buffer, where DataBufferPtr points to, can hold all the conversion results of the specified
 * group. The initialization with Adc_SetupResultBuffer is required after reset, before a group
 * conversion can be started.
 *
 * @param    Group Numeric ID of requested ADC channel group.
 * @param    DataBufferPtr Pointer to result data buffer.
 *
 * @retval  E_OK: result buffer pointer initialized correctly
 *          E_NOT_OK: operation failed or development error occured
 *
 * @reqs    SWS_Adc_91000
 */
Std_ReturnType Adc_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    Std_ReturnType RetValue;
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_PARAM_GROUP );
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_UNINIT );
    }
    else if ( DataBufferPtr == NULL_PTR )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_PARAM_POINTER );
    }
    else
    {
        RetValue = Adc_Arch_SetupResultBuffer( &HwUnit_Adc, Group, DataBufferPtr );
        Det_Adc.Adc_InitState = TRUE;
    }
    return RetValue;
}

/**
 * @brief    **ADC Deinitialization**
 *
 * This function Returns all ADC HW Units to a state comparable to their power on reset state.
 *
 * @reqs    SWS_Adc_00366 SWS_Adc_00228
 */
#if ADC_DE_INIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DeInit( void )
{
    if( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ID_DE_INIT, ADC_E_UNINIT );
    }
    else
    {
        Adc_Arch_DeInit( &HwUnit_Adc );
        Det_Adc.Adc_InitState = FALSE;
    }
}
#endif

/**
 * @brief    **ADC Start Group Conversion**
 *
 * Starts the conversion of all channels of the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_00367 SWS_Adc_00259
 */
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_StartGroupConversion( Adc_GroupType Group )
{
    Std_ReturnType RetValue = NULL_PTR;
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_PARAM_GROUP );
    }
    else if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_HW )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_WRONG_TRIGG_SRC );
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_UNINIT );
    }
    else if ( Det_Adc.Adc_SetupResultBuffer == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_BUFFER_UNINIT );
    }
    else
    {
        Adc_Arch_StartGroupConversion( &HwUnit_Adc, Group );
    }
}
#endif

/**
 * @brief    **ADC Stop Group Conversion**
 *
 * Stops the conversion of the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_00368 SWS_Adc_00260
 */
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_StopGroupConversion( Adc_GroupType Group )
{
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_PARAM_GROUP );
    }
    else if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_HW )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_WRONG_TRIGG_SRC );
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_UNINIT );
    }
    else
    {
        Adc_Arch_StopGroupConversion( &HwUnit_Adc, Group );
    }
}
#endif

/**
 * @brief    **ADC Read Group**
 *
 * Reads the group conversion result of the last completed conversion round of the requested group
 * and stores the channel values starting at the DataBufferPtr address. The group channel values
 * are stored in ascending channel number order (in contrast to the storage layout of the result
 * buffer if streaming access is configured).
 *
 * @param    Group Numeric ID of requested ADC channel group.
 * @param    DataBufferPtr ADC results of all channels of the selected group are stored in the data
 *                          buffer addressed with the pointer.
 *
 * @retval  E_OK: results are available and written to the data buffer
 *          E_NOT_OK: no results are available or development error occured
 *
 * @reqs    SWS_Adc_00369 SWS_Adc_00359
 */
#if ADC_READ_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
Std_ReturnType Adc_ReadGroup( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    Std_ReturnType RetValue = E_NOT_OK;
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_READ_GROUP, ADC_E_PARAM_GROUP );
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_READ_GROUP, ADC_E_UNINIT );
    }
    else
    {
        RetValue = Adc_Arch_ReadGroup( &HwUnit_Adc, Group, DataBufferPtr );
    }
    return RetValue;
}
#endif

/**
 * @brief    **ADC Enable Hardware Trigger**
 *
 * Enables the hardware trigger for the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91001 SWS_Adc_00265
 */
#if ADC_HW_TRIGGER_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_EnableHardwareTrigger( Adc_GroupType Group )
{
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_PARAM_GROUP );
    }
    else if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
    }
    else if ( AdcConfig.Adc_GroupConvMode == ADC_CONV_MODE_CONTINUOUS )
    {
        if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
        {
            Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
        }
        else
        {
            Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_CONV_MODE );
        }
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_UNINIT );
    }
    else if ( Det_Adc.Adc_SetupResultBuffer == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_BUFFER_UNINIT );
    }
    else
    {
        Adc_Arch_EnableHardwareTrigger( &HwUnit_Adc, Group );
    }
}
#endif

/**
 * @brief    **ADC Disable Hardware Trigger**
 *
 * Disables the hardware trigger for the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91002 SWS_Adc_00266
 */
#if ADC_HW_TRIGGER_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DisableHardwareTrigger( Adc_GroupType Group )
{
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_PARAM_GROUP );
    }
    else if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
    }
    else if ( AdcConfig.Adc_GroupConvMode == ADC_CONV_MODE_CONTINUOUS )
    {
        if ( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
        {
            Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
        }
        else
        {
            Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_CONV_MODE );
        }
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_UNINIT );
    }
    else
    {
        Adc_Arch_DisableHardwareTrigger( &HwUnit_Adc, Group );
    }
}
#endif

/**
 * @brief    **ADC Enable Group Notification**
 *
 * Enables the notification mechanism for the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91003 SWS_Adc_00100
 */
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_EnableGroupNotification( Adc_GroupType Group )
{
    if ( Group > 10 )   /*(Size tbd)*/
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_PARAM_GROUP );
    }
    else if ( GroupNotifFunctionPtr == NULL_PTR )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_NOTIF_CAPABILITY );
    }
    else if ( Det_Adc.Adc_InitState == FALSE )
    {
        Det_ReportError( ADC_MODULE_ID , ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_UNINIT );
    }
    else
    {
        Adc_Arch_EnableGroupNotification( HwUnit_Adc, Group );
    }
}
#endif

/**
 * @brief    **ADC Disable Group Notification**
 *
 * Disables the notification mechanism for the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91004 SWS_Adc_00101
 */
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DisableGroupNotification( Adc_GroupType Group )
{
    Adc_Arch_DisableGroupNotification( &HwUnit_Adc, Group );
}
#endif

/**
 * @brief    **ADC Get Group Status**
 *
 * Returns the conversion status of the requested ADC Channel group.
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @retval  Conversion status for the requested group.
 *
 * @reqs    SWS_Adc_00374
 */
Adc_StatusType Adc_GetGroupStatus( Adc_GroupType Group )
{
    return Adc_Arch_GetGroupStatus( &HwUnit_Adc, Group );
}

/**
 * @brief    **ADC Get Stream Last Pointer**
 *
 * Returns the number of valid samples per channel, stored in the result buffer. Reads a pointer,
 * pointing to a position in the group result buffer. With the pointer position, the results of all
 * group channels of the last completed conversion round can be accessed. With the pointer and the
 * return value, all valid group conversion results can be accessed (the user has to take the
 * layout of the result buffer into account).
 *
 * @param    Group Numeric ID of requested ADC Channel group.
 * @param    PtrToSamplePtr Pointer to result buffer pointer.
 *
 * @retval  Number of valid samples per channel.
 *
 * @reqs    SWS_Adc_00375
 */
Adc_StreamNumSampleType Adc_GetStreamLastPointer( Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr )
{
    return Adc_Arch_GetStreamLastPointer( &HwUnit_Adc, Group, PtrToSamplePtr );
}

/**
 * @brief    **ADC Get Version Info**
 *
 * Returns the version information of this module.
 *
 * @param    versioninfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Adc_00376
 */
#if ADC_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void)versioninfo;
}
#endif

/**
 * @brief    **ADC Set Power State**
 *
 * This API configures the Adc module so that it enters the already prepared power state, chosen
 * between a predefined set of configured ones.
 *
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: Power state change executed.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *                  ADC_SEQUENCE_ERROR: wrong API call sequence. ADC_HW_FAILURE: the HW module has
 *                  a failure which prevents it to enter the required power state.
 *
 * @retval  E_OK: Power Mode changed
 *          E_NOT_OK: request rejected
 *
 * @reqs    SWS_Adc_00475
 */
Std_ReturnType Adc_SetPowerState( Adc_PowerStateRequestResultType *Result )
{
    return Adc_Arch_SetPowerState( &HwUnit_Adc, Result );
}

/**
 * @brief    **ADC Get Current Power State**
 *
 * This API returns the current power state of the ADC HW unit.
 *
 * @param    CurrentPowerState The current power mode of the ADC HW Unit is returned in this
 *                              parameter.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: Current power mode was returned.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00476
 */
Std_ReturnType Adc_GetCurrentPowerState( Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result )
{
    return Adc_Arch_GetCurrentPowerState( &HwUnit_Adc, CurrentPowerState, Result );
}

/**
 * @brief    **ADC Get Target Power State**
 *
 * This API returns the Target power state of the ADC HW unit.
 *
 * @param    TargetPowerState The Target power mode of the ADC HW Unit is returned in this
 *                              parameter.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED:Target power mode was returned.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00477
 */
Std_ReturnType Adc_GetTargetPowerState( Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result )
{
    return Adc_Arch_GetTargetPowerState( &HwUnit_Adc, TargetPowerState, Result );
}

/**
 * @brief    **ADC Prepare Power State**
 *
 * This API starts the needed process to allow the ADC HW module to enter the requested power state
 *
 * @param    PowerState The target power state intended to be attained.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: ADC Module power state
 *                  preparation was started. If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module
 *                  not initialized. ADC_SEQUENCE_ERROR: wrong API call sequence (Current Power
 *                  State = Target Power State). ADC_POWER_STATE_NOT_SUPP: ADC Module does not
 *                  support the requested power state. ADC_TRANS_NOT_POSSIBLE: ADC Module cannot
 *                  transition directly from the current power state to the requested power state
 *                  or the HW peripheral is still busy.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00478
 */
Std_ReturnType Adc_PreparePowerState( Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result )
{
    return Adc_Arch_PreparePowerState( &HwUnit_Adc, PowerState, Result );
}
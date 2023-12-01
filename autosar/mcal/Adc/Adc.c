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
#include "Adc_Lcfg.h"

#if ADC_DEV_ERROR_DETECT == STD_OFF /* cppcheck-suppress misra-c2012-20.9 ; declared at Adc_Cfg.h */
/**
 * @param   ModuleId    Module ID number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Api id
 * @param   ErrorId     Error code
 */
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
    .Config                = NULL_PTR,
    .InitState             = FALSE,
    .ModuleID              = ADC_MODULE_ID,
    .SetupResltBuffer      = FALSE,
    .GroupNotifFunctionPtr = NULL_PTR,
    .PwrState              = 0,
    .PreparePwrStateFlag   = FALSE 
};
/* clang-format on */

/**
 * @brief    **ADC Initialization**
 *
 * This function Initializes the ADC hardware units and driver.
 *
 * @param    ConfigPtr Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 *
 * @reqs    SWS_Adc_00365 SWS_Adc_00107
 */
void Adc_Init( const Adc_ConfigType *ConfigPtr )
{
    if( *HwUnit_Adc.InitState == TRUE )
    {
        /*If called before the module has been initialized, the function Adc_DeInit shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ID_INIT, ADC_E_ALREADY_INITIALIZED );
    }
    else
    {
        Adc_Arch_Init( &HwUnit_Adc, ConfigPtr );
        *HwUnit_Adc.InitState = TRUE;
        HwUnit_Adc.Config     = ConfigPtr;
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
 * @reqs    SWS_Adc_91000 SWS_Adc_00423 SWS_Adc_00434 SWS_Adc_00457
 */
Std_ReturnType Adc_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    Std_ReturnType RetValue = E_NOT_OK;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*When called prior to initializing the driver, the function Adc_SetupResultBuffer shall
        raise development error ADC_E_UNINIT.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_UNINIT );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*If the channel group ID is non-existing, the function Adc_SetupResultBuffer shall raise
        development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_PARAM_GROUP );
    }
    else if( DataBufferPtr == NULL_PTR )
    {
        /*When called with a NULL_PTR as DataBufferPtr, the function Adc_SetupResultBuffer shall
        raise development error ADC_E_PARAM_POINTER.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_RESULT_BUFFER, ADC_E_PARAM_POINTER );
    }
    else
    {
        RetValue              = Adc_Arch_SetupResultBuffer( &HwUnit_Adc, Group, DataBufferPtr );
        *HwUnit_Adc.InitState = TRUE;
    }
    return RetValue;
}

/**
 * @brief    **ADC Deinitialization**
 *
 * This function Returns all ADC HW Units to a state comparable to their power on reset state.
 *
 * @reqs    SWS_Adc_00366 SWS_Adc_00228 SWS_Adc_00154
 */
#if ADC_DE_INIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DeInit( void )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*If called before the module has been initialized, the function Adc_DeInit shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ID_DE_INIT, ADC_E_UNINIT );
    }
    else
    {
        Adc_Arch_DeInit( &HwUnit_Adc );
        *HwUnit_Adc.InitState = FALSE;
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
 * @reqs    SWS_Adc_00367 SWS_Adc_00259 SWS_Adc_00125 SWS_Adc_00133 SWS_Adc_00294 SWS_Adc_00424
 */
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_StartGroupConversion( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*when called prior to initializing the driver, the function Adc_StartGroupConversion shall
        raise development error ADC_E_UNINIT.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_UNINIT );
    }
    else if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_HW )
    {
        /*When called on a group with trigger source configured as hardware, function 
        Adc_StartGroupConversion shall raise development error ADC_E_WRONG_TRIGG_SRC and return
        without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_WRONG_TRIGG_SRC );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*When called with a non-existing channel group ID, function Adc_StartGroupConversion shall
        raise development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_PARAM_GROUP );
    }
    else if( *HwUnit_Adc.SetupResltBuffer == FALSE )
    {
        /*When called prior to initializing the result buffer pointer with function
        Adc_SetupResultBuffer, the function Adc_StartGroupConversion shall raise development error
        ADC_E_BUFFER_UNINIT.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION, ADC_E_BUFFER_UNINIT );
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
 * @reqs    SWS_Adc_00368 SWS_Adc_00260 SWS_Adc_00126 SWS_Adc_00164 SWS_Adc_00295
 */
#if ADC_ENABLE_START_STOP_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_StopGroupConversion( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*If called prior to initializing the module, function Adc_StopGroupConversion shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_UNINIT );
    }
    else if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_HW )
    {
        /*If the group has a trigger source configured as hardware, function
        Adc_StopGroupConversion shall raise development error ADC_E_WRONG_TRIGG_SRC and return
        without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_WRONG_TRIGG_SRC );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*if the group ID is non-existing, the function Adc_StopGroupConversion shall raise
        development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION, ADC_E_PARAM_GROUP );
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
 * @reqs    SWS_Adc_00369 SWS_Adc_00359 SWS_Adc_00152 SWS_Adc_00296
 */
#if ADC_READ_GROUP_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
Std_ReturnType Adc_ReadGroup( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    Std_ReturnType RetValue = E_NOT_OK;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*when called prior to initializing the driver, the function Adc_ReadGroup shall raise
        development error ADC_E_UNINIT and return E_NOT_OK.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP, ADC_E_UNINIT );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*If the group ID is non-existing, the function Adc_ReadGroup shall raise development error
        ADC_E_PARAM_GROUP and return E_NOT_OK.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP, ADC_E_PARAM_GROUP );
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
 * @reqs    SWS_Adc_91001 SWS_Adc_00265 SWS_Adc_00128 SWS_Adc_00136 SWS_Adc_00281 SWS_Adc_00297
 *          SWS_Adc_00425
 */
#if ADC_HW_TRIGGER_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_EnableHardwareTrigger( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*If called prior to initializing the driver, the function Adc_EnableHardwareTrigger shall
        raise development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_UNINIT );
    }
    else if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
    {
        /*If the group is configured for software API trigger mode, the function
        Adc_EnableHardwareTrigger shall raise development error ADC_E_WRONG_TRIGG_SRC and return
        without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
    }
    else if( AdcConfig.Adc_GroupConvMode == ADC_CONV_MODE_CONTINUOUS )
    {
        if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
        {
            /*SW groups configured in continuous conversion mode shall raise development error
            ADC_E_WRONG_TRIGG_SRC instead of the next condition.*/
            Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
        }
        else
        {
            /*If a HW group is erroneously configured for continuous conversion mode, the function
            Adc_EnableHardwareTrigger shall raise development error ADC_E_WRONG_CONV_MODE and
            return without any action.*/
            Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_CONV_MODE );
        }
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*if the channel group ID is invalid, the function Adc_EnableHardwareTrigger shall raise
        development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_PARAM_GROUP );
    }
    else if( *HwUnit_Adc.SetupResltBuffer == FALSE )
    {
        /*when called prior to initializing the result buffer pointer with function
        Adc_SetupResultBuffer, the function Adc_EnableHardwareTrigger shall raise development error
        ADC_E_BUFFER_UNINIT.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER, ADC_E_BUFFER_UNINIT );
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
 * @reqs    SWS_Adc_91002 SWS_Adc_00266 SWS_Adc_00129 SWS_Adc_00137 SWS_Adc_00282 SWS_Adc_00298
 */
#if ADC_HW_TRIGGER_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DisableHardwareTrigger( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*if called prior to initializing the ADC module, Adc_DisableHardwareTrigger shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_UNINIT );
    }
    else if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
    {
        /*if the group is configured for software API trigger mode, the function
        Adc_DisableHardwareTrigger shall raise development error ADC_E_WRONG_TRIGG_SRC and return
        without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
    }
    else if( AdcConfig.Adc_GroupConvMode == ADC_CONV_MODE_CONTINUOUS )
    {
        if( AdcConfig.Adc_TriggerSource == ADC_TRIGG_SRC_SW )
        {
            /*SW groups configured in continuous conversion mode shall raise development error
            ADC_E_WRONG_TRIGG_SRC instead of the next condition*/
            Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC );
        }
        else
        {
            /*if a HW group is erroneously configured for continuous conversion mode, the function
            Adc_DisableHardwareTrigger shall raise development error ADC_E_WRONG_CONV_MODE and
            return without any action.*/
            Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_WRONG_CONV_MODE );
        }
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*If the channel group ID is non-existing, the function Adc_DisableHardwareTrigger shall
        raise development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER, ADC_E_PARAM_GROUP );
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
 * @reqs    SWS_Adc_91003 SWS_Adc_00100 SWS_Adc_00130 SWS_Adc_00165 SWS_Adc_00299
 */
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_EnableGroupNotification( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*if called prior to initializing the ADC module, Adc_EnableGroupNotification shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_UNINIT );
    }
    else if( GroupNotifFunctionPtr == NULL_PTR )
    {
        /*if the  is NULL, the function Adc_EnableGroupNotification shall raise development error
        ADC_E_NOTIF_CAPABILITY and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_NOTIF_CAPABILITY );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*if the channel group ID is non-existing, the function Adc_EnableGroupNotification shall
        raise development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION, ADC_E_PARAM_GROUP );
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
 * @reqs    SWS_Adc_91004 SWS_Adc_00101 SWS_Adc_00131 SWS_Adc_00166 SWS_Adc_00300
 */
#if ADC_GRP_NOTIF_CAPABILITY == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_DisableGroupNotification( Adc_GroupType Group )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*if called prior to initializing the ADC module, Adc_DisableGroupNotification shall raise
        development error ADC_E_UNINIT and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION, ADC_E_UNINIT );
    }
    else if( GroupNotifFunctionPtr == NULL_PTR )
    {
        /*if the group notification function pointer is NULL, the function
        Adc_DisableGroupNotification shall raise development error ADC_E_NOTIF_CAPABILITY and
        return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION, ADC_E_NOTIF_CAPABILITY );
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*If the channel group ID is non-existing, the function Adc_DisableGroupNotification shall
        raise development error ADC_E_PARAM_GROUP and return without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION, ADC_E_PARAM_GROUP );
    }
    else
    {
        Adc_Arch_DisableGroupNotification( &HwUnit_Adc, Group );
    }
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
 * @reqs    SWS_Adc_00374 SWS_Adc_00301
 */
Adc_StatusType Adc_GetGroupStatus( Adc_GroupType Group )
{
    Adc_StatusType RetValue = ADC_IDLE;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*If called prior to initializing the ADC module, Adc_GetGroupStatus shall raise
        development error ADC_E_UNINIT and return ADC_IDLE without any action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_GROUP_STATUS, ADC_E_UNINIT );
    }
    else
    {
        RetValue = Adc_Arch_GetGroupStatus( &HwUnit_Adc, Group );
    }
    return RetValue;
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
 * @reqs    SWS_Adc_00375 SWS_Adc_00218 SWS_Adc_00302
 */
Adc_StreamNumSampleType Adc_GetStreamLastPointer( Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr )
{
    Adc_StreamNumSampleType RetValue = 0;

    if( HwUnit_Adc.InitState == FALSE )
    {
        /*if called prior to initializing the driver, the function Adc_GetStreamLastPointer shall
        raise development error ADC_E_UNINIT, set the pointer, passed as parameter
        (PtrToSamplePtr), to NULL and return 0 without any further action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER, ADC_E_UNINIT );
        *PtrToSamplePtr = NULL_PTR;
    }
    else if( Group > GROUP_10 ) /*(Size tbd)*/
    {
        /*If the group ID is non-existent, the function Adc_GetStreamLastPointer shall raise
        development error ADC_E_PARAM_GROUP, set the pointer, passed as parameter (PtrToSamplePtr),
        to NULL and return 0 without any further action.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER, ADC_E_PARAM_GROUP );
        *PtrToSamplePtr = NULL_PTR;
    }
    else
    {
        RetValue = Adc_Arch_GetStreamLastPointer( &HwUnit_Adc, Group, PtrToSamplePtr );
    }
    return RetValue;
}

/**
 * @brief    **ADC Get Version Info**
 *
 * Returns the version information of this module.
 *
 * @param    versioninfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Adc_00376 SWS_Adc_00458
 */
#if ADC_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is defined on the Adc_Cfg.h file */
void Adc_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /*The function Adc_GetVersionInfo shall check the parameter versioninfo for not being NULL
        and shall raise the development error ADC_E_PARAM_POINTER if the check fails.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_VERSION_INFO, ADC_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = ADC_MODULE_ID;
        versioninfo->vendorID         = ADC_VENDOR_ID;
        versioninfo->sw_major_version = ADC_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = ADC_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = ADC_SW_PATCH_VERSION;
    }
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
 * @reqs    SWS_Adc_00475 SWS_Adc_00486 SWS_Adc_00488 SWS_Adc_00490
 */
Std_ReturnType Adc_SetPowerState( Adc_PowerStateRequestResultType *Result )
{
    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*The API shall report the DET error ADC_E_UNINIT in case this API is called before having
        initialized the HW unit.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SET_POWER_STATE, ADC_E_UNINIT );
    }
    else if( *HwUnit_Adc.PwrState > GROUP_10 ) /*(Size tbd)*/
    {
        /*The API shall report the DET error ADC_E_POWER_STATE_NOT_SUPPORTED in case this API is
        called with an unsupported power state or the peripheral does not support low power states
        at all.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SET_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED );
    }
    else if( *HwUnit_Adc.PreparePwrStateFlag == FALSE ) /*(Size tbd)*/
    {
        /*The API shall report the DET error ADC_E_PERIPHERAL_NOT_PREPARED in case the HW unit has
        not been previously prepared for the target power state by use of the API
        Adc_PreparePowerState().*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SET_POWER_STATE, ADC_E_PERIPHERAL_NOT_PREPARED );
    }
    else
    {
        return Adc_Arch_SetPowerState( &HwUnit_Adc, Result );
    }
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
 * @reqs    SWS_Adc_00476 SWS_Adc_00491
 */
Std_ReturnType Adc_GetCurrentPowerState( Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result )
{
    Std_ReturnType RetValue = E_NOT_OK;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*The API shall report the DET error ADC_E_UNINIT in case this API is called before having
        initialized the HW unit.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_CURRENT_POWER_STATE, ADC_E_UNINIT );
    }
    else
    {
        RetValue = Adc_Arch_GetCurrentPowerState( &HwUnit_Adc, CurrentPowerState, Result );
    }
    return RetValue;
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
 * @reqs    SWS_Adc_00477 SWS_Adc_00493
 */
Std_ReturnType Adc_GetTargetPowerState( Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result )
{
    Std_ReturnType RetValue = E_NOT_OK;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*The API shall report the DET error ADC_E_UNINIT in case this API is called before having
        initialized the HW unit.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_TARGET_POWER_STATE, ADC_E_UNINIT );
    }
    else
    {
        RetValue = Adc_Arch_GetTargetPowerState( &HwUnit_Adc, TargetPowerState, Result );
    }
    return RetValue;
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
 * @reqs    SWS_Adc_00478 SWS_Adc_00496 SWS_Adc_00497
 */
Std_ReturnType Adc_PreparePowerState( Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result )
{
    Std_ReturnType RetValue = E_NOT_OK;

    if( *HwUnit_Adc.InitState == FALSE )
    {
        /*The API shall report the DET error ADC_E_UNINIT in case this API is called before having
        initialized the HW unit.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_PREPARE_POWER_STATE, ADC_E_UNINIT );
    }
    else if( *HwUnit_Adc.PwrState > PWR_STATE_10 ) /*(Size tbd)*/
    {
        /*The API shall report the DET error ADC_E_POWER_STATE_NOT_SUPPORTED in case this API is
        called with an unsupported power state is requested or the peripheral does not support low
        power states at all.*/
        Det_ReportError( ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_PREPARE_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED );
    }
    else
    {
        RetValue = Adc_Arch_PreparePowerState( &HwUnit_Adc, PowerState, Result );
    }
    return RetValue;
}
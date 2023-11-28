/**
 * @file    Gpt.c
 * @brief   **GPT driver configuration**
 * @author  Rodrigo Lopez
 *
 * The GPT driver provides services for starting and stopping timer channels (logical timer
 * instances assigned to a timer hardware), individual for each channel.
 *
 * The tick duration of a timer channel depends on channel specific settings (part of GPT driver)
 * as well as on system clock and settings of the clock tree controlled by the MCU module.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"
#include "Gpt_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Mcu_Cfg.h */
#if MCU_DEV_ERROR_DETECT == STD_OFF
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
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
/* cppcheck-suppress misra-c2012-8.4 ; qualifier is declared at Mcu.h */
GPT_STATIC Gpt_HwUnit HwUnit_Gpt =
{
    .HwUnitState = GPT_STATE_UNINIT,
    .Config      = NULL_PTR
};
/* clang-format on */

/**
 * @brief  Variable for the initial value of the GPT configuration array.
 */
/* cppcheck-suppress misra-config ; The GPT_NUMBER_OF_CHANNELS define is already available through Gpt.h */
static const Gpt_ConfigType *LocalGptConfigPtr = NULL_PTR;

/**
 * @brief Initialize the GPT registers to the configuration stored on ConfigPtr.
 *
 * The function Gpt_Init shall initialize the hardware timer module according to a configuration
 * set referenced by ConfigPtr. The functions disables all interrupt notifications.
 *
 * Resources that are not configured in the configuration file are not touched.
 *
 * @param ConfigPtr       Pointer to ConfigPtr struct array.
 *
 * @reqs   SWS_Gpt_00280, SWS_Gpt_00006, SWS_Gpt_00107, SWS_Gpt_00068, SWS_Gpt_00258, SWS_Gpt_00307
 */
void Gpt_Init( const Gpt_ConfigType *ConfigPtr )
{
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_UNINIT )
    {
        /* If development error detection for the GPT module is enabled:
        The function Gpt_Init shall raise the error GPT_E_ALREADY_INITIALIZED if the parameter
        versionInfo is a null pointer */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_INIT, GPT_E_ALREADY_INITIALIZED );
    }
    else
    {
        for( uint32 ChannelsToInit = 0; ChannelsToInit < ConfigPtr->NumberOfChannels; ChannelsToInit++ )
        {
            Gpt_Arch_Init( ConfigPtr, ChannelsToInit );
        }
        LocalGptConfigPtr      = ConfigPtr;
        HwUnit_Gpt.HwUnitState = GPT_STATE_INIT;
    }
}

/**
 * @brief Deinitializes the GPT driver.
 *
 * The function deinitializes the hardware used by the GPT driver (depending on configuration) to
 * the power on reset state. Values of registers which are not writeable are excluded.
 *
 * @reqs   SWS_Gpt_00281, SWS_Gpt_00008, SWS_Gpt_00105, SWS_Gpt_00162, SWS_Gpt_00194, SWS_Gpt_00220
 */
#if GPT_DEINIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DeInit( void )
{
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for the GPT module: If the driver is not
        initialized, the function Gpt_DeInit shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_DEINIT, GPT_E_UNINIT );
    }
    else
    {
        for( uint32 ChannelsToDeinit = 0; ChannelsToDeinit < LocalGptConfigPtr->NumberOfChannels; ChannelsToDeinit++ )
        {
            Gpt_Arch_DeInit( LocalGptConfigPtr, ChannelsToDeinit );
        }
        HwUnit_Gpt.HwUnitState = GPT_STATE_UNINIT;
    }
}
#endif

/**
 * @brief Returns the time already elapsed.
 *
 * The function returns the time already elapsed. When the channel is in mode “one-shot mode”,
 * this is the value relative to the point in time, the channel has been started.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the current number of ticks already elapsed.
 *
 * @reqs   SWS_Gpt_00282, SWS_Gpt_00010, SWS_Gpt_00361, SWS_Gpt_00195, SWS_Gpt_00222, SWS_Gpt_00210
 */
#if GPT_TIME_ELAPSED_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_ValueType Result = 0;

    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not
        initialized, the function Gpt_GetTimeElapsed shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_GET_TIME_ELAPSED, GPT_E_UNINIT );
    }
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the parameter Channel is
        invalid (not within the range specified by configuration), the function Gpt_GetTimeElapsed
        shall raise the error GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_GET_TIME_ELAPSED, GPT_E_PARAM_CHANNEL );
    }
    else
    {
        Result = Gpt_Arch_GetTimeElapsed( LocalGptConfigPtr, Channel );
    }
    return Result;
}
#endif

/**
 * @brief Returns the time remaining until the target time is reached.
 *
 * The function returns the timer value remaining until the target time will be reached next time.
 * he remaining time is the "target time" minus the time already elapsed.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the remaining number of ticks before the timer overflows.
 *
 * @reqs   SWS_Gpt_00283, SWS_Gpt_00083, SWS_Gpt_00196, SWS_Gpt_00223, SWS_Gpt_00211
 */
#if GPT_TIME_REMAINING_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_ValueType Result = 0;

    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
         the function Gpt_GetTimeRemaining shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_GET_TIME_REMAINING, GPT_E_UNINIT );
    }
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the parameter Channel is
        invalid (not within the range specified by configuration), the function Gpt_GetTimeRemaining
        shall raise the error GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_GET_TIME_REMAINING, GPT_E_PARAM_CHANNEL );
    }
    else
    {
        Result = Gpt_Arch_GetTimeRemaining( LocalGptConfigPtr, Channel );
    }
    return Result;
}
#endif

/**
 * @brief Starts a timer channel.
 *
 * The function starts the selected timer channel with a defined target time. If configured and
 * enabled, an interrupt notification or a wakeup interrupt occurs, when the target time is reached.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 * @param Value         Target time in number of ticks.
 *
 * @reqs   SWS_Gpt_00284, SWS_Gpt_00274, SWS_Gpt_00275, SWS_Gpt_00212, SWS_Gpt_00218, SWS_Gpt_00224
 */
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the parameter Channel is
        invalid (not within the range specified by configuration), the function Gpt_StartTimer shall
        raise the error GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_START_TIMER, GPT_E_PARAM_CHANNEL );
    }
    if( ( Value == 0 ) || ( Value < GPT_ARR_MAX ) )
    {
        /* If development error detection is enabled for GPT module: The function Gpt_StartTimer
        shall raise the error GPT_E_PARAM_VALUE if the parameter Value is "0" or not within the
        allowed range (exceeding the maximum timer resolution). */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_START_TIMER, GPT_E_PARAM_VALUE );
    }
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
        the function Gpt_StartTimer shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_START_TIMER, GPT_E_UNINIT );
    }
    else
    {
        Gpt_Arch_StartTimer( LocalGptConfigPtr, Channel, Value );
    }
}

/**
 * @brief Stops a timer channel.
 *
 * The function stops the selected timer channel.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00285, SWS_Gpt_00013, SWS_Gpt_00099, SWS_Gpt_00213, SWS_Gpt_00225
 */
void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the parameter Channel is
        invalid (not within the range specified by configuration), the function Gpt_StopTimer shall
        raise the error GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_STOP_TIMER, GPT_E_PARAM_CHANNEL );
    }
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
        the function Gpt_StopTimer shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_STOP_TIMER, GPT_E_UNINIT );
    }
    else
    {
        Gpt_Arch_StopTimer( LocalGptConfigPtr, Channel );
    }
}

/**
 * @brief Gets the current version.
 *
 * The function gives the versioninfo struct the values of the current version. to eneable this
 * function change the value of GPT_VERSION_INFO_API to STD_ON on the Gpt_Cfg file.
 *
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 *
 * @reqs   SWS_Gpt_00279, SWS_Gpt_00338
 */
#if GPT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /* If development error detection for the GPT module is enabled:
        The function Gpt_GetVersionInfo shall raise the error GPT_E_PARAM_POINTER if the parameter
        versionInfo is a null pointer */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_GET_VERSION_INFO, GPT_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = 0;
        versioninfo->sw_major_version = 0;
        versioninfo->sw_minor_version = 0;
        versioninfo->sw_patch_version = 0;
        versioninfo->vendorID         = 0;
    }
}
#endif

/**
 * @brief Enables the interrupt notification for a channel.
 *
 * The function enables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00286, SWS_Gpt_00199, SWS_Gpt_00226, SWS_Gpt_00214, SWS_Gpt_00377
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
        the function Gpt_EnableNotification shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_ENABLE_NOTIFICATION, GPT_E_UNINIT );
    }
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the parameter Channel is
        invalid (not within the range specified by configuration), the function
        Gpt_EnableNotification shall raise the error GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_ENABLE_NOTIFICATION, GPT_E_PARAM_CHANNEL );
    }
    if( LocalGptConfigPtr->Channels->GptNotification == NULL_PTR )
    {
        /* If development error detection is enabled for GPT module: If no valid notification function
        is configured (GptNotification), the function Gpt_EnableNotification shall raise the error
        GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_ENABLE_NOTIFICATION, GPT_E_PARAM_CHANNEL );
    }
    else
    {
        Gpt_Arch_EnableNotification( LocalGptConfigPtr, Channel );
    }
}
#endif

/**
 * @brief Disables the interrupt notification for a channel.
 *
 * The function disables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00287, SWS_Gpt_00200, SWS_Gpt_00227, SWS_Gpt_00217
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    if( HwUnit_Gpt.HwUnitState != GPT_STATE_INIT )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
        the function Gpt_DisableNotification shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_DISABLE_NOTIFICATION, GPT_E_UNINIT );
    }
    if( ( Channel != GPT_CHANNEL_0 ) && ( Channel != GPT_CHANNEL_1 ) )
    {
        /* If development error detection is enabled for GPT module: If the driver is not initialized,
        the function Gpt_DisableNotification shall raise the error GPT_E_UNINIT. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_DISABLE_NOTIFICATION, GPT_E_PARAM_CHANNEL );
    }
    if( LocalGptConfigPtr->Channels->GptNotification == NULL_PTR )
    {
        /* If development error detection is enabled for GPT module: If no valid notification function
        is configured (GptNotification), the function Gpt_DisableNotification shall raise the error
        GPT_E_PARAM_CHANNEL. */
        Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ID_DISABLE_NOTIFICATION, GPT_E_PARAM_CHANNEL );
    }
    else
    {
        Gpt_Arch_DisableNotification( LocalGptConfigPtr, Channel );
    }
}
#endif

/**
 * @brief Executes the callback function defined by the user on the GPT_CHANNEL_0,
 * validating the interrupt flag and turning it off afterwards.
 *
 * The notification prototype Gpt_Notification_Channel0 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @reqs   SWS_Gpt_00292, SWS_Gpt_00086, SWS_Gpt_00209, SWS_Gpt_00093, SWS_Gpt_00233, SWS_Gpt_00206
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel0( void )
{
    Gpt_Arch_Notification_Channel0( LocalGptConfigPtr );
}
#endif

/**
 * @brief Executes the callback function defined by the user on the GPT_CHANNEL_1,
 * validating the interrupt flag and turning it off afterwards.
 *
 * The notification prototype Gpt_Notification_Channel1 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @reqs   SWS_Gpt_00292, SWS_Gpt_00086, SWS_Gpt_00209, SWS_Gpt_00093, SWS_Gpt_00233, SWS_Gpt_00206
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel1( void )
{
    Gpt_Arch_Notification_Channel0( LocalGptConfigPtr );
}
#endif

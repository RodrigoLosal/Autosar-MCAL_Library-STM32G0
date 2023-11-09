/**
 * @file    Gpt_Arch.c
 * @brief   **Gpt Architecture Driver**
 * @author  Rodrigo Lopez
 *
 * Gpt driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Gpt driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Gpt_Cfg.h"
#include "Gpt_Arch.h"

/**
 * @brief    **Gpt low level Initialization**
 *
 * This function initialize all internals variables and the used GPT structure of the
 * microcontroller according to the parameters specified in ConfigPtr and HwUnit.
 * Furthermore disable all notifications.
 *
 * @param    HwUnit Pointer to the hardware unit configuration.
 * @param    Config Pointer to driver configuration.
 */
void Gpt_Arch_Init( Gpt_HwUnit *HwUnit, const Gpt_ConfigType *Config )
{
    (void)HwUnit;
    (void)Config;
}

/**
 * @brief    **Gpt low level Deinitialization**
 *
 * This function de-initializes the Gpt module.
 *
 * @param    HwUnit Pointer to the hardware unit configuration.
 */
void Gpt_Arch_DeInit( Gpt_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief **Returns the time already elapsed**
 *
 * The function returns the time already elapsed. When the channel is in mode “one-shot mode”,
 * this is the value relative to the point in time, the channel has been started.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the current number of ticks already elapsed.
 */
Gpt_ValueType Gpt_Arch_GetTimeElapsed( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel )
{
    (void)HwUnit;
    (void)Channel;
    return E_NOT_OK;
}

/**
 * @brief **Returns the time remaining until the target time is reached**
 *
 * The function returns the timer value remaining until the target time will be reached next time.
 * he remaining time is the "target time" minus the time already elapsed.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the remaining number of ticks before the timer overflows.
 */
Gpt_ValueType Gpt_Arch_GetTimeRemaining( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel )
{
    (void)HwUnit;
    (void)Channel;
    return E_NOT_OK;
}

/**
 * @brief **Starts a timer channel**
 *
 * The function starts the selected timer channel with a defined target time. If configured and
 * enabled, an interrupt notification or a wakeup interrupt occurs, when the target time is reached.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 * @param Value         Target time in number of ticks.
 */
void Gpt_Arch_StartTimer( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    (void)Channel;
    (void)Value;
    (void)HwUnit;
}

/**
 * @brief **Stops a timer channel**
 *
 * The function stops the selected timer channel.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 */
void Gpt_Arch_StopTimer( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel )
{
    (void)Channel;
    (void)HwUnit;
}

/**
 * @brief **Gets the current version**
 *
 * The function gives the versioninfo struct the values of the current version. to eneable this
 * function change the value of GPT_VERSION_INFO_API to STD_ON on the Gpt_Cfg file.
 *
 * @param HwUnit                  Pointer to the hardware unit configuration.
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 */
void Gpt_Arch_GetVersionInfo( Gpt_HwUnit *HwUnit, Std_VersionInfoType *versioninfo )
{
    (void)HwUnit;
    (void)versioninfo;
}

/**
 * @brief **Enables the interrupt notification for a channel**
 *
 * The function enables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 */
void Gpt_Arch_EnableNotification( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel )
{
    (void)Channel;
    (void)HwUnit;
}

/**
 * @brief **Disables the interrupt notification for a channel**
 *
 * The function disables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 */
void Gpt_Arch_DisableNotification( Gpt_HwUnit *HwUnit, Gpt_ChannelType Channel )
{
    (void)Channel;
    (void)HwUnit;
}

/**
 * @brief **Executes the callback function defined by the user on the GPT_CHANNEL_0,
 * validating the interrupt flag and turning it off afterwards**
 *
 * The notification prototype Gpt_Notification_Channel0 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 */
void Gpt_Arch_Notification_Channel0( Gpt_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief **Executes the callback function defined by the user on the GPT_CHANNEL_1,
 * validating the interrupt flag and turning it off afterwards**
 *
 * The notification prototype Gpt_Notification_Channel1 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @param HwUnit        Pointer to the hardware unit configuration.
 */
void Gpt_Arch_Notification_Channel1( Gpt_HwUnit *HwUnit )
{
    (void)HwUnit;
}

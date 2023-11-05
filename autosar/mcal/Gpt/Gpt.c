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
#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"

/**
 * @brief Global GPT register array.
 */
static Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 }; /* cppcheck-suppress misra-config ; The define is already available through Gpt.h */

/**
 * @brief  Variable for the initial value of the GPT configuration array.
 */
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
 * @reqs   SWS_Gpt_00280
 */
void Gpt_Init( const Gpt_ConfigType *ConfigPtr )
{
    Gpt_RegisterType *channel;

    for( uint8 ChannelsToInit = 0; ChannelsToInit < GPT_NUMBER_OF_CHANNELS; ChannelsToInit++ )
    {
        channel = channels[ ( &ConfigPtr[ ChannelsToInit ] )->GptChannelId ];
        Bfx_SetBitMask_u32u32( (uint32 *)&channel->PSC, (uint32)( &ConfigPtr[ ChannelsToInit ] )->GptChannelPrescaler );                 /*Writing the value of the prescaler on TIMx_PSC*/
        Bfx_PutBit_u32u8u8( (uint32 *)&channel->CR1, GPT_ONE_PULSE_MODE_BIT, (uint32)( &ConfigPtr[ ChannelsToInit ] )->GptChannelMode ); /*Writing the OPM: bit of TIMx_CR1 for continuous or one-pulse mode*/
        Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the Status Register Flag*/                        /*Clearing the update interrupt flag of TIMx_SR*/
    }
    LocalGptConfigPtr = ConfigPtr;
}

/**
 * @brief Deinitializes the GPT driver.
 *
 * The function deinitializes the hardware used by the GPT driver (depending on configuration) to
 * the power on reset state. Values of registers which are not writeable are excluded.
 *
 * @reqs   SWS_Gpt_00281
 */
#if GPT_DEINIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DeInit( void )
{
    Gpt_RegisterType *channel;

    for( uint8 ChannelsToDeinit = 0; ChannelsToDeinit < GPT_NUMBER_OF_CHANNELS; ChannelsToDeinit++ )
    {
        channel = channels[ ChannelsToDeinit ];
        Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->PSC, GPT_PRESCALER_LSB, GPT_PRESCALER_MSB, RESET );   /*Clearing the value of the prescaler on TIMx_PSC*/
        Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, GPT_INTERRUPT_FLAG_BIT );                              /*Clearing the update interrupt flag of TIMx_SR*/
        Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, GPT_AUTO_RELOAD_LSB, GPT_AUTO_RELOAD_MSB, SET ); /*Setting back the reset value of TIMx_ARR*/
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
 * @reqs   SWS_Gpt_00282
 */
#if GPT_TIME_ELAPSED_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = channels[ Channel ];

    return channel->CNT;
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
 * @reqs   SWS_Gpt_00282
 */
#if GPT_TIME_REMAINING_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = channels[ Channel ];

    return channel->ARR - channel->CNT;
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
 * @reqs   SWS_Gpt_00284
 */
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, GPT_AUTO_RELOAD_LSB, GPT_AUTO_RELOAD_MSB, RESET ); /*Clearing the reset value of TIMx_ARR*/
    Bfx_SetBitMask_u32u32( (uint32 *)&channel->ARR, Value );                                           /*Writing the value of Period on TIMx_ARR*/
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT );                               /*Setting the CEN: bit of TIMx_CR1*/
}

/**
 * @brief Stops a timer channel.
 *
 * The function stops the selected timer channel.
 *
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00285
 */
void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT ); /*Clearing the CEN: bit of TIMx_CR1*/
}

/**
 * @brief Gets the current version.
 *
 * The function gives the versioninfo struct the values of the current version. to eneable this
 * function change the value of GPT_VERSION_INFO_API to STD_ON on the Gpt_Cfg file.
 *
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 *
 * @reqs   SWS_Gpt_00279
 */
#if GPT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    versioninfo->moduleID         = 0;
    versioninfo->sw_major_version = 0;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;
    versioninfo->vendorID         = 0;
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
 * @reqs   SWS_Gpt_00286
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Clearing the UDIS: bit of TIMx_CR1*/
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
 * @reqs   SWS_Gpt_00287
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Setting the UDIS: bit of TIMx_CR1*/
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
 * @reqs   SWS_Gpt_00292
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel0( void )
{
    if( Bfx_GetBit_u32u8_u8( TIM6->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        LocalGptConfigPtr->GptNotification[ GPT_CHANNEL_0 ]( );
        Bfx_ClrBit_u32u8( (uint32 *)&TIM6->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
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
 * @reqs   SWS_Gpt_00292
 */
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel1( void )
{
    if( Bfx_GetBit_u32u8_u8( TIM7->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        LocalGptConfigPtr->GptNotification[ GPT_CHANNEL_1 ]( );
        Bfx_ClrBit_u32u8( (uint32 *)&TIM7->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
}
#endif

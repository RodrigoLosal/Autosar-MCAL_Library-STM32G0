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
#include "Bfx.h"
#include "Std_Types.h"
#include "Gpt_Cfg.h"
#include "Gpt.h"
#include "Gpt_Arch.h"

/**
 * @brief Global GPT register array.
 */
/* cppcheck-suppress misra-config ; The GPT_NUMBER_OF_CHANNELS define is already available through Gpt.h */
static Gpt_RegisterType *GptPeripherals[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

/**
 * @brief    **Gpt low level Initialization**
 *
 * This function initialize all internals variables and the used GPT structure of the
 * microcontroller according to the parameters specified in ConfigPtr and HwUnit.
 * Furthermore disable all notifications.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param    ChannelsToInit Number of channels to init.
 *
 * @reqs   SWS_Gpt_00280, SWS_Gpt_00006, SWS_Gpt_00107, SWS_Gpt_00068, SWS_Gpt_00258
 */
void Gpt_Arch_Init( const Gpt_ConfigType *ConfigPtr, uint32 ChannelsToInit )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ ChannelsToInit ].GptReference ];
    /*Clearing the value of the prescaler on TIMx_PSC*/
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->PSC, GPT_PRESCALER_LSB, GPT_PRESCALER_MSB, STD_OFF );
    /*Writing the value of the prescaler on TIMx_PSC*/
    Bfx_SetBitMask_u32u32( (uint32 *)&channel->PSC, (uint32)ConfigPtr->Channels[ ChannelsToInit ].GptChannelPrescaler );
    /*Writing the OPM: bit of TIMx_CR1 for continuous or one-pulse mode*/
    Bfx_PutBit_u32u8u8( (uint32 *)&channel->CR1, GPT_ONE_PULSE_MODE_BIT, (uint32)ConfigPtr->Channels[ ChannelsToInit ].GptChannelMode );
    /*Clearing the update interrupt flag of TIMx_SR*/
    Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, GPT_INTERRUPT_FLAG_BIT );
}

/**
 * @brief    **Gpt low level Deinitialization**
 *
 * This function de-initializes the Gpt module.
 *
 * @param ConfigPtr              Pointer to driver configuration.
 * @param ChannelsToDeinit       Numeric identifier of the GPT channels to Deinit.
 *
 * @reqs   SWS_Gpt_00281, SWS_Gpt_00008, SWS_Gpt_00105, SWS_Gpt_00162, SWS_Gpt_00194
 */
void Gpt_Arch_DeInit( const Gpt_ConfigType *ConfigPtr, uint32 ChannelsToDeinit )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ ChannelsToDeinit ].GptReference ];
    /*Clearing the value of the prescaler on TIMx_PSC*/
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->PSC, GPT_PRESCALER_LSB, GPT_PRESCALER_MSB, STD_OFF );
    /*Clearing the OPM: bit of TIMx_CR1*/
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_ONE_PULSE_MODE_BIT );
    /*Clearing the update interrupt flag of TIMx_SR*/
    Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, GPT_INTERRUPT_FLAG_BIT );
    /*Setting back the reset value of TIMx_ARR*/
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, GPT_AUTO_RELOAD_LSB, GPT_AUTO_RELOAD_MSB, STD_ON );
}

/**
 * @brief **Returns the time already elapsed**
 *
 * The function returns the time already elapsed. When the channel is in mode “one-shot mode”,
 * this is the value relative to the point in time, the channel has been started.
 *
 * @param ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the current number of ticks already elapsed.
 *
 * @reqs   SWS_Gpt_00282, SWS_Gpt_00010, SWS_Gpt_00361, SWS_Gpt_00195
 */
Gpt_ValueType Gpt_Arch_GetTimeElapsed( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];

    return channel->CNT;
}

/**
 * @brief **Returns the time remaining until the target time is reached**
 *
 * The function returns the timer value remaining until the target time will be reached next time.
 * he remaining time is the "target time" minus the time already elapsed.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @retval  Returns the remaining number of ticks before the timer overflows.
 *
 * @reqs   SWS_Gpt_00283, SWS_Gpt_00083, SWS_Gpt_00196
 */
Gpt_ValueType Gpt_Arch_GetTimeRemaining( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];

    return channel->ARR - channel->CNT;
}

/**
 * @brief **Starts a timer channel**
 *
 * The function starts the selected timer channel with a defined target time. If configured and
 * enabled, an interrupt notification or a wakeup interrupt occurs, when the target time is reached.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 * @param Value         Target time in number of ticks.
 *
 * @reqs   SWS_Gpt_00284, SWS_Gpt_00274, SWS_Gpt_00275
 */
void Gpt_Arch_StartTimer( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];
    /*Clearing the reset value of TIMx_ARR*/
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, GPT_AUTO_RELOAD_LSB, GPT_AUTO_RELOAD_MSB, STD_OFF );
    /*Writing the value of Period on TIMx_ARR*/
    Bfx_SetBitMask_u32u32( (uint32 *)&channel->ARR, Value );
    /*Setting the CEN: bit of TIMx_CR1*/
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT );
}

/**
 * @brief **Stops a timer channel**
 *
 * The function stops the selected timer channel.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00285, SWS_Gpt_00013
 */
void Gpt_Arch_StopTimer( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT ); /*Clearing the CEN: bit of TIMx_CR1*/
}

/**
 * @brief **Enables the interrupt notification for a channel**
 *
 * The function enables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00286, SWS_Gpt_00199
 */
void Gpt_Arch_EnableNotification( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Clearing the UDIS: bit of TIMx_CR1*/
}

/**
 * @brief **Disables the interrupt notification for a channel**
 *
 * The function disables the interrupt notification of the referenced channel configured for
 * notification.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 * @param Channel       Numeric identifier of the GPT channel.
 *
 * @reqs   SWS_Gpt_00287, SWS_Gpt_00200
 */
void Gpt_Arch_DisableNotification( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;

    channel = GptPeripherals[ ConfigPtr->Channels[ Channel ].GptReference ];
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Setting the UDIS: bit of TIMx_CR1*/
}

/**
 * @brief **Executes the callback function defined by the user on the GPT_CHANNEL_0,
 * validating the interrupt flag and turning it off afterwards**
 *
 * The notification prototype Gpt_Notification_Channel0 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 *
 * @reqs   SWS_Gpt_00292, SWS_Gpt_00086, SWS_Gpt_00209, SWS_Gpt_00093, SWS_Gpt_00233, SWS_Gpt_00206
 */
void Gpt_Arch_Notification_Channel0( const Gpt_ConfigType *ConfigPtr )
{
    Gpt_RegisterType *channel;
    channel = GptPeripherals[ GPT_CHANNEL_0 ];

    if( Bfx_GetBit_u32u8_u8( channel->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        if( ConfigPtr->Channels[ GPT_CHANNEL_0 ].GptNotification != NULL_PTR )
        {
            ConfigPtr->Channels[ GPT_CHANNEL_0 ].GptNotification( );
        }

        Bfx_ClrBit_u32u8( (uint32 *)channel->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
}

/**
 * @brief **Executes the callback function defined by the user on the GPT_CHANNEL_1,
 * validating the interrupt flag and turning it off afterwards**
 *
 * The notification prototype Gpt_Notification_Channel1 is for the notification callback function
 * and shall be implemented by the user. The callback notifications Gpt_Notification_<channel> shall
 * be configurable as pointers to user defined functions within the configuration structure.
 *
 * @param    ConfigPtr      Pointer to driver configuration.
 *
 * @reqs   SWS_Gpt_00292, SWS_Gpt_00086, SWS_Gpt_00209, SWS_Gpt_00093, SWS_Gpt_00233, SWS_Gpt_00206
 */
void Gpt_Arch_Notification_Channel1( const Gpt_ConfigType *ConfigPtr )
{
    Gpt_RegisterType *channel;
    channel = GptPeripherals[ GPT_CHANNEL_1 ];

    if( Bfx_GetBit_u32u8_u8( channel->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        if( ConfigPtr->Channels[ GPT_CHANNEL_1 ].GptNotification != NULL_PTR )
        {
            ConfigPtr->Channels[ GPT_CHANNEL_1 ].GptNotification( );
        }

        Bfx_ClrBit_u32u8( (uint32 *)channel->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
}

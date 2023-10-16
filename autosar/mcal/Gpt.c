#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"

static Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

static const Gpt_ConfigType *LocalGptConfigPtr = NULL_PTR;

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

#if GPT_TIME_ELAPSED_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    Gpt_ValueType TimeElapsed;

    channel     = channels[ Channel ];
    TimeElapsed = channel->CNT;

    return TimeElapsed;
}
#endif

#if GPT_TIME_REMAINING_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    Gpt_ValueType TimeRemaining;

    channel       = channels[ Channel ];
    TimeRemaining = channel->ARR - channel->CNT;

    return TimeRemaining;
}
#endif

void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, GPT_AUTO_RELOAD_LSB, GPT_AUTO_RELOAD_MSB, RESET ); /*Clearing the reset value of TIMx_ARR*/
    Bfx_SetBitMask_u32u32( (uint32 *)&channel->ARR, Value );                                           /*Writing the value of Period on TIMx_ARR*/
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT );                               /*Setting the CEN: bit of TIMx_CR1*/
}

void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_COUNTER_ENABLE_BIT ); /*Clearing the CEN: bit of TIMx_CR1*/
}

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

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Clearing the UDIS: bit of TIMx_CR1*/
}
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    channel = channels[ Channel ];
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, GPT_UPDATE_DISABLE_BIT ); /*Setting the UDIS: bit of TIMx_CR1*/
}
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel0( void )
{
    if( Bfx_GetBit_u32u8_u8( (uint32 *)&TIM6->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        LocalGptConfigPtr->GptNotification[ GPT_CHANNEL_0 ]( );
        Bfx_ClrBit_u32u8( (uint32 *)&TIM6->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
}
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel1( void )
{
    if( Bfx_GetBit_u32u8_u8( (uint32 *)&TIM7->SR, GPT_INTERRUPT_FLAG_BIT ) == TRUE ) /*Checking if the update interrupt flag of TIMx_SR is set*/
    {
        LocalGptConfigPtr->GptNotification[ GPT_CHANNEL_1 ]( );
        Bfx_ClrBit_u32u8( (uint32 *)&TIM7->SR, GPT_INTERRUPT_FLAG_BIT ); /*Clearing the update interrupt flag of TIMx_SR*/
    }
}
#endif

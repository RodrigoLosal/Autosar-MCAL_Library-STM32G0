#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"

void Gpt_Init( const Gpt_ConfigType *ConfigPtr )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    for( uint8 j = 0; j < GPT_NUMBER_OF_CHANNELS; j++ )
    {
        channel = channels[ ( &ConfigPtr[ j ] )->Channel ];
        Bfx_SetBitMask_u32u32( (uint32 *)&channel->PSC, (uint32)( &ConfigPtr[ j ] )->Prescaler );    /*Writing the value of the prescaler on TIMx_PSC*/
        Bfx_PutBit_u32u8u8( (uint32 *)&channel->CR1, 3u, (uint32)( &ConfigPtr[ j ] )->ChannelMode ); /*Writing the OPM: bit of TIMx_CR1 for continuous or one-pulse mode*/
        Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, 0 );                                               /*Clearing the update interrupt flag of TIMx_SR*/
    }
}

void Gpt_DeInit( void )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    for( uint8 j = 0; j < GPT_NUMBER_OF_CHANNELS; j++ )
    {
        channel = channels[ j ];
        Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->PSC, 0, 16u, 0 ); /*Clearing the value of the prescaler on TIMx_PSC*/
        Bfx_ClrBit_u32u8( (uint32 *)&channel->SR, 0 );               /*Clearing the update interrupt flag of TIMx_SR*/
        Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, 0, 16u, 1 ); /*Setting back the reset value of TIMx_ARR*/
    }
}

Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_ValueType TimeElapsed;
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel     = channels[ Channel ];
    TimeElapsed = ( 1 / ( 16000000 / channel->PSC ) ) * ( channel->CNT ); /*Convertion to ms*/

    return TimeElapsed;
}

Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_ValueType TimeRemaining;
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel       = channels[ Channel ];
    TimeRemaining = ( 1 / ( 16000000 / channel->PSC ) ) * ( channel->ARR - channel->CNT ); /*Convertion to ms*/
    ;

    return TimeRemaining;
}

void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel = channels[ Channel ];
    Bfx_SetBits_u32u8u8u8( (uint32 *)&channel->ARR, 0, 16u, 0 ); /*Clearing the reset value of TIMx_ARR*/
    Bfx_SetBitMask_u32u32( (uint32 *)&channel->ARR, Value );     /*Writing the value of Period on TIMx_ARR*/
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, 0 );              /*Setting the CEN: bit of TIMx_CR1*/
}

void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, 0 ); /*Clearing the CEN: bit of TIMx_CR1*/
}

void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel = channels[ Channel ];
    Bfx_ClrBit_u32u8( (uint32 *)&channel->CR1, 1 ); /*Clearing the UDIS: bit of TIMx_CR1*/
}

void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

    channel = channels[ Channel ];
    Bfx_SetBit_u32u8( (uint32 *)&channel->CR1, 1 ); /*Setting the UDIS: bit of TIMx_CR1*/
}

void Gpt_Notification_Channel1( void )
{
    /*Implemented by the user*/

    Bfx_ClrBit_u32u8( (uint32 *)&TIM6->SR, 0 ); /*Clearing the update interrupt flag of TIMx_SR*/
}

void Gpt_Notification_Channel2( void )
{
    /*Implemented by the user*/

    Bfx_ClrBit_u32u8( (uint32 *)&TIM7->SR, 0 ); /*Clearing the update interrupt flag of TIMx_SR*/
}
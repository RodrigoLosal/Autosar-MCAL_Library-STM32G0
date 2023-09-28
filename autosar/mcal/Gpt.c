<<<<<<< HEAD
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
<<<<<<< HEAD

    LocalGptPtr = ConfigPtr;
=======
#include "Gpt.h"

void Gpt_GetVersionInfo( Std_VersionInfoType *VersionInfoPtr )
{

}

void Gpt_Init( const Gpt_ConfigType *ConfigPtr )
{

>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
>>>>>>> bbfe89e (GPT-Code-Implementation. Rest of the functions filled.)
}

void Gpt_DeInit( void )
{
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ 2 ] = { TIM6, TIM7 };

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
<<<<<<< HEAD
<<<<<<< HEAD
    switch ( Channel )
=======
    Gpt_ValueType TimeElapsed;
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

<<<<<<< HEAD
    switch( Channel )
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
    {
        case Channel1:
            TimeElapsed = TIM6->CNT;
            break;

        case Channel2:
            TimeElapsed = TIM7->CNT;
            break;

        default:
            break;
    }
<<<<<<< HEAD
=======

>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
=======
    channel     = channels[ Channel ];
    TimeElapsed = ( 1 / ( 16000000 / channel->PSC ) ) * ( channel->CNT ); /*Convertion to ms*/
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)

    return TimeElapsed;
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
}

Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
<<<<<<< HEAD
<<<<<<< HEAD
    switch ( Channel )
=======
    Gpt_ValueType TimeRemaining;
    Gpt_RegisterType *channel;
    Gpt_RegisterType *channels[ GPT_NUMBER_OF_CHANNELS ] = { TIM6, TIM7 };

<<<<<<< HEAD
    switch( Channel )
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
    {
        case Channel1:
            TimeRemaining = TIM6->ARR - TIM6->CNT;
            break;

        case Channel2:
            TimeRemaining = TIM7->ARR - TIM7->CNT;
            break;

        default:
            break;
    }
<<<<<<< HEAD
=======

>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
=======
    channel       = channels[ Channel ];
    TimeRemaining = ( 1 / ( 16000000 / channel->PSC ) ) * ( channel->ARR - channel->CNT ); /*Convertion to ms*/
    ;
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)

    return TimeRemaining;
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
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

<<<<<<< HEAD
<<<<<<< HEAD
=======
void Gpt_SetMode( Gpt_ModeType Mode )
{

}

void Gpt_DisableWakeUp( Gpt_ChannelType Channel )
{

}

void Gpt_EnableWakeUp( Gpt_ChannelType Channel )
{

}

>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
void Gpt_Notification_TIM6( void )
=======
void Gpt_Notification_Channel1( void )
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)
{
    /*Implemented by the user*/

    Bfx_ClrBit_u32u8( (uint32 *)&TIM6->SR, 0 ); /*Clearing the update interrupt flag of TIMx_SR*/
}

void Gpt_Notification_Channel2( void )
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

=======
    
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
=======
    /*Implemented by the user*/
<<<<<<< HEAD
>>>>>>> bbfe89e (GPT-Code-Implementation. Rest of the functions filled.)
=======

    Bfx_ClrBit_u32u8( (uint32 *)&TIM7->SR, 0 ); /*Clearing the update interrupt flag of TIMx_SR*/
>>>>>>> d5b5122 (GPT-Code-Implementation. Corrections made on the functions.)
}
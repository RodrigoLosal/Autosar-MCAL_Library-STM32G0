#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"

static const Gpt_ConfigType *LocalGptPtr = NULL_PTR;

void Gpt_Init( const Gpt_ConfigType *ConfigPtr )
{
    switch( ConfigPtr->Channel )
    {
        case Channel1:
            /*cppcheck-suppress misra-c2012-11.4 ; Required for the unavailability of the use of RCC register.*/
            Bfx_SetBit_u32u8( *(const unsigned long *)0x4002103C, 4 ); /*Activation TIM6EN: bit in RCC_APBENR1*/
            Bfx_SetBitMask_u32u32( TIM6.PSC, ConfigPtr->Prescaler );
            Bfx_SetBits_u32u8u8u8( TIM6.ARR, 0, 16u, 0 );         /*Clearing the reset value of TIMx_ARR*/
            Bfx_SetBitMask_u32u32( TIM6.ARR, ConfigPtr->Period ); /*Writing the value of Period on TIMx_ARR*/
            Bfx_SetBit_u32u8( TIM6.SR, 0 );                       /*Clearing the update interrupt flag of TIMx_SR*/
            break;

        case Channel2:
            /*cppcheck-suppress misra-c2012-11.4 ; Required for the unavailability of the use of RCC register.*/
            Bfx_SetBit_u32u8( *(const unsigned long *)0x4002103C, 5 ); /*Activation TIM7EN: bit in RCC_APBENR1*/
            Bfx_SetBitMask_u32u32( TIM7.PSC, ConfigPtr->Prescaler );   /*Writing the value of the prescaler on TIMx_PSC*/
            Bfx_SetBits_u32u8u8u8( TIM7.ARR, 0, 16u, 0 );              /*Clearing the reset value of TIMx_ARR*/
            Bfx_SetBitMask_u32u32( TIM7.ARR, ConfigPtr->Period );      /*Writing the value of Period on TIMx_ARR*/
            Bfx_SetBit_u32u8( TIM7.SR, 0 );                            /*Clearing the update interrupt flag of TIMx_SR*/
            break;

        default:
            break;
    }

    LocalGptPtr = ConfigPtr;
}

void Gpt_DeInit( void )
{
}

Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_ValueType TimeElapsed;

    switch( Channel )
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

    return TimeElapsed;
}

Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_ValueType TimeRemaining;

    switch( Channel )
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

    return TimeRemaining;
}

void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
}

void Gpt_StopTimer( Gpt_ChannelType Channel )
{
}

void Gpt_EnableNotification( Gpt_ChannelType Channel )
{
}

void Gpt_DisableNotification( Gpt_ChannelType Channel )
{
}

void Gpt_Notification_TIM6( void )
{
}

void Gpt_Notification_TIM7( void )
{
}
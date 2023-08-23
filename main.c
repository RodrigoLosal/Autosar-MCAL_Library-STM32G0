#include "Nvic.h"
#include <stdint.h>

static void TIM7_Init( void ); // Forward declaration for Timer 7 initialization function.

// Timer 7 Interrupt Handler.
void TIM7_IRQHandler( void );

// Timer 7 initialization function.
static void TIM7_Init( void )
{
    RCC->APBSMENR1 |= ( 0x1UL << 5U ); // Enable the Timer 7 clock.
    RCC->APBRSTR1 |= ( 0x1UL << 5U );  // Reset the Timer 7.
    RCC->APBRSTR1 &= ~( 0x1UL << 5U );

    TIM7->PSC = 16000;
    TIM7->ARR = 0xFFFF;            // Set the auto-reload value.
    TIM7->SR &= ~( 0x1UL << 0U );  // Clear the update flag (UIF).
    TIM7->DIER |= ( 0x1UL << 0U ); // Enable Timer 7 overflow interrupt.

    CDD_Nvic_EnableIrq( TIM7_LPTIM2_IRQn ); // Enable Timer 7 interrupt in the NVIC.

    TIM7->CR1 |= ( 0x1UL << 0U ); // Start Timer 7.
    CDD_Nvic_SetPriority( TIM7_LPTIM2_IRQn, 2 );
}

int main( void )
{
    /* Enable GPIOA clock */
    RCC_GPIOA_CLK_EN( );

    /* Configure pin 5 of port A as output */
    GPIOA->MODER &= ~( 0x3UL << ( 5 * 2 ) );
    GPIOA->MODER |= ( 0x1UL << ( 5 * 2 ) ); // Set PA5 as output

    TIM7_Init( );

    while( 1 )
    {
        TIM7_IRQHandler( );
    }

    return 0;
}

// ISR
void TIM7_IRQHandler( void )
{
    TIM7->SR &= ~( 0x1UL << 0U ); // Clear the TIM7 interrupt flag.
    GPIOA->ODR ^= ( 0x1UL << 5 ); // Toggle the LED.
}

#include "Nvic.h"
#include <stdint.h>

void TIM7_LPTIM2_IRQHandler( void );
int main( void )
{
    /* Enable GPIOC clock */
    RCC_GPIOA_CLK_EN( );

    /* Configure pin 5 of port C as output */
    GPIOA->MODER &= ~( 0x3UL << ( 5 * 2 ) );
    GPIOA->MODER |= ( 0x1UL << ( 5 * 2 ) ); // Set PA5 as output
    // GPIOA->ODR ^= ( 0x1UL << 5 );
    CDD_Nvic_EnableIrq( (Nvic_IrqType)TIM7_LPTIM2_IRQn ); // Enable Timer 7 interrupt in the NVIC.
    CDD_Nvic_SetPriority( (Nvic_IrqType)TIM7_LPTIM2_IRQn, 1 );


    while( 1 )
    {
        CDD_Nvic_SetPendingIrq( TIM7_LPTIM2_IRQn );

        for( int i = 0; i < 100000; i++ )
            ;
    }

    return 0;
}
void TIM7_LPTIM2_IRQHandler( void )
{
    GPIOA->ODR ^= ( 0x1UL << 5 );
    CDD_Nvic_ClearPendingIrq( TIM7_LPTIM2_IRQn );
}
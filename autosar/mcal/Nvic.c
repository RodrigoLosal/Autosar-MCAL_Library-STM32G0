#include "Nvic.h"

/**
 * @brief Sets the priority for a specific interrupt.
 * @param irq The type of interrupt.
 * @param priority The priority level to set for the interrupt.
 */
void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
    {
        uint32 ip_idx    = irq / 4U;
        uint32 bit_shift = ( irq % 4U ) * 8U;

        NVIC->IP[ ip_idx ] &= ~( 0xFFU << bit_shift );           // Clear the current priority bits for the interrupt
        NVIC->IP[ ip_idx ] |= ( priority & 0xFFU ) << bit_shift; // Set the new priority for the interrupt
    }
}

/**
 * @brief Returns the priority value of a specific interrupt.
 * @param irq The type of interrupt.
 * @return The priority value of the specified interrupt.
 */
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    uint32 priority;
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        uint32 ip_idx    = irq / 4U;
        uint32 bit_shift = ( irq % 4U ) * 8U;
        priority         = ( NVIC->IP[ ip_idx ] >> bit_shift ) & 0xFFU;
    }
    else
    {
        priority = 0xFFU;
    }
    return priority;
}


/**
 * @brief Enables a specific interrupt.
 * @param irq The type of interrupt to enable.
 */
void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        uint32 bit_offset = irq % 32U;
        // Enable the interrupt by setting the corresponding bit in NVIC_ISER
        NVIC->ISER[ 0U ] = ( 1U << bit_offset );
    }
}

/**
 * @brief Disables a specific interrupt.
 * @param irq The type of interrupt to disable.
 */
void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        uint32 bit_offset = irq % 32U;
        // Disable the interrupt by setting the corresponding bit in NVIC_ICER
        NVIC->ICER[ 0U ] = ( 1U << bit_offset );
    }
}

/**
 * @brief Checks if a specific interrupt is pending.
 * @param irq The type of interrupt to check.
 * @return 1 if the interrupt is pending, 0 if not.
 */
uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{

    uint32 pending = 0U;

    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
    {
        uint32 bit_offset = irq % 32U; // Calculate the bit position for the interrupt
        if( NVIC->ISPR[ 0U ] & ( 1U << bit_offset ) )
        {
            pending = 1U;
        }
    }
    return pending;
}

/**
 * @brief Sets a specific interrupt as pending.
 * @param irq The type of interrupt to set as pending.
 */
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
    {
        uint32 bit_offset = irq % 32U;            // Calculate the bit position for the interrupt
        NVIC->ISPR[ 0U ] |= ( 1U << bit_offset ); // Set the bit to mark the interrupt as pending
    }
}

/**
 * @brief Clears the pending status of a specific interrupt.
 * @param irq The type of interrupt to clear pending status for.
 */
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        uint32 bit_offset = irq % 32U;
        // Clear the pending interrupt by setting the corresponding bit in NVIC_ICPR
        NVIC->ICPR[ 0U ] = (uint32)( 1UL << bit_offset );
    }
}
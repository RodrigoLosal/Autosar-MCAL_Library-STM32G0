#include "Nvic.h"

/**
 * @brief Sets the priority for a specific interrupt.
 * @param irq The type of interrupt.
 * @param priority The priority level to set for the interrupt.
 */
void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( (uint32)( irq ) >= 0 )
    {
        uint32 byte_offset = (uint32)irq % 4U;

        NVIC->IP[ ( ( ( (uint32)(uint32)( irq ) ) >> 2UL ) ) ] &= ~( 0xFFU << ( byte_offset * 8U ) );           // Clear existing priority bits
        NVIC->IP[ ( ( ( (uint32)(uint32)( irq ) ) >> 2UL ) ) ] |= ( priority & 0xFFU ) << ( byte_offset * 8U ); // Set new priority
    }
}

/**
 * @brief Returns the priority value of a specific interrupt.
 * @param irq The type of interrupt.
 * @return The priority value of the specified interrupt.
 */
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    if( (uint32)( irq ) >= 0 )
    {
        uint32 byte_offset = (uint32)irq % 4U;

        // Extract and return the priority value from NVIC_IPR
        uint32 priority = ( NVIC->IP[ 0U ] >> ( byte_offset * 8U ) ) & 0xFFU;
        return priority;
    }
}

/**
 * @brief Enables a specific interrupt.
 * @param irq The type of interrupt to enable.
 */
void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( (uint32)( irq ) >= 0 )
    {
        uint32 bit_offset = ( ( (uint32)irq ) & 0x1FUL );
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
    if( (uint32)( irq ) >= 0 )
    {
        uint32 bit_offset = ( ( (uint32)irq ) & 0x1FUL );
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

    if( (uint32)( irq ) >= 0 )
    {
        uint32 bit_offset = ( ( (uint32)irq ) & ( 0x1FUL ) );
        return ( (uint32)( ( ( ( NVIC->ISPR[ 0U ] & ( 1UL << bit_offset ) ) != 0UL ) ? 1UL : 0UL ) ) );
    }
    else
    {
        return ( 0U );
    }
}

/**
 * @brief Sets a specific interrupt as pending.
 * @param irq The type of interrupt to set as pending.
 */
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( (uint32)( irq ) >= 0 )
    {
        uint32 bit_offset = ( (uint32)irq ) & 0x1FUL;
        // Set the interrupt as pending by setting the corresponding bit in NVIC_ISPR
        NVIC->ISPR[ 0U ] = (uint32)( 1UL << bit_offset );
    }
}

/**
 * @brief Clears the pending status of a specific interrupt.
 * @param irq The type of interrupt to clear pending status for.
 */
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( (uint32)( irq ) >= 0 )
    {
        uint32 bit_offset = ( (uint32)irq ) & 0x1FUL;
        // Clear the pending interrupt by setting the corresponding bit in NVIC_ICPR
        NVIC->ICPR[ 0U ] = (uint32)( 1UL << bit_offset );
    }
}
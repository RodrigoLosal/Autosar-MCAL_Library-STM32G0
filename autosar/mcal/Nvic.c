#include "Nvic.h"
#include "Registers.h"

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        NVIC->IP[ _IP_IDX( irq ) ] &= ~( 0xFFU << _BIT_SHIFT( irq ) );          
        NVIC->IP[ _IP_IDX( irq ) ] |= ( priority & 0xFFU ) << _BIT_SHIFT( irq ); 
    }
}

uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    uint32 priority;
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        priority = ( NVIC->IP[ _IP_IDX( irq ) ] >> _BIT_SHIFT( irq ) ) & 0xFFU;
    }
    else
    {
        priority = 0xFFU;
    }
    return priority;
}

void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        NVIC->ISER[ 0U ] = (uint32)( 1UL << ( ( (uint32)irq ) & 0x1FUL ) );
    }
}

void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        NVIC->ICER[ 0U ] = (uint32)( 1UL << ( ( (uint32)irq ) & 0x1FUL ) );
    }
}

uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{
    uint32 pending;
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        
        if( ( NVIC->ISPR[ 0U ] & ( 1UL << ( ( (uint32)irq ) & 0x1FUL ) ) ) != 0UL )
        {
            pending = 1UL;
        }
        else
        {
            pending = 0UL;
        }
    }
    else{
        pending = 0UL;
    }
    return pending;
}

void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        NVIC->ISPR[ 0U ] |= (uint32)(1UL << (((uint32)irq) & 0x1FUL));
    }
}

void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
         NVIC->ICPR[0U] = (uint32)(1UL << (((uint32)irq) & 0x1FUL));
    }
}
#include "Nvic.h"

#define _BIT_SHIFT( irq ) ( ( ( ( (uint32)irq ) ) & 0x03UL ) * 8UL )
#define _IP_IDX( irq )    ( ( ( (uint32)irq ) >> 2UL ) )

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
    {
        NVIC->IP[ _IP_IDX( irq ) ] &= ~( 0xFFU << _BIT_SHIFT( irq ) );          
        NVIC->IP[ _IP_IDX( irq ) ] |= ( priority & 0xFFU ) << _BIT_SHIFT( irq ); 
    }
}

uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    uint32 priority;
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
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
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        NVIC->ISER[ 0U ] = (uint32)( 1UL << ( ( (uint32)irq ) & 0x1FUL ) );
    }
}

void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
        NVIC->ICER[ 0U ] = (uint32)( 1UL << ( ( (uint32)irq ) & 0x1FUL ) );
    }
}

uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{
    uint32 pending;
    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
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
    if( ( (uint32)irq >= 16 ) && ( (uint32)irq <= 30 ) )
    {
        NVIC->ISPR[ 0U ] |= (uint32)(1UL << (((uint32)irq) & 0x1FUL));
    }
}

void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= 16 && ( (uint32)( irq ) <= 30 ) )
    {
         NVIC->ICPR[0U] = (uint32)(1UL << (((uint32)irq) & 0x1FUL));
    }
}
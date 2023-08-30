#include "Registers.h"
#include "Nvic.h"
#include "Platform_Types.h"

#define _BIT_SHIFT( irq ) ( ( ( ( (uint32)irq ) ) & 0x03UL ) * 8UL )
#define _IP_IDX( irq )    ( ( ( (uint32)irq ) >> 2UL ) )
#define NVIC_MIN_IRQ      16U
#define NVIC_MAX_IRQ      30U

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBitsMask_u32u32u32( &NVIC->IP[ _IP_IDX( irq ) ], ( priority & 0xFFU ) << _BIT_SHIFT( irq ), 0xFFU << _BIT_SHIFT( irq ) );
    }
}

uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    uint32 priority;
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        priority = Bfx_GetBits_u32u8u8_u32( NVIC->IP[ _IP_IDX( irq ) ], _BIT_SHIFT( irq ), 8 );
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
        Bfx_SetBit_u32u8( &NVIC->ISER[ 0U ], ( (uint32)irq ) & 0x1FUL );
    }
}

void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICER[ 0U ], ( (uint32)irq ) & 0x1FUL, TRUE );
    }
}

uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{
    uint32 pending;
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {

        if( ( Bfx_GetBit_u32u8_u8( &NVIC->ISPR[ 0U ], ( (uint32)irq ) & 0x1FUL ) ) )
        {
            pending = 1UL;
        }
        else
        {
            pending = 0UL;
        }
    }
    else
    {
        pending = 0UL;
    }
    return pending;
}

void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISPR[ 0U ], ( (uint32)irq ) & 0x1FUL );
    }
}

void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICPR[ 0U ], ( (uint32)irq ) & 0x1FUL, TRUE );
    }
}
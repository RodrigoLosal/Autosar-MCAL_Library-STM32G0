#include "Registers.h"
#include "Nvic.h"
#include "Std_Types.h"

#define _BIT_SHIFT( irq ) ( ( ( ( (uint32)irq ) ) & 0x03UL ) * 8UL )
#define _IP_IDX( irq )    ( ( ( (uint32)irq ) >> 2UL ) )
#define NVIC_MIN_IRQ      16U
#define NVIC_MAX_IRQ      30U
#define IRQ_MASK          0x1FUL
#define FIRST_INDEX       0U
#define BYTE_MASK         0xFFU
#define IRQ_PENDING       1UL
#define IRQ_NOT_PENDING   0UL
#define INVALID_PRIORITY  0xFFU

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBitsMask_u32u32u32( &NVIC->IP[ _IP_IDX( irq ) ], ( priority & BYTE_MASK) << _BIT_SHIFT( irq ), BYTE_MASK << _BIT_SHIFT( irq ) );
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
        priority = INVALID_PRIORITY;
    }
    return priority;
}

void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}

uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{
    uint32 pending;
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
         pending = Bfx_GetBit_u32u8_u8( &NVIC->ISPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK ) 
    }
    else
    {
        pending = IRQ_NOT_PENDING;
    }
    return pending;
}

void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}
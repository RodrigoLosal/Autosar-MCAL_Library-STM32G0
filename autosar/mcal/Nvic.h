#ifndef NVIC_H
#define NVIC_H

#include "Platform_Types.h"

#define _BIT_SHIFT( irq ) ( ( ( ( (uint32)irq ) ) & 0x03UL ) * 8UL )
#define _IP_IDX( irq )    ( ( ( (uint32)irq ) >> 2UL ) )
#define NVIC_MIN_IRQ      16U
#define NVIC_MAX_IRQ      30U

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority );
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq );
void CDD_Nvic_EnableIrq( Nvic_IrqType irq );
void CDD_Nvic_DisableIrq( Nvic_IrqType irq );
uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq );

#endif

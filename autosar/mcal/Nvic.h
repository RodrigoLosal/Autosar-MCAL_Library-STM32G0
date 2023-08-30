#ifndef NVIC_H
#define NVIC_H

#include "Std_Types.h"

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority );
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq );
void CDD_Nvic_EnableIrq( Nvic_IrqType irq );
void CDD_Nvic_DisableIrq( Nvic_IrqType irq );
uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq );

#endif

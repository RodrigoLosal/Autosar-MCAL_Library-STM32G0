/**
 * @file Nvic.h
 * @brief Complex Device Driver (CDD) for the NVIC.
 *
 * This file provides the interface for controlling the NVIC functionality. It controls the activation
 * of interrupts in ARM microcontrollers via the NVIC peripheral
 */
#ifndef NVIC_H__
#define NVIC_H__

#include "Nvic_Cfg.h"

void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority );
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq );
void CDD_Nvic_EnableIrq( Nvic_IrqType irq );
void CDD_Nvic_DisableIrq( Nvic_IrqType irq );
uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq );
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq );

#endif

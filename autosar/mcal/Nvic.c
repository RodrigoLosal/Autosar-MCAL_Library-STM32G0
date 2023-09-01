/**
 * @file    Nvic.c
 * @brief   Complex NVIC Driver
 * This file provides a comprehensive set of functions to interface with the 
 * NVIC peripheral. 
 *
 */
#include "Registers.h"
#include "Nvic.h"
#include "Bfx_32bits.h"

#define _BIT_SHIFT( irq ) ( ( ( ( (uint32)irq ) ) & 0x03UL ) * 8UL )    /*!< Calculate the bit shift for IRQ priority */
#define _IP_IDX( irq )    ( ( ( (uint32)irq ) >> 2UL ) )                /*!< Calculate the index for IRQ priority register */
#define NVIC_MIN_IRQ      16U                                           /*!< Minimum IQR value */
#define NVIC_MAX_IRQ      30U                                           /*!< Maximum IRQ value*/
#define IRQ_MASK          0x1FUL                                        /*!< Mask to obtain bits from an IRQ value */
#define FIRST_INDEX       0U                                            /*!< Starting index for NVIC register */
#define BYTE_MASK         0xFFU                                         /*!< Byte mask in 32-bit */
#define IRQ_PENDING       1UL                                           /*!< Value to specifie IRQ is pending */
#define IRQ_NOT_PENDING   0UL                                           /*!< Value to specifie IRQ is not pending */
#define INVALID_PRIORITY  0xFFU                                         /*!< Invalid priority indicator */

/**
 * @brief Set the priority of a given NVIC interrupt.
 * @param irq is the interrupt to be configured.
 * @param priority is the priority to be set.
 */
void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBitsMask_u32u32u32( &NVIC->IP[ IP_IDX( irq ) ], ( priority & BYTE_MASK ) << BIT_SHIFT( irq ), BYTE_MASK << BIT_SHIFT( irq ) );
    }
}

/**
 * @brief Return the priority of a given NVIC interrupt.
 * @param irq is the interrupt to be checked.
 * @retval The priority of the interrupt or INVALID_PRIORITY if the interrupt is out of range
 */
uint32 CDD_Nvic_GetPriority( Nvic_IrqType irq )
{
    uint32 priority;
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        priority = Bfx_GetBits_u32u8u8_u32( NVIC->IP[ IP_IDX( irq ) ], BIT_SHIFT( irq ), 8 );
    }
    else
    {
        priority = INVALID_PRIORITY;
    }
    return priority;
}

/**
 * @brief Enable a specific NVIC interrupt.
 * @param irq  i the interrupt to be enabled.
 */
void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

/**
 * @brief Disable a specific NVIC interrupt.
 * @param irq is the interrupt to be Disabled.
 */
void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}

/**
 * @brief Check if a Nvic interrupt is pending.
 * @param irq is the interrupt to check.
 * @retval IRQ_PENDING if the interrupt is pending, otherwise IRQ_NOT_PENDING.
 */
uint32 CDD_Nvic_GetPendingIrq( Nvic_IrqType irq )
{
    uint32 pending;
    if( ( ( (uint32)irq >= NVIC_MIN_IRQ ) ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        pending = Bfx_GetBit_u32u8_u8( &NVIC->ISPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
    else
    {
        pending = IRQ_NOT_PENDING;
    }
    return pending;
}

/**
 * @brief Set a Nvic interrupt as pending.
 * @param irq is the interrupt to set pending.
 */
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

/**
 * @brief Clears a specific pending interrupt 
 * @param irq is the interrupt to clear.
 */
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}
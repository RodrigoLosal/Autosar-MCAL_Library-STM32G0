/**
 * @file Nvic.c
 * @brief Complex Device Driver (CDD).
 *
 * Complex Nvic Driver controls the NVIC (Nested Vectored Interrupt Controller) functionality.
 * It  specifically controls the activation of interrupts in ARM microcontrollers via the NVIC
 * peripheral, providing functionalities including setting priorities, enabling/disabling
 * interrupts, and handling interrupt pending statuses.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Nvic.h"
#include "Bfx_32bits.h"

#define BIT_SHIFT( irq ) ( ( ( ( (uint32)( irq ) ) ) & 0x03UL ) * 8UL ) /*!< Calculate the bit shift for IRQ priority */
#define IP_IDX( irq )    ( ( ( (uint32)( irq ) ) >> 2UL ) )             /*!< Calculate the index for IRQ priority register */
#define NVIC_MIN_IRQ     16U                                            /*!< Minimum IQR value */
#define NVIC_MAX_IRQ     30U                                            /*!< Maximum IRQ value*/
#define IRQ_MASK         0x1FUL                                         /*!< Mask to obtain bits from an IRQ value */
#define FIRST_INDEX      0U                                             /*!< Starting index for NVIC register */
#define BYTE_MASK        0xFFU                                          /*!< Byte mask in 32-bit */
#define IRQ_PENDING      1UL                                            /*!< Value to specifie IRQ is pending */
#define IRQ_NOT_PENDING  0UL                                            /*!< Value to specifie IRQ is not pending */
#define INVALID_PRIORITY 0xFFU                                          /*!< Invalid priority indicator */

/**
 * @brief Sets the priority for a specific peripheral interrupt in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If valid, it utilizes the Bfx_PutBitsMask_u32u32u32 function
 * to update the NVIC's IP register with the desired priority.
 *
 * @param irq       Interrupt number to set.
 * @param priority  Priority value to assign to the interrupt.
 */
void CDD_Nvic_SetPriority( Nvic_IrqType irq, uint32 priority )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBitsMask_u32u32u32( &NVIC->IP[ IP_IDX( irq ) ], ( priority & BYTE_MASK ) << BIT_SHIFT( irq ), BYTE_MASK << BIT_SHIFT( irq ) );
    }
}

/**
 * @brief Return the priority of a specific peripheral interrupt from the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If the number is valid, it uses the Bfx_GetBits_u32u8u8_u32 function to
 * extract the priority from the NVIC's IP register. Otherwise, it returns an
 * INVALID_PRIORITY value.
 *
 * @param irq       Interrupt number whose priority is to be retrieved.
 *
 * @retval          Priority value of the interrupt. Returns INVALID_PRIORITY if the
 *                  interrupt number is not a valid peripheral interrupt.
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
 * @brief Enables a specific peripheral interrupt in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If the number is valid, it uses the Bfx_SetBit_u32u8 function
 * to enable the interrupt in the NVIC's ISER register.
 *
 * @param irq Interrupt number to be enabled.
 */
void CDD_Nvic_EnableIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

/**
 * @brief Disables a specific peripheral interrupt in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If the number is valid, it uses the Bfx_PutBit_u32u8u8 function
 * to disable the interrupt in the NVIC's ICER register.
 *
 * @param irq Interrupt number to be disabled.
 */
void CDD_Nvic_DisableIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICER[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}

/**
 * @brief Return the pending status of a specific peripheral interrupt in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If the number is valid, it uses the Bfx_GetBit_u32u8_u8 function to determine
 * if the interrupt is pending in the NVIC's ISPR register.
 *
 * @param irq Interrupt number whose pending status is to be checked.
 *
 * @return     Returns TRUE if the interrupt is pending, otherwise returns IRQ_NOT_PENDING.
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
 * @brief Sets a specific peripheral interrupt as pending in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's
 * peripherals. If the number is valid, it utilizes the Bfx_SetBit_u32u8 function
 * to set the interrupt as pending in the NVIC's ISPR register.
 *
 * @param irq Interrupt number to set as pending.
 */
void CDD_Nvic_SetPendingIrq( Nvic_IrqType irq )
{
    if( ( (uint32)irq >= NVIC_MIN_IRQ ) && ( (uint32)irq <= NVIC_MAX_IRQ ) )
    {
        Bfx_SetBit_u32u8( &NVIC->ISPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK );
    }
}

/**
 * @brief Clears the pending status of a specific peripheral interrupt in the NVIC.
 *
 * The function checks if the interrupt number belongs to the microcontroller's peripherals.
 * If the number is valid, it uses the Bfx_PutBit_u32u8u8 function to clear the
 * pending status of that interrupt in the NVIC's ICPR register.
 *
 * @param irq Interrupt number whose pending status is to be cleared.
 */
void CDD_Nvic_ClearPendingIrq( Nvic_IrqType irq )
{
    if( ( ( (uint32)( irq ) ) >= NVIC_MIN_IRQ ) && ( (uint32)( irq ) <= NVIC_MAX_IRQ ) )
    {
        Bfx_PutBit_u32u8u8( &NVIC->ICPR[ FIRST_INDEX ], ( (uint32)irq ) & IRQ_MASK, TRUE );
    }
}
/**
 * @file    Nvic_Lcfg.c
 * @brief   **Nvic Driver**
 * @author  Diego Perez
 *
 * This file contains the interrupt vector declaration for each of the entries in the vector table.
 * table. The vector table is located at the beginning of the program memory. The vector table is
 * initialized with the address of the interrupt service routine for each interruptm each vector
 * name can be found at file startup.c, user can add or remove vectors as needed.
 */

#include "Std_Types.h"
#include "Nvic_Cfg.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Nvic_Cfg.h */
#if NVIC_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief Non Maskable Interrupt Handler
 */
void NMI_Handler( void )
{
    Det_ReportError( NVIC_MODULE_ID, NVIC_INSTANCE_ID, NVIC_E_NMI_ENTRY, NVIC_ID_NMI_HANDLER );
}

/**
 * @brief Hard Fault Interrupt Handler
 */
void HardFault_Handler( void )
{
    Det_ReportError( NVIC_MODULE_ID, NVIC_INSTANCE_ID, NVIC_ID_SET_PRIORITY, NVIC_ID_HARDFAULT_HANDLER );
}

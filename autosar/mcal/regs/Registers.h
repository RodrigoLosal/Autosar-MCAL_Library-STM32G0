#ifndef REGISTERS_H
#define REGISTERS_H
#include "Platform_Types.h"

#define PERIPH_BASE 0x40000000UL /*!< Peripherals register base address*/

#define SCS_BASE  ( 0xE000E000UL )           /*!< System Control Space Base Address */
#define NVIC_BASE ( SCS_BASE + 0x0100UL )    /*!< NVIC Base Address */
#define NVIC      ( (NVIC_Type *)NVIC_BASE ) /*!< NVIC configuration struct */

typedef struct
{
    uint32 ISER[ 1U ]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32 RESERVED0[ 31U ];
    uint32 ICER[ 1U ]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32 RESERVED1[ 31U ];
    uint32 ISPR[ 1U ]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32 RESERVED2[ 31U ];
    uint32 ICPR[ 1U ]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32 RESERVED3[ 31U ];
    uint32 RESERVED4[ 64U ];
    uint32 IP[ 8U ]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_Type;

#endif

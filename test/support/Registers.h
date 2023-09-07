#ifndef REGISTERS_H__
#define REGISTERS_H__

#include "Std_Types.h"

/**
 * @brief  Struct for GPIO registers
 *
 */
typedef struct
{
    volatile uint32 MODER;   /*!< GPIO port mode register*/
    volatile uint32 OTYPER;  /*!< GPIO port output type register*/
    volatile uint32 OSPEEDR; /*!< GPIO port output speed register*/
    volatile uint32 PUPDR;   /*!< GPIO port pull-up/pull-down register*/
    volatile uint32 IDR;     /*!< GPIO port input data register*/
    volatile uint32 ODR;     /*!< GPIO port output data register*/
    volatile uint32 BSRR;    /*!< GPIO port bit set/reset register*/
    volatile uint32 LCKR;    /*!< GPIO port configuration lock register*/
    volatile uint32 AFRL;    /*!< GPIO alternate function low register*/
    volatile uint32 AFRH;    /*!< GPIO alternate function high register*/
    volatile uint32 BRR;     /*!< GPIO port bit reset register*/
} Port_RegisterType;

extern Port_RegisterType PORTA_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTB_BASE; /*!< GPIOB ADDRESS */
extern Port_RegisterType PORTC_BASE; /*!< GPIOC ADDRESS */
extern Port_RegisterType PORTD_BASE; /*!< GPIOD ADDRESS */
extern Port_RegisterType PORTE_BASE; /*!< GPIOE ADDRESS */
extern Port_RegisterType PORTF_BASE; /*!< GPIOF ADDRESS */

/**
 * @name    Register access
 *
 * Symbols to access the registers
/**@{*/
#define PORTA ( (Port_RegisterType *)&PORTA_BASE ) /*!< Access to PORTA registers*/
#define PORTB ( (Port_RegisterType *)&PORTB_BASE ) /*!< Access to PORTB registers*/
#define PORTC ( (Port_RegisterType *)&PORTC_BASE ) /*!< Access to PORTC registers*/
#define PORTD ( (Port_RegisterType *)&PORTD_BASE ) /*!< Access to PORTD registers*/
#define PORTE ( (Port_RegisterType *)&PORTE_BASE ) /*!< Access to PORTE registers*/
#define PORTF ( (Port_RegisterType *)&PORTF_BASE ) /*!< Access to PORTF registers*/
/**@}*/

#endif
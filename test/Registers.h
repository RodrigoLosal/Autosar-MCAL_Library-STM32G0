#ifndef REGISTERS_H__
#define REGISTERS_H__

#include "Std_Types.h"

/**
 * @name    Base_address
 *
 * Symbols to specify Base addresses of memories and buses
/**@{*/


/**@}*/

/**
 * @brief  Struct for RCC registers
 *
 */
typedef struct
{
    volatile uint32 CR;        /*!< RCC clock control register*/
    volatile uint32 ICSCR;     /*!< RCC internal clock sources calibration register*/
    volatile uint32 CFGR;      /*!< Clock configuration register*/
    volatile uint32 PLLCFGR;   /*!< PLL configuration register*/
    volatile uint32 Reserv;    /*!< Reserv memory space*/
    volatile uint32 CRRCR;     /*!< clock recovery RC register*/
    volatile uint32 CIER;      /*!< Clock interrupt enable register*/
    volatile uint32 CIFR;      /*!< Clock interrupt flag register*/
    volatile uint32 CICR;      /*!< Clock interrupt clear register*/
    volatile uint32 IOPRSTR;   /*!< I/O port reset register*/
    volatile uint32 AHBRSTR;   /*!< AHB peripheral reset register*/
    volatile uint32 APBRSTR1;  /*!< APB1 peripheral reset register*/
    volatile uint32 APBRSTR2;  /*!< APB2 peripheral reset register*/
    volatile uint32 IOPENR;    /*!< I/O port clock enable register*/
    volatile uint32 AHBENR;    /*!< AHB peripheral clock enable register*/
    volatile uint32 APBENR1;   /*!< APB1 peripheral clock enable register */
    volatile uint32 APBENR2;   /*!< APB2 peripheral clock enable register */
    volatile uint32 IOPSMENR;  /*!< I/O port in Sleep mode clock enable register*/
    volatile uint32 AHBSMENR;  /*!< AHB peripheral clock enable in sleep/stop mode register*/
    volatile uint32 APBSMENR1; /*!< APB1 peripheral clock enable in Sleep/stop mode register */
    volatile uint32 APBSMENR2; /*!< APB2 peripheral clock enable in Sleep/stop mode register*/
    volatile uint32 CCIPR;     /*!< Peripherals independent clock configuration register*/
    volatile uint32 CCIPR2;    /*!< Peripherals independent clock configuration register 2*/
    volatile uint32 BDCR;      /*!< RTC domain control register*/
    volatile uint32 CSR;       /*!< control/status register*/

} RCC_RegisterType;

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

/**
 * @brief  Struct for DIO registers
 *
 */
typedef struct
{
    volatile uint32 Reverved[ 4 ];  /*!< reserved memory*/
    volatile uint32 IDR;            /*!< GPIO port input data register*/
    volatile uint32 ODR;            /*!< GPIO port output data register*/
    volatile uint32 BSRR;           /*!< GPIO port bit set/reset register*/
    volatile uint32 Reverved2[ 3 ]; /*!< reserved memory*/
    volatile uint32 BRR;            /*!< GPIO port bit reset register*/
} Dio_RegisterType;

extern Port_RegisterType PORTA_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTB_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTC_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTD_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTE_BASE; /*!< GPIOA ADDRESS */
extern Port_RegisterType PORTF_BASE; /*!< GPIOA ADDRESS */

extern Dio_RegisterType DIOA_BASE;
extern Dio_RegisterType DIOB_BASE;
extern Dio_RegisterType DIOC_BASE;
extern Dio_RegisterType DIOD_BASE;
extern Dio_RegisterType DIOE_BASE;
extern Dio_RegisterType DIOF_BASE;


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
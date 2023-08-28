#ifndef REGISTERS_H__
#define REGISTERS_H__

#include "Std_Types.h"

#define FLASH_BASE_ADDRESS  0x08000000                           /*!< FLASH ADDRESS */
#define SRAM_BASE_ADDRESS   0x20000000                           /*!< SRAM ADDRESS */
#define PERIPH_BASE_ADDRESS 0x40000000                           /*!< PREIPH ADDRESS */
#define APB1_BASE_ADDRESS   ( PERIPH_BASE_ADDRESS + 0x00000000 ) /*!< APB1 ADDRESS */
#define APB2_BASE_ADDRESS   ( PERIPH_BASE_ADDRESS + 0x00010000 ) /*!< APB2 ADDRESS */
#define AHB_BASE_ADDRESS    ( PERIPH_BASE_ADDRESS + 0x00020000 ) /*!< AHB ADDRESS */
#define RCC_BASE_ADDRESS    0x40021000                           /*!< RCC ADDRESS */
#define IOPORT_BASE         0x50000000                           /*!< IOPORT ADDRESS */
#define PORTA_BASE          ( IOPORT_BASE + 0x00000000UL )       /*!< GPIOA ADDRESS */
#define PORTB_BASE          ( IOPORT_BASE + 0x00000400UL )       /*!< GPIOB ADDRESS */
#define PORTC_BASE          ( IOPORT_BASE + 0x00000800UL )       /*!< GPIOC ADDRESS */
#define PORTD_BASE          ( IOPORT_BASE + 0x00000C00UL )       /*!< GPIOD ADDRESS */
#define PORTE_BASE          ( IOPORT_BASE + 0x00001000UL )       /*!< GPIOE ADDRESS */
#define PORTF_BASE          ( IOPORT_BASE + 0x00001400UL )       /*!< GPIOF ADDRESS */

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
} Rcc_RegisterType;


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


#define PORTA                ( (Port_RegisterType *)PORTA_BASE )      /*!< Access to PORTA registers*/
#define PORTB                ( (Port_RegisterType *)PORTB_BASE )      /*!< Access to PORTB registers*/
#define PORTC                ( (Port_RegisterType *)PORTC_BASE )      /*!< Access to PORTC registers*/
#define PORTD                ( (Port_RegisterType *)PORTD_BASE )      /*!< Access to PORTD registers*/
#define PORTE                ( (Port_RegisterType *)PORTE_BASE )      /*!< Access to PORTE registers*/
#define PORTF                ( (Port_RegisterType *)PORTF_BASE )      /*!< Access to PORTF registers*/
#define RCC                  ( (RCC_RegisterType *)RCC_BASE_ADDRESS ) /*!< Access to RCC registers*/

#define RCC_GPIOA_CLK_EN( )  RCC->IOPENR |= 0x01u; /*!< GPIO PORTA clock enable*/
#define RCC_GPIOB_CLK_EN( )  RCC->IOPENR |= 0x02u; /*!< GPIO PORTB clock enable*/
#define RCC_GPIOC_CLK_EN( )  RCC->IOPENR |= 0x04u; /*!< GPIO PORTC clock enable*/
#define RCC_GPIOD_CLK_EN( )  RCC->IOPENR |= 0x08u; /*!< GPIO PORTD clock enable*/
#define RCC_GPIOE_CLK_EN( )  RCC->IOPENR |= 0x10u; /*!< GPIO PORTE clock enable*/
#define RCC_GPIOF_CLK_EN( )  RCC->IOPENR |= 0x20u; /*!< GPIO PORTF clock enable*/

#define RCC_GPIOA_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 0u ); /*!< GPIO PORTA clock disable*/
#define RCC_GPIOB_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 1u ); /*!< GPIO PORTB clock disable*/
#define RCC_GPIOC_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 2u ); /*!< GPIO PORTC clock disable*/
#define RCC_GPIOD_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 3u ); /*!< GPIO PORTD clock disable*/
#define RCC_GPIOE_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 4u ); /*!< GPIO PORTE clock disable*/
#define RCC_GPIOF_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 5u ); /*!< GPIO PORTF clock disable*/
/**@}*/

#endif
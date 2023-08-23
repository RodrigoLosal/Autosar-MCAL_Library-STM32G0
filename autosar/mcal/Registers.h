

#ifndef REGISTERS_H
#define REGISTERS_H
#include "Platform_Types.h"

#define PERIPH_BASE 0x40000000UL /*!< Peripherals register base address*/
#define IOPORT_BASE 0x50000000UL /*!< IOPORT register base address*/


typedef struct
{
    volatile uint32 MODER;
    volatile uint32 OTYPER;
    volatile uint32 OSPEEDR;
    volatile uint32 PUPDR;
    volatile uint32 IDR;
    volatile uint32 ODR;
    volatile uint32 BSRR;
    volatile uint32 LCKR;
    volatile uint32 AFRL;
    volatile uint32 AFRH;
    volatile uint32 BRR;
} GPIO_RegisterTypeDef;

#define GPIOA_BASE     ( IOPORT_BASE + 0x00000000UL )
#define GPIOB_BASE     ( IOPORT_BASE + 0x00000400UL )
#define GPIOC_BASE     ( IOPORT_BASE + 0x00000800UL )
#define GPIOD_BASE     ( IOPORT_BASE + 0x00000C00UL )
#define GPIOE_BASE     ( IOPORT_BASE + 0x00001000UL )
#define GPIOF_BASE     ( IOPORT_BASE + 0x00001400UL )

#define AHBPERIPH_BASE ( PERIPH_BASE + 0x00020000UL )
#define APBPERIPH_BASE ( PERIPH_BASE + 0x00010000UL )
#define RCC_BASE       ( AHBPERIPH_BASE + 0x00001000UL )

typedef struct
{
    volatile uint32 CR;
    volatile uint32 ICSCR;
    volatile uint32 CFGR;
    volatile uint32 PLL;
    volatile uint32 CRRCR;
    volatile uint32 CIER;
    volatile uint32 CIFR;
    volatile uint32 CICR;
    volatile uint32 IOPRSTR;
    volatile uint32 AHBRSTR;
    volatile uint32 APBRSTR1;
    volatile uint32 APBRSTR2;
    volatile uint32 IOPENR;
    volatile uint32 AHBENR;
    volatile uint32 APBENR1;
    volatile uint32 APBENR2;
    volatile uint32 IOPSMENR;
    volatile uint32 AHBSMENR;
    volatile uint32 APBSMENR1;
    volatile uint32 APBSMENR2;
    volatile uint32 CCIPR;
    volatile uint32 CCIPR2;
    volatile uint32 BDCR;
    volatile uint32 CSR;
} RCC_RegisterTypeDef;


#define GPIOA                    ( (GPIO_RegisterTypeDef *)GPIOA_BASE )
#define GPIOB                    ( (GPIO_RegisterTypeDef *)GPIOB_BASE )
#define GPIOC                    ( (GPIO_RegisterTypeDef *)GPIOC_BASE )
#define GPIOD                    ( (GPIO_RegisterTypeDef *)GPIOD_BASE )
#define GPIOE                    ( (GPIO_RegisterTypeDef *)GPIOE_BASE )
#define GPIOF                    ( (GPIO_RegisterTypeDef *)GPIOF_BASE )


#define RCC                      ( (RCC_RegisterTypeDef *)RCC_BASE )

#define RCC_GPIOA_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 0 ) )
#define RCC_GPIOA_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 0 ) )
#define RCC_GPIOB_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 1 ) )
#define RCC_GPIOB_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 1 ) )
#define RCC_GPIOC_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 2 ) )
#define RCC_GPIOC_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 2 ) )
#define RCC_GPIOD_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 3 ) )
#define RCC_GPIOD_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 3 ) )
#define RCC_GPIOE_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 4 ) )
#define RCC_GPIOE_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 4 ) )
#define RCC_GPIOF_CLK_EN( )      ( RCC->IOPENR |= ( 1 << 5 ) )
#define RCC_GPIOF_CLK_DIS( )     ( RCC->IOPENR &= ~( 1 << 5 ) )


#define RCC_TIM7_CLK_DIS( )      ( RCC->APBSMENR1 &= ~( 1 << 5 ) )
#define RCC_TIM7_CLK_EN( )       ( RCC->APBSMENR1 |= ( 1 << 5 ) )


#define SCS_BASE                 ( 0xE000E000UL )           /*!< System Control Space Base Address */
#define NVIC_BASE                ( SCS_BASE + 0x0100UL )    /*!< NVIC Base Address */
#define NVIC                     ( (NVIC_Type *)NVIC_BASE ) /*!< NVIC configuration struct */

#define RCC_APBENR1_TIM7EN_Pos   ( 5U )
#define RCC_APBENR1_TIM7EN_Msk   ( 0x1UL << RCC_APBENR1_TIM7EN_Pos ) /*!< 0x00000020 */
#define RCC_APBENR1_TIM7EN       RCC_APBENR1_TIM7EN_Msk

#define RCC_APBRSTR1_TIM7RST_Pos ( 5U )
#define RCC_APBRSTR1_TIM7RST_Msk ( 0x1UL << RCC_APBRSTR1_TIM7RST_Pos ) /*!< 0x00000020 */
#define RCC_APBRSTR1_TIM7RST     RCC_APBRSTR1_TIM7RST_Msk


/**
 * @brief TIM
 */
typedef struct
{
    volatile uint32 CR1;   /*!< TIM control register 1,                   Address offset: 0x00 */
    volatile uint32 CR2;   /*!< TIM control register 2,                   Address offset: 0x04 */
    volatile uint32 SMCR;  /*!< TIM slave mode control register,          Address offset: 0x08 */
    volatile uint32 DIER;  /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
    volatile uint32 SR;    /*!< TIM status register,                      Address offset: 0x10 */
    volatile uint32 EGR;   /*!< TIM event generation register,            Address offset: 0x14 */
    volatile uint32 CCMR1; /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
    volatile uint32 CCMR2; /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
    volatile uint32 CCER;  /*!< TIM capture/compare enable register,      Address offset: 0x20 */
    volatile uint32 CNT;   /*!< TIM counter register,                     Address offset: 0x24 */
    volatile uint32 PSC;   /*!< TIM prescaler register,                   Address offset: 0x28 */
    volatile uint32 ARR;   /*!< TIM auto-reload register,                 Address offset: 0x2C */
    volatile uint32 RCR;   /*!< TIM repetition counter register,          Address offset: 0x30 */
    volatile uint32 CCR1;  /*!< TIM capture/compare register 1,           Address offset: 0x34 */
    volatile uint32 CCR2;  /*!< TIM capture/compare register 2,           Address offset: 0x38 */
    volatile uint32 CCR3;  /*!< TIM capture/compare register 3,           Address offset: 0x3C */
    volatile uint32 CCR4;  /*!< TIM capture/compare register 4,           Address offset: 0x40 */
    volatile uint32 BDTR;  /*!< TIM break and dead-time register,         Address offset: 0x44 */
    volatile uint32 DCR;   /*!< TIM DMA control register,                 Address offset: 0x48 */
    volatile uint32 DMAR;  /*!< TIM DMA address for full transfer,        Address offset: 0x4C */
    volatile uint32 OR1;   /*!< TIM option register,                      Address offset: 0x50 */
    volatile uint32 CCMR3; /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
    volatile uint32 CCR5;  /*!< TIM capture/compare register5,            Address offset: 0x58 */
    volatile uint32 CCR6;  /*!< TIM capture/compare register6,            Address offset: 0x5C */
    volatile uint32 AF1;   /*!< TIM alternate function register 1,        Address offset: 0x60 */
    volatile uint32 AF2;   /*!< TIM alternate function register 2,        Address offset: 0x64 */
    volatile uint32 TISEL; /*!< TIM Input Selection register,             Address offset: 0x68 */
} TIM_TypeDef;


#define TIM7_BASE ( APBPERIPH_BASE + 0x00001400UL )
#define TIM7      ( (TIM_TypeDef *)TIM7_BASE )

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
    uint32 ISER[ 1U ]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32 ICER[ 1U ]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32 ISPR[ 1U ]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32 ICPR[ 1U ]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32 IP[ 8U ];   /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_Type;

#endif

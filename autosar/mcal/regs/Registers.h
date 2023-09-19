/**
 * @file        Registers.h
 * @brief       This file contains definitions and configurations for the NVIC.
 *
 * This file defines addresses, interrupts, and NVIC structures for Cortex-M0+.
 */
#ifndef REGISTERS_H
#define REGISTERS_H

/**
 * @name    Base address values
 * Symbols to specify the Base values of the registers.
 */
/**@{*/
#define PERIPH_BASE        0x40000000UL                       /*!< Peripherals register base address*/
#define FLASH_BASE_ADDRESS 0x08000000                         /*!< FLASH ADDRESS */
#define SRAM_BASE_ADDRESS  0x20000000                         /*!< SRAM ADDRESS */
#define APB1_BASE_ADDRESS  ( PERIPH_BASE + 0x00000000 )       /*!< APB1 ADDRESS */
#define APB2_BASE_ADDRESS  ( PERIPH_BASE + 0x00010000 )       /*!< APB2 ADDRESS */
#define AHB_BASE_ADDRESS   ( PERIPH_BASE + 0x00020000 )       /*!< AHB ADDRESS */
#define RCC_BASE_ADDRESS   0x40021000                         /*!< RCC ADDRESS */
#define IOPORT_BASE        0x50000000                         /*!< IOPORT ADDRESS */
#define PORTA_BASE         ( IOPORT_BASE + 0x00000000UL )     /*!< GPIOA ADDRESS */
#define PORTB_BASE         ( IOPORT_BASE + 0x00000400UL )     /*!< GPIOB ADDRESS */
#define PORTC_BASE         ( IOPORT_BASE + 0x00000800UL )     /*!< GPIOC ADDRESS */
#define PORTD_BASE         ( IOPORT_BASE + 0x00000C00UL )     /*!< GPIOD ADDRESS */
#define PORTE_BASE         ( IOPORT_BASE + 0x00001000UL )     /*!< GPIOE ADDRESS */
#define PORTF_BASE         ( IOPORT_BASE + 0x00001400UL )     /*!< GPIOF ADDRESS */
#define SCS_BASE           ( 0xE000E000UL )                   /*!< System Control Space Base Address */
#define NVIC_BASE          ( SCS_BASE + 0x0100UL )            /*!< NVIC Base Address */
#define NVIC               ( (Nvic_RegisterType *)NVIC_BASE ) /*!< NVIC configuration struct */
/**@}*/

/**
 * @brief RCC registers struct.
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
} Rcc_RegisterType;

/**
 * @brief GPIOS registers struct.
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


typedef struct
{
    volatile uint32 Reserved1[ 4 ];
    volatile uint32 IDR;
    volatile uint32 ODR;
    volatile uint32 BSRR;
    volatile uint32 Reserved2[ 3 ];
    volatile uint32 BRR;
} Dio_RegisterType;

/**
  * @defgroup  Struct casting to base address of the PORTS and RCC
  @{ */
#define PORTA                ( (Port_RegisterType *)PORTA_BASE )      /*!< Access to PORTA registers*/
#define PORTB                ( (Port_RegisterType *)PORTB_BASE )      /*!< Access to PORTB registers*/
#define PORTC                ( (Port_RegisterType *)PORTC_BASE )      /*!< Access to PORTC registers*/
#define PORTD                ( (Port_RegisterType *)PORTD_BASE )      /*!< Access to PORTD registers*/
#define PORTE                ( (Port_RegisterType *)PORTE_BASE )      /*!< Access to PORTE registers*/
#define PORTF                ( (Port_RegisterType *)PORTF_BASE )      /*!< Access to PORTF registers*/
#define RCC                  ( (RCC_RegisterType *)RCC_BASE_ADDRESS ) /*!< Access to RCC registers*/
/**@}*/

#define DIOA                 ( (Dio_RegisterType *)PORTA_BASE )
#define DIOB                 ( (Dio_RegisterType *)PORTB_BASE )
#define DIOC                 ( (Dio_RegisterType *)PORTC_BASE )
#define DIOD                 ( (Dio_RegisterType *)PORTD_BASE )
#define DIOE                 ( (Dio_RegisterType *)PORTE_BASE )
#define DIOF                 ( (Dio_RegisterType *)PORTF_BASE )


/**
  * @defgroup Clock-eneable of different ports
  @{ */
#define RCC_GPIOA_CLK_EN( )  RCC->IOPENR |= 0x01u; /*!< GPIO PORTA clock enable*/
#define RCC_GPIOB_CLK_EN( )  RCC->IOPENR |= 0x02u; /*!< GPIO PORTB clock enable*/
#define RCC_GPIOC_CLK_EN( )  RCC->IOPENR |= 0x04u; /*!< GPIO PORTC clock enable*/
#define RCC_GPIOD_CLK_EN( )  RCC->IOPENR |= 0x08u; /*!< GPIO PORTD clock enable*/
#define RCC_GPIOE_CLK_EN( )  RCC->IOPENR |= 0x10u; /*!< GPIO PORTE clock enable*/
#define RCC_GPIOF_CLK_EN( )  RCC->IOPENR |= 0x20u; /*!< GPIO PORTF clock enable*/
/**@}*/

/**
  * @defgroup Clock-disable of different ports
  @{ */
#define RCC_GPIOA_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 0u ); /*!< GPIO PORTA clock disable*/
#define RCC_GPIOB_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 1u ); /*!< GPIO PORTB clock disable*/
#define RCC_GPIOC_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 2u ); /*!< GPIO PORTC clock disable*/
#define RCC_GPIOD_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 3u ); /*!< GPIO PORTD clock disable*/
#define RCC_GPIOE_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 4u ); /*!< GPIO PORTE clock disable*/
#define RCC_GPIOF_CLK_DIS( ) RCC->IOPENR &= ~( 1u << 5u ); /*!< GPIO PORTF clock disable*/
/**@}*/

/**
 * @brief Nested Vectored Interrupt Controller (NVIC) interrupt types for Cortex-M0+ and STM32G0xxxx.
 *  This enumeration lists the Cortex-M0+ exceptions and STM32G0xxxx microcontroller interrupts
 */
typedef enum
{
    /******  Cortex-M0+ Processor Exceptions Numbers ***************************************************************/
    NonMaskableInt_IRQn = -14,                   /*!< 2 Non Maskable Interrupt                                          */
    HardFault_IRQn      = -13,                   /*!< 3 Cortex-M Hard Fault Interrupt                                   */
    SVCall_IRQn         = -5,                    /*!< 11 Cortex-M SV Call Interrupt                                     */
    PendSV_IRQn         = -2,                    /*!< 14 Cortex-M Pend SV Interrupt                                     */
    SysTick_IRQn        = -1,                    /*!< 15 Cortex-M System Tick Interrupt                                 */
                                                 /******  STM32G0xxxx specific Interrupt Numbers ****************************************************************/
    WWDG_IRQn                              = 0,  /*!< Window WatchDog Interrupt                                         */
    PVD_VDDIO2_IRQn                        = 1,  /*!< PVD through EXTI line 16, PVM (monit. VDDIO2) through EXTI line 34*/
    RTC_TAMP_IRQn                          = 2,  /*!< RTC interrupt through the EXTI line 19 & 21                       */
    FLASH_IRQn                             = 3,  /*!< FLASH global Interrupt                                            */
    RCC_CRS_IRQn                           = 4,  /*!< RCC and CRS global Interrupt                                      */
    EXTI0_1_IRQn                           = 5,  /*!< EXTI 0 and 1 Interrupts                                           */
    EXTI2_3_IRQn                           = 6,  /*!< EXTI Line 2 and 3 Interrupts                                      */
    EXTI4_15_IRQn                          = 7,  /*!< EXTI Line 4 to 15 Interrupts                                      */
    USB_UCPD1_2_IRQn                       = 8,  /*!< USB, UCPD1 and UCPD2 global Interrupt                             */
    DMA1_Channel1_IRQn                     = 9,  /*!< DMA1 Channel 1 Interrupt                                          */
    DMA1_Channel2_3_IRQn                   = 10, /*!< DMA1 Channel 2 and Channel 3 Interrupts                           */
    DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn = 11, /*!< DMA1 Ch4 to Ch7, DMA2 Ch1 to Ch5 and DMAMUX1 Overrun Interrupts */
    ADC1_COMP_IRQn                         = 12, /*!< ADC1, COMP1,COMP2, COMP3 Interrupts (combined with EXTI 17 & 18)  */
    TIM1_BRK_UP_TRG_COM_IRQn               = 13, /*!< TIM1 Break, Update, Trigger and Commutation Interrupts            */
    TIM1_CC_IRQn                           = 14, /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn                              = 15, /*!< TIM2 Interrupt                                                    */
    TIM3_TIM4_IRQn                         = 16, /*!< TIM3, TIM4 global Interrupt                                       */
    TIM6_DAC_LPTIM1_IRQn                   = 17, /*!< TIM6, DAC and LPTIM1 global Interrupts                            */
    TIM7_LPTIM2_IRQn                       = 18, /*!< TIM7 and LPTIM2 global Interrupt                                  */
    TIM14_IRQn                             = 19, /*!< TIM14 global Interrupt                                            */
    TIM15_IRQn                             = 20, /*!< TIM15 global Interrupt                                            */
    TIM16_FDCAN_IT0_IRQn                   = 21, /*!< TIM16, FDCAN1_IT0 and FDCAN2_IT0 Interrupt                        */
    TIM17_FDCAN_IT1_IRQn                   = 22, /*!< TIM17, FDCAN1_IT1 and FDCAN2_IT1 Interrupt                        */
    I2C1_IRQn                              = 23, /*!< I2C1 Interrupt  (combined with EXTI 23)                           */
    I2C2_3_IRQn                            = 24, /*!< I2C2, I2C3 Interrupt (combined with EXTI 24 and EXTI 22)          */
    SPI1_IRQn                              = 25, /*!< SPI1/I2S1 Interrupt                                               */
    SPI2_3_IRQn                            = 26, /*!< SPI2/I2S2, SPI3/I2S3 Interrupt                                    */
    USART1_IRQn                            = 27, /*!< USART1 Interrupt                                                  */
    USART2_LPUART2_IRQn                    = 28, /*!< USART2 + LPUART2 Interrupt                                        */
    USART3_4_5_6_LPUART1_IRQn              = 29, /*!< USART3, USART4, USART5, USART6, LPUART1 globlal Interrupts (combined with EXTI 28) */
    CEC_IRQn                               = 30, /*!< CEC Interrupt(combined with EXTI 27)                               */
} Nvic_IrqType;

/**
 * @brief Nested Vectored Interrupt Controller (NVIC) structure.
 */
typedef struct
{
    uint32 ISER[ 1U ];       /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32 RESERVED0[ 31U ]; /*!< Reserved memory. */
    uint32 ICER[ 1U ];       /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32 RESERVED1[ 31U ]; /*!< Reserved memory. */
    uint32 ISPR[ 1U ];       /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32 RESERVED2[ 31U ]; /*!< Reserved memory. */
    uint32 ICPR[ 1U ];       /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32 RESERVED3[ 31U ]; /*!< Reserved memory. */
    uint32 RESERVED4[ 64U ]; /*!< Reserved memory. */
    uint32 IP[ 8U ];         /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} Nvic_RegisterType;

#endif

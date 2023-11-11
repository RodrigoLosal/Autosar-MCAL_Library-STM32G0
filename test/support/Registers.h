/**
 * @file        Registers.h
 * @brief       This file contains definitions and configurations for the NVIC.
 *
 * This file defines simulated addresses, interrupts, and NVIC structures for Cortex-M0+.
 */
#ifndef REGISTERS_H__
#define REGISTERS_H__

#include "Std_Types.h"

typedef enum
{
    /******  Cortex-M0+ Processor Exceptions Numbers ***************************************************************/
    NonMaskableInt_IRQn = -14,                   /*!< 2 Non Maskable Interrupt                                          */
    HardFault_IRQn      = -13,                   /*!< 3 Cortex-M Hard Fault Interrupt                                   */
    SVCall_IRQn         = -5,                    /*!< 11 Cortex-M SV Call Interrupt                                     */
    PendSV_IRQn         = -2,                    /*!< 14 Cortex-M Pend SV Interrupt                                     */
    SysTick_IRQn        = -1,                    /*!< 15 Cortex-M System Tick Interrupt                                 */
                                                 /******  STM32G0xxxx specific Interrupt Numbers ************************/
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
 * @brief  Struct for PORT registers
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
  * @defgroup  Port_pointers_address PORT Base Address
  @{ */
#define PORTA ( (Port_RegisterType *)&PORTA_BASE ) /*!< Access to PORTA registers*/
#define PORTB ( (Port_RegisterType *)&PORTB_BASE ) /*!< Access to PORTB registers*/
#define PORTC ( (Port_RegisterType *)&PORTC_BASE ) /*!< Access to PORTC registers*/
#define PORTD ( (Port_RegisterType *)&PORTD_BASE ) /*!< Access to PORTD registers*/
#define PORTE ( (Port_RegisterType *)&PORTE_BASE ) /*!< Access to PORTE registers*/
#define PORTF ( (Port_RegisterType *)&PORTF_BASE ) /*!< Access to PORTF registers*/
/**
 * @} */

/**
 * @brief  Struct for DIO registers
 */
typedef struct
{
    volatile uint32 Reserved1[ 4 ]; /*!< Reserved memory. */
    volatile uint32 IDR;            /*!< GPIO port input data register*/
    volatile uint32 ODR;            /*!< GPIO port output data register*/
    volatile uint32 BSRR;           /*!< GPIO port bit set/reset register*/
    volatile uint32 Reserved2[ 3 ]; /*!< Reserved memory. */
    volatile uint32 BRR;            /*!< GPIO port bit reset register*/
} Dio_RegisterType;

/**
 * @defgroup  Dio_references References for DIO registers
 */
extern Dio_RegisterType DIOA_BASE; /*!< GPIOA Reference */
extern Dio_RegisterType DIOB_BASE; /*!< GPIOB Reference */
extern Dio_RegisterType DIOC_BASE; /*!< GPIOC Reference */
extern Dio_RegisterType DIOD_BASE; /*!< GPIOD Reference */
extern Dio_RegisterType DIOE_BASE; /*!< GPIOE Reference */
extern Dio_RegisterType DIOF_BASE; /*!< GPIOF Reference */
/**
 * @} */

/**
  * @defgroup  Dio_pointers_address DIO Base Address
  @{ */
#define DIOA ( (Dio_RegisterType *)&DIOA_BASE )
#define DIOB ( (Dio_RegisterType *)&DIOB_BASE )
#define DIOC ( (Dio_RegisterType *)&DIOC_BASE )
#define DIOD ( (Dio_RegisterType *)&DIOD_BASE )
#define DIOE ( (Dio_RegisterType *)&DIOE_BASE )
#define DIOF ( (Dio_RegisterType *)&DIOF_BASE )
/**
 * @} */

/**
 * @brief Nested Vectored Interrupt Controller (NVIC) structure.
 */
typedef struct
{
    volatile uint32 ISER[ 1U ];       /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    volatile uint32 RESERVED0[ 31U ]; /*!< Reserved memory. */
    volatile uint32 ICER[ 1U ];       /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    volatile uint32 RESERVED1[ 31U ]; /*!< Reserved memory. */
    volatile uint32 ISPR[ 1U ];       /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    volatile uint32 RESERVED2[ 31U ]; /*!< Reserved memory. */
    volatile uint32 ICPR[ 1U ];       /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    volatile uint32 RESERVED3[ 31U ]; /*!< Reserved memory. */
    volatile uint32 RESERVED4[ 64U ]; /*!< Reserved memory. */
    volatile uint32 IP[ 8U ];         /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} Nvic_RegisterType;

extern Nvic_RegisterType NVIC_BASE; /* NVIC ADDRESS */

#define NVIC ( (Nvic_RegisterType *)&NVIC_BASE ) /*!< Access to NVIC registers*/

/**
 * @brief CAN Controller Area Network
 */
typedef struct
{
    volatile uint32 CREL;   /*!< FDCAN Core Release register,                                     Address offset: 0x000 */
    volatile uint32 ENDN;   /*!< FDCAN Endian register,                                           Address offset: 0x004 */
    uint32 RESERVED1;       /*!< Reserved,                                                                        0x008 */
    volatile uint32 DBTP;   /*!< FDCAN Data Bit Timing & Prescaler register,                      Address offset: 0x00C */
    volatile uint32 TEST;   /*!< FDCAN Test register,                                             Address offset: 0x010 */
    volatile uint32 RWD;    /*!< FDCAN RAM Watchdog register,                                     Address offset: 0x014 */
    volatile uint32 CCCR;   /*!< FDCAN CC Control register,                                       Address offset: 0x018 */
    volatile uint32 NBTP;   /*!< FDCAN Nominal Bit Timing & Prescaler register,                   Address offset: 0x01C */
    volatile uint32 TSCC;   /*!< FDCAN Timestamp Counter Configuration register,                  Address offset: 0x020 */
    volatile uint32 TSCV;   /*!< FDCAN Timestamp Counter Value register,                          Address offset: 0x024 */
    volatile uint32 TOCC;   /*!< FDCAN Timeout Counter Configuration register,                    Address offset: 0x028 */
    volatile uint32 TOCV;   /*!< FDCAN Timeout Counter Value register,                            Address offset: 0x02C */
    uint32 RESERVED2[ 4 ];  /*!< Reserved,                                                                0x030 - 0x03C */
    volatile uint32 ECR;    /*!< FDCAN Error Counter register,                                    Address offset: 0x040 */
    volatile uint32 PSR;    /*!< FDCAN Protocol Status register,                                  Address offset: 0x044 */
    volatile uint32 TDCR;   /*!< FDCAN Transmitter Delay Compensation register,                   Address offset: 0x048 */
    uint32 RESERVED3;       /*!< Reserved,                                                                        0x04C */
    volatile uint32 IR;     /*!< FDCAN Interrupt register,                                        Address offset: 0x050 */
    volatile uint32 IE;     /*!< FDCAN Interrupt Enable register,                                 Address offset: 0x054 */
    volatile uint32 ILS;    /*!< FDCAN Interrupt Line Select register,                            Address offset: 0x058 */
    volatile uint32 ILE;    /*!< FDCAN Interrupt Line Enable register,                            Address offset: 0x05C */
    uint32 RESERVED4[ 8 ];  /*!< Reserved,                                                                0x060 - 0x07C */
    volatile uint32 RXGFC;  /*!< FDCAN Global Filter Configuration register,                      Address offset: 0x080 */
    volatile uint32 XIDAM;  /*!< FDCAN Extended ID AND Mask register,                             Address offset: 0x084 */
    volatile uint32 HPMS;   /*!< FDCAN High Priority Message Status register,                     Address offset: 0x088 */
    uint32 RESERVED5;       /*!< Reserved,                                                                        0x08C */
    volatile uint32 RXF0S;  /*!< FDCAN Rx FIFO 0 Status register,                                 Address offset: 0x090 */
    volatile uint32 RXF0A;  /*!< FDCAN Rx FIFO 0 Acknowledge register,                            Address offset: 0x094 */
    volatile uint32 RXF1S;  /*!< FDCAN Rx FIFO 1 Status register,                                 Address offset: 0x098 */
    volatile uint32 RXF1A;  /*!< FDCAN Rx FIFO 1 Acknowledge register,                            Address offset: 0x09C */
    uint32 RESERVED6[ 8 ];  /*!< Reserved,                                                                0x0A0 - 0x0BC */
    volatile uint32 TXBC;   /*!< FDCAN Tx Buffer Configuration register,                          Address offset: 0x0C0 */
    volatile uint32 TXFQS;  /*!< FDCAN Tx FIFO/Queue Status register,                             Address offset: 0x0C4 */
    volatile uint32 TXBRP;  /*!< FDCAN Tx Buffer Request Pending register,                        Address offset: 0x0C8 */
    volatile uint32 TXBAR;  /*!< FDCAN Tx Buffer Add Request register,                            Address offset: 0x0CC */
    volatile uint32 TXBCR;  /*!< FDCAN Tx Buffer Cancellation Request register,                   Address offset: 0x0D0 */
    volatile uint32 TXBTO;  /*!< FDCAN Tx Buffer Transmission Occurred register,                  Address offset: 0x0D4 */
    volatile uint32 TXBCF;  /*!< FDCAN Tx Buffer Cancellation Finished register,                  Address offset: 0x0D8 */
    volatile uint32 TXBTIE; /*!< FDCAN Tx Buffer Transmission Interrupt Enable register,          Address offset: 0x0DC */
    volatile uint32 TXBCIE; /*!< FDCAN Tx Buffer Cancellation Finished Interrupt Enable register, Address offset: 0x0E0 */
    volatile uint32 TXEFS;  /*!< FDCAN Tx Event FIFO Status register,                             Address offset: 0x0E4 */
    volatile uint32 TXEFA;  /*!< FDCAN Tx Event FIFO Acknowledge register,                        Address offset: 0x0E8 */
    uint32 RESERVED7[ 5 ];  /*!< Reserved,                                                                0x0EC - 0x0FC */
    volatile uint32 CKDIV;  /*!< FDCAN clock divider register,                                     Address offset: 0x100 */
} Can_RegisterType;

extern Can_RegisterType CAN1_BASE; /*!< CAN1 Base Address */
extern Can_RegisterType CAN2_BASE; /*!< CAN2 Base Address */

#define CAN1 ( (Can_RegisterType *)&CAN1_BASE ) /*!< Access to CAN1 Registers */
#define CAN2 ( (Can_RegisterType *)&CAN2_BASE ) /*!< Access to CAN2 Registers */

/**
 * @brief SRAM CAN for Hardware objects
 */
typedef struct
{
    volatile uint32 FLSSA[ 28 ]; /*!< Standart filters*/
    volatile uint32 FLESA[ 16 ]; /*!< Extended filters*/
    volatile uint32 F0SA[ 54 ];  /*!< Reception FIFO 0*/
    volatile uint32 F1SA[ 54 ];  /*!< Reception FIFO 1*/
    volatile uint32 EFSA[ 6 ];   /*!< Event FIFO*/
    volatile uint32 TBSA[ 54 ];  /*!< Transmission buffer*/
} SramCan_RegisterType;

extern SramCan_RegisterType SRAMCAN1_BASE; /*!< SRAM CAN1 Base Address */
extern SramCan_RegisterType SRAMCAN2_BASE; /*!< SRAM CAN2 Base Address */

#define SRAMCAN1 ( (SramCan_RegisterType *)&SRAMCAN1_BASE ) /*!< Access to SRAM CAN1 Registers */
#define SRAMCAN2 ( (SramCan_RegisterType *)&SRAMCAN2_BASE ) /*!< Access to SRAM CAN2 Registers */

#endif

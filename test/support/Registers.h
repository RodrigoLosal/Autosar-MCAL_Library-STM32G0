#ifndef REGISTERS_H
#define REGISTERS_H

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
} NVIC_Type;

extern NVIC_Type *NVIC_Mock;

#define NVIC NVIC_Mock 


#endif

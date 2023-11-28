/**
 * @file    Gpt_Arch.h
 * @brief   **Gpt Architecture Driver**
 * @author  Rodrigo Lopez
 *
 * Gpt driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Gpt driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef GPT_ARCH_H__
#define GPT_ARCH_H__

#include "Gpt_Types.h"

/**
 * @defgroup GPT_Peripherals GPT TIM References
 *
 * Specifies the controller IDs of the MCU TIM's
 *
 * @{ */
#define GPT_TIM6                   0 /*!< TIM6 */
#define GPT_TIM7                   1 /*!< TIM7  */
/**
 * @} */

/**
 * @defgroup GPT Maximum values
 *
 * Specifies the controller maximum values for its config. parameters.
 *
 * @{ */
#define GPT_MAX_NUMBER_OF_CHANNELS 2u         /* GPT Module maximum number of channels available */
#define GPT_ARR_MAX                0X0000FFFF /*!< TIMx Auto-reload register maximum admissible value */
/**
 * @} */

/**
 * @defgroup GPT_Bit_Values GPT bits values
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define GPT_INTERRUPT_FLAG_BIT     0   /*!< TIMx_SR -> UIF: Update Interrupt flag bit */
#define GPT_ONE_PULSE_MODE_BIT     3u  /*!< TIMx_CR1 -> OPM: One pulse mode bit */
#define GPT_PRESCALER_LSB          0   /*!< TIMx_PSC -> [PSC:0]: GPT prescaler least significant bit */
#define GPT_PRESCALER_MSB          16u /*!< TIMx_PSC -> [PSC:15]: GPT prescaler most significant bit */
#define GPT_AUTO_RELOAD_LSB        0   /*!< TIMx_ARR -> [ARR:0]: GPT auto-reload counter least significant bit */
#define GPT_AUTO_RELOAD_MSB        16u /*!< TIMx_ARR -> [ARR:15]: GPT auto-reload counter most significant bit */
#define GPT_COUNTER_ENABLE_BIT     0   /*!< TIMx_CR1 -> CEN: Counter enable bit */
#define GPT_UPDATE_DISABLE_BIT     1u  /*!< TIMx_CR1 -> UDIS: Update disable bit */
/**
 * @} */

void Gpt_Arch_Init( const Gpt_ConfigType *ConfigPtr, uint32 ChannelsToInit );
void Gpt_Arch_DeInit( const Gpt_ConfigType *ConfigPtr, uint32 ChannelsToDeinit );
Gpt_ValueType Gpt_Arch_GetTimeElapsed( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel );
Gpt_ValueType Gpt_Arch_GetTimeRemaining( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel );
void Gpt_Arch_StartTimer( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_Arch_StopTimer( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel );
void Gpt_Arch_EnableNotification( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel );
void Gpt_Arch_DisableNotification( const Gpt_ConfigType *ConfigPtr, Gpt_ChannelType Channel );
void Gpt_Arch_Notification_Channel0( const Gpt_ConfigType *ConfigPtr );
void Gpt_Arch_Notification_Channel1( const Gpt_ConfigType *ConfigPtr );

#endif
/**
 * @file    Port.h
 * @brief   **GPT driver configuration**
 * @author  Rodrigo Lopez
 *
 * The GPT driver provides services for starting and stopping timer channels (logical timer
 * instances assigned to a timer hardware), individual for each channel.
 *
 * The tick duration of a timer channel depends on channel specific settings (part of GPT driver)
 * as well as on system clock and settings of the clock tree controlled by the MCU module.
 */
#ifndef GPT_H__
#define GPT_H__

#include "Gpt_Cfg.h" /* cppcheck-suppress misra-c2012-20.1 ; it is necesary to use a define for this function */

/**
 * @defgroup    Bit state defines
 * @{ */
#define SET                    1u /*!< Set state */
#define RESET                  0  /*!< Reset state */
/**
 * @} */

/**
 * @defgroup    GPT bits values
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define GPT_INTERRUPT_FLAG_BIT 0   /*!< TIMx_SR -> UIF: Update Interrupt flag bit */
#define GPT_ONE_PULSE_MODE_BIT 3u  /*!< TIMx_CR1 -> OPM: One pulse mode bit */
#define GPT_PRESCALER_LSB      0   /*!< TIMx_PSC -> [PSC:0]: GPT prescaler least significant bit */
#define GPT_PRESCALER_MSB      16u /*!< TIMx_PSC -> [PSC:15]: GPT prescaler most significant bit */
#define GPT_AUTO_RELOAD_LSB    0   /*!< TIMx_ARR -> [ARR:0]: GPT auto-reload counter least significant bit */
#define GPT_AUTO_RELOAD_MSB    16u /*!< TIMx_ARR -> [ARR:15]: GPT auto-reload counter most significant bit */
#define GPT_COUNTER_ENABLE_BIT 0   /*!< TIMx_CR1 -> CEN: Counter enable bit */
#define GPT_UPDATE_DISABLE_BIT 1u  /*!< TIMx_CR1 -> UDIS: Update disable bit */
/**
 * @} */

void Gpt_Init( const Gpt_ConfigType *ConfigPtr );

#if GPT_DEINIT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DeInit( void );
#endif

#if GPT_TIME_ELAPSED_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
#endif

#if GPT_TIME_REMAINING_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
#endif

void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );

#if GPT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_EnableNotification( Gpt_ChannelType Channel );
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_DisableNotification( Gpt_ChannelType Channel );
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel0( void );
#endif

#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Gpt_Notification_Channel1( void );
#endif

#endif
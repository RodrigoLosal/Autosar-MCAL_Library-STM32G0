/**
 * @file    Gpt.h
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

/**
 * @brief **Definition of the external data structure containing the initialization data**
 *
 * This is the type of the data structure including the configuration set required for
 * initializing the GPT timer unit.
 *
 * @note It is the responsibility of the user to ensure that the values defined in this structure are
 * valid and appropriate, as the GPT Driver does not perform any validation. The values must be generated
 * and validated within the code generation tool.
 *
 * @reqs   SWS_Gpt_00357
 */
typedef struct _Gpt_ConfigType
{
    uint8 GptChannelId;                      /*!< Gpt Channel to be configured */
    uint8 GptChannelMode;                    /*!< Continuous or One-Pulse mode*/
    uint16 GptChannelPrescaler;              /*!< Prescaler from 0x0 to 0xFFFF*/
    void ( *GptNotification[ 2u ] )( void ); /*!< Array of Pointers to user-defined functions*/
} Gpt_ConfigType;

/**
 * @brief **Numeric ID of a GPT channel**
 *
 * @reqs   SWS_Gpt_00358
 */
typedef enum
{
    GPT_CHANNEL_0 = 0,
    GPT_CHANNEL_1,
} Gpt_ChannelType;

/**
 * @brief **Type for reading and setting the timer values (in number of ticks).**
 *
 * @reqs   SWS_Gpt_00359
 */
typedef uint32 Gpt_ValueType;

#include "Gpt_Cfg.h" /* cppcheck-suppress misra-c2012-20.1 ; it is necesary to use a define for this function */

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
/**
 * @file    Port.h
 * @brief   **Gpt driver configuration**
 * @author  Rodrigo Lopez, Diego Perez
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
 * @defgroup    PORTS_pins Pins values
 *
 * Symbols to specify the values of PORTS pins on any port, this needs to
 * be use in combination with ports when specify in Port_Cfg.h.
 *
 * @{ */
#define SET                    1u
#define RESET                  0

/**
 * @defgroup    GPT bits values
 *
 * Symbols to specify the values of the bits on the registers.
 * @{ */
#define GPT_INTERRUPT_FLAG_BIT 0
#define GPT_ONE_PULSE_MODE_BIT 3u
#define GPT_PRESCALER_LSB      0
#define GPT_PRESCALER_MSB      16u
#define GPT_AUTO_RELOAD_LSB    0
#define GPT_AUTO_RELOAD_MSB    16u
#define GPT_COUNTER_ENABLE_BIT 0
#define GPT_UPDATE_DISABLE_BIT 1u

/**
 * @defgroup    GPT channel mode values
 *
 * Symbols to specify the values of the possible channel modes.
 * @{ */
#define GPT_CH_MODE_CONTINUOUS 0
#define GPT_CH_MODE_ONESHOT    1u

typedef struct _Gpt_ConfigType
{
    uint8 GptChannelId;
    uint8 GptChannelMode;
    uint16 GptChannelPrescaler;
    void ( *GptNotification[ 2u ] )( void );
} Gpt_ConfigType;

typedef enum
{
    GPT_CHANNEL_0 = 0,
    GPT_CHANNEL_1,
} Gpt_ChannelType;

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
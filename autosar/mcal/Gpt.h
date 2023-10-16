#ifndef GPT_H__
#define GPT_H__

#define SET                    1u
#define RESET                  0

#define GPT_INTERRUPT_FLAG_BIT 0
#define GPT_ONE_PULSE_MODE_BIT 3u
#define GPT_PRESCALER_LSB      0
#define GPT_PRESCALER_MSB      16u
#define GPT_AUTO_RELOAD_LSB    0
#define GPT_AUTO_RELOAD_MSB    16u
#define GPT_COUNTER_ENABLE_BIT 0
#define GPT_UPDATE_DISABLE_BIT 1u

#include "Gpt_Cfg.h" /* cppcheck-suppress misra-c2012-20.1 ; it is necesary to use a define for this function */

typedef struct _Gpt_ConfigType
{
    uint8 GptChannelId;
    uint8 GptChannelMode;
    uint16 GptChannelPrescaler;
    void ( *GptNotification[ GPT_NUMBER_OF_CHANNELS ] )( void );
} Gpt_ConfigType;

typedef enum
{
    GPT_CHANNEL_0 = 0,
    GPT_CHANNEL_1,
} Gpt_ChannelType;

typedef enum
{
    GPT_CH_MODE_CONTINUOUS = 0,
    GPT_CH_MODE_ONESHOT,
} Gpt_ChannelMode;

typedef uint32 Gpt_ValueType;

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
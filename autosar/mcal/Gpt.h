#ifndef GPT_H__
#define GPT_H__

#define GPT_NUMBER_OF_CHANNELS 2

typedef struct _Gpt_ConfigType
{
    uint8 Channel;
    uint8 NotificationMode;
    uint8 ChannelMode;
    uint16 Prescaler;
    void ( *Notifications[ 2u ] )( void );
} Gpt_ConfigType;

typedef enum
{
    Channel0 = 0,
    Channel1,
} Gpt_ChannelType;

typedef enum
{
    GPT_CH_MODE_CONTINUOUS = 0,
    GPT_CH_MODE_ONESHOT,
} Gpt_ChannelMode;

typedef enum
{
    Enabled = 0,
    Disabled,
} Gpt_NotificationMode;

typedef enum
{
    Uninitialized = 0,
    Initialized,
    Running,
    Stopped,
    Expired
} Gpt_ChannelState;

typedef uint32 Gpt_ValueType;

void Gpt_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_DeInit( void );
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );
void Gpt_EnableNotification( Gpt_ChannelType Channel );
void Gpt_DisableNotification( Gpt_ChannelType Channel );
void Gpt_Notification_Channel1( void );
void Gpt_Notification_Channel2( void );

#endif
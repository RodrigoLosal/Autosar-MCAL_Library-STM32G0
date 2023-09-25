#ifndef GPT_H__
#define GPT_H__

typedef struct _Gpt_ConfigType
{
    uint8 Channel;
    uint16 Prescaler;
    uint16 Period;
} Gpt_ConfigType;

typedef enum
{
	Channel1,
	Channel2,
} Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

void Gpt_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_DeInit( void );
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );
void Gpt_EnableNotification( Gpt_ChannelType Channel );
void Gpt_DisableNotification( Gpt_ChannelType Channel );
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );

#endif
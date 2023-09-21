#include "Registers.h"
#include "Std_Types.h"
#include "Bfx.h"

typedef struct _Gpt_ConfigType
{
    
} Gpt_ConfigType;

typedef enum
{
	TIM6 = 0,
	TIM7,
} Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum
{
	GPT_MODE_NORMAL = 0x00,
	GPT_MODE_SLEEP = 0x01
} Gpt_ModeType;

void Gpt_GetVersionInfo( Std_VersionInfoType *VersionInfoPtr );
void Gpt_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_DeInit( void );
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );
void Gpt_EnableNotification( Gpt_ChannelType Channel );
void Gpt_DisableNotification( Gpt_ChannelType Channel );
void Gpt_SetMode( Gpt_ModeType Mode );
void Gpt_DisableWakeUp( Gpt_ChannelType Channel );
void Gpt_EnableWakeUp( Gpt_ChannelType Channel );
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );
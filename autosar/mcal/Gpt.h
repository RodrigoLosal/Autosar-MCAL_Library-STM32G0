<<<<<<< HEAD
#ifndef GPT_H__
#define GPT_H__

typedef struct _Gpt_ConfigType
{
    uint8 Channel;
    uint16 Prescaler;
    uint16 Period;
=======
#include "Registers.h"
#include "Std_Types.h"
#include "Bfx.h"

typedef struct _Gpt_ConfigType
{
    
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
} Gpt_ConfigType;

typedef enum
{
<<<<<<< HEAD
<<<<<<< HEAD
	Channel1,
	Channel2,
=======
	TIM6 = 0,
	TIM7,
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
=======
    Channel1,
    Channel2,
>>>>>>> 8a205fd (GPT-Code-Implementation. Autoformat runned, fixed some warnings.)
} Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

<<<<<<< HEAD
=======
typedef enum
{
	GPT_MODE_NORMAL = 0x00,
	GPT_MODE_SLEEP = 0x01
} Gpt_ModeType;

void Gpt_GetVersionInfo( Std_VersionInfoType *VersionInfoPtr );
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)
void Gpt_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_DeInit( void );
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_StopTimer( Gpt_ChannelType Channel );
void Gpt_EnableNotification( Gpt_ChannelType Channel );
void Gpt_DisableNotification( Gpt_ChannelType Channel );
<<<<<<< HEAD
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );

#endif
=======
void Gpt_SetMode( Gpt_ModeType Mode );
void Gpt_DisableWakeUp( Gpt_ChannelType Channel );
void Gpt_EnableWakeUp( Gpt_ChannelType Channel );
void Gpt_Notification_TIM6( void );
void Gpt_Notification_TIM7( void );
>>>>>>> cf843bd (GPT-Code-Implementation. Creation of the files, control variables & functions. TIM6 & TIM7 registers added to Registers.h)

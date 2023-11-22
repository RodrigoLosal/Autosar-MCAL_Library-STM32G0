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

void Gpt_Arch_Init( const Gpt_ConfigType *ConfigPtr );
void Gpt_Arch_DeInit( void );
Gpt_ValueType Gpt_Arch_GetTimeElapsed( Gpt_ChannelType Channel );
Gpt_ValueType Gpt_Arch_GetTimeRemaining( Gpt_ChannelType Channel );
void Gpt_Arch_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
void Gpt_Arch_StopTimer( Gpt_ChannelType Channel );
void Gpt_Arch_EnableNotification( Gpt_ChannelType Channel );
void Gpt_Arch_DisableNotification( Gpt_ChannelType Channel );
void Gpt_Arch_Notification_Channel0( void );
void Gpt_Arch_Notification_Channel1( void );

#endif
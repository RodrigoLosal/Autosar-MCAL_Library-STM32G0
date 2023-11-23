/**
 * @file    Port_Arch.h
 * @brief   **  **
 * @author  Enrique Ortega
 *
 * PORT driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the PORT driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef PORT_ARCH_H__
#define PORT_ARCH_H__

#include "Port_Types.h"

void Port_Arch_Init( const Port_ConfigType *ConfigPtr );
void Port_Arch_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
void Port_Arch_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
void Port_Arch_RefreshPortDirection( void );

#endif /* PORT_ARCH_H__ */
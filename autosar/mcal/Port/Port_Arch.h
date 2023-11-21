/**
 * @file    Port_Arch.h
 * @brief   **  **
 * @author  Enrique Ortega
 *
 * This PORT driver module control the overall configuration and initialization of the port structure
 * which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports which are
 * configured by the PORT driver.
 */
#ifndef PORT_ARCH_H__
#define PORT_ARCH_H__

void Port_Arch_Init( const Port_ConfigType *ConfigPtr );
void Port_Arch_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
void Port_Arch_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
void Port_Arch_RefreshPortDirection( void );

#endif /* PORT_ARCH_H__ */
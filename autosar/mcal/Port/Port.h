/**
 * @file    Port.h
 * @brief   **Port driver configuration**
 * @author  Daniel Byuerly, Diego Perez
 *
 * This PORT driver module control the overall configuration and initialization of the port structure
 * which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports which are
 * configured by the PORT driver.
 *
 * The PORT driver shall be initialized prior to the use of the DIO functions. Otherwise, DIO
 * functions will exhibit undefined behavior. The diagram below identifies the PORT driver functions
 * and the structure of the PORT driver and DIO driver within the MCAL software layer. To use some
 * functions check the Port_Cfg.h file to configured the values.
 */
#ifndef PORT_H__
#define PORT_H__

#include "Port_Cfg.h"

void Port_Init( const Port_ConfigType *ConfigPtr );

#if PORT_SET_PIN_DIRECTION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

#if PORT_SET_PIN_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif

#if PORT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif

void Port_RefreshPortDirection( void );

#endif
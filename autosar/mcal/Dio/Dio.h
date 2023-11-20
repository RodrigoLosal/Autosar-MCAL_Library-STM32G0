/**
 * @file Dio.h
 * @brief Dio driver configuration.
 *
 * This is the file for the Dio driver, it provides functions for accessing the hardware
 * pins of the microcontroller. It also allows the grouping of those pins.
 *
 * The DIO driver provides services for reading and writing to/from:
 * DIO Channels (Pins)
 * DIO Ports
 * DIO Channel Groups
 *
 * This module operates on pins and ports configured by the PORT driver for this purpose.
 * For this reason, there is no configuration and initialization of this port structure in
 * the DIO driver.
 *
 * The DIO driver provides the following functions:
 * The Dio controller will define functions to modify the output channel levels individually,
 * for a port or for a channel group.
 * The Dio driver will define functions to read the level of the input and output channels
 * individually, for a port or for a group of channels.
 *
 * @note Dio module will use the definitions that have been created during the configuration
 * process in the Dio_Cfg.h file.
 */
#ifndef DIO_H__
#define DIO_H__

#include "Dio_Cfg.h"

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
#if DIO_FLIP_CHANNEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId );
#endif
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr );
void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level );
#if DIO_GET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Dio_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#if DIO_MASKED_WRITE_PORT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask );
#endif

#endif /* DIO_H_ */

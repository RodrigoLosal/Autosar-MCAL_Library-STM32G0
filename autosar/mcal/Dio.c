/**
 * @file Dio.c
 * @brief Port driver configuration.
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
#include "Std_Types.h"
#include "Dio.h"


/**
 * @brief Read Channel 
 *
 * The function will return the value of the specified DIO channel, taking the MSB bit as 
 * the port and the LSB bit as the pin. 
 * 
 * @param ChannelId ID of DIO channel
 */
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
}


/**
 * @brief 
 *
 * The function will return the value of the specified DIO channel, taking the MSB bit as 
 * the port and the LSB bit as the pin. 
 * 
 * @param ChannelId ID of DIO channel
 * @param Level ID of DIO channel
 */
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
}


/**
 * @brief 
 *
 * The function will return the value of the specified DIO channel, taking the MSB bit as 
 * the port and the LSB bit as the pin. 
 * 
 * @param ChannelId ID of DIO channel
 */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
}

Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
}

void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
}

Dio_PortLevelType Dio_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
}

void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
}
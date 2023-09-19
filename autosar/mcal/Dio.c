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
#include "Registers.h"
#include "Bfx.h"
#include "Dio_Cfg.h"
#include "Dio.h"

#define VALUE_F (Dio_LevelType)0xF
#define SIX     6u
#define FOUR    4u


static Dio_RegisterType *Dios_Port[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_LevelType Pin     = ChannelId & VALUE_F;

    return Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );
}


void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_PortType Pin      = ChannelId & VALUE_F;

    Bfx_PutBit_u32u8u8( (uint32 *)&Dio->ODR, Pin, Level );
}


Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_PortType Pin      = ChannelId & VALUE_F;

    Bfx_ToggleBitMask_u32u32( (uint32 *)&Dio->ODR, ( 1u << Pin ) );

    return Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );
}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
    return (Dio_PortLevelType)Dios_Port[ PortId ];
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    Dios_Port[ PortId ] = (Dio_RegisterType *)Level;
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = 0;
    const Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    GroupLevel = ( Port->IDR ) & ( ChannelGroupIdPtr->mask );

    Bfx_ShiftBitRt_u32u8( (uint32 *)GroupLevel, ChannelGroupIdPtr->offset );

    return GroupLevel;
}


void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&Port->ODR, ChannelGroupIdPtr->offset, ChannelGroupIdPtr->mask, Level );
}


Dio_PortLevelType Dio_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    Dio_PortLevelType Level = 0;

    versioninfo->vendorID         = DIO_VENDOR_ID;
    versioninfo->moduleID         = DIO_MODULE_ID;
    versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;

    return Level;
}


void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
    Dio_RegisterType *Port = Dios_Port[ PortId ];

    Port->ODR = Mask & ( ( Port->ODR ) | Level );
}
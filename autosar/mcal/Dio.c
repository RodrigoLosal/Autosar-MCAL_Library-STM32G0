#include "Std_Types.h"
#include "Registers.h"
#include "Bfx.h"
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
    Dio_RegisterType *Port = Dios_Port[ PortId ];

    return (Dio_PortLevelType)Port->IDR;
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    Dios_Port[ PortId ] = (Dio_RegisterType *)&Level;
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = 0;
    const Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    GroupLevel = ( Port->IDR ) & ( ChannelGroupIdPtr->mask );

    Bfx_ShiftBitRt_u32u8( (uint32 *)&GroupLevel, ChannelGroupIdPtr->offset );

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

    versioninfo->vendorID         = 0;
    versioninfo->moduleID         = 0;
    versioninfo->sw_major_version = 0;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;

    return Level;
}


void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
    Dio_RegisterType *Port = Dios_Port[ PortId ];

    Port->ODR = Mask & ( ( Port->ODR ) | Level );
}
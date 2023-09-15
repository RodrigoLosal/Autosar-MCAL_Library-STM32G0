#include "Dio.h"
#include "Registers.h"
#include "Dio_Cfg.h"
#include "Bfx.h"

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
    Dio_RegisterType *Port = Dios_Port[ PortId ];

    Port->ODR = Level;
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = 0;
    const Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    GroupLevel = ( ( Port->IDR ) & ( ChannelGroupIdPtr->mask ) ) >> ChannelGroupIdPtr->offset;

    return GroupLevel;
}


void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    Port->ODR = (Dio_PortLevelType)( ( Port->ODR ) & ( ~( ( ChannelGroupIdPtr->mask ) ) ) ) | (Dio_PortLevelType)( Level << ( ChannelGroupIdPtr->offset ) );
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
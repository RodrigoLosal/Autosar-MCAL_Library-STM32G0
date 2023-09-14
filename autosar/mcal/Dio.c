#include "Dio.h"
#include "Registers.h"
#include "Dio_Cfg.h"
#include "Bfx.h"


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_LevelType ChannelLevel = 0;
    Dio_RegisterType *Dio      = NULL;
    Dio_LevelType Pin;

    Dio_RegisterType *Dios[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };
    Dio                           = Dios[ ChannelId >> FOUR ];

    Pin = ChannelId & VALUE_F;

    ChannelLevel = Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );

    return ChannelLevel;
}


void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    Dio_RegisterType *Dio = NULL;
    Dio_PortType Pin;

    Dio_RegisterType *Dios[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };
    Dio                           = Dios[ ChannelId >> FOUR ];

    Pin = ChannelId & VALUE_F;

    Bfx_PutBit_u32u8u8( (uint32 *)&Dio->ODR, Pin, Level );
}


Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
    Dio_LevelType FlipChannel = 0;
    Dio_RegisterType *Dio     = NULL;
    Dio_PortType Pin;
    Dio_RegisterType *Dios[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Dio = Dios[ ChannelId >> FOUR ];

    Pin = ChannelId & VALUE_F;

    Bfx_ToggleBits_u32( (uint32 *)&Dio->ODR );

    FlipChannel = Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );

    return FlipChannel;
}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
    Dio_PortLevelType *Port_Data;
    Dio_RegisterType *Port         = NULL;
    Dio_RegisterType *Ports[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Port = Ports[ PortId ];

    Port_Data = (Dio_PortLevelType *)&Port->IDR;

    return *Port_Data;
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port         = NULL;
    Dio_RegisterType *Ports[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Port = Ports[ PortId ];

    Port->ODR = Level;
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel   = 0;
    Dio_RegisterType *Port         = NULL;
    Dio_RegisterType *Ports[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Port = Ports[ ChannelGroupIdPtr->port ];

    GroupLevel = ( ( Port->IDR ) & ( ChannelGroupIdPtr->mask ) ) >> ChannelGroupIdPtr->offset;

    return GroupLevel;
}


void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port;
    Dio_RegisterType *Ports[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Port = Ports[ ChannelGroupIdPtr->port ];

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
    Dio_RegisterType *Port         = NULL;
    Dio_RegisterType *Ports[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

    Port = Ports[ PortId ];

    Port->ODR = Mask & ( ( Port->ODR ) | Level );
}
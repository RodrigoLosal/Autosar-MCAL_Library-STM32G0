#include "Dio.h"
#include "Registers.h"
#include "Std_Types.h"
#include "Dio_Cfg.h"


extern Dio_ConfigChannel Dio_PortChannels[ DIO_CONFIGURED_CHANNLES ];


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_LevelType ChannelLevel = 0;

    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        Dio_PortType *Pin_Ch    = NULL;
        Dio_PortType Channel_Id = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                Channel_Id = Array_ID;
            }
        }

        Pin_Ch = &( Dio_PortChannels[ Channel_Id ].Pin_Reg );

        ChannelLevel = Bfx_GetBit_u32u8_u8( (uint32 *)&Pin_Ch, Dio_PortChannels[ Channel_Id ].Pin );
    }
    else
    {
    }

    return ChannelLevel;
}


void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        Dio_PortLevelType *Port_Ch = NULL;
        Dio_PortType Channel_Id    = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                Channel_Id = Array_ID;
            }
        }

        Port_Ch = &Dio_PortChannels[ Channel_Id ].Port;

        if( Level == STD_HIGH )
        {
            Bfx_SetBit_u32u8( (uint32 *)&Port_Ch, Dio_PortChannels[ Channel_Id ].Pin );
        }
        else if( Level == STD_LOW )
        {
            Bfx_ClrBit_u32u8( (uint32 *)&Port_Ch, Dio_PortChannels[ Channel_Id ].Pin );
        }
        else
        {
        }
    }
    else
    {
    }
}

Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
    Dio_LevelType ChannelLevel = STD_LOW;

    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        Dio_PortLevelType *Port_Ch = NULL;
        Dio_PortLevelType *Pin_Ch  = NULL;
        Dio_PortType Channel_Id    = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                Channel_Id = Array_ID;
            }
        }

        Port_Ch = &( Dio_PortChannels[ Channel_Id ].Port );
        Pin_Ch  = &( Dio_PortChannels[ Channel_Id ].Pin_Reg );

        if( Bfx_GetBit_u32u8_u8( (uint32 *)&Pin_Ch, Dio_PortChannels[ Channel_Id ].Pin ) != 0 )
        {
            Bfx_ClrBit_u32u8( (uint32 *)&Port_Ch, Dio_PortChannels[ Channel_Id ].Pin );
            ChannelLevel = STD_LOW;
        }
        else
        {
            Bfx_ClrBit_u32u8( (uint32 *)&Port_Ch, Dio_PortChannels[ ChannelId ].Pin );
            ChannelLevel = STD_HIGH;
        }
    }
    else
    {
    }

    return ChannelLevel;
}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
    Dio_PortLevelType *Pin_Port = NULL;
    Dio_PortLevelType PortLevel = 0;

    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {

        Dio_PortType Port_Id = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( PortId == Dio_PortChannels[ Array_ID ].Port_Num )
            {
                Port_Id = Array_ID;
            }
        }

        Pin_Port = &( Dio_PortChannels[ Port_Id ].Pin_Reg );

        PortLevel = *Pin_Port;
    }
    else
    {
    }

    return PortLevel;
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {
        Dio_PortLevelType *Port_Pt = NULL;
        Dio_PortType Port_Id       = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( PortId == Dio_PortChannels[ Array_ID ].Port_Num )
            {
                Port_Id = Array_ID;
            }
        }

        Port_Pt = &( Dio_PortChannels[ Port_Id ].Port );

        *Port_Pt = Level;
    }
    else
    {
    }
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = 0;

    if( ChannelGroupIdPtr != NULL )
    {
        Dio_PortLevelType Port = 0;

        Port = ChannelGroupIdPtr->port;

        GroupLevel = ( ( Port ) & ( ChannelGroupIdPtr->mask ) ) >> ChannelGroupIdPtr->offset;
    }

    else
    {
    }

    return GroupLevel;
}


void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    if( ChannelGroupIdPtr != NULL )
    {
        Dio_PortLevelType *Port_Pt = NULL;
        Dio_PortType Port_Id       = 0;
        uint8 Array_ID;

        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelGroupIdPtr->port == Dio_PortChannels[ Array_ID ].Port_Num )
            {
                Port_Id = Array_ID;
            }
        }

        Port_Pt = &Dio_PortChannels[ Port_Id ].Port;

        *Port_Pt = (Dio_PortLevelType)( ( *Port_Pt ) & ( ~( ( ChannelGroupIdPtr->mask ) ) ) ) | (Dio_PortLevelType)( Level << ( ChannelGroupIdPtr->offset ) );
    }

    else
    {
    }
}


void Dio_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    versioninfo->vendorID         = DIO_VENDOR_ID;
    versioninfo->moduleID         = DIO_MODULE_ID;
    versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;
}


void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {
        if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
        {
            Dio_PortLevelType *Port = NULL;
            Dio_PortType Port_Id    = 0;
            uint8 Array_ID;

            for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
            {
                if( PortId == Dio_PortChannels[ Array_ID ].Port_Num )
                {
                    Port_Id = Array_ID;
                }
            }

            Port = &( Dio_PortChannels[ Port_Id ].Port );

            *Port = Level;

            *Port &= Mask;
        }
        else
        {
        }
    }
    else
    {
    }
}
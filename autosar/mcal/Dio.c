#include "Dio.h"
#include "Platform_Types.h"
#include "Register.h"
#include "Bfx.h"
#include "Std_Types.h"
#include "Dio_Cfg.h"


extern Dio_ConfigChannel Dio_PortChannels[ DIO_CONFIGURED_CHANNLES ];


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_PortType Port_Ch;
    Dio_LevelType ChannelLevel = 0;
    uint8 Array_ID;

    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                ChannelId = Array_ID;
            }
        }

        Port_Ch = Dio_PortChannels[ ChannelId ].Port;

        ChannelLevel = Bfx_GetBit_u32u8_u8( Port_Ch, Dio_PortChannels[ ChannelId ].Pin );
    }
    else
    {
    }

    return ChannelLevel;
}


void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    Dio_PortLevelType *Port;
    Dio_LevelType ChannelLevel;
    uint8 Array_ID;

    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                ChannelId = Array_ID;
            }
        }

        Port = Dio_PortChannels[ ChannelId ].Port;

        if( Level == STD_HIGH )
        {
            Bfx_SetBit_u32u8_u8( *Port, Dio_PortChannePort_Chls[ ChannelId ].Pin );
        }
        else if( Level == STD_LOW )
        {
            Bfx_ClearBit_u32u8_u8( *Port, Dio_PortChannels[ ChannelId ].Pin );
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
    Dio_PortLevelType Port;
    Dio_LevelType ChannelLevel = STD_LOW;
    uint8 Array_ID;

    if( ( ChannelId >= MIN_NUM_CHANNELS ) && ( ChannelId <= MAX_NUM_CHANNELS ) )
    {
        for( Array_ID = 0; Array_ID < NUM_CHANNELS; Array_ID++ )
        {
            if( ChannelId == Dio_PortChannels[ Array_ID ].Ch_Num )
            {
                ChannelId = Array_ID;
            }
        }

        Port = Dio_PortChannels[ ChannelId ].Port;

        if( Bfx_SetBit_u32u8_u8( Port, Dio_PortChannels[ ChannelId ].Pin ) )
        {
            Bfx_ClearBit_u32u8_u8( Port, Dio_PortChannels[ ChannelId ].Pin );
            ChannelLevel = STD_LOW;
        }
        else
        {
            Bfx_SetBit_u32u8_u8( Port, Dio_PortChannels[ ChannelId ].Pin );
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
    Dio_PortLevelType Port;
    Dio_PortLevelType PortLevel = 0;

    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {
        switch( PortId )
        {
            case 0:
                Port = PORTA;
                break;

            case 1:
                Port = PORTB;
                break;

            case 2:
                Port = PORTC;
                break;

            case 3:
                Port = PORTD;
                break;

            case 4:
                Port = PORTE;
                break;

            case 5:
                Port = PORTF;
                break;

            default:
                break;
        }

        PortLevel = Port;
    }
    else
    {
    }

    return PortLevel;
}

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    Dio_PortLevelType *Port;

    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {
        switch( PortId )
        {
            case 0:
                Port = &PORTA;
                break;

            case 1:
                Port = &PORTB;
                break;

            case 2:
                Port = &PORTC;
                break;

            case 3:
                Port = &PORTD;
                break;

            case 4:
                Port = &PORTE;
                break;

            case 5:
                Port = &PORTF;
                break;

            default:
                break;
        }

        *Port = Level;
    }
    else
    {
    }
}


Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_PortLevelType Port;
    Dio_PortLevelType GroupLevel = 0;

    if( ChannelGroupIdPtr != Null )
    {
        Port = ChannelGroupIdPtt->port;

        GroupLevel = ( ( Port ) & ( ChannelGroupIdPtr->mask ) ) >> ChannelGroupIdPtr->offset;
    }

    else
    {
    }

    return GroupLevel;
}


void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_PortLevelType Port;

    if( ChannelGroupIdPtr != Null )
    {
        Port = ChannelGroupIdPtt->port;

        Port = ( ( Port ) & ( ~( ChannelGroupIdPtr->mask ) ) ) | ( Level << ChannelGroupIdPtr->offset );
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
    Dio_PortLevelType *Port;

    if( ( PortId >= MIN_NUM_PORTS ) && ( PortId <= MAX_NUM_PORTS ) )
    {
        switch( PortId )
        {
            case 0:
                Port = &PORTA;
                break;

            case 1:
                Port = &PORTB;
                break;

            case 2:
                Port = &PORTC;
                break;

            case 3:
                Port = &PORTD;
                break;

            case 4:
                Port = &PORTE;
                break;

            case 5:
                Port = &PORTF;
                break;

            default:
                break;
        }

        *Port = Level;

        *Port &= Mask;
    }
    else
    {
    }
}
#include "Crc.h"

#define CRC8             0x1D
#define FIRSTCALLCRC8    0xFF
#define CRC8NBITS        8
#define CRC8MSB          0x80

#define CRC8H2F          0x2F
#define FIRSTCALLCRC8H2F 0xFF
#define CRC8H2FNBITS     8
#define CRC8H2NMSB       0x80

#define CRC16            0x1021
#define FIRSTCALLCRC16   0xFFFF
#define CRC16NBITS       8
#define CRC16MSB         0x8000
#define CRC16_8LEFT      8

#define REFLECTLSB       0x01

#define VENDOR_ID   0x0000
#define MODULE_ID   0x0000
#define CRC_SW_MAJOR_VERSION 0
#define CRC_SW_MINOR_VERSION 0
#define CRC_SW_PATCH_VERSION 0

typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8  sw_major_version;
    uint8  sw_minor_version;
    uint8  sw_patch_version;
} Std_VersionInfoType;

uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = CRC8;
    uint8 crcValue             = Crc_StartValue8;

    if( Crc_IsFirstCall )
    {
        crcValue = FIRSTCALLCRC8;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ];

        for( uint8 bit = 0; bit < CRC8NBITS; bit++ )
        {
            if( crcValue & CRC8MSB )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue ^ 0xFF;
}

uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = CRC8H2F;
    uint8 crcValue             = Crc_StartValue8H2F;

    if( Crc_IsFirstCall )
    {
        crcValue = FIRSTCALLCRC8H2F;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ];

        for( uint8 bit = 0; bit < CRC8H2FNBITS; bit++ )
        {
            if( crcValue & CRC8H2NMSB )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue;
}

uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall )
{
    const uint16 Crc_Polynomial = CRC16;
    uint16 crcValue             = Crc_StartValue16;

    if( Crc_IsFirstCall )
    {
        crcValue = FIRSTCALLCRC16;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= (uint16)Crc_DataPtr[ i ] << CRC16_8LEFT;

        for( uint8 bit = 0; bit < CRC16NBITS; bit++ )
        {
            if( crcValue & CRC16MSB )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue;
}

void Crc_GetVersionInfo(Std_VersionInfoType* Versioninfo)
{
    Versioninfo -> vendorID = VENDOR_ID;
    Versioninfo -> moduleID = MODULE_ID;
    Versioninfo ->sw_major_version = CRC_SW_MAJOR_VERSION;
    Versioninfo ->sw_minor_version = CRC_SW_MINOR_VERSION;
    Versioninfo ->sw_patch_version = CRC_SW_PATCH_VERSION;
}

/*
Auxiliary function in future implementations.
*/
uint32 Reflect( uint32 data, uint8 bit_count )
{
    uint32 reflection = 0;
    for( uint8 bit = 0; bit < bit_count; bit++ )
    {
        if( data & REFLECTLSB )
        {
            reflection |= ( 1 << ( ( bit_count - 1 ) - bit ) );
        }
        data >>= 1;
    }
    return reflection;
}
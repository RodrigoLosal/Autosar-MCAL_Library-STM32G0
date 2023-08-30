#ifndef CRC_H_
#define CRC_H_

#include "Std_Types.h"

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

uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall );
uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall );
uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );
uint32 Reflect( uint32 data, uint8 bit_count );

#endif
#ifndef CRC_H_
#define CRC_H_

#include "Std_Types.h"

uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall );
uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall );
uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );
uint32 Reflect( uint32 data, uint8 bit_count );

#endif
/**
 * @file    Crc.h
 * @brief   **This file contains the API and the configuration of the AUTOSAR Basic Software module CRC.**
 *
 * The Crc library contains the following routines for CRC calculation
 * • CRC8: SAEJ1850
 * • CRC8H2F: CRC8 0x2F polynomial
 * • CRC16
 * • CRC32
 * • CRC32P4: CRC32 0xF4ACFB13 polynomial
 * • CRC64: CRC-64-ECMA
 * 
 * This library was designed like a Runtime calculation: 
 * Slower execution, but small code size (no ROM table)
 */


#ifndef CRC_H_
#define CRC_H_

uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall );
uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall );
uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );
uint16 Crc_CalculateCRC16ARC( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );
uint32 Crc_CalculateCRC32( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall );
uint32 Crc_CalculateCRC32P4( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall );
uint64 Crc_CalculateCRC64( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint64 Crc_StartValue64, boolean Crc_IsFirstCall );
uint8 Crc_GetVersionInfo( Std_VersionInfoType *Versioninfo );

#endif
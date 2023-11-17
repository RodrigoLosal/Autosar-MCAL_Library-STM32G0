/**
 * @file    Fls.h
 * @brief   **Flash Driver header**
 * @author  Christopher Bogarin
 *
 * The flash driver provides services for reading,
 * writing and erasing flash memory and a configuration interface
 * for setting / resetting the write / erase protection
 * if supported by the underlying hardware. In application mode of the ECU,
 * the flash driver is only to be used by the Flash EEPROM
 * emulation module for writing data.
 * It is not intended to write program code to flash memory in application mode.
 *
 */
#ifndef FLASH_H__
#define FLASH_H__

#include "Fls_Cfg.h"
#include "MemIf.h"

void Fls_Init( const Fls_ConfigType *ConfigPtr );
Std_ReturnType Fls_Erase( Fls_AddressType TargetAddress, Fls_LengthType Length );
Std_ReturnType Fls_Write( Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length );
#if FLS_CANCEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_Cancel( void );
#endif
#if FLS_GET_STATUS_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_StatusType Fls_GetStatus( void );
#endif
#if FLS_GET_JOB_RESULT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_JobResultType Fls_GetJobResult( void );
#endif
Std_ReturnType Fls_Read( Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length );
#if FLS_COMPARE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length );
#endif
#if FLS_SET_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_SetMode( MemIf_ModeType Mode );
#endif
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr );
#if FLS_BLANK_CHECK_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_BlankCheck( Fls_AddressType TargetAddress, Fls_LengthType Length );
#endif

#endif
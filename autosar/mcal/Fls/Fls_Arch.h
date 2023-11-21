/**
 * @file    Fls_Arch.h
 * @brief   **Flash Architecture Driver**
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
#ifndef FLS_ARCH_H__
#define FLS_ARCH_H__

#include "Fls_Types.h"
#include "MemIf.h"

void Fls_Arch_Init( Fls_HwUnit *HwUnit, const Fls_ConfigType *ConfigPtr );
Std_ReturnType Fls_Arch_Erase( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, Fls_LengthType Length );
Std_ReturnType Fls_Arch_Write( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length );
void Fls_Arch_Cancel( Fls_HwUnit *HwUnit );
MemIf_StatusType Fls_Arch_GetStatus( Fls_HwUnit *HwUnit );
MemIf_JobResultType Fls_Arch_GetJobResult( Fls_HwUnit *HwUnit );
Std_ReturnType Fls_Arch_Read( Fls_HwUnit *HwUnit, Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length );
Std_ReturnType Fls_Arch_Compare( Fls_HwUnit *HwUnit, Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length );
void Fls_Arch_SetMode( Fls_HwUnit *HwUnit, MemIf_ModeType Mode );
void Fls_Arch_GetVersionInfo( Fls_HwUnit *HwUnit, Std_VersionInfoType *VersioninfoPtr );
Std_ReturnType Fls_Arch_BlankCheck( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, Fls_LengthType Length );

#endif
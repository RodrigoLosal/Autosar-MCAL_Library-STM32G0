/**
 * @file    Mcu_Arch.c
 * @brief   **Mcu Specific Architecture Driver**
 * @author  Angel Lozano
 *
 * Mcu driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Mcu driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef MCU_ARCH_H__
#define MCU_ARCH_H__

#include "Mcu_Types.h"

void Mcu_Arch_Init( Mcu_HwUnit *HwUnit, const Mcu_ConfigType *ConfigPtr );
Std_ReturnType Mcu_Arch_InitRamSection( Mcu_HwUnit *HwUnit, Mcu_RamSectionType RamSection );
Std_ReturnType Mcu_Arch_InitClock( Mcu_HwUnit *HwUnit, Mcu_ClockType ClockSetting );
Std_ReturnType Mcu_Arch_DistributePllClock( Mcu_HwUnit *HwUnit );
Mcu_PllStatusType Mcu_Arch_GetPllStatus( Mcu_HwUnit *HwUnit );
Mcu_ResetType Mcu_Arch_GetResetReason( Mcu_HwUnit *HwUnit );
Mcu_RawResetType Mcu_Arch_GetResetRawValue( Mcu_HwUnit *HwUnit );
void Mcu_Arch_PerformReset( Mcu_HwUnit *HwUnit );
void Mcu_Arch_SetMode( Mcu_HwUnit *HwUnit, Mcu_ModeType McuMode );
void Mcu_Arch_GetVersionInfo( Mcu_HwUnit *HwUnit, Std_VersionInfoType *versioninfo );
Mcu_RamStateType Mcu_Arch_GetRamState( Mcu_HwUnit *HwUnit );

#endif
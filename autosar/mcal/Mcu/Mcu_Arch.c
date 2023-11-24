/**
 * @file    Mcu_Arch.c
 * @brief   **Mcu Architecture Driver**
 * @author  Angel Lozano
 *
 * Mcu driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Mcu driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Mcu_Cfg.h"
#include "Mcu_Arch.h"

/**
 * @brief    **MCU Low Level Initialization**
 *
 * Service to initialize the MCU driver
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   ConfigPtr  Pointer to MCU driver configuration set
 *
 * @reqs    SWS_Mcu_00153
 */
void Mcu_Arch_Init( Mcu_HwUnit *HwUnit, const Mcu_ConfigType *ConfigPtr )
{
    (void)HwUnit;
    (void)ConfigPtr;
}

/**
 * @brief    **MCU Low Level RAM Initialization**
 *
 * Service to initialize the RAM section wise
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   RamSection  Selects RAM memory section provided in configuration set
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00154
 */
Std_ReturnType Mcu_Arch_InitRamSection( Mcu_HwUnit *HwUnit, Mcu_RamSectionType RamSection )
{
    (void)HwUnit;
    (void)RamSection;
    return E_NOT_OK;
}

/**
 * @brief    **MCU Low Level Clock Initialization**
 *
 * Service to initialize the PLL and other MCU specific clock options.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   ClockSetting  Pass the settings to configure Mcu clock
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00155
 */
Std_ReturnType Mcu_Arch_InitClock( Mcu_HwUnit *HwUnit, Mcu_ClockType ClockSetting )
{
    (void)HwUnit;
    (void)ClockSetting;
    return E_NOT_OK;
}

/**
 * @brief    **Low Level PLL to MCU Clock distribution**
 *
 * Service to activate the PLL clock to the MCU clock distribution.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00156
 */
Std_ReturnType Mcu_Arch_DistributePllClock( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Get PLL Low Level  lock status**
 *
 * Service which provides the lock status of the PLL
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_PllStatusType: MCU_PLL_LOCKED when the PLL is locked, MCU_PLL_UNLOCKED,
 *          MCU_PLL_STATUS_UNDEFINED when status is unknown
 *
 * @reqs    SWS_Mcu_00157
 */
Mcu_PllStatusType Mcu_Arch_GetPllStatus( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Get MCU Low Level reset type**
 *
 * Service which reads the reset type from the hardware, if supported
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_ResetType: MCU_POWER_ON_RESET, MCU_WATCHDOG_RESET, MCU_SW_RESET,
 *          MCU_RESET_UNDEFINED
 *
 * @reqs    SWS_Mcu_00158
 */
Mcu_ResetType Mcu_Arch_GetResetReason( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Get reset raw value Low Level**
 *
 * Service which reads the reset type from the hardware register, if supported
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_RawResetType: Reset raw value
 *
 * @reqs    SWS_Mcu_00159
 */
Mcu_RawResetType Mcu_Arch_GetResetRawValue( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Reset the MCU Low Level**
 *
 * Service to perform a microcontroller reset
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @reqs    SWS_Mcu_00160
 */
void Mcu_Arch_PerformReset( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief    **Set MCU Low Level power mode**
 *
 * Service to activate the MCU power modes
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   McuMode  Set different MCU power modes configured in the configuration set
 *
 * @reqs    SWS_Mcu_00161
 */
void Mcu_Arch_SetMode( Mcu_HwUnit *HwUnit, Mcu_ModeType McuMode )
{
    (void)HwUnit;
    (void)McuMode;
}

/**
 * @brief    **Get status of MCU RAM Low Level **
 *
 * Service which provides the actual status of the microcontroller RAM. (if supported)
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Mcu_RamStateType: Status of the RAM Content
 *
 * @reqs    SWS_Mcu_00207
 */
Mcu_RamStateType Mcu_Arch_GetRamState( Mcu_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

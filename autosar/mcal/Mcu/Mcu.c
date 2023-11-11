/**
 * @file    Mcu.c
 * @brief   **Mcu Driver**
 * @author  Angel Lozano
 *
 * The MCU driver provides services for basic microcontroller initialization, power down
 * functionality, reset and microcontroller specific functions required by other MCAL
 * software modules. The initialization services allow a flexible and application related
 * MCU initialization in addition to the start-up code.
 */

#include "Std_Types.h"
#include "Mcu.h"

/**
 * @brief    **MCU Initialization**
 *
 * Service to initialize the MCU driver
 *
 * @param   ConfigPtr  Pointer to MCU driver configuration set
 *
 * @reqs    SWS_Mcu_00153
 */
void Mcu_Init( const Mcu_ConfigType *ConfigPtr )
{
    (void)ConfigPtr;
}

/**
 * @brief    **MCU RAM Initialization**
 *
 * Service to initialize the RAM section wise
 *
 * @param   RamSection  Selects RAM memory section provided in configuration set
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00154
 */
Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection )
{
    (void)RamSection;
    return E_OK;
}

/**
 * @brief    **MCU Clock Initialization**
 *
 * Service to initialize the PLL and other MCU specific clock options.
 *
 * @param   ClockSetting  Pass the settings to configure Mcu clock
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00155
 */
Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting )
{
    (void)ClockSetting;
    return E_OK;
}

/**
 * @brief    **PLL to MCU Clock distribution**
 *
 * Service to activate the PLL clock to the MCU clock distribution.
 *
 * @retval  Std_ReturnType: E_OK if the command has been accepted, E_NOT_OK if the command has
 *          not been accepted e.g. due to parameter error
 *
 * @reqs    SWS_Mcu_00156
 */
Std_ReturnType Mcu_DistributePllClock( void )
{
    return E_OK;
}

/**
 * @brief    **Get PLL lock status**
 *
 * Service which provides the lock status of the PLL
 *
 * @retval  Mcu_PllStatusType: MCU_PLL_LOCKED when the PLL is locked, MCU_PLL_UNLOCKED,
 *          MCU_PLL_STATUS_UNDEFINED when status is unknown
 *
 * @reqs    SWS_Mcu_00157
 */
Mcu_PllStatusType Mcu_GetPllStatus( void )
{
    return E_OK;
}

/**
 * @brief    **Get MCU reset type**
 *
 * Service which reads the reset type from the hardware, if supported
 *
 * @retval  Mcu_ResetType: MCU_POWER_ON_RESET, MCU_WATCHDOG_RESET, MCU_SW_RESET,
 *          MCU_RESET_UNDEFINED
 *
 * @reqs    SWS_Mcu_00158
 */
Mcu_ResetType Mcu_GetResetReason( void )
{
    return E_OK;
}

/**
 * @brief    **Get reset raw value**
 *
 * Service which reads the reset type from the hardware register, if supported
 *
 * @retval  Mcu_RawResetType: Reset raw value
 *
 * @reqs    SWS_Mcu_00159
 */
Mcu_RawResetType Mcu_GetResetRawValue( void )
{
    return E_OK;
}

/**
 * @brief    **Reset the MCU**
 *
 * Service to perform a microcontroller reset
 *
 * @reqs    SWS_Mcu_00160
 */
void Mcu_PerformReset( void )
{
}

/**
 * @brief    **Set MCU power mode**
 *
 * Service to activate the MCU power modes
 *
 * @param   McuMode  Set different MCU power modes configured in the configuration set
 *
 * @reqs    SWS_Mcu_00161
 */
void Mcu_SetMode( Mcu_ModeType McuMode )
{
    (void)McuMode;
}

/**
 * @brief    **Get version information**
 *
 * Service to return the version information of this module
 *
 * @param   versioninfo  Pointer to where to store the version information of this module
 *
 * @reqs    SWS_Mcu_00162
 */
void Mcu_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void)versioninfo;
}

/**
 * @brief    **Get status of MCU RAM**
 *
 * Service which provides the actual status of the microcontroller RAM. (if supported)
 *
 * @retval  Mcu_RamStateType: Status of the RAM Content
 *
 * @reqs    SWS_Mcu_00207
 */
Mcu_RamStateType Mcu_GetRamState( void )
{
    return E_OK;
}
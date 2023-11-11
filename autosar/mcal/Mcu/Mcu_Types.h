/**
 * @file    Mcu_Types.h
 * @brief   **Mcu Driver Types**
 * @author  Angel Lozano
 *
 * This header file contains type definitions used by Mcu module
 */
#ifndef MCU_TYPES_H__
#define MCU_TYPES_H__

#include "Registers.h"
#include "Std_Types.h"

/**
 * @brief **Hardware dependent structure**
 *
 * A pointer to this type is provided to MCU initialization routines for configuration
 *
 * @reqs SWS_Mcu_00249
 */
typedef struct _Mcu_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Mcu_ConfigType;

/**
 * @brief   **Status value returned by the function Mcu_GetPllStatus of the MCU module**
 *
 * @reqs    SWS_Mcu_00250
 */
typedef enum _Mcu_PllStatusType
{
    MCU_PLL_LOCKED = 0x00,   /*!< The PLL is locked         */
    MCU_PLL_UNLOCKED,        /*!< The PLL is unlocked       */
    MCU_PLL_STATUS_UNDEFINED /*!< The PLL Status is unknown */
} Mcu_PllStatusType;

/**
 * @brief   **ID for a clock setting**
 *
 * The range is dependent on the number of different clock settings provided in the
 * configuration structure
 *
 * @reqs    SWS_Mcu_00251
 */
typedef uint32 Mcu_ClockType;

/**
 * @brief   **Reset types**
 *
 * @reqs    SWS_Mcu_00252
 */
typedef enum _Mcu_ResetType
{
    MCU_POWER_ON_RESET = 0x00, /*!< Power On Reset                */
    MCU_WATCHDOG_RESET,        /*!< Internal Watchdog Timer Reset */
    MCU_SW_RESET,              /*!< Software Reset                */
    MCU_RESET_UNDEFINED        /*!< Reset is undefined            */
} Mcu_ResetType;

/**
 * @brief   **Specifies the reset reason in raw register format read from reset status register**
 *
 * @reqs    SWS_Mcu_00253
 */
typedef uint32 Mcu_RawResetType;

/**
 * @brief   **Specifies the identification (ID) for a MCU mode**
 *
 * @reqs    SWS_Mcu_00254
 */
typedef uint32 Mcu_ModeType;

/**
 * @brief   **Specifies the identification (ID) for a RAM section**
 *
 * @reqs    SWS_Mcu_00255
 */
typedef uint32 Mcu_RamSectionType;

/**
 * @brief   **RAM state (valid or invalid)**
 *
 * Ram State data type returned by the function Mcu_GetRamState of the Mcu module
 *
 * @reqs    SWS_Mcu_00256
 */
typedef enum _Mcu_RamStateType
{
    MCU_RAMSTATE_INVALID = 0x00, /*!< Ram content is not valid or unknown */
    MCU_RAMSTATE_VALID,          /*!< Ram content is valid                */
} Mcu_RamStateType;

#endif
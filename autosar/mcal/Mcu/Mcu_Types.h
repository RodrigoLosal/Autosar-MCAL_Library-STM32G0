/**
 * @file    Mcu_Types.h
 * @brief   **Mcu Driver Types**
 * @author  Angel Lozano
 *
 * This header file contains type definitions used by Mcu module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef MCU_TYPES_H__
#define MCU_TYPES_H__

#include "Registers.h"
#include "Std_Types.h"

/**
 * @defgroup MCU_Ids MCU Id number for module and each API service
 *
 * @{ */
#define MCU_ID_INIT                 0x00u /*!< Mcu_Init() api service id */
#define MCU_ID_INIT_RAM             0x01u /*!< Mcu_InitRamSection() api service id */
#define MCU_ID_INIT_CLOCK           0x02u /*!< Mcu_InitClock() api service id */
#define MCU_ID_DISTRIBUTE_PLL_CLOCK 0x03u /*!< Mcu_DistributePllClock() api service id */
#define MCU_ID_GET_PLL_STATUS       0x04u /*!< Mcu_GetPllStatus() api service id */
#define MCU_ID_GET_RESET_REASON     0x05u /*!< Mcu_GetResetReason() api service id */
#define MCU_ID_GET_RESET_RAW_VALUE  0x06u /*!< Mcu_GetResetRawValue() api service id */
#define MCU_ID_PERFORM_RESET        0x07u /*!< Mcu_PerformReset() api service id */
#define MCU_ID_SET_MODE             0x08u /*!< Mcu_SetMode() api service id */
#define MCU_ID_GET_VERSION_INFO     0x09u /*!< Mcu_GetVersionInfo() api service id */
#define MCU_ID_GET_RAM_STATE        0x0Au /*!< Mcu_GetRamState() api service id */
/**
 * @} */

/**
 * @defgroup MCU_Error_Type MCU Development Error Types
 *
 * @{ */
#define MCU_E_PARAM_CONFIG          0x0Au /*!< API service called with wrong parameter */
#define MCU_E_PARAM_CLOCK           0x0Bu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_MODE            0x0Cu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_RAMSECTION      0x0Du /*!< API service called with wrong parameter */
#define MCU_E_PLL_NOT_LOCKED        0x0Eu /*!< API service called with wrong parameter */
#define MCU_E_UNINIT                0x0Fu /*!< API service called with wrong parameter */
#define MCU_E_PARAM_POINTER         0x10u /*!< API service called with wrong parameter */
#define MCU_E_INIT_FAILED           0x11u /*!< API service called with wrong parameter */
/**
 * @} */

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

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Mcu_HwUnit
{
    const Mcu_ConfigType *Config; /*!< Pointer to the configuration structure */
} Mcu_HwUnit;

#endif
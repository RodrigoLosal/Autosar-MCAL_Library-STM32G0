/**
 * @file    Fls_Types.h
 * @brief   **Flash Driver Types**
 * @author  Christopher Bogarin
 *
 * The header contains the type definitions that are used by the Flash module.
 * The file is implemnted as a means of abstraction from the hardware,
 * this way we can avoid to include Arch headers in the actual driver header,
 * making the low level interfaces available for upper layers.
 */
#ifndef FLASH_TYPES_H__
#define FLASH_TYPES_H__

#include "Registers.h"

/**
  * @defgroup Fls_Ids Flash Id number for module and each API.
  @{ */
#define FLS_ID_INIT               0x00u /*!< Fls_Init() api service id */
#define FLS_ID_ERASE              0x01u /*!< Fls_Erase() api service id */
#define FLS_ID_WRITE              0x02u /*!< Fls_Write() api service id */
#define FLS_ID_CANCEL             0x03u /*!< Fls_Cancel() api service id */
#define FLS_ID_GETSTATUS          0x04u /*!< Fls_GetStatus() api service id */
#define FLS_ID_GETJOBRESULT       0x05u /*!< Fls_GetJobResults() api service id */
#define FLS_ID_READ               0x07u /*!< Fls_Read() api service id */
#define FLS_ID_COMPARE            0x08u /*!< Fls_Compare() api service id */
#define FLS_ID_SETMODE            0x09u /*!< Fls_SetMode() api service id */
#define FLS_ID_GETVERSIONINFO     0x10u /*!< Fls_GetVersionInfo() api service id */
#define FLS_ID_BLANKCHECK         0x0au /*!< Fls_BlankCheck() api service id */
/**
  @} */

/**
  * @defgroup Flash Development errors.
  @{ */
#define FLS_E_PARAM_CONFIG        0x00u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_ADDRESS       0x01u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_LENGTH        0x02u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_DATA          0x03u /*!< API service called with wrong parameter */
#define FLS_E_UNINIT              0x04u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_POINTER       0x05u /*!< API service called with wrong parameter */
#define FLS_E_ALREADY_INITIALIZED 0x06u /*!< - */
/**
  @} */

/**
  * @defgroup FLS_Error_Type Flash Runtime Errors.
  @{ */
#define FLS_E_BUSY                0x06u /*!< API service called while driver still busy */
#define FLS_E_VERIFY_ERASE_FAILED 0x07u /*!< Erase verification (blank check) failed */
#define FLS_E_VERIFY_WRITE_FAILED 0x08u /*!< Write verification (compare) failed */
#define FLS_E_TIMEOUT             0x09u /*!< Timeout exceeded */
/**
  @} */

/**
  * @defgroup FLS_Error_TYPE Flash Transient Faults.
  @{ */
#define FLS_E_ERASE_FAILED        0x01u /*!< Flash erase failed (HW) */
#define FLS_E_WRITE_FAILED        0x02u /*!< Flash write failed (HW) */
#define FLS_E_READ_FAILED         0x03u /*!< Flash read failed (HW) */
#define FLS_E_COMPARE_FAILED      0x04u /*!< Flash compare failed (HW) */
#define FLS_E_UNEXPECTED_FLASH_ID 0x05u /*!< Expected hardware ID not matched (see SWS_ Fls_00144) */
/**
  @} */

/**
 * @brief   Fls_AddressType.
 *
 * Used as address offset from the configured flash base address
 * to access a certain flash memory area.
 *
 * @reqs    SWS_Fls_00369, SWS_Fls_00216
 */
typedef uint32 Fls_AddressType;

/**
 * @brief   Fls_LengthType.
 *
 * Specifies the number of bytes to read/write/erase/compare.
 *
 * @reqs    SWS_Fls_00370
 */
typedef uint32 Fls_LengthType;


/**
 * @brief   Fls_ConfigType.
 *
 * A pointer to such a structure is provided to the flash driver initialization routine
 * for configuration of the driver and flash memory hardware.
 *
 * @reqs    SWS_Fls_00368
 */
typedef struct _Fls_ConfigType
{
    Fls_AddressType MemoryBaseAddress; /*!<Variable to use to erase start address*/
    Fls_AddressType EraseStartAddress; /*!<Variable to use to erase end address*/
    Fls_LengthType FlsSectorSize;      /*!<Variable to use to flash sector boundary*/
    uint16 FlsNumberOfSectors;         /*!<Variable to describe the sector in Flash*/
    Fls_LengthType MaxReadMode;        /*!<Maximum elemnt to read*/
    Fls_LengthType MaxWriteMode;       /*!<Maximum element to write*/
    Fls_LengthType num_bytes;          /*!<Num of bytes to read, write, erase, compare*/
    uint32 dummy;                      /*!< dummy element for the moment */
} Fls_ConfigType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Fls_HwUnit
{
    const Fls_ConfigType *Config; /*!< Pointer to the configuration structure */
    uint8 HwUnitState;            /*!< FLS hardware unit state                */
} Fls_HwUnit;


#endif
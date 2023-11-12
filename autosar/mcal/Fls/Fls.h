/**
 * @file    Fls.h
 * @brief   **Flash Driver header**
 * @author  Christopher Bogarin
 *
 * The flash driver provides services for reading, writing and erasing flash memory and a
 * configuration interface for setting / resetting the write / erase protection
 * if supported by the underlying hardware.
 * In application mode of the ECU, the flash driver is only to be used by the Flash EEPROM
 * emulation module for writing data. It is not intended to write program code to flash memory
 * in application mode.
 *
 */
#ifndef FLASH_H__
#define FLASH_H__

#include "Fls_Cfg.h"

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
#define FLS_E_PARAM_CONFIG        0x01u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_ADDRESS       0x02u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_LENGTH        0x03u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_DATA          0x04u /*!< API service called with wrong parameter */
#define FLS_E_UNINIT              0x05u /*!< API service called with wrong parameter */
#define FLS_E_PARAM_POINTER       0x0au /*!< API service called with wrong parameter */
#define FLS_E_ALREADY_INITIALIZED 0x0bu /*!< - */
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

void Fls_Init( const Fls_ConfigType *ConfigPtr );
Std_ReturnType Fls_Erase( Fls_AddressType TargetAddress, Fls_LengthType Length );
Std_ReturnType Fls_Write( Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length );
#if FLS_CANCEL_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_Cancel( void );
#endif
#if FLS_GET_STATUS_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_StatusType Fls_GetStatus( void );
#endif
#if FLS_GET_JOB_RESULT_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_JobResultType Fls_GetJobResult( void );
#endif
Std_ReturnType Fls_Read( Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length );
#if FLS_COMPARE_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length );
#endif
#if FLS_SET_MODE_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_SetMode( MemIf_ModeType Mode );
#endif
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr );
#if FLS_BLANK_CHECK_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_BlankCheck( Fls_AddressType TargetAddress, Fls_LengthType Length );
#endif

#endif
/**
 * @file    Mcu.h
 * @brief   **Mcu Driver header**
 * @author  Angel Lozano
 *
 * The MCU driver provides services for basic microcontroller initialization, power down
 * functionality, reset and microcontroller specific functions required by other MCAL
 * software modules. The initialization services allow a flexible and application related
 * MCU initialization in addition to the start-up code.
 */
#ifndef MCU_H__
#define MCU_H__

#include "Mcu_Cfg.h"

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

void Mcu_Init( const Mcu_ConfigType *ConfigPtr );
Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection );
#if MCU_INIT_CLOCK == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting );
#endif
#if MCU_NO_PLL == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Mcu_DistributePllClock( void );
#endif
Mcu_PllStatusType Mcu_GetPllStatus( void );
Mcu_ResetType Mcu_GetResetReason( void );
Mcu_RawResetType Mcu_GetResetRawValue( void );
#if MCU_PERFORM_RESET_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Mcu_PerformReset( void );
#endif
void Mcu_SetMode( Mcu_ModeType McuMode );
void Mcu_GetVersionInfo( Std_VersionInfoType *versioninfo );
#if MCU_GET_RAM_STATE_API == TRUE /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Mcu_RamStateType Mcu_GetRamState( void );
#endif

#endif
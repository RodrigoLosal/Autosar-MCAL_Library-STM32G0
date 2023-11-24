/**
 * @file    Det.h
 * @brief   **DET driver configuration**
 * @author  Oscar Gonzalez
 *
 * The driver Default Error Tracer serve as a mechanisim for reporting and tracing
 * development and runtime errors within the Basic Software.
 */
#ifndef DET_H__
#define DET_H__

/**
 * @defgroup DET_Ids Dt Id number for module and each API
 *
 * @{ */
#define DET_ID_INIT                   0x00u /*!< Det_Init() api service id */
#define DET_ID_REPORT_ERROR           0x01u /*!< Det_ReportError() api service id */
#define DET_ID_DE_START               0x02u /*!< Det_Start() api service id */
#define DET_ID_GET_VERSION_INFO       0x03u /*!< Det_GetVersionInfo() api service id */
#define DET_ID_REPORT_RUNTIME_ERROR   0x04u /*!< Det_ReportRuntimeError() api service id */
#define DET_ID_REPORT_TRANSIENT_FAULT 0x05u /*!< Det_ReportTransientFault() api service id */
/**
 * @} */

/**
 * @defgroup DET_Error_Type Det Developtment Error Types
 *
 * @{ */
#define DET_E_PARAM_POINTER           0x01u /*!< Det_GetVersionInfo called with null parameter pointer */
/**
 * @} */

/**
 * @brief **Det Config type**
 *
 * 	Configuration data structure of the Det module
 *
 * @reqs SWS_Det_00210
 */
typedef struct _Det_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Det_ConfigType;

/**
 * @brief **Structure for Reporting error**
 *
 * @reqs    SWS_Det_00009
 */
typedef struct
{
    const char *Module;   /**< Report Error for ModuleId*/
    const char *Instance; /**< Report Error for InstanceId*/
    const char *Api;      /**< Report Error for ApiId*/
    const char *Error;    /**< Report Error for ErrorId*/
} DetError;

#include "Det_Cfg.h" /* cppcheck-suppress misra-c2012-20.1 ; Include should be add it after a ConfigType */

void Det_Init( const Det_ConfigType *ConfigPtr );
void Det_Start( void );
Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportRuntimeError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportTransientFault( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId );
#if DET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Det_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#endif
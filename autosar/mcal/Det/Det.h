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

#include "Det_Cfg.h"

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

void Det_Init( const Det_ConfigType *ConfigPtr );
void Det_Start( void );
Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportRuntimeError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportTransientFault( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId );
#if DET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Det_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#endif
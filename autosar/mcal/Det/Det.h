/**
 * @file    Det.h
 * @brief   **DET driver configuration**
 * @author  Oscar Gonzalez
 *
 */

#ifndef DET_H__
#define DET_H__

void Det_Init( const Det_ConfigType *ConfigPtr );
void Det_Start( void );
Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportRuntimeError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId );
Std_ReturnType Det_ReportTransientFault( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId );
#if DET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Det_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#endif
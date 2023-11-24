/**
 * @file    Spi.h
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * The SPI module provides services to initiate transmissions with a terminal buffer and call callback functions
 * to notify events. Additionally, you have the option of having an external buffer to have more memory capacity.
 * This module has the possibility of several JOBs, Channels and sequences.
 */
#ifndef SPI_H__
#define SPI_H__

#include "Spi_Cfg.h"

void Spi_Init( const Spi_ConfigType *Config );
Std_ReturnType Spi_DeInit( void );
Std_ReturnType Spi_WriteIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr );
#if SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Spi_AsyncTransmit( Spi_SequenceType Sequence );
#endif
Std_ReturnType Spi_ReadIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr );
Std_ReturnType Spi_SetupEB( Spi_ChannelType Channel, const Spi_DataBufferType *SrcDataBufferPtr, Spi_DataBufferType *DesDataBufferPtr, Spi_NumberOfDataType Length );
Spi_StatusType Spi_GetStatus( void );
Spi_JobResultType Spi_GetJobResult( Spi_JobType Job );
Spi_SeqResultType Spi_GetSequenceResult( Spi_SequenceType Sequence );
#if SPI_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Spi_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
Std_ReturnType Spi_SyncTransmit( Spi_SequenceType Sequence );
#if SPI_HW_STATUS_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Spi_StatusType Spi_GetHWUnitStatus( Spi_HWUnitType HWUnit );
#endif
#if SPI_CANCEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Spi_Cancel( Spi_SequenceType Sequence );
Std_ReturnType Spi_SetAsyncMode( Spi_AsyncModeType Mode );
#endif

#endif /* SPI_H__ */

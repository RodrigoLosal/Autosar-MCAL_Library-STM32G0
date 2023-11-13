/**
 * @file    Spi_Arch.h
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * The SPI module provides services to initiate transmissions with a terminal buffer and call callback functions
 * to notify events. Additionally, you have the option of having an external buffer to have more memory capacity.
 * This module has the possibility of several JOBs, Channels and sequences.
 */
#ifndef SPI_ARCH_H__
#define SPI_ARCH_H__

#include "Spi_Cfg.h"


void Spi_Arch_Init( Spi_HwUnit *HwUnit, const Spi_ConfigType *Config );
Std_ReturnType Spi_Arch_DeInit( Spi_HwUnit *HwUnit );
Std_ReturnType Spi_Arch_WriteIB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr );
#if SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Spi_Arch_AsyncTransmit( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence );
#endif
Std_ReturnType Spi_Arch_ReadIB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr );
Std_ReturnType Spi_Arch_SetupEB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *SrcDataBufferPtr, Spi_DataBufferType *DesDataBufferPtr, Spi_NumberOfDataType Length );
Spi_StatusType Spi_Arch_GetStatus( Spi_HwUnit *HwUnit );
Spi_JobResultType Spi_Arch_GetJobResult( Spi_HwUnit *HwUnit, Spi_JobType Job );
Spi_SeqResultType Spi_Arch_GetSequenceResult( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence );
#if SPI_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Spi_Arch_GetVersionInfo( Spi_HwUnit *HwUnit, Std_VersionInfoType *versioninfo );
#endif
Std_ReturnType Spi_Arch_SyncTransmit( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence );
#if SPI_HW_STATUS_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Spi_StatusType Spi_Arch_GetHWUnitStatus( Spi_HwUnit *HwUnit, Spi_HWUnitType HWUnit );
#endif
#if SPI_CANCEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Spi_Arch_Cancel( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence );
Std_ReturnType Spi_Arch_SetAsyncMode( Spi_HwUnit *HwUnit, Spi_AsyncModeType Mode );
#endif

#endif /* SPI_H__ */

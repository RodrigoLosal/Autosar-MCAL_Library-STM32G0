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

/**
 * @defgroup Spi_Ids Spi Id number for module and each API
 *
 * @{ */
#define SPI_ID_INIT                0x00u /*!< Spi_Init() api service id */
#define SPI_ID_DE_INIT             0x01u /*!< Spi_DeInit() api service id */
#define SPI_ID_WRITE_IB            0x02u /*!< Spi_WriteIB() api service id */
#define SPI_ID_ASYNC_TRANSMIT      0x03u /*!< Spi_AsyncTransmit() api service id */
#define SPI_ID_READ_IB             0x04u /*!< Spi_ReadIB() api service id */
#define SPI_ID_SET_UP_EB           0x05u /*!< Spi_SetupEB() api service id */
#define SPI_ID_GET_STATUS          0x06u /*!< Spi_GetStatus() api service id */
#define SPI_ID_GET_JOB_RESULT      0x07u /*!< Spi_GetJobResult() api service id */
#define SPI_ID_GET_SEQUENCE_RESULT 0x08u /*!< Spi_GetSequenceResult() api service id */
#define SPI_ID_GET_VERSION_INFO    0x09u /*!< Spi_GetVersionInfo() api service id */
#define SPI_ID_SYNC_TRANSMIT       0x0Au /*!< Spi_SyncTransmit() api service id */
#define SPI_ID_GET_HWUNIT_STATUS   0x0Bu /*!< Spi_GetHWUnitStatus() api service id */
#define SPI_ID_CANCEL              0x0Cu /*!< Spi_Cancel() api service id */
#define SPI_ID_SET_ASYNC_MODE      0x0Du /*!< Spi_SetAsyncMode() api service id */
/**
 * @} */

/**
 * @defgroup Spi_Error_Typse Spi Developtmnet Error Types
 *
 * @{ */
#define SPI_E_PARAM_CHANNEL        0x0Au /*!< API service called with wrong channel  */
#define SPI_E_PARAM_JOB            0x0Bu /*!< API service called with wrong job */
#define SPI_E_PARAM_SEQ            0x0Cu /*!< API service called with wrong sequence */
#define SPI_E_PARAM_LENGTH         0x0Du /*!< API service called with wrong length for EB */
#define SPI_E_PARAM_UNIT           0x0Eu /*!< API service called with wrong hardware unit */
#define SPI_E_PARAM_POINTER        0x10u /*!< APIs called with an unexpected value for the pointer */
#define SPI_E_UNINIT               0x1Au /*!< API service used without module initialization */
#define SPI_E_ALREADY_INITIALIZED  0x4Au /*!< API SPI_Init service called while the SPI driver has been already initialized*/
/**
 * @} */

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

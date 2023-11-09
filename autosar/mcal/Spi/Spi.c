/**
 * @file    Spi.c
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * The SPI module provides services to initiate transmissions with a terminal buffer and call callback functions
 * to notify events. Additionally, you have the option of having an external buffer to have more memory capacity.
 * This module has the possibility of several JOBs, Channels and sequences.
 *
 * A Job is composed of one or several Channels with the same Chip Select (CS) .
 */

#include "Std_Types.h"
#include "Spi.h"

/**
 * @brief    **Spi Initialization**
 *
 * Service for SPI initialization.
 *
 * @param    ConfigPtr Pointer to configuration set
 *
 * @reqs    SWS_Spi_00175
 */
void Spi_Init( const Spi_ConfigType *ConfigPtr )
{
    (void)ConfigPtr;
}

/**
 * @brief    **Spi De-Initialization**
 *
 * Service for SPI de-initialization.
 *
 * @retval  E_OK: de-initialisation command has been accepted
 *          E_NOT_OK: de-initialisation command has not been accepted
 *
 * @reqs    SWS_Spi_00176
 */
Std_ReturnType Spi_DeInit( void )
{
    return E_NOT_OK;
}

/**
 * @brief    **Spi Write in the Internal Buffer**
 *
 * Service for writing one or more data to an IB SPI Handler/Driver Channel specified
 * by parameter.
 *
 * @param    Channel Channel ID
 * @param    DataBufferPtr  Pointer to source data buffer. If this pointer is null, it is assumed that
 *                          the data to be transmitted is not relevant and the default transmit
 *                          value of this channel will be used instead.
 *
 * @retval  E_OK: write command has been accepted
 *          E_NOT_OK: write command has not been accepted
 *
 * @reqs    SWS_Spi_00177
 */
Std_ReturnType Spi_WriteIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    (void)Channel;
    (void)DataBufferPtr;
    return E_NOT_OK;
}

#if SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Spi Asynchronous Transmit**
 *
 * Service to transmit data on the SPI bus.
 *
 * @param    Sequence Sequence ID
 *
 * @retval  E_OK: Transmission command has been accepted
 *          E_NOT_OK: Transmission command has not been accepted
 *
 * @reqs    SWS_Spi_00178
 */
Std_ReturnType Spi_AsyncTransmit( Spi_SequenceType Sequence )
{
    (void)Sequence;
    return E_NOT_OK;
}
#endif

/**
 * @brief    **Spi Read in the Internal Buffer**
 *
 * Service for reading synchronously one or more data from an IB SPI
 * Handler/Driver Channel specified by parameter.
 *
 * @param    Channel Channel ID
 * @param    DataBufferPtr Pointer to destination data buffer in RAM
 *
 * @retval  E_OK: read command has been accepted
 *          E_NOT_OK: read command has not been accepted
 *
 * @reqs    SWS_Spi_00179
 */
Std_ReturnType Spi_ReadIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    (void)Channel;
    (void)DataBufferPtr;
    return E_NOT_OK;
}

/**
 * @brief    **Spi set up external buffer**
 *
 * Service to setup the buffers and the length of data for the EB SPI
 * Handler/Driver Channel specified.
 *
 * @param   Channel Channel ID
 * @param   SrcDataBufferPtr Pointer to source data buffer
 * @param   Length Length (number of data elements) of the data to be transmitted from
 *                 SrcDataBufferPtr and/or received from DesDataBufferPtr Min.: 1 Max.:
 *                 Max of data specified at configuration for this channel
 * @param   DesDataBufferPtr Pointer to destination data buffer in RAM
 *
 * @retval  E_OK: Setup command  has been accepted
 *          E_NOT_OK: Setup command  has not been accepted
 *
 * @reqs    SWS_Spi_00180
 */
Std_ReturnType Spi_SetupEB( Spi_ChannelType Channel, const Spi_DataBufferType *SrcDataBufferPtr, Spi_DataBufferType *DesDataBufferPtr, Spi_NumberOfDataType Length )
{
    (void)Channel;
    (void)SrcDataBufferPtr;
    (void)DesDataBufferPtr;
    (void)Length;
    return E_NOT_OK;
}

/**
 * @brief    **Spi get status**
 *
 * Service returns the SPI Handler/Driver software module status.
 *
 * @retval  Spi_StatusType: Spi_StatusType
 *
 * @reqs    SWS_Spi_00181
 */
Spi_StatusType Spi_GetStatus( void )
{
    return SPI_UNINIT;
}

/**
 * @brief    **Spi get job result**
 *
 * This service returns the last transmission result of the specified Job.
 *
 * @param   Job Job ID. An invalid job ID will return an undefined result
 *
 * @retval  Spi_JobResultType: Spi_JobResultType
 *
 * @reqs    SWS_Spi_00182
 */
Spi_JobResultType Spi_GetJobResult( Spi_JobType Job )
{
    (void)Job;
    return SPI_JOB_FAILED;
}

/**
 * @brief    **Spi get sequence result**
 *
 * This service returns the last transmission result of the specified Sequence.
 *
 * @param   Sequence Sequence ID. An invalid sequence ID will return an undefined result
 *
 * @retval  Spi_SeqResultType: Spi_SeqResultType
 *
 * @reqs    SWS_Spi_00183
 */
Spi_SeqResultType Spi_GetSequenceResult( Spi_SequenceType Sequence )
{
    (void)Sequence;
    return SPI_SEQ_FAILED;
}

#if SPI_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Spi get version information**
 *
 * This service returns the version information of this module.
 *
 * @param   versioninfo Pointer to where to store the version information of this module
 *
 * @reqs    SWS_Spi_00184
 */
void Spi_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void)versioninfo;
}
#endif

/**
 * @brief    **Spi synchronous transmit**
 *
 * Service to transmit data on the SPI bus.
 *
 * @param   Sequence Sequence ID
 *
 * @retval  E_OK: Transmission has been successful
 *          E_NOT_OK: Transmission failed
 *
 * @reqs    SWS_Spi_00185
 */
Std_ReturnType Spi_SyncTransmit( Spi_SequenceType Sequence )
{
    (void)Sequence;
    return E_NOT_OK;
}

#if SPI_HW_STATUS_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Spi get Hardware microcontroller peripheral Unit Status**
 *
 * This service returns the status of the specified SPI Hardware microcontroller
 * peripheral.
 *
 * @param   HWUnit SPI Hardware microcontroller peripheral (unit) ID.
 *
 * @retval  Spi_StatusType: Spi_StatusType
 *
 * @reqs    SWS_Spi_00186
 */
Spi_StatusType Spi_GetHWUnitStatus( Spi_HWUnitType HWUnit )
{
    (void)HWUnit;
    return SPI_UNINIT;
}
#endif

#if SPI_CANCEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Spi cancel**
 *
 * Service cancels the specified on-going sequence transmission.
 *
 * @param   Sequence Sequence ID
 *
 * @reqs    SWS_Spi_00187
 */
void Spi_Cancel( Spi_SequenceType Sequence )
{
    (void)Sequence;
}
#endif

/**
 * @brief    **Spi set asynchronous mode**
 *
 * Service to set the asynchronous mechanism mode for SPI busses handled asynchronously.
 *
 * @param   Mode New mode required.
 *
 * @retval  E_OK: Setting command has been done
 *          E_NOT_OK: setting command has not been accepted
 *
 * @reqs    SWS_Spi_00188
 */
Std_ReturnType Spi_SetAsyncMode( Spi_AsyncModeType Mode )
{
    (void)Mode;
    return E_NOT_OK;
}
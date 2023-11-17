/**
 * @file    Spi_Arch.c
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
#include "Spi_Arch.h"

/**
 * @brief    **Spi Initialization**
 *
 * Service for SPI initialization.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Config Pointer to configuration set
 */
void Spi_Arch_Init( Spi_HwUnit *HwUnit, const Spi_ConfigType *Config )
{
    (void)HwUnit;
    (void)Config;
}

/**
 * @brief    **Spi De-Initialization**
 *
 * Service for SPI de-initialization.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  E_OK: de-initialisation command has been accepted
 *          E_NOT_OK: de-initialisation command has not been accepted
 */
Std_ReturnType Spi_Arch_DeInit( Spi_HwUnit *HwUnit )
{
    (void)HwUnit;
    return E_NOT_OK;
}

/**
 * @brief    **Spi Write in the Internal Buffer**
 *
 * Service for writing one or more data to an IB SPI Handler/Driver Channel specified
 * by parameter.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param    Channel Channel ID
 * @param    DataBufferPtr  Pointer to source data buffer. If this pointer is null, it is assumed that the data to be transmitted
 *                          is not relevant and the default transmit value of this channel will be used instead.
 *
 * @retval  E_OK: write command has been accepted
 *          E_NOT_OK: write command has not been accepted
 */
Std_ReturnType Spi_Arch_WriteIB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    (void)HwUnit;
    (void)Channel;
    (void)DataBufferPtr;
    return E_NOT_OK;
}

/**
 * @brief    **Spi Asynchronous Transmit**
 *
 * Service to transmit data on the SPI bus.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Sequence Sequence ID
 *
 * @retval  E_OK: Transmission command has been accepted
 *          E_NOT_OK: Transmission command has not been accepted
 */
Std_ReturnType Spi_Arch_AsyncTransmit( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence )
{
    (void)HwUnit;
    (void)Sequence;
    return E_NOT_OK;
}

/**
 * @brief    **Spi Read in the Internal Buffer**
 *
 * Service for reading synchronously one or more data from an IB SPI
 * Handler/Driver Channel specified by parameter.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param    Channel Channel ID
 * @param    DataBufferPtr Pointer to destination data buffer in RAM
 *
 * @retval  E_OK: read command has been accepted
 *          E_NOT_OK: read command has not been accepted
 */
Std_ReturnType Spi_Arch_ReadIB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    (void)HwUnit;
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
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Channel Channel ID
 * @param   SrcDataBufferPtr Pointer to source data buffer
 * @param   Length Length (number of data elements) of the data to be transmitted from SrcDataBufferPtr and/or received from
 *                 DesDataBufferPtr Min.: 1 Max.: Max of data specified at configuration for this channel.
 * @param   DesDataBufferPtr Pointer to destination data buffer in RAM
 *
 * @retval  E_OK: Setup command  has been accepted
 *          E_NOT_OK: Setup command  has not been accepted
 */
Std_ReturnType Spi_Arch_SetupEB( Spi_HwUnit *HwUnit, Spi_ChannelType Channel, const Spi_DataBufferType *SrcDataBufferPtr, Spi_DataBufferType *DesDataBufferPtr, Spi_NumberOfDataType Length )
{
    (void)HwUnit;
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
 * @param   HwUnit Pointer to the hardware unit configuration
 *
 * @retval  Spi_StatusType: Spi_StatusType
 */
Spi_StatusType Spi_Arch_GetStatus( Spi_HwUnit *HwUnit )
{
    (void)HwUnit;
    return SPI_UNINIT;
}

/**
 * @brief    **Spi get job result**
 *
 * This service returns the last transmission result of the specified Job.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Job Job ID. An invalid job ID will return an undefined result
 *
 * @retval  Spi_JobResultType: Spi_JobResultType
 */
Spi_JobResultType Spi_Arch_GetJobResult( Spi_HwUnit *HwUnit, Spi_JobType Job )
{
    (void)HwUnit;
    (void)Job;
    return SPI_JOB_FAILED;
}

/**
 * @brief    **Spi get sequence result**
 *
 * This service returns the last transmission result of the specified Sequence.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Sequence Sequence ID. An invalid sequence ID will return an undefined result
 *
 * @retval  Spi_SeqResultType: Spi_SeqResultType
 */
Spi_SeqResultType Spi_Arch_GetSequenceResult( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence )
{
    (void)HwUnit;
    (void)Sequence;
    return SPI_SEQ_FAILED;
}

/**
 * @brief    **Spi get version information**
 *
 * This service returns the version information of this module.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   versioninfo Pointer to where to store the version information of this module
 */
void Spi_Arch_GetVersionInfo( Spi_HwUnit *HwUnit, Std_VersionInfoType *versioninfo )
{
    (void)HwUnit;
    (void)versioninfo;
}

/**
 * @brief    **Spi synchronous transmit**
 *
 * Service to transmit data on the SPI bus.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Sequence Sequence ID
 *
 * @retval  E_OK: Transmission has been successful
 *          E_NOT_OK: Transmission failed
 */
Std_ReturnType Spi_Arch_SyncTransmit( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence )
{
    (void)HwUnit;
    (void)Sequence;
    return E_NOT_OK;
}

/**
 * @brief    **Spi get Hardware microcontroller peripheral Unit Status**
 *
 * This service returns the status of the specified SPI Hardware microcontroller
 * peripheral.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   HWUnit SPI Hardware microcontroller peripheral (unit) ID.
 *
 * @retval  Spi_StatusType: Spi_StatusType
 */
Spi_StatusType Spi_Arch_GetHWUnitStatus( Spi_HwUnit *HwUnit, Spi_HWUnitType HWUnit )
{
    (void)HwUnit;
    (void)HWUnit;
    return SPI_UNINIT;
}
/**
 * @brief    **Spi cancel**
 *
 * Service cancels the specified on-going sequence transmission.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Sequence Sequence ID
 */
void Spi_Arch_Cancel( Spi_HwUnit *HwUnit, Spi_SequenceType Sequence )
{
    (void)HwUnit;
    (void)Sequence;
}

/**
 * @brief    **Spi set asynchronous mode**
 *
 * Service to set the asynchronous mechanism mode for SPI busses handled asynchronously.
 *
 * @param   HwUnit Pointer to the hardware unit configuration
 * @param   Mode New mode required.
 *
 * @retval  E_OK: Setting command has been done
 *          E_NOT_OK: setting command has not been accepted
 */
Std_ReturnType Spi_Arch_SetAsyncMode( Spi_HwUnit *HwUnit, Spi_AsyncModeType Mode )
{
    (void)HwUnit;
    (void)Mode;
    return E_NOT_OK;
}
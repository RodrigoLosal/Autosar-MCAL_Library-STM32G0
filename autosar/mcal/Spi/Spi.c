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
#include "Spi_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Spi_Cfg.h */
#if SPI_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
static Spi_HwUnit HwUnit_Spi =
{
    .Config         = NULL_PTR,
    .HwUnitState    = SPI_UNINIT,
    .SpiState       = SPI_UNINIT,
};
/* clang-format on */

/**
 * @brief    **Spi Initialization**
 *
 * Service for SPI initialization.
 *
 * @param    ConfigPtr Pointer to configuration set
 *
 * @reqs    SWS_Spi_00175, SWS_Spi_00233
 */
void Spi_Init( const Spi_ConfigType *ConfigPtr )
{
    if( ( HwUnit_Spi.HwUnitState != SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /* If development error detection for the SPI module is enabled, the calling of the rou-
        tine SPI_Init() while the SPI driver is already initialized will cause a development error
        SPI_E_ALREADY_INITIALIZED and the desired functionality shall be left without
        any action. */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_ALREADY_INITIALIZED );
    }
    else
    {
        Spi_Arch_Init( &HwUnit_Spi, ConfigPtr );
        HwUnit_Spi.Config = ConfigPtr;
    }
}

/**
 * @brief    **Spi De-Initialization**
 *
 * Service for SPI de-initialization.
 *
 * @retval  E_OK: de-initialisation command has been accepted
 *          E_NOT_OK: de-initialisation command has not been accepted
 *
 * @reqs    SWS_Spi_00176, SWS_Spi_00046
 */
Std_ReturnType Spi_DeInit( void )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else
    {
        value = Spi_Arch_DeInit( &HwUnit_Spi );
    }
    return value;
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
 * @reqs    SWS_Spi_00177, SWS_Spi_00046, SWS_Spi_00031, SWS_Spi_00371
 */
Std_ReturnType Spi_WriteIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Channel >= HwUnit_Spi.Config->ChannelCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_WriteIB shall raise the error SPI_E_PARAM_CHANNEL if the parameter
        Channel ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_CHANNEL );
    }
    else if( DataBufferPtr == NULL_PTR )
    {
        /*If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error SPI_E_PARAM_POINTER
        shall be reported in case the value is a NULL pointer*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_POINTER );
    }
    else
    {
        value = Spi_Arch_WriteIB( &HwUnit_Spi, Channel, DataBufferPtr );
    }
    return value;
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
 * @reqs    SWS_Spi_00178, SWS_Spi_00046, SWS_Spi_00032
 */
Std_ReturnType Spi_AsyncTransmit( Spi_SequenceType Sequence )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Sequence >= HwUnit_Spi.Config->SequenceCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_AsyncTransmit shall raise the error SPI_E_PARAM_SEQ if the parameter
        Sequence ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_SEQ );
    }
    else
    {
        value = Spi_Arch_AsyncTransmit( &HwUnit_Spi, Sequence );
    }
    return value;
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
 * @reqs    SWS_Spi_00179, SWS_Spi_00046, SWS_Spi_00031, SWS_Spi_00371
 */
Std_ReturnType Spi_ReadIB( Spi_ChannelType Channel, const Spi_DataBufferType *DataBufferPtr )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Channel >= HwUnit_Spi.Config->ChannelCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_ReadIB shall raise the error SPI_E_PARAM_CHANNEL if the parameter
        Channel ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_CHANNEL );
    }
    else if( DataBufferPtr == NULL_PTR )
    {
        /*If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error SPI_E_PARAM_POINTER
        shall be reported in case the value is a NULL pointer*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_POINTER );
    }
    else
    {
        value = Spi_Arch_ReadIB( &HwUnit_Spi, Channel, DataBufferPtr );
    }
    return value;
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
 * @reqs    SWS_Spi_00180, SWS_Spi_00046, SWS_Spi_00031, SWS_Spi_00371,SWS_Spi_00060
 */
Std_ReturnType Spi_SetupEB( Spi_ChannelType Channel, const Spi_DataBufferType *SrcDataBufferPtr, Spi_DataBufferType *DesDataBufferPtr, Spi_NumberOfDataType Length )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Channel >= HwUnit_Spi.Config->ChannelCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_SetupEB shall raise the error SPI_E_PARAM_CHANNEL if the parameter
        Channel ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_CHANNEL );
    }
    else if( SrcDataBufferPtr == NULL_PTR )
    {
        /*If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error SPI_E_PARAM_POINTER
        shall be reported in case the value is a NULL pointer*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_POINTER );
    }
    else if( DesDataBufferPtr == NULL_PTR )
    {
        /*If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error SPI_E_PARAM_POINTER
        shall be reported in case the value is a NULL pointer*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_POINTER );
    }
    else if( ( Length > 0 ) && ( Length <= SpiEbMaxLength ) )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_SetupEB shall raise the error SPI_E_PARAM_LENGTH if the parameter
        Length data is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_LENGTH );
    }
    else
    {
        value = Spi_Arch_SetupEB( &HwUnit_Spi, Channel, SrcDataBufferPtr, DesDataBufferPtr, Length );
    }
    return value;
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
    return Spi_Arch_GetStatus( &HwUnit_Spi );
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
 * @reqs    SWS_Spi_00182, SWS_Spi_00046, SWS_Spi_00032
 */
Spi_JobResultType Spi_GetJobResult( Spi_JobType Job )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Job >= HwUnit_Spi.Config->JobCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_GetJobResult shall raise the error SPI_E_PARAM_JOB if the parameter
        Job ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_JOB );
    }
    else
    {
        value = Spi_Arch_GetJobResult( &HwUnit_Spi, Job );
    }
    return value;
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
 * @reqs    SWS_Spi_00183, SWS_Spi_00046, SWS_Spi_00032
 */
Spi_SeqResultType Spi_GetSequenceResult( Spi_SequenceType Sequence )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Sequence >= HwUnit_Spi.Config->SequenceCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_GetSequenceResult shall raise the error SPI_E_PARAM_SEQ if the parameter
        Sequence ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_SEQ );
    }
    else
    {
        value = Spi_Arch_GetSequenceResult( &HwUnit_Spi, Sequence );
    }
    return value;
}

#if SPI_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Spi get version information**
 *
 * This service returns the version information of this module.
 *
 * @param   versioninfo Pointer to where to store the version information of this module
 *
 * @reqs    SWS_Spi_00184, SWS_Spi_00371
 */
void Spi_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /*If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error SPI_E_PARAM_POINTER
        shall be reported in case the value is a NULL pointer*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = SPI_MODULE_ID;
        versioninfo->vendorID         = SPI_VENDOR_ID;
        versioninfo->sw_major_version = SPI_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = SPI_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = SPI_SW_PATCH_VERSION;
    }
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
 * @reqs    SWS_Spi_00185, SWS_Spi_00046, SWS_Spi_00032
 */
Std_ReturnType Spi_SyncTransmit( Spi_SequenceType Sequence )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( Sequence >= HwUnit_Spi.Config->SequenceCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_SyncTransmit shall raise the error SPI_E_PARAM_SEQ if the parameter
        Sequence ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_SEQ );
    }
    else
    {
        value = Spi_Arch_SyncTransmit( &HwUnit_Spi, Sequence );
    }
    return value;
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
 * @reqs    SWS_Spi_00186, SWS_Spi_00046, SWS_Spi_00143
 */
Spi_StatusType Spi_GetHWUnitStatus( Spi_HWUnitType HWUnit )
{
    Std_ReturnType value = E_NOT_OK;

    if( ( HwUnit_Spi.HwUnitState == SPI_UNINIT ) || ( HwUnit_Spi.SpiState != SPI_UNINIT ) )
    {
        /*If development error detection for the SPI module is enabled and the SPI Handler/Driver’s environment
        calls any API function before initialization, an error should be reported to the DET with the error value
        SPI_E_UNINIT according to the configuration */
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_UNINIT );
    }
    else if( HWUnit >= HwUnit_Spi.Config->HWUnitCount )
    {
        /* If development error detection for the Spi module is enabled:
        the function Spi_GetHWUnitStatus shall raise the error SPI_E_PARAM_UNIT if the parameter
        HWUnit ID is out of range.*/
        Det_ReportError( SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ID_INIT, SPI_E_PARAM_UNIT );
    }
    else
    {
        value = Spi_Arch_GetHWUnitStatus( &HwUnit_Spi, HWUnit );
    }
    return value;
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
    Spi_Arch_Cancel( &HwUnit_Spi, Sequence );
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
    return Spi_Arch_SetAsyncMode( &HwUnit_Spi, Mode );
}
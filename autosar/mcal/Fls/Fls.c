/**
 * @file    Fls.c
 * @brief   **Flash Driver**
 * @author  Christopher Bogarin
 *
 * The flash driver provides services for reading,
 * writing and erasing flash memory and a configuration interface
 * for setting / resetting the write / erase protection
 * if supported by the underlying hardware. In application mode of the ECU,
 * the flash driver is only to be used by the Flash EEPROM
 * emulation module for writing data.
 * It is not intended to write program code to flash memory in application mode.
 */

#include "Std_Types.h"
#include "Fls.h"
#include "Fls_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Fls_Cfg.h */
#if FLS_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    Module ID number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Api id
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
static Fls_HwUnit HwUnit_Fls =
{
    .HwUnitState = MEMIF_UNINIT,
    .Config = NULL_PTR,
};
/* clang-format on */

/**
 * @brief   **Fls_Init**
 *
 * Initializes the Flash Driver.
 *
 * @param   ConfigPtr Pointer to flash driver configuration set.
 *
 * @reqs    SWS_Fls_00249, SWS_Fls_00015, SWS_Fls_00323
 */
void Fls_Init( const Fls_ConfigType *ConfigPtr )
{
    if( HwUnit_Fls.HwUnitState != MEMIF_UNINIT )
    {
        /*If development error detection for the module Fls is enabled:
        the function Fls_Init shall check the (hardware specific) contents
        of the given configuration set for being within the allowed range.
        If this is not the case, it shall raise the development error FLS_E_PARAM_CONFIG.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_INIT, FLS_E_PARAM_CONFIG );
    }
    else
    {
        /*Init driver */
        Fls_Arch_Init( &HwUnit_Fls, ConfigPtr );
        /*update Hardware init state*/
        HwUnit_Fls.HwUnitState = MEMIF_IDLE;
        /* make the configuration available */
        HwUnit_Fls.Config = ConfigPtr;
    }
}

/**
 * @brief   **Fls_Erase**
 *
 * Erases flash sector(s).
 *
 * @param   TargetAddress Target address in flash memory. This address offset will be added to the
 *                        flash memory base address. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   Length Number of bytes to erase Min.: 1 Max.: FLS_SIZE - Target Address.
 *
 * @retval  Std_ReturnType E_OK: erase command has been accepted E_NOT_OK: erase command has not been accepted.
 *
 * @reqs     SWS_Fls_00250, SWS_Fls_00020, SWS_Fls_00021, SWS_Fls_00065
 */
Std_ReturnType Fls_Erase( Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    Std_ReturnType returnValue = E_NOT_OK;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Erase shall check
        that the FLS module has been initialized. If this check fails, the function Fls_Erase shall reject 
        the erase request, raise the development error FLS_E_UNINIT and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_ERASE, FLS_E_UNINIT );
    }
    else if( ((HwUnit_Fls.Config->MemoryBaseAddress + TargetAddress) != HwUnit_Fls.Config->FlsSectorSize) || ( TargetAddress > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -1) )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Erase shall check that 
        the erase start address (flash memory base address + TargetAddress) is aligned to a flash sector boundary 
        and that it lies within the specified lower and upper flash address boundaries. If this check fails, the 
        function Fls_Erase shall reject the erase request, raise the development error FLS_E_- PARAM_ADDRESS and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_ERASE, FLS_E_PARAM_ADDRESS );
    }
    else if( (Length == 0) || ((TargetAddress + Length) != HwUnit_Fls.Config->FlsSectorSize) || (Length > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) - TargetAddress))
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Erase shall check that the 
        erase length is greater than 0 and that the erase end address (erase start address + length) is aligned to a 
        flash sector boundary and that it lies within the specified upper flash address boundary. If this check fails,
        the function Fls_Erase shall reject the erase request, raise the development error FLS_E_PARAM_LENGTH and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_ERASE, FLS_E_PARAM_LENGTH);
    }
    else
    {
        return Fls_Arch_Erase( &HwUnit_Fls, TargetAddress, Length );
    }
}

/**
 * @brief   **Fls_Write**
 *
 * Writes one or more complete flash pages.
 *
 * @param   TargetAddress Target address in flash memory. This address offset will be added to the
 *                        flash memory base address. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   SourceAddressPtr Pointer to source data buffer.
 * @param   Length Number of bytes to write Min.: 1 Max.: FLS_SIZE - TargetAddress.
 *
 * @retval  Std_ReturnType E_OK: write command has been accepted E_NOT_OK: write command has not been accepted.
 *
 * @reqs    SWS_Fls_00251, SWS_Fls_00026, SWS_Fls_00027, SWS_Fls_00066, SWS_Fls_00157
 */
Std_ReturnType Fls_Write( Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length )
{
    Std_ReturnType returnValue = E_NOT_OK;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Write shall check that 
        the FLS module has been initialized. If this check fails, the function Fls_Write shall reject the write
        request, raise the development error FLS_E_UNINIT and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_WRITE, FLS_E_UNINIT);
    }
    else if( ((HwUnit_Fls.Config->MemoryBaseAddress + TargetAddress) != HwUnit_Fls.Config->FlsSectorSize) || (TargetAddress > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -1))
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Write shall check that the 
        write start address (flash memory base address + TargetAddress) is aligned to a flash page boundary and that 
        it lies within the specified lower and upper flash address boundaries. If this check fails, the function Fls_Write 
        shall reject the write request, raise the development error FLS_E_- PARAM_ADDRESS and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_WRITE, FLS_E_PARAM_ADDRESS);
    }
    else if( (Length == 0) || ((TargetAddress + Length) != HwUnit_Fls.Config->FlsSectorSize) || (Length > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) - TargetAddress))
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Write shall check that the write 
        length is greater than 0, that the write end address (write start address + length) is aligned to a flash page boundary 
        and that it lies within the specified upper flash address boundary. If this check fails, the function Fls_Write shall 
        reject the write request, raise the development error FLS_E_- PARAM_LENGTH and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_WRITE, FLS_E_PARAM_LENGTH);
    }
    else if( SourceAddressPtr == NULL_PTR)
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Write shall check the given data buffer 
        pointer for not being a null pointer. If the data buffer pointer is a null pointer, the function Fls_Write shall reject 
        the write request, raise the development error FLS_E_PARAM_DATA and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_WRITE, FLS_E_PARAM_DATA);
    }
    else
    {
        return Fls_Arch_Write( &HwUnit_Fls, TargetAddress, SourceAddressPtr, Length );
    }
}

/**
 * @brief   **Fls_Cancel**
 *
 * Cancels an ongoing job.
 *
 * @reqs    SWS_Fls_00252, SWS_Fls_00183, SWS_Fls_00356
 */
#if FLS_CANCEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_Cancel( void )
{
    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Cancel shall check that the FLS module 
        has been initialized. If this check fails, the function Fls_Cancel shall raise the development error FLS_E_- UNINIT and return.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_CANCEL, FLS_E_UNINIT);
    }
    else{
        Fls_Arch_Cancel( &HwUnit_Fls );
    }
}
#endif

/**
 * @brief   **Fls_GetStatus**
 *
 * Returns the driver state.
 *
 * @retval  MemIf_StatusType
 *
 * @reqs    SWS_Fls_00253, SWS_Fls_00184
 */
#if FLS_GET_STATUS_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_StatusType Fls_GetStatus( void )
{
    MemIf_StatusType returnValue = 0;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT)
    {
        returnValue = MEMIF_UNINIT;
    }
    else{
       
        returnValue = Fls_Arch_GetStatus( &HwUnit_Fls );
    }
    return returnValue;
}
#endif

/**
 * @brief   **Fls_GetJobResult**
 *
 * Returns the result of the last job.
 *
 * @retval  MemIf_JobResultType
 *
 * @reqs    SWS_Fls_00254, SWS_Fls_00185,  SWS_Fls_00358
 */
#if FLS_GET_JOB_RESULT_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
MemIf_JobResultType Fls_GetJobResult( void )
{
    MemIf_JobResultType returnValue = MEMIF_JOB_FAILED;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT )
    {
        /*f development error detection for the module Fls is enabled: the function Fls_GetJobResult
        shall check that the FLS module has been initialized. If this check fails, the function Fls_GetJobResult
        shall raise the development error FLS_E_UNINIT and return with MEMIF_JOB_FAILED.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_GETJOBRESULT, FLS_E_UNINIT);
    }
    else
    {
        return Fls_Arch_GetJobResult( &HwUnit_Fls );
    }
}
#endif

/**
 * @brief   **Fls_Read**
 *
 * Reads from flash memory.
 *
 * @param   SourceAddress Source address in flash memory. This address offset will be added to the flash memory base address.
 *                        Min.: 0 Max.: FLS_ SIZE - 1.
 * @param   Length Number of bytes to read Min.: 1 Max.: FLS_SIZE - Source Address.
 * @param   TargetAddressPtr Pointer to target data buffer.
 *
 * @retval  Std_ReturnType E_OK: read command has been accepted E_NOT_OK: read command has not been accepted.
 *
 * @reqs    SWS_Fls_00256, SWS_Fls_00097, SWS_Fls_00098, SWS_Fls_00099, SWS_Fls_00158
 */
Std_ReturnType Fls_Read( Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    Std_ReturnType returnValue = E_NOT_OK;

    if ( HwUnit_Fls.HwUnitState == MEMIF_UNINIT )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Read 
        shall check that the driver has been initialized. If this check fails, the function Fls_Read 
        shall reject the read request, raise the development error FLS_- E_UNINIT and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_READ, FLS_E_UNINIT);
    }
    else if( (HwUnit_Fls.Config->MemoryBaseAddress + SourceAddress) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -1 )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Read shall check 
        that the read start address (flash memory base address + SourceAddress) lies within the specified 
        lower and upper flash address boundaries. If this check fails, the function Fls_Read shall reject 
        the read job, raise development error FLS_E_PARAM_ADDRESS and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_READ, FLS_E_PARAM_ADDRESS);
    }
    else if( (Length == 0) || (SourceAddress + Length) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) - SourceAddress )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Read shall check
        that the read length is greater than 0 and that the read end address (read start address + length) 
        lies within the specified upper flash address boundary. If this check fails, the function Fls_Read 
        shall reject the read job, raise the development error FLS_E_PARAM_LENGTH and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_READ, FLS_E_PARAM_LENGTH);
    }
    else if( TargetAddressPtr == NULL_PTR)
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Read shall check the 
        given data buffer pointer for not being a null pointer. If the data buffer pointer is a null pointer, 
        the function Fls_Read shall reject the read request, raise the development error FLS_E_PARAM_DATA and
        return with E_NOT_ OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_READ, FLS_E_PARAM_DATA);
    }
    else
    {
        return Fls_Arch_Read( &HwUnit_Fls, SourceAddress, TargetAddressPtr, Length );
    }
}

/**
 * @brief   **Fls_Compare**
 *
 * Compares the contents of an area of flash memory with that of an application data buffer.
 *
 * @param   SourceAddress Source address in flash memory.
 *                        This address offset will be added to the flash memory base address. Min.: 0 Max.: FLS_ SIZE - 1.
 * @param   TargetAddressPtr  Pointer to target data buffer.
 * @param   Length Number of bytes to compare Min.: 1 Max.: FLS_SIZE - Source Address.
 *
 * @retval  Std_ReturnType E_OK: read command has been accepted E_NOT_OK: read command has not been accepted.
 *
 * @reqs    SWS_Fls_00257, SWS_Fls_00150, SWS_Fls_00151, SWS_Fls_00152, SWS_Fls_00273, SWS_Fls_00186
 */
#if FLS_COMPARE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    Std_ReturnType returnValue = E_NOT_OK;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT)
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Compare shall check 
        that the driver has been initialized. If this check fails, the function Fls_Compare shall reject the 
        compare job, raise the development error FLS_E_UNINIT and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_COMPARE, FLS_E_UNINIT);
    }
    else if( (HwUnit_Fls.Config->MemoryBaseAddress + SourceAddress) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -1 )
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Compare shall check 
        that the compare start address (flash memory base address + SourceAddress) lies within the specified 
        lower and upper flash address boundaries. If this check fails, the function Fls_Compare shall reject 
        the compare job, raise the development error FLS_E_PARAM_ADDRESS and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_COMPARE, FLS_E_PARAM_ADDRESS);
    }
    else if( (Length == 0) || ((SourceAddress + Length) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -SourceAddress))
    {
        /*If If development error detection for the module Fls is enabled: the function Fls_Compare shall check 
        that the given length is greater than 0 and that the compare end address (compare start address + length) 
        lies within the specified upper flash address boundary. If this check fails, the function Fls_Compare shall 
        reject the compare job, raise the development error FLS_E_PARAM_LENGTH and return with E_ NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_COMPARE, FLS_E_PARAM_LENGTH);
    }
    else if( TargetAddressPtr == NULL_PTR)
    {
        /*If development error detection for the module Fls is enabled: the function Fls_Compare shall check the 
        given data buffer pointer for not being a null pointer. If the data buffer pointer is a null pointer, 
        the function Fls_Compare shall reject the request, raise the development error FLS_E_PARAM_DATA and return
        with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_COMPARE, FLS_E_PARAM_DATA);
    }
    else{
        return Fls_Arch_Compare( &HwUnit_Fls, SourceAddress, TargetAddressPtr, Length );
    }
}
#endif

/**
 * @brief   **Fls_SetMode**
 *
 * Sets the flash driver’s operation mode.
 *
 * @param   Mode  MEMIF_MODE_SLOW: Slow read access / normal SPI access.
 *                MEMIF_MODE_FAST: Fast read access / SPI burst access.
 *
 * @reqs    SWS_Fls_00258, SWS_Fls_00187
 */
#if FLS_SET_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_SetMode( MemIf_ModeType Mode )
{
    Fls_Arch_SetMode( &HwUnit_Fls, Mode );
}
#endif

/**
 * @brief   **Fls_GetVersionInfo**
 *
 * Returns the version information of this module.
 *
 * @param   VersioninfoPtr   Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Fls_00259, SWS_Fls_00363
 */
#if FLS_GET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr )
{
    if( VersioninfoPtr == NULL_PTR)
    {
        /*If development error detection for the module Fls is enabled: the function Fls_GetVersionInfo 
        shall raise the development error FLS_E_PARAM_- POINTER if the argument is a NULL pointer and 
        return without any action.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_GETVERSIONINFO, FLS_E_PARAM_POINTER);
    }else
    {
        VersioninfoPtr->moduleID = FLS_MODULE_ID;
        VersioninfoPtr->vendorID = FLS_VENDOR_ID;
        VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
        VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
        VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;
        
    }
}
#endif

/**
 * @brief   **Fls_BlankCheck**
 *
 * The function Fls_BlankCheck shall verify, whether a given memory area has been erased but not (yet) programmed.
 * The function shall limit the maximum number of checked flash cells per main function
 * cycle to the configured value FlsMaxReadNormalMode or FlsMaxReadFastMode respectively.
 *
 * @param   TargetAddress   Address in flash memory from which the blank check should be started. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   Length   Number of bytes to be checked for erase pattern. Min.: 1 Max.: FLS_SIZE - TargetAddress.
 *
 * @retval  Std_ReturnType E_OK: request for blank checking has been accepted by the module
 *                         E_NOT_OK: request for blank checking has not been accepted by the module.
 *
 * @reqs    SWS_Fls_00371, SWS_Fls_00380, SWS_Fls_00381, SWS_Fls_00382
 */
#if FLS_BLANK_CHECK_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Fls_BlankCheck( Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    Std_ReturnType returnValue = E_NOT_OK;

    if( HwUnit_Fls.HwUnitState == MEMIF_UNINIT)
    {
        /*If development error detection for the module FLS is enabled: the function Fls_BlankCheck shall 
        check that the driver has been initialized. If this check fails, the function Fls_BlankCheck shall 
        reject the verification request, raise the development error FLS_E_UNINIT and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_BLANKCHECK, FLS_E_UNINIT);
    }
    else if( (HwUnit_Fls.Config->MemoryBaseAddress + TargetAddress) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) -1 )
    {
        /*If development error detection for the module FLS is enabled; the function Fls_BlankCheck shall 
        check that the verification start address (flash memory base address + TargetAddress) lies within 
        the specified lower and upper flash address boundaries. If this check fails, the function Fls_BlankCheck 
        shall reject the verification job, raise the development error FLS_E_PARAM_ADDRESS and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_BLANKCHECK, FLS_E_PARAM_ADDRESS);
    }
    else if( (Length == 0) || (TargetAddress + Length) > (HwUnit_Fls.Config->FlsSectorSize * HwUnit_Fls.Config->FlsNumberOfSectors) - TargetAddress)
    {
        /*If development error detection for the module FLS is enabled: the function Fls_BlankCheck shall 
        check that the given length is greater than 0 and that the verification end address 
        (verification start address + length) lies within the specified upper flash address boundary. 
        If this check fails, the function Fls_BlankCheck shall reject the verification job, raise the 
        development error FLS_E_PARAM_LENGTH and return with E_NOT_OK.*/
        Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_ID_BLANKCHECK, FLS_E_PARAM_LENGTH);
    }
    else{
        return Fls_Arch_BlankCheck( &HwUnit_Fls, TargetAddress, Length );
    }
}
#endif

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

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
static Fls_HwUnit HwUnit_Fls =
{
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
 * @reqs    SWS_Fls_00249
 */
void Fls_Init( const Fls_ConfigType *ConfigPtr )
{
    Fls_Arch_Init( &HwUnit_Fls, ConfigPtr );
    HwUnit_Fls.Config = ConfigPtr;
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
 * @reqs     SWS_Fls_00250
 */
Std_ReturnType Fls_Erase( Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    return Fls_Arch_Erase( &HwUnit_Fls, TargetAddress, Length );
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
 * @reqs    SWS_Fls_00251
 */
Std_ReturnType Fls_Write( Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length )
{
    return Fls_Arch_Write( &HwUnit_Fls, TargetAddress, SourceAddressPtr, Length );
}

/**
 * @brief   **Fls_Cancel**
 *
 * Cancels an ongoing job.
 *
 * @reqs    SWS_Fls_00252
 */
void Fls_Cancel( void )
{
    Fls_Arch_Cancel( &HwUnit_Fls );
}

/**
 * @brief   **Fls_GetStatus**
 *
 * Returns the driver state.
 *
 * @retval  MemIf_StatusType
 *
 * @reqs    SWS_Fls_00253
 */
MemIf_StatusType Fls_GetStatus( void )
{
    return Fls_Arch_GetStatus( &HwUnit_Fls );
}

/**
 * @brief   **Fls_GetJobResult**
 *
 * Returns the result of the last job.
 *
 * @retval  MemIf_JobResultType
 *
 * @reqs    SWS_Fls_00254
 */
MemIf_JobResultType Fls_GetJobResult( void )
{
    return Fls_Arch_GetJobResult( &HwUnit_Fls );
}

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
 * @reqs    SWS_Fls_00256
 */
Std_ReturnType Fls_Read( Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    return Fls_Arch_Read( &HwUnit_Fls, SourceAddress, TargetAddressPtr, Length );
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
 * @reqs    SWS_Fls_00257
 */
Std_ReturnType Fls_Compare( Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    return Fls_Arch_Compare( &HwUnit_Fls, SourceAddress, TargetAddressPtr, Length );
}

/**
 * @brief   **Fls_SetMode**
 *
 * Sets the flash driver’s operation mode.
 *
 * @param   Mode  MEMIF_MODE_SLOW: Slow read access / normal SPI access.
 *                MEMIF_MODE_FAST: Fast read access / SPI burst access.
 *
 * @reqs    SWS_Fls_00258
 */
void Fls_SetMode( MemIf_ModeType Mode )
{
    Fls_Arch_SetMode( &HwUnit_Fls, Mode );
}

/**
 * @brief   **Fls_GetVersionInfo**
 *
 * Returns the version information of this module.
 *
 * @param   VersioninfoPtr   Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Fls_00259
 */
void Fls_GetVersionInfo( Std_VersionInfoType *VersioninfoPtr )
{
    Fls_Arch_GetVersionInfo( &HwUnit_Fls, VersioninfoPtr );
}

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
 * @reqs    SWS_Fls_00371
 */
Std_ReturnType Fls_BlankCheck( Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    return Fls_Arch_BlankCheck( &HwUnit_Fls, TargetAddress, Length );
}

/**
 * @file    Fls_Arch.c
 * @brief   **Flash Architecture Driver**
 * @author  Christopher Bogarin
 *
 * Mcu driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Mcu driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Fls_Cfg.h"
#include "Fls_Arch.h"

/**
 * @brief   **FLS_Init Low Level Initialization**
 *
 * Initializes the Flash Driver.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   ConfigPtr Pointer to flash driver configuration set.
 */
void Fls_Arch_Init( Fls_HwUnit *HwUnit, const Fls_ConfigType *ConfigPtr )
{
    (void)HwUnit;
    (void)ConfigPtr;
}

/**
 * @brief   **Fls_Erase Low Level Initialization**
 *
 * Erases flash sector(s).
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   TargetAddress Target address in flash memory. This address offset will be added to the
 *                        flash memory base address. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   Length Number of bytes to erase Min.: 1 Max.: FLS_SIZE - Target Address.
 *
 * @retval  Std_ReturnType E_OK: erase command has been accepted E_NOT_OK: erase command has not been accepted.
 */
Std_ReturnType Fls_Arch_Erase( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    (void)HwUnit;
    (void)TargetAddress;
    (void)Length;
    return E_OK;
}

/**
 * @brief   **Fls_Write Low Level Initialization**
 *
 * Writes one or more complete flash pages.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   TargetAddress Target address in flash memory. This address offset will be added to the
 *                        flash memory base address. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   SourceAddressPtr Pointer to source data buffer.
 * @param   Length Number of bytes to write Min.: 1 Max.: FLS_SIZE - TargetAddress.
 *
 * @retval  Std_ReturnType E_OK: write command has been accepted E_NOT_OK: write command has not been accepted.
 */
Std_ReturnType Fls_Arch_Write( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length )
{
    (void)HwUnit;
    (void)TargetAddress;
    (void)SourceAddressPtr;
    (void)Length;
    return E_OK;
}

/**
 * @brief   **Fls_Cancel Low Level Initialization**
 *
 * Cancels an ongoing job.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 */
void Fls_Arch_Cancel( Fls_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief   **Fls_GetStatus Low Level Initialization**
 *
 * Returns the driver state.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 *
 * @retval  MemIf_StatusType
 */
MemIf_StatusType Fls_Arch_GetStatus( Fls_HwUnit *HwUnit )
{
    (void)HwUnit;
    return 0x01; /*!< dummy element for the moment */
}

/**
 * @brief   **Fls_GetJobResult Low Level Initialization**
 *
 * Returns the result of the last job.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 *
 * @retval  MemIf_JobResultType
 */
MemIf_JobResultType Fls_Arch_GetJobResult( Fls_HwUnit *HwUnit )
{
    (void)HwUnit;
    return 0x01; /*!< dummy element for the moment */
}

/**
 * @brief   **Fls_Read Low Level Initialization**
 *
 * Reads from flash memory.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   SourceAddress Source address in flash memory. This address offset will be added to the flash memory base address.
 *                        Min.: 0 Max.: FLS_ SIZE - 1.
 * @param   Length Number of bytes to read Min.: 1 Max.: FLS_SIZE - Source Address.
 * @param   TargetAddressPtr Pointer to target data buffer.
 *
 * @retval  Std_ReturnType E_OK: read command has been accepted E_NOT_OK: read command has not been accepted.
 */
Std_ReturnType Fls_Arch_Read( Fls_HwUnit *HwUnit, Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    (void)HwUnit;
    (void)SourceAddress;
    (void)TargetAddressPtr;
    (void)Length;
    return E_OK;
}

/**
 * @brief   **Fls_Compare Low Level Initialization**
 *
 * Compares the contents of an area of flash memory with that of an application data buffer.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   SourceAddress Source address in flash memory.
 *                        This address offset will be added to the flash memory base address. Min.: 0 Max.: FLS_ SIZE - 1.
 * @param   TargetAddressPtr  Pointer to target data buffer.
 * @param   Length Number of bytes to compare Min.: 1 Max.: FLS_SIZE - Source Address.
 *
 * @retval  Std_ReturnType E_OK: read command has been accepted E_NOT_OK: read command has not been accepted.
 */
Std_ReturnType Fls_Arch_Compare( Fls_HwUnit *HwUnit, Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length )
{
    (void)HwUnit;
    (void)SourceAddress;
    (void)TargetAddressPtr;
    (void)Length;
    return E_OK;
}

/**
 * @brief   **Fls_SetMode Low Level Initialization**
 *
 * Sets the flash driver’s operation mode.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   Mode  MEMIF_MODE_SLOW: Slow read access / normal SPI access.
 *                MEMIF_MODE_FAST: Fast read access / SPI burst access.
 */
void Fls_Arch_SetMode( Fls_HwUnit *HwUnit, MemIf_ModeType Mode )
{
    (void)HwUnit;
    (void)Mode;
}

/**
 * @brief   **Fls_BlankCheck Low Level Initialization**
 *
 * The function Fls_BlankCheck shall verify, whether a given memory area has been erased but not (yet) programmed.
 * The function shall limit the maximum number of checked flash cells per main function
 * cycle to the configured value FlsMaxReadNormalMode or FlsMaxReadFastMode respectively.
 *
 * @param   HwUnit Pointer to the hardware unit configuration.
 * @param   TargetAddress   Address in flash memory from which the blank check should be started. Min.: 0 Max.: FLS_SIZE - 1.
 * @param   Length   Number of bytes to be checked for erase pattern. Min.: 1 Max.: FLS_SIZE - TargetAddress.
 *
 * @retval  Std_ReturnType E_OK: request for blank checking has been accepted by the module
 *                         E_NOT_OK: request for blank checking has not been accepted by the module.
 */
Std_ReturnType Fls_Arch_BlankCheck( Fls_HwUnit *HwUnit, Fls_AddressType TargetAddress, Fls_LengthType Length )
{
    (void)HwUnit;
    (void)TargetAddress;
    (void)Length;
    return E_OK;
}

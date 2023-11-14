/**
 * @file    Fls_Types.h
 * @brief   **Flash Driver Types**
 * @author  Christopher Bogarin
 *
 * The header contains the type definitions that are used by the Flash module.
 * The file is implemnted as a means of abstraction from the hardware,
 * this way we can avoid to include Arch headers in the actual driver header,
 * making the low level interfaces available for upper layers.
 *
 */
#ifndef FLASH_TYPES_H__
#define FLASH_TYPES_H__

#include "Registers.h"


/**
 * @brief   Fls_ConfigType.
 *
 * A pointer to such a structure is provided to the flash driver initialization routine
 * for configuration of the driver and flash memory hardware.
 *
 * @reqs    SWS_Fls_00368
 */
typedef struct _Fls_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Fls_ConfigType;

/**
 * @brief   Fls_AddressType.
 *
 * Used as address offset from the configured flash base address
 * to access a certain flash memory area.
 *
 * @reqs    SWS_Fls_00369
 */
typedef uint32 Fls_AddressType;

/**
 * @brief   Fls_LengthType.
 *
 * Specifies the number of bytes to read/write/erase/compare.
 *
 * @reqs    SWS_Fls_00370
 */
typedef uint32 Fls_LengthType;


#endif
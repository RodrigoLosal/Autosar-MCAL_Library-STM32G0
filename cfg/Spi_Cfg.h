/**
 * @file    Spi_Cfg.h
 * @brief   **Spi Driver Configuration Header**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * ...
 */
#ifndef SPI_CFG_H__
#define SPI_CFG_H__

#include "Spi_Types.h"

/**
 * @defgroup Spi_SWC_Ids CAN software Ids
 *
 * {@ */
#define SPI_MODULE_ID        0u /*!< Spi Module ID */
#define SPI_INSTANCE_ID      0u /*!< Spi Instance ID */
#define SPI_VENDOR_ID        0u /*!< Spi Module Vendor ID */
/**
 * @} */

/**
 * @defgroup Spi_SWC_Ids Spi software version
 *
 * {@ */
#define SPI_SW_MAJOR_VERSION 0u /*!< Spi Module Major Version */
#define SPI_SW_MINOR_VERSION 0u /*!< Spi Module Minor Version */
#define SPI_SW_PATCH_VERSION 0u /*!< Spi Module Patch Version */
/**
 * @} */

extern const Spi_ConfigType SpiConfig;

#endif /* SPI_CFG_H__ */

/**
 * @file Dio_Cfg.h
 * @brief Dio driver configuration.
 *
 * In this file we find the definitions for the Pre-Compiler configuration
 * header for the Dio module.
 */
#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Dio_Types.h"

/**
 * @defgroup DIO_SWC_Ids DIO software version and Ids
 *
 * {@ */
#define DIO_MODULE_ID             8u /*!< Dio Module ID */
#define DIO_INSTANCE_ID           8u /*!< Dio Instance ID */
#define DIO_VENDOR_ID             0u /*!< Dio Module Vendor ID */
/**
 * @} */

/**
 * @defgroup DIO_SWC_Ids DIO software version and Ids
 *
 * {@ */
#define DIO_SW_MAJOR_VERSION      0u /*!< Dio Module Major Version */
#define DIO_SW_MINOR_VERSION      0u /*!< Dio Module Minor Version */
#define DIO_SW_PATCH_VERSION      0u /*!< Dio Module Patch Version */
/**
 * @} */

/**
 * @defgroup DIO_Numbers DIO channles, port and groups numbers
 *
 * {@ */
#define DIO_NUMBERS_OF_PORTS      6u /*!< Number of ports in the microcontroller */
#define DIO_NUMBERS_OF_PINS       3u /*!< Number of pins in the microcontroller */
#define DIO_NUMBERS_OF_GROUPS     1u /*!< Number of groups in the microcontroller */
/**
 * @} */

/**
 * @defgroup DIO_Channels_Ids Channels Id for each pin in use
 *
 * @{ */
#define DIO_CHANNEL_RED_LED       0u /*!< Red LED channel */
#define DIO_CHANNEL_GREEN_LED     1u /*!< Green LED channel */
#define DIO_CHANNEL_BLUE_LED      2u /*!< Blue LED channel */
/**
 * @} */

/**
 * @defgroup DIO_Groups_Ids Groups Id for each group in use
 *
 * @{ */
#define DIO_GROUP_LCD_DATA        &DioConfig.Groups[ 0 ] /*!< LCD data group */
/**
 * @} */

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define DIO_DEV_ERROR_DETECT      STD_ON

/**
 * @brief Adds / removes the service Dio_FlipChannel() from the code
 * @typedef EcucBooleanParamDef
 */
#define DIO_FLIP_CHANNEL_API      STD_ON

/**
 * @brief Adds / removes the service Dio_MaskedWritePort() from the code
 * @typedef EcucBooleanParamDef
 */
#define DIO_MASKED_WRITE_PORT_API STD_ON

/**
 * @brief Adds / removes the service GetVersionInfo() from the code
 * @typedef EcucBooleanParamDef
 */
#define DIO_GET_VERSION_INFO_API  STD_ON

extern const Dio_ConfigType DioConfig;

#endif /* DIO_CFG_H_ */

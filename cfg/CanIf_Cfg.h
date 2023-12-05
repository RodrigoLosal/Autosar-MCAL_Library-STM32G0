/**
 * @file CanIf_Cfg.h
 * @brief Configuration file for the CAN interface.
 * @author Diego Perez
 *
 * ...
 */
#ifndef CANIF_CFG_H__
#define CANIF_CFG_H__

#include "CanIf_Types.h"

/**
 * @defgroup CANIF_SWC_Ids CanIf software version and Ids
 *
 * {@ */
#define CANIF_MODULE_ID                        0u /*!< Dio Module ID */
#define CANIF_INSTANCE_ID                      0u /*!< Dio Instance ID */
#define CANIF_VENDOR_ID                        0u /*!< Dio Module Vendor ID */
/**
 * @} */

/**
 * @defgroup CANIF_SWC_Ids CanIf software version and Ids
 *
 * {@ */
#define CANIF_SW_MAJOR_VERSION                 0u /*!< Dio Module Major Version */
#define CANIF_SW_MINOR_VERSION                 0u /*!< Dio Module Minor Version */
#define CANIF_SW_PATCH_VERSION                 0u /*!< Dio Module Patch Version */
/**
 * @} */

/**
 * @brief Enable support for Bus Mirroring.
 * * @typedef EcucBooleanParamDef
 */
#define CANIF_BUS_MIRRORING_SUPPORT            STD_ON

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_DEV_ERROR_DETECT                 STD_ON

/**
 * @brief Enables / Disables the API CanIf_ReadRxPduData() for reading received L-SDU data.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_PUBLIC_READ_RX_PDU_DATA          STD_ON

/**
 * @brief Enables and disables the API for reading the notification status of receive L-PDUs.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS STD_ON

/**
 * @brief Enables and disables the API for reading the notification status of transmit L-PDUs.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS STD_ON

/**
 * @brief Enables/Disables the Global Time APIs used when hardware timestamping is supported.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_GLOBAL_TIME_SUPPORT              STD_ON

/**
 * @brief Specifies if the CanIf_SetBaudrate API shall be supported.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_SET_BAUDRATE_API                 STD_ON

/**
 * @brief Specifies if the CanIf_GetVersionInfo API shall be supported.
 * @typedef EcucBooleanParamDef
 */
#define CANIF_VERSION_INFO_API                 STD_ON

extern const CanIf_ConfigType CanIfConfig;

#endif /* CANIF_CFG_H__ */

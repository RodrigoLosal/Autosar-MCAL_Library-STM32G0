/**
 * @file    Fls_Cgf.h
 * @brief   **Flash Driver Configuration Header**
 * @author  Christopher Bogarin
 *
 * Configuration for the FLASH driver. This file, as per AUTOSAR guidelines,
 * is not application-dependent and should be generated by a configuration tool.
 * For the moment, the files shall be written manually by the user
 * according to their application.
 * Also, the user is responsible for setting the parameter in the right way.
 *
 */
#ifndef FLASH_CFG_H__
#define FLASH_CFG_H__

#include "Fls_Types.h"

/**
 * @defgroup FLS_SWC_Ids FLS software version and Ids
 *
 * {@ */
#define FLS_MODULE_ID            0x0Au /*!< Fls Module ID */
#define FLS_INSTANCE_ID          0x0Au /*!< Fls Instance ID */
#define FLS_VENDOR_ID            0u    /*!< Fls Module Vendor ID */
/**
 * @} */

/**
 * @defgroup FLS_SWC_Ids FLS software version and Ids
 *
 * {@ */
#define FLS_SW_MAJOR_VERSION     0u /*!< Fls Module Major Version */
#define FLS_SW_MINOR_VERSION     0u /*!< Fls Module Minor Version */
#define FLS_SW_PATCH_VERSION     0u /*!< Fls Module Patch Version */
/**
 * @} */

/**
 * @brief Enable / disable the Fls_Cancel() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_CANCEL_API           STD_ON

/**
 * @brief Enable / disable the Fls_GetStatus() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_GET_STATUS_API       STD_ON

/**
 * @brief Enable / disable the Fls_GetJobResult() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_GET_JOB_RESULT_API   STD_ON

/**
 * @brief Enable / disable the Fls_Compare() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_COMPARE_API          STD_ON

/**
 * @brief Enable / disable the Fls_SetMode() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_SET_MODE_API         STD_ON

/**
 * @brief Enable / disable the Fls_GetVersionInfo() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_GET_VERSION_INFO_API STD_ON

/**
 * @brief Enable / disable the Fls_BlankCheck() function.
 * @typedef EcucBooleanParamDef
 */
#define FLS_BLANK_CHECK_API      STD_ON

/**
 * @brief Switches the development error detection and notification on or off.
 * @typedef EcucBooleanParamDef
 */
#define FLS_DEV_ERROR_DETECT     STD_ON

extern const Fls_ConfigType FlashConfig;

#endif
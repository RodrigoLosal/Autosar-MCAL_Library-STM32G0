/**
 * @file Dio_Cfg.h
 * @brief Port driver configuration.
 *
 * In this file we find the definitions for the Pre-Compiler configuration
 * header for the Dio module.
 */
#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/**
  * @defgroup DIO-ID to get the version information of this module.
  @{ */
#define DIO_VENDOR_ID        (uint16)1000u /*!< Id for the company in the AUTOSAR \
                                                for example Ortega's ID = 1000 */
#define DIO_MODULE_ID        (uint16)120u  /*!< Dio Module Id */
#define DIO_SW_MAJOR_VERSION (uint8)1u     /*!< Dio Module Major Version */
#define DIO_SW_MINOR_VERSION (uint8)0u     /*!< Dio Module Minor Version */
#define DIO_SW_PATCH_VERSION (uint8)0u     /*!< Dio Module Patch Version */
/**
  @} */

#endif /* DIO_CFG_H_ */
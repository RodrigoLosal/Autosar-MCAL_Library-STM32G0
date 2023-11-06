/**
 * @file    Pwm_Cfg.h
 * @brief   **Pwm Driver Configuration Header**
 * @author  Jazmin Melendrez
 *
 * Descripcion...
 */
#ifndef Pwm_CFG_H__
#define Pwm_CFG_H__

#include "Pwm_Types.h"

/**
 * @defgroup Pwm_SWC_Ids CAN software Ids
 *
 * {@ */
#define PWM_MODULE_ID        0u /*!< Pwm Module ID */
#define PWM_INSTANCE_ID      0u /*!< Pwm Instance ID */
#define PWM_VENDOR_ID        0u /*!< Pwm Module Vendor ID */
/**
 * @} */

/**
 * @defgroup Pwm_SWC_Ids Pwm software version
 *
 * {@ */
#define PWM_SW_MAJOR_VERSION 0u /*!< Pwm Module Major Version */
#define PWM_SW_MINOR_VERSION 0u /*!< Pwm Module Minor Version */
#define PWM_SW_PATCH_VERSION 0u /*!< PWm Module Patch Version */
/**
 * @} */

extern const Pwm_ConfigType PwmConfig;

#endif /* PWM_CFG_H__ */
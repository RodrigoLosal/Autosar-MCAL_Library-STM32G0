/**
 * @file    Adc_Lcfg.c
 * @brief   **ADC Driver**
 * @author  Naim Leon
 *
 * This file contains the configuration structures for the ADC driver, this file as per AUTOSAR
 * indication is not application dependant and shall be generated by a configuration tool. For the
 * moment the files shall be written manually by the user according its application. Also the user
 * is responsible for setting the paramter in the right way.
 */
#include "Std_Types.h"
#include "Adc_Cfg.h"


/**
 * @brief ADC driver configuration.
 */
/* clang-format off */
const Adc_ConfigType AdcConfig =
{
    .dummy = 0x12345678u
};
/* clang-format on */
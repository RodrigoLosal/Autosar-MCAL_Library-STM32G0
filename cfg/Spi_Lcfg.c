/**
 * @file    Spi_Cfg.c
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * This file contains the configuration structures for the SPI driver, this file as per AUTOSAR indication
 * is not application dependant and shall be generated by a configuration tool. for the moment the files
 * shall be written manually by the user according its application. Also the user is responsible for setting
 * the paramter in the right way.
 */
#include "Std_Types.h"
#include "Spi_Cfg.h"

/**
 * @brief Spi driver configuration.
 */
/* clang-format off */
const Spi_ConfigType SpiConfig =
{
    .ChannelCount   = 0u,
    .SequenceCount  = 0u,
    .JobCount       = 0u,
    .HWUnitCount    = 0u,
};
/* clang-format off */

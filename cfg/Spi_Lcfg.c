/**
 * @file    Spi_Cfg.c
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 */
#include "Std_Types.h"
#include "Spi_Cfg.h"

/**
 * @brief Spi driver configuration.
 */
/* clang-format off */
const Spi_ConfigType SpiConfig =
{
    .dummy = 0x12345678;
};
/* clang-format off */

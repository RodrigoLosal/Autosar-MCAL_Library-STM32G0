/**
 * @file Port.h
 * @brief Port driver configuration.
 *
 * This file provides the interface for the GPIO configuration, to use some
 * functions check the Port_Cfg.h file to configured the values.
 */
#ifndef PORT_H__
#define PORT_H__

/**
 * @brief  Type of the external data structure containing the initialization data for this module.
 *
 * @reqs   SWS_Port_00228
 */
typedef struct _Port_ConfigType
{
    uint8 Port;        /*!< Port where the pin to config is grouped*/
    uint16 Pins;       /*!< Pins to configured*/
    uint8 Pull;        /*!< Pullup, pull down or no pull ressitor*/
    uint8 OutputDrive; /*!< Pus-Pull or Open conlector*/
    uint8 Speed;       /*!< Speed of the pin*/
    uint8 Mode;        /*!< Input, Output, analog or any of the altern modes*/
    uint8 DirChange;   /*!< Pin direction changeable during runtime*/
    uint8 ModeChange;  /*!< Pin mode changeable during runtime*/
} Port_ConfigType;

/**
 * @brief  Data type for the symbolic name of a port pin. the 4 most significant
 *         bits represent the port of the pin and the 4 least significatn bits
 *         represent the pin.
 *
 * @reqs   SWS_Port_00229
 */
typedef uint16 Port_PinType; /*!< Data type for the symbolic name of a port pin.*/

/**
 * @brief  Data type for the symbolic direction of a pin.
 *         range: PORT_PIN_IN and PORT_PIN_OUT
 *
 * @reqs   SWS_Port_00046
 */
typedef uint8 Port_PinDirectionType; /*!< Data type for the symbolic direction of a pin.*/

/**
 * @brief  Data type for the altern functions of a pin.
 *         range: PORT_PIN_MODE_AF0, PORT_PIN_MODE_AF1, PORT_PIN_MODE_AF2, PORT_PIN_MODE_AF3,
 *         PORT_PIN_MODE_AF4, PORT_PIN_MODE_AF5, PORT_PIN_MODE_AF6, PORT_PIN_MODE_AF7 and
 *         PORT_PIN_MODE_AF8.
 *
 * @reqs   SWS_Port_00231
 */
typedef uint8 Port_PinModeType; /*!< Data type for the symbolic mode of a pin.*/

/**
 * @name    PORTS values.
 * Symbols to specify ports values.
 */
/**@{*/
#define PORTS_A               0u /*!< Port A value */
#define PORTS_B               1u /*!< Port B value */
#define PORTS_C               2u /*!< Port C value */
#define PORTS_D               3u /*!< Port D value */
#define PORTS_E               4u /*!< Port E value */
#define PORTS_F               5u /*!< Port F value */
/**@}*/

/**
 * @name    GPIO pins values
 * Symbols to specify the values of GPIO pins on any port, this needs to be use in combination
 * with ports when specify in Port_Cfg.h.
 */
/**@{*/
#define PORTS_PIN_00_VAL      0x0000u /*!< Pin 0 value */
#define PORTS_PIN_01_VAL      0x0001u /*!< Pin 1 value */
#define PORTS_PIN_02_VAL      0x0002u /*!< Pin 2 value */
#define PORTS_PIN_03_VAL      0x0003u /*!< Pin 3 value */
#define PORTS_PIN_04_VAL      0x0004u /*!< Pin 4 value */
#define PORTS_PIN_05_VAL      0x0005u /*!< Pin 5 value */
#define PORTS_PIN_06_VAL      0x0006u /*!< Pin 6 value */
#define PORTS_PIN_07_VAL      0x0007u /*!< Pin 7 value */
#define PORTS_PIN_08_VAL      0x0008u /*!< Pin 8 value */
#define PORTS_PIN_09_VAL      0x0009u /*!< Pin 9 value */
#define PORTS_PIN_10_VAL      0x000Au /*!< Pin 10 value */
#define PORTS_PIN_11_VAL      0x000Bu /*!< Pin 11 value */
#define PORTS_PIN_12_VAL      0x000Cu /*!< Pin 12 value */
#define PORTS_PIN_13_VAL      0x000Du /*!< Pin 13 value */
#define PORTS_PIN_14_VAL      0x000Eu /*!< Pin 14 value */
#define PORTS_PIN_15_VAL      0x000Fu /*!< Pin 15 value */
/**@}*/

/**
 * @name    GPIO Pin values.
 * Symbols to specify values of GPIO pins.
 */
/**@{*/
#define PORTS_PIN_00          ( 1u << PORTS_PIN_00_VAL ) /*!< Pin 0 value */
#define PORTS_PIN_01          ( 1u << PORTS_PIN_01_VAL ) /*!< Pin 1 value */
#define PORTS_PIN_02          ( 1u << PORTS_PIN_02_VAL ) /*!< Pin 2 value */
#define PORTS_PIN_03          ( 1u << PORTS_PIN_03_VAL ) /*!< Pin 3 value */
#define PORTS_PIN_04          ( 1u << PORTS_PIN_04_VAL ) /*!< Pin 4 value */
#define PORTS_PIN_05          ( 1u << PORTS_PIN_05_VAL ) /*!< Pin 5 value */
#define PORTS_PIN_06          ( 1u << PORTS_PIN_06_VAL ) /*!< Pin 6 value */
#define PORTS_PIN_07          ( 1u << PORTS_PIN_07_VAL ) /*!< Pin 7 value */
#define PORTS_PIN_08          ( 1u << PORTS_PIN_08_VAL ) /*!< Pin 8 value */
#define PORTS_PIN_09          ( 1u << PORTS_PIN_09_VAL ) /*!< Pin 9 value */
#define PORTS_PIN_10          ( 1u << PORTS_PIN_10_VAL ) /*!< Pin 10 value */
#define PORTS_PIN_11          ( 1u << PORTS_PIN_11_VAL ) /*!< Pin 11 value */
#define PORTS_PIN_12          ( 1u << PORTS_PIN_12_VAL ) /*!< Pin 12 value */
#define PORTS_PIN_13          ( 1u << PORTS_PIN_13_VAL ) /*!< Pin 13 value */
#define PORTS_PIN_14          ( 1u << PORTS_PIN_14_VAL ) /*!< Pin 14 value */
#define PORTS_PIN_15          ( 1u << PORTS_PIN_15_VAL ) /*!< Pin 15 value */
/**@}*/

/**
 * @name    PORT mode.
 * Symbols to specify the mode value of GPIO pins on init function.
 */
/**@{*/
#define PORTS_MODE_INPUT      0x00u /*!< Input mode value */
#define PORTS_MODE_OUTPUT     0x10u /*!< General purpose output mode value */
#define PORTS_MODE_ANALOG     0x30u /*!< Analog mode (reset state) value */
#define PORTS_MODE_ALT_AF0    0x20u /*!< Alternarive funcion 0 */
#define PORTS_MODE_ALT_AF1    0x21u /*!< Alternarive funcion 1 */
#define PORTS_MODE_ALT_AF2    0x22u /*!< Alternarive funcion 2 */
#define PORTS_MODE_ALT_AF3    0x23u /*!< Alternarive funcion 3 */
#define PORTS_MODE_ALT_AF4    0x24u /*!< Alternarive funcion 4 */
#define PORTS_MODE_ALT_AF5    0x25u /*!< Alternarive funcion 5 */
#define PORTS_MODE_ALT_AF6    0x26u /*!< Alternarive funcion 6 */
#define PORTS_MODE_ALT_AF7    0x27u /*!< Alternarive funcion 7 */
/**@}*/

/**
 * @name    PORT mode.
 * Symbols to specify the mode value of GPIO pins on init function.
 */
/**@{*/
#define PORTS_NOPULL          0x00u /*!< No pull-up, pull-down value */
#define PORTS_PULLUP          0x01u /*!< Pull-up */
#define PORTS_PULLDOWN        0x02u /*!< Pull-down */
/**@}*/

/**
 * @name    GPIO pull values.
 * Symbols to specify the pull value of GPIO pins on init function.
 */
/**@{*/
#define PORTS_PUSH_PULL       0x00u /*!< Output push-pull (reset state) value */
#define PORTS_OPEN_COLECTOR   0x01u /*!< Output open-drain */
/**@}*/

/**
 * @name    GPIO Speed values
 * Symbols to specify the Speed value of GPIO pins on init function.
 */
/**@{*/
#define PORTS_VERY_LOW_SPEED  0x00u /*!< Very low speed value */
#define PORTS_LOW_SPEED       0x01u /*!< Low speed value */
#define PORTS_HIGH_SPEED      0x02u /*!< High speed value */
#define PORTS_VERY_HIGH_SPEED 0x03u /*!< Very high speed value */
/**@}*/

/**
 * @name    GPIOD pins direction
 * Symbols to specify the direction of the GPIO pins
 */
/**@{*/
#define PORTS_PIN_IN          (Port_PinDirectionType)0x00u /*!< Input mode value */
#define PORTS_PIN_OUT         (Port_PinDirectionType)0x01u /*!< General purpose output mode value */
/**@}*/

/**
 * @defgroup PORT_errors PORT Driver Errors
 * @{ */
#define PORT_E_PARAM_PIN              0x0Au /*!< Invalid Port Pin ID requested        */
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0Bu /*!< Port Pin not configured as changeable */
#define PORT_E_INIT_FAILED            0x0Cu /*!< Invalid configuration set            */
#define PORT_E_PARAM_INVALID_MODE     0x0Du /*!< Invalid Port Pin mode specified      */
#define PORT_E_MODE_UNCHANGEABLE      0x0Eu /*!< Port Pin mode is not configurable    */
#define PORT_E_UNINIT                 0x0Fu /*!< Port driver not initialized          */
#define PORT_E_PARAM_POINTER          0x10u /*!< Invalid Port Pin ID requested        */
/**
 * @} */

#include "Port_Cfg.h" /* cppcheck-suppress misra-c2012-20.1 ; it is necesary to use a define for this function */

void Port_Init( const Port_ConfigType *ConfigPtr );

#if PORT_SET_PIN_DIRECTION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

#if PORT_SET_PIN_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif

#if PORT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif

void Port_RefreshPortDirection( void );

#endif
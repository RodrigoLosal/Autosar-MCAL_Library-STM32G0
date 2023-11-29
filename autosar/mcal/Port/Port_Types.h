/**
 * @file    Port_Types.h
 * @brief   **PORT Driver Types**
 * @author  Diego Perez, Enrique Ortega
 *
 * The header contains the type definitions that are used by the PORT module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef PORT_TYPES_H__
#define PORT_TYPES_H__

#include "Std_Types.h"

/**
 * @defgroup PORT_errors Driver erros
 *
 * PORTS Driver Errors messages, this values are intended to use with DET functionality
 *
 * @{ */
#define PORT_E_PARAM_PIN               0x00u /*!< Invalid Port Pin ID requested        */
#define PORT_E_DIRECTION_UNCHANGEABLE  0x01u /*!< Port Pin not configured as changeable */
#define PORT_E_INIT_FAILED             0x02u /*!< Invalid configuration set            */
#define PORT_E_PARAM_INVALID_MODE      0x03u /*!< Invalid Port Pin mode specified      */
#define PORT_E_MODE_UNCHANGEABLE       0x04u /*!< Port Pin mode is not configurable    */
#define PORT_E_UNINIT                  0x05u /*!< Port driver not initialized          */
#define PORT_E_PARAM_POINTER           0x06u /*!< Invalid Port Pin ID requested        */
/**
 * @} */

/**
 * @defgroup PORT_Ids Can Id number for module and each API
 *
 * @{ */
#define PORT_ID_INIT                   0x00u /*!< Port_Init() api service id */
#define PORT_ID_SET_PIN_DIRECTION      0x01u /*!< Port_SetPinDirection() api service id */
#define PORT_ID_SET_PIN_MODE           0x02u /*!< Port_SetPinMode() api service id */
#define PORT_ID_GET_VERSION_INFO       0x03u /*!< Port_GetVersionInfo() api service id */
#define PORT_ID_REFRESH_PORT_DIRECTION 0x04u /*!< Port_RefreshPortDirection() api service id */
/**
 * @} */

/**
 * @brief **Definition of the external data structure containing the initialization data**
 *
 * The Port_PortsConfigType data structure holds the initialization information for each port available
 * on the microcontroller. An array of these structures must be defined in the Port_Cfg.c file, with
 * each entry representing a specific port.
 *
 * @note It is the responsibility of the user to ensure that the values defined in this structure are
 * valid and appropriate, as the Port Driver does not perform any validation. The values must be generated
 * and validated within the code generation tool.
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
 * @brief  Data type for the symbolic name of a port pin. the 8 most significant
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

#endif /* PORT_TYPES_H__ */
/**
 * @file    Port.h
 * @brief   **Port driver configuration**
 * @author  Daniel Byuerly, Diego Perez
 *
 * This PORT driver module control the overall configuration and initialization of the port structure
 * which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports which are
 * configured by the PORT driver.
 *
 * The PORT driver shall be initialized prior to the use of the DIO functions. Otherwise, DIO
 * functions will exhibit undefined behavior. The diagram below identifies the PORT driver functions
 * and the structure of the PORT driver and DIO driver within the MCAL software layer. To use some
 * functions check the Port_Cfg.h file to configured the values.
 */
#ifndef PORT_H__
#define PORT_H__

/**
 * @defgroup max_port_values  max number of Mcu ports, pins and altern modes
 *
 * @{ */
#define MAX_PORT_NUMBER      6u  /*!< Max number of port in Mcu */
#define MAX_PIN_NUMBER       16u /*!< Max number of pins on each port*/
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_PIN_MODES        4u /*!< Max values on pin modes */
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_ALT_MODES        11u /*!< Max values on altern modes */
/**
 * @}*/

/**
 * @defgroup get_bits  macros to extract certaing number of bits from a variable
 *
 * @{*/
#define GET_LOW_NIBBLE( x )  ( (x)&0x0fu )   /*!< get the less significant bits */
#define GET_HIGH_NIBBLE( x ) ( ( x ) >> 4u ) /*!< get the four most significant nibble */
#define GET_HIGH_BYTE( x )   ( ( x ) >> 8u ) /*!< get hte MSB from and 16 bit variable */
/**
 * @}*/

/**
 * @defgroup PORT_errors Driver erros
 *
 * PORTS Driver Errors messages, this values are intended to use with DET functionality
 *
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

/**
 * @defgroup PORT_Ids Can Id number for module and each API
 *
 * @{ */
#define PORT_ID_INIT                        0x00u /*!< Port_Init() api service id */
#define PORT_ID_SET_PIN_DIRECTION           0x10u /*!< Port_SetPinDirection() api service id */
#define PORT_ID_SET_PIN_MODE                0x0fu /*!< Port_SetPinMode() api service id */
#define PORT_ID_GET_VERSION_INFO            0x03u /*!< Port_GetVersionInfo() api service id */
#define PORT_ID_REFRESH_PORT_DIRECTION      0x04u /*!< Port_RefreshPortDirection() api service id */
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
/**
 * @file    Port.c
 * @brief   **Port driver configuration**
 * @author  Daniel Byuerly, Diego Perez, Enrique Ortega
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
#include "Std_Types.h"
#include "Port.h"
#include "Port_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Can_Cfg.h */
#if PORT_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @defgroup max_port_values  max number of Mcu ports, pins and altern modes
 *
 * @{ */
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_PIN_MODES 4u /*!< Max values on pin modes */
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_ALT_MODES 11u /*!< Max values on altern modes */
/**
 * @}*/

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
static const Port_ConfigType *Port_ConfigPtr = NULL_PTR;

/**
 * @brief Initialize the GPIO pins to the configuration store on ConfigPTR.
 *
 * The function changes the registers values of the GPIOS depending on the values of the ConfigPtr
 * struct, this function Initialize all pins and port of the ConfigPtr array, the length of the
 * array is given by PORT_PIN_NUMBER_OF_PORTS, To configure the values of the struct use the symbols
 * defined on the Port.h file.
 *
 * @param ConfigPtr       Pointer to ConfigPtr struct array.
 *
 * @reqs   SWS_Port_00140, SWS_Port_00004, SWS_Port_00079, SWS_Port_00081, SWS_Port_00082
 */
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    if( ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_Init shall raise the error PORT_E_INIT_FAILED
        if the parameter ConfigPtr is a null value.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_INIT, PORT_E_INIT_FAILED );
    }
    else
    {
        for( uint8 Port = 0u; Port < ConfigPtr->NumbersOfPins; Port++ )
        {
            Port_Arch_Init( &ConfigPtr->PortPins[ Port ] );
        }
        /*make the port configuration accesible for other functions*/
        Port_ConfigPtr = ConfigPtr;
    }
}

/**
 * @brief Set the direction of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS direction during runtime, to enable this
 * function change the value of PORT_SET_PIN_DIRECTION_API to STD_ON on the Port_Cfg file. To change
 * the direction use the symbols of PORT direction
 *
 * @param Pin             Pin to change the direction.
 * @param Direction       Direction to be changed.
 *
 * @reqs   SWS_Port_00141, SWS_Port_00137, SWS_Port_00138
 */
/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if PORT_SET_PIN_DIRECTION_API == STD_ON
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    if( Port_ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinDirection shall raise the error PORT_E_UNINIT
        if the parameter Port_ConfigPtr is a null value.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_UNINIT );
    }
    else if( Pin >= Port_ConfigPtr->NumbersOfPins )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinDirection shall raise the error PORT_E_PARAM_PIN
        if an incorrect port pin ID has been passed.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_PARAM_PIN );
    }
    else if( Port_ConfigPtr->PortPins[ Pin ].DirChange == FALSE )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinDirection shall raise the error PORT_E_DIRECTION_UNCHANGEABLE
        if the pin is not configured as changeable.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_DIRECTION_UNCHANGEABLE );
    }
    else
    {
        Port_Arch_SetPinDirection( &Port_ConfigPtr->PortPins[ Pin ], Direction );
    }
}
#endif

/**
 * @brief Set the mode of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS mode during runtime, to eneable this
 * function change the value of PORT_SET_PIN_MODE_API to STD_ON on the Port_Cfg file.
 * To change the mode use the symbols of GPIO altern values.
 *
 * @param Pin             Pin to change the direction.
 * @param Mode            Mode to be changed.
 *
 * @reqs   SWS_Port_00145, SWS_Port_00005
 */
/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if PORT_SET_PIN_MODE_API == STD_ON
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    uint8 PinMode = GET_HIGH_NIBBLE( Mode );
    uint8 AltMode = GET_LOW_NIBBLE( Mode );

    if( Port_ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinMode shall raise the error PORT_E_UNINIT
        if the parameter Port_ConfigPtr is a null value.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_MODE, PORT_E_UNINIT );
    }
    else if( Pin >= Port_ConfigPtr->NumbersOfPins )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinMode shall raise the error PORT_E_PARAM_PIN
        if an incorrect port pin ID has been passed.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_MODE, PORT_E_PARAM_PIN );
    }
    else if( Port_ConfigPtr->PortPins[ Pin ].ModeChange == FALSE )
    {
        /* If development error detection for the Can module is enabled:
        The function Port_SetPinMode shall raise the error PORT_E_MODE_UNCHANGEABLE
        if the mode is unchangeable.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_MODE, PORT_E_MODE_UNCHANGEABLE );
    }
    else if( ( PinMode > MAX_PIN_MODES ) || ( AltMode > MAX_ALT_MODES ) )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_SetPinMode shall raise the error PORT_E_PARAM_PIN
        if an incorrect port pin ID has been passed.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_MODE, PORT_E_PARAM_INVALID_MODE );
    }
    else
    {
        Port_Arch_SetPinMode( &Port_ConfigPtr->PortPins[ Pin ], PinMode, AltMode );
    }
}
#endif

/**
 * @brief Gets the current version.
 *
 * The function gives the versioninfo struct the values of the current version. to eneable this
 * function change the value of PORT_VERSION_INFO_API to STD_ON on the Port_Cfg file.
 *
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 *
 * @reqs   SWS_Port_00143
 */
/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if PORT_VERSION_INFO_API == STD_ON
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo != NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        The function Port_GetVersionInfo shall raise the error PORT_E_PARAM_POINTER
        if the parameter versioninfo is a null pointer */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_GET_VERSION_INFO, PORT_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = 0;
        versioninfo->sw_major_version = 0;
        versioninfo->sw_minor_version = 0;
        versioninfo->sw_patch_version = 0;
        versioninfo->vendorID         = 0;
    }
}
#endif

/**
 * @brief Refresh port direction.
 *
 * The function refreshes the registers values of the GPIOS moder during runtime to the initial values
 * only if they are configured as non changeables.
 *
 * @reqs   SWS_Port_00142, SWS_Port_00066
 */
void Port_RefreshPortDirection( void )
{
    if( Port_ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the PORT module is enabled:
        The function Port_RefreshPortDirection shall raise the error PORT_E_UNINIT
        if the parameter Port_ConfigPtr is a null value.*/
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_REFRESH_PORT_DIRECTION, PORT_E_UNINIT );
    }
    else
    {
        for( uint8 Port = 0u; Port < Port_ConfigPtr->NumbersOfPins; Port++ )
        {
            Port_Arch_RefreshPortDirection( &Port_ConfigPtr->PortPins[ Port ] );
        }
    }
}

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
#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Port.h"
#include "Port_Types.h"
#include "Port_Arch.h"

/**
 * @defgroup get_bits  macros to extract certaing number of bits from a variable
 *
 * @{*/

/**
 * @}*/

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
static const Port_ConfigType *Port_ConfigPtr = NULL_PTR;

/* cppcheck-suppress misra-c2012-20.9 ; This is declared at Port_Cfg.h */
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
 * @brief Initialize the GPIO pins to the configuration store on ConfigPTR.
 *
 * The function changes the registers values of the GPIOS depending on the values of the ConfigPtr
 * struct, this function Initialize all pins and port of the ConfigPtr array, the length of the
 * array is given by PORT_PIN_NUMBER_OF_PORTS, To configure the values of the struct use the symbols
 * defined on the Port.h file.
 *
 * @param ConfigPtr       Pointer to ConfigPtr struct array.
 *
 * @reqs   SWS_Port_00140
 */
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    if( ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_INIT, PORT_E_INIT_FAILED );
    }
    else
    {
        Port_Arch_Init( &ConfigPtr );
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
 * @reqs   SWS_Port_00141
 */
/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if PORT_SET_PIN_DIRECTION_API == STD_ON
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    if( Port_ConfigPtr == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_UNINIT );
    }
    else if( ( GET_HIGH_BYTE( Pin ) < MAX_PORT_NUMBER ) && ( GET_LOW_NIBBLE( Pin ) < MAX_PIN_NUMBER ) )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_PARAM_PIN );
    }
    else if( Port_ConfigPtr[ Pin >> 8u ].DirChange == PORTS_CHANGEABLE )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_SET_PIN_DIRECTION, PORT_E_DIRECTION_UNCHANGEABLE );
    }
    else
    {
        Port_Arch_SetPinDirection( Pin, Direction );
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
 * @reqs   SWS_Port_00145
 */
/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if PORT_SET_PIN_MODE_API == STD_ON
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    if( 0 )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_INIT, PORT_E_INIT_FAILED );
    }
    else
    {
        Port_Arch_SetPinMode( Pin, Mode );
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
    if( 0 )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_INIT, PORT_E_INIT_FAILED );
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
 * @reqs   SWS_Port_00142
 */
void Port_RefreshPortDirection( void )
{
    if( 0 )
    {
        /* If development error detection for the Can module is enabled:
        */
        Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_ID_INIT, PORT_E_INIT_FAILED );
    }
    else
    {
        Port_Arch_RefreshPortDirection( );
    }
}
/**
 * @file Port.c
 * @brief Port driver configuration.
 *
 * The port driver provides functions to Initialize and change values on the
 * GPIO registers, this makes use of previously defined symbols that point to
 * those specific registers and symbols to specify the port, pin and configuration
 * that will be applied to the pin.
 */

#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Port.h"

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
static const Port_ConfigType *LocalConfigPtr = NULL_PTR;

/**
 * @brief Initialize the GPIO pins to the confiduration store on ConfigPTR.
 *
 * The function changes the registers values of the GPIOS depending on the values
 * of the ConfigPtr struct, this function Initialize all pins and port of the
 * ConfigPtr array, the length of the array is given by PORT_PIN_NUMBER_OF_PORTS,
 * To configure the values of the struct use the symbols defined on the Port.h file.
 *
 * @param ConfigPtr       Pointer to ConfigPtr struct array.
 *
 * * @reqs   SWS_Port_00140
 */
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *port;
    uint32 mask;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };

    for( uint8 j = 0; j < PORT_PIN_NUMBER_OF_PORTS; j++ )
    {
        port = ports[ ( &ConfigPtr[ j ] )->Port ];
        mask = 1u;
        for( uint32 i = 0u; i < 16u; i++ )
        {
            if( Bfx_TstBitLnMask_u32u32_u8( ( &ConfigPtr[ j ] )->Pins, mask ) == TRUE )
            {
                /*change values on PUPDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->PUPDR, (uint8)( i * 2u ), (uint8)2u, (uint32)( &ConfigPtr[ j ] )->Pull );
                /*change values on OTYPER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OTYPER, i, 1, (uint32)( &ConfigPtr[ j ] )->OutputDrive );
                /*change values on OSPEEDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OSPEEDR, ( i * 2 ), 2, (uint32)( &ConfigPtr[ j ] )->Speed );
                /*change values on MODER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, ( i * 2 ), 2, (uint32)( &ConfigPtr[ j ] )->Mode );
                if( i < 8u )
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( i * 4 ), 4, (uint32)( &ConfigPtr[ j ] )->Altern );
                }
                else
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, ( i - 8 ) * 4, 4, (uint32)( &ConfigPtr[ j ] )->Altern );
                }
            }
            mask = mask << 1;
        }
    }
    LocalConfigPtr = ConfigPtr;
}

/**
 * @brief Set the direction of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS direction during runtime,
 * to eneable this function change the value of PORT_SET_PIN_DIRECTION_API to STD_ON
 * on the Port_Cfg file.
 * To change the direction use the symbols of PORT direction
 *
 * @param Pin             Pin to change the direction.
 * @param Direction       Direction to be changed.
 *
 * * @reqs   SWS_Port_00141
 */
#if PORT_SET_PIN_DIRECTION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Port_RegisterType *port;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, (uint8)( Pin & 0xFu ), 2, (uint8)Direction );
}
#endif

/**
 * @brief Set the mode of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS mode during runtime,
 * to eneable this function change the value of PORT_SET_PIN_MODE_API to STD_ON
 * on the Port_Cfg file.
 * To change the mode use the symbols of GPIO altern values.
 *
 * @param Pin             Pin to change the direction.
 * @param Mode            Mode to be changed.
 *
 * * @reqs   SWS_Port_00145
 */
#if PORT_SET_PIN_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Port_RegisterType *port;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    if( ( Pin & 0xFu ) < 8u )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( Pin & 0xFu ), 4, (uint32)Mode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, ( ( Pin & 0xFu ) - 8 ), 4, (uint32)Mode );
    }
}
#endif

/**
 * @brief Gets the current version.
 *
 * The function gives the versioninfo struct the values of the current version.
 * to eneable this function change the value of PORT_VERSION_INFO_API to STD_ON
 * on the Port_Cfg file.
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 * @reqs   SWS_Port_00143
 */
#if PORT_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    versioninfo->moduleID         = 0;
    versioninfo->sw_major_version = 0;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;
    versioninfo->vendorID         = 0;
}
#endif

/**
 * @brief Refresh port direction.
 *
 * The function refreshes the registers values of the GPIOS moder during runtime to
 * the initial values only if they are configured as non changeables.
 *
 * * @reqs   SWS_Port_00142
 */
void Port_RefreshPortDirection( void )
{
    Port_RegisterType *port;
    uint32 mask;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };

    for( uint8 j = 0; j < PORT_PIN_NUMBER_OF_PORTS; j++ )
    {
        port = ports[ ( &LocalConfigPtr[ j ] )->Port ];
        mask = 1u;
        if( ( ( &LocalConfigPtr[ j ] )->Pin_direction == PORTS_NON_CHANGEABLE ) && ( ( ( &LocalConfigPtr[ j ] )->Mode == PORTS_MODE_INPUT ) || ( ( &LocalConfigPtr[ j ] )->Mode == PORTS_MODE_OUTPUT ) ) )
        {
            for( uint32 i = 0u; i < 16u; i++ )
            {
                if( Bfx_TstBitLnMask_u32u32_u8( ( &LocalConfigPtr[ j ] )->Pins, mask ) == TRUE )
                {
                    /*change values on MODER*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, ( i * 2 ), 2, (uint32)( &LocalConfigPtr[ j ] )->Mode );
                }
                mask = mask << 1;
            }
        }
    }
}

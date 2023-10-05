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
 * @defgroup max_port_values  max number of Mcu ports and pins
 * @{*/
#define MAX_PORT_NUMBER      6u  /*!< Port A value */
#define MAX_PIN_NUMBER       16u /*!< Port A value */
/**
 * @}*/

/**
 * @defgroup bits  defines to replace magic numbers
 * @{*/
#define TWO_BITS             0x02u /*!< operation on two bits */
#define FOUR_BITS            0x04u /*!< operation on four bits */
/**
 * @}*/

/**
 * @defgroup max_port_values  max number of Mcu ports and pins
 * @{*/
#define GET_LOW_NIBBLE( x )  ( (x)&0x0fu )   /*!< Port A value */
#define GET_HIGH_NIBBLE( x ) ( ( x ) >> 4u ) /*!< Port A value */
#define GET_HIGH_BYTE( x )   ( ( x ) >> 8u ) /*!< Port A value */
/**
 * @}*/

/**
 * @defgroup max_port_values  max number of Mcu ports and pins
 * @{*/
#define MUL_BY_TWO           1u /*!< Port A value */
#define MUL_BY_FOUR          2u /*!< Port A value */
/**
 * @}*/

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
static const Port_ConfigType *LocalConfigPtr = NULL_PTR;

/**
 * @brief Global port register array
 */
/* clang-format off */
static Port_RegisterType *Port_Ports[ MAX_PORT_NUMBER ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
/* clang-format on */

/**
 * @brief Initialize the GPIO pins to the configuration store on ConfigPTR.
 *
 * The function changes the registers values of the GPIOS depending on the values
 * of the ConfigPtr struct, this function Initialize all pins and port of the
 * ConfigPtr array, the length of the array is given by PORT_PIN_NUMBER_OF_PORTS,
 * To configure the values of the struct use the symbols defined on the Port.h file.
 *
 * @param ConfigPtr       Pointer to ConfigPtr struct array.
 *
 * @reqs   SWS_Port_00140
 */
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *PortReg;

    for( uint8 Port = 0u; Port < PORT_PIN_NUMBER_OF_PORTS; Port++ )
    {
        PortReg = Port_Ports[ ConfigPtr[ Port ].Port ];

        for( uint8 Pin = 0u; Pin < MAX_PIN_NUMBER; Pin++ )
        {
            if( Bfx_GetBit_u32u8_u8( (uint32 *)&ConfigPtr[ Port ].Pins, Pin ) == TRUE )
            {
                /*change values on PUPDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->PUPDR, ( Pin << MUL_BY_TWO ), TWO_BITS, ConfigPtr[ Port ].Pull );
                /*change values on OTYPER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OTYPER, Pin, 1u, ConfigPtr[ Port ].OutputDrive );
                /*change values on OSPEEDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OSPEEDR, ( Pin << MUL_BY_TWO ), TWO_BITS, ConfigPtr[ Port ].Speed );
                /*change values on MODER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( ConfigPtr[ Port ].Mode ) );

                if( Pin < PORTS_PIN_08_VAL )
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( Pin << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( ConfigPtr[ Port ].Mode ) );
                }
                else
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( Pin - PORTS_PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( ConfigPtr[ Port ].Mode ) );
                }
            }
        }
    }
    /*make the port configuration accesible for other functions*/
    LocalConfigPtr = ConfigPtr;
}

/**
 * @brief Set the direction of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS direction during runtime,
 * to enable this function change the value of PORT_SET_PIN_DIRECTION_API to STD_ON
 * on the Port_Cfg file.
 * To change the direction use the symbols of PORT direction
 *
 * @param Pin             Pin to change the direction.
 * @param Direction       Direction to be changed.
 *
 * @reqs   SWS_Port_00141
 */
#if PORT_SET_PIN_DIRECTION_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, GET_LOW_NIBBLE( Pin ), TWO_BITS, Direction );
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
 * @reqs   SWS_Port_00145
 */
#if PORT_SET_PIN_MODE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    /*Set mode*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( Mode ) );

    if( GET_LOW_NIBBLE( Pin ) < PORTS_PIN_08_VAL )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( GET_LOW_NIBBLE( Pin ) << MUL_BY_FOUR ), FOUR_BITS, Mode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( GET_LOW_NIBBLE( Pin ) - PORTS_PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, Mode );
    }
}
#endif

/**
 * @brief Gets the current version.
 *
 * The function gives the versioninfo struct the values of the current version.
 * to eneable this function change the value of PORT_VERSION_INFO_API to STD_ON
 * on the Port_Cfg file.
 *
 * @param versioninfo             Pointer to Std_VersionInfoType struct.
 *
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
 * @reqs   SWS_Port_00142
 */
void Port_RefreshPortDirection( void )
{
    Port_RegisterType *PortReg;

    for( uint8 Port = 0; Port < PORT_PIN_NUMBER_OF_PORTS; Port++ )
    {
        PortReg = Port_Ports[ LocalConfigPtr[ Port ].Port ];

        if( ( LocalConfigPtr[ Port ].DirChange == FALSE ) && ( ( LocalConfigPtr[ Port ].Mode == PORTS_MODE_INPUT ) || ( LocalConfigPtr[ Port ].Mode == PORTS_MODE_OUTPUT ) ) )
        {
            for( uint8 Pin = 0u; Pin < MAX_PIN_NUMBER; Pin++ )
            {
                if( Bfx_GetBit_u32u8_u8( (uint32 *)&LocalConfigPtr[ Port ].Pins, Pin ) == TRUE )
                {
                    /*change values on MODER*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( LocalConfigPtr[ Port ].Mode ) );
                }
            }
        }
    }
}

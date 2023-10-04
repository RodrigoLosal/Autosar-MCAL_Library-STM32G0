/**
 * @file    Port.c
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
#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Port.h"

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
 * @defgroup bits  defines to replace magic numbers
 * @{*/
#define TWO_BITS             0x02u /*!< operation on two bits */
#define FOUR_BITS            0x04u /*!< operation on four bits */
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
 * @defgroup mlu_factors  multiplication factors
 *
 * @{*/
#define MUL_BY_TWO           1u /*!< Multiply by two on a shift operation */
#define MUL_BY_FOUR          2u /*!< Multiply by four on a shift operation */
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

/*temporary macro to be remove when Det is implemented*/
#define assert_det( param, error ) (void)0

/**
 * @brief  temporary macro to be remove when Det is implemented
 *
 * @param   param sentence to validate if true
 * @param   error if not true send this error
 */
#define assert_det( param, error ) (void)0

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
    Port_RegisterType *PortReg;

    /*validate if the intialization pointer is not NULL, in case null trigger an error*/
    assert_det( ConfigPtr != NULL_PTR, PORT_E_INIT_FAILED );

    /*validate if the intialization pointer is not NULL, in case null trigger an error*/
    assert_det( ConfigPtr != NULL_PTR, PORT_E_INIT_FAILED );

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
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    /*validate if Port_Init function has been called previously*/
    assert_det( LocalConfigPtr != NULL_PTR, PORT_E_UNINIT );
    /*validate is Pin is a valid value*/
    assert_det( ( GET_HIGH_BYTE( Pin ) < MAX_PORT_NUMBER ) && ( GET_LOW_NIBBLE( Pin ) < MAX_PIN_NUMBER ), PORT_E_PARAM_PIN );
    /*validate if the pin has active its corresponding changeable flag*/
    assert_det( LocalConfigPtr[ Pin >> 8u ].Pin_direction == PORTS_CHANGEABLE, PORT_E_DIRECTION_UNCHANGEABLE );

    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, GET_LOW_NIBBLE( Pin ), 2u, Direction );
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
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    /*validate if Port_Init function has been called previously*/
    assert_det( LocalConfigPtr != NULL_PTR, PORT_E_UNINIT );
    /*validate is Pin is a valid value*/
    assert_det( ( GET_HIGH_BYTE( Pin ) < MAX_PORT_NUMBER ) && ( GET_LOW_NIBBLE( Pin ) < MAX_PIN_NUMBER ), PORT_E_PARAM_PIN );
    /*validate is Mode is a valid value*/
    assert_det( ( GET_HIGH_NIBBLE < MAX_PIN_MODES ) && ( GET_LOW_NIBBLE( Mode ) < MAX_ALT_MODES ), PORT_E_PARAM_INVALID_MODE );
    /*validate if the pin has active its corresponding changeable flag*/
    assert_det( LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].ModeChange == TRUE, PORT_E_MODE_UNCHANGEABLE );

    /*validate if Port_Init function has been called previously*/
    assert_det( LocalConfigPtr != NULL_PTR, PORT_E_UNINIT );
    /*validate is Pin is a valid value*/
    assert_det( ( GET_HIGH_BYTE( Pin ) < MAX_PORT_NUMBER ) && ( GET_LOW_NIBBLE( Pin ) < MAX_PIN_NUMBER ), PORT_E_PARAM_PIN );
    /*validate is Mode is a valid value*/
    assert_det( ( GET_HIGH_NIBBLE < MAX_PIN_MODES ) && ( GET_LOW_NIBBLE( Mode ) < MAX_ALT_MODES ), PORT_E_PARAM_INVALID_MODE );
    /*validate if the pin has active its corresponding changeable flag*/
    assert_det( LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].ModeChange == TRUE, PORT_E_MODE_UNCHANGEABLE );

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
    assert_det( versioninfo != NULL, PORT_E_PARAM_POINTER );

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
 * The function refreshes the registers values of the GPIOS moder during runtime to the initial values
 * only if they are configured as non changeables.
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

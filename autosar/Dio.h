#ifndef DIO_H_
#define DIO_H_

#include "../autosar/mcal/Platform_Types.h"


/**
 * @name    Dio Channel Type 
 * @reqs    SWS_Dio_00182
 *
 * Numeric ID of a DIO channel.
 */
/**@{*/
typedef uint8 Dio_ChannelType;
/**@}*/


/**
 * @name    Dio Port Type 
 * @reqs    SWS_Dio_00183
 *
 * Numeric ID of a DIO port.
 */
/**@{*/
typedef uint8 Dio_PortType;
/**@}*/


/**
 * @name    Dio Level Type 
 * @reqs    SWS_Dio_00185
 *
 * These are the possible levels a DIO channel can have (input or output).
 */
/**@{*/
typedef uint8 Dio_LevelType;
/**@}*/


/**
 * @name    Dio Port Level Type 
 * @reqs    SWS_Dio_00186
 *
 * If the µC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_PortLevelType
 * inherits the size of the largest port.
 */
/**@{*/
typedef uint8 Dio_PortLevelType;
/**@}*/


/**
 * @name    Dio Channel Group Type
 * @reqs    SWS_Dio_00184
 *
 * Type for the definition of a channel group, which consists of several adjoining
 * channels within a port.
 */
/**@{*/
typedef struct Dio_ChannelGroupType
{
    uint8 mask;             /* This element mask which defines the positions of the channel group. */
    uint8 offset;           /* This element shall be the position of the Channel Group on the port,
                                counted from the LSB. */
    Dio_PortType port;      /* This shall be the port on which the Channel group is defined. */
} Dio_ChannelGroupType;
/**@}*/



#define PORTA   0u /*!< Port A pin 0 value*/
#define PORTB   1u /*!< Port A pin 0 value*/
#define PORTC   2u /*!< Port A pin 0 value*/
#define PORTD   3u /*!< Port A pin 0 value*/
#define PORTE   4u /*!< Port A pin 0 value*/
#define PORTF   5u /*!< Port A pin 0 value*/
/*#define GPIO_PORTA_DATA_REG       (((volatile uint32)0x400043FC))
#define GPIO_PORTB_DATA_REG       (((volatile uint32)0x400053FC))
#define GPIO_PORTC_DATA_REG       (((volatile uint32)0x400063FC))
#define GPIO_PORTD_DATA_REG       (((volatile uint32)0x400073FC))
#define GPIO_PORTE_DATA_REG       (((volatile uint32)0x400243FC))
#define GPIO_PORTF_DATA_REG       (((volatile uint32)0x400253FC))*/

/**
 * @name   DIO A pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port A
 */
/**@{*/
#define DIO_PIN_PA_00   (Dio_ChannelType)0x00u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_01   (Dio_ChannelType)0x01u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_02   (Dio_ChannelType)0x02u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_03   (Dio_ChannelType)0x03u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_04   (Dio_ChannelType)0x04u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_05   (Dio_ChannelType)0x05u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_06   (Dio_ChannelType)0x06u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_07   (Dio_ChannelType)0x07u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_08   (Dio_ChannelType)0x08u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_09   (Dio_ChannelType)0x09u  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_10   (Dio_ChannelType)0x0Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_11   (Dio_ChannelType)0x0Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_12   (Dio_ChannelType)0x0Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_13   (Dio_ChannelType)0x0Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_14   (Dio_ChannelType)0x0Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PA_15   (Dio_ChannelType)0x0Fu  /*!< Port A pin 0 value*/
/**@}*/


/**
 * @name   DIO B pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port B
 */
/**@{*/
#define DIO_PIN_PB_00   (Dio_ChannelType)0x10u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_01   (Dio_ChannelType)0x11u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_02   (Dio_ChannelType)0x12u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_03   (Dio_ChannelType)0x13u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_04   (Dio_ChannelType)0x14u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_05   (Dio_ChannelType)0x15u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_06   (Dio_ChannelType)0x16u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_07   (Dio_ChannelType)0x17u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_08   (Dio_ChannelType)0x18u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_09   (Dio_ChannelType)0x19u  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_10   (Dio_ChannelType)0x1Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_11   (Dio_ChannelType)0x1Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_12   (Dio_ChannelType)0x1Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_13   (Dio_ChannelType)0x1Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_14   (Dio_ChannelType)0x1Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PB_15   (Dio_ChannelType)0x1Fu  /*!< Port A pin 0 value*/
/**@}*/


/**
 * @name   DIO C pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port C
 */
/**@{*/
#define DIO_PIN_PC_00   (Dio_ChannelType)0x20u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_01   (Dio_ChannelType)0x21u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_02   (Dio_ChannelType)0x22u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_03   (Dio_ChannelType)0x23u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_04   (Dio_ChannelType)0x24u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_05   (Dio_ChannelType)0x25u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_06   (Dio_ChannelType)0x26u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_07   (Dio_ChannelType)0x27u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_08   (Dio_ChannelType)0x28u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_09   (Dio_ChannelType)0x29u  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_10   (Dio_ChannelType)0x2Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_11   (Dio_ChannelType)0x2Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_12   (Dio_ChannelType)0x2Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_13   (Dio_ChannelType)0x2Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_14   (Dio_ChannelType)0x2Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PC_15   (Dio_ChannelType)0x2Fu  /*!< Port A pin 0 value*/
/**@}*/


/**
 * @name   DIO D pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port D
 */
/**@{*/
#define DIO_PIN_PD_00   (Dio_ChannelType)0x30u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_01   (Dio_ChannelType)0x31u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_02   (Dio_ChannelType)0x32u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_03   (Dio_ChannelType)0x33u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_04   (Dio_ChannelType)0x34u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_05   (Dio_ChannelType)0x35u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_06   (Dio_ChannelType)0x36u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_07   (Dio_ChannelType)0x37u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_08   (Dio_ChannelType)0x38u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_09   (Dio_ChannelType)0x39u  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_10   (Dio_ChannelType)0x3Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_11   (Dio_ChannelType)0x3Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_12   (Dio_ChannelType)0x3Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_13   (Dio_ChannelType)0x3Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_14   (Dio_ChannelType)0x3Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PD_15   (Dio_ChannelType)0x3Fu  /*!< Port A pin 0 value*/
/**@}*/


/**
 * @name   DIO E pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port E
 */
/**@{*/
#define DIO_PIN_PE_00   (Dio_ChannelType)0x40u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_01   (Dio_ChannelType)0x41u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_02   (Dio_ChannelType)0x42u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_03   (Dio_ChannelType)0x43u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_04   (Dio_ChannelType)0x44u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_05   (Dio_ChannelType)0x45u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_06   (Dio_ChannelType)0x46u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_07   (Dio_ChannelType)0x47u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_08   (Dio_ChannelType)0x48u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_09   (Dio_ChannelType)0x49u  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_10   (Dio_ChannelType)0x4Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_11   (Dio_ChannelType)0x4Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_12   (Dio_ChannelType)0x4Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_13   (Dio_ChannelType)0x4Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_14   (Dio_ChannelType)0x4Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PE_15   (Dio_ChannelType)0x4Fu  /*!< Port A pin 0 value*/
/**@}*/


/**
 * @name   DIO F pin Values 
 * @reqs    SWS_Dio_00184
 *
 * Symbols to specify pins on port F
 */
/**@{*/
#define DIO_PIN_PF_00   (Dio_ChannelType)0x50u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_01   (Dio_ChannelType)0x51u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_02   (Dio_ChannelType)0x52u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_03   (Dio_ChannelType)0x53u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_04   (Dio_ChannelType)0x54u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_05   (Dio_ChannelType)0x55u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_06   (Dio_ChannelType)0x56u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_07   (Dio_ChannelType)0x57u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_08   (Dio_ChannelType)0x58u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_09   (Dio_ChannelType)0x59u  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_10   (Dio_ChannelType)0x5Au  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_11   (Dio_ChannelType)0x5Bu  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_12   (Dio_ChannelType)0x5Cu  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_13   (Dio_ChannelType)0x5Du  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_14   (Dio_ChannelType)0x5Eu  /*!< Port A pin 0 value*/
#define DIO_PIN_PF_15   (Dio_ChannelType)0x5Fu  /*!< Port A pin 0 value*/
/**@}*/


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId );
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );


#endif /* DIO_H_ */
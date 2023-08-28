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


Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId );
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );


#endif /* DIO_H_ */
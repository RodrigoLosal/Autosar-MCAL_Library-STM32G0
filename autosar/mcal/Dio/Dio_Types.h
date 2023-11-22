/**
 * @file    Dio_Types.h
 * @brief   **Dio Driver Types**
 * @author  Enrique, Diego Perez
 *
 * The header contains the type definitions that are used by the Dio module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef DIO_TYPES_H__
#define DIO_TYPES_H__

/**
 * @defgroup DIO_STATIC DIO static define for testing purposes
 *
 * @{ */
#ifndef UTEST
#define DIO_STATIC static /*!< Add static when no testing */
#else
#define DIO_STATIC /*!< remove static for testing purposes */
#endif
/**
 * @} */

/**
 * @defgroup DIO_Ids Can Id number for module and each API
 *
 * @{ */
#define DIO_ID_READ_CHANNEL            0x00u /*!< *!< Dio_ReadChannel() api service id */
#define DIO_ID_WRITE_CHANNEL           0x01u /*!< *!< Dio_WriteChannel() api service id */
#define DIO_ID_READ_PORT               0x02u /*!< *!< Dio_ReadPort() api service id */
#define DIO_ID_WRITE_PORT              0x03u /*!< *!< Dio_WritePort() api service id */
#define DIO_ID_READ_CHANNEL_GRP        0x04u /*!< *!< Dio_ReadChannelGroup() api service id */
#define DIO_ID_WRITE_CHANNEL_GRP       0x05u /*!< *!< Dio_WriteChannelGroup() api service id */
#define DIO_ID_GET_VERSION_INFO        0x12u /*!< *!< Dio_GetVersionInfo() api service id */
#define DIO_ID_FLIP_CHANNEL            0x11u /*!< *!< Dio_FlipChannel() api service id */
#define DIO_ID_MASKED_WRITE_PORT       0x13u /*!< *!< Dio_MaskedWritePort() api service id */
/**
 * @} */

/**
 * @defgroup DIO_Error_Typse Dio Developtmnet Error Types
 *
 * @reqs  SWS_Dio_91001
 *
 * @{ */
#define DIO_E_PARAM_INVALID_CHANNEL_ID 0x0Au /*!< *!< Invalid Channel ID */
#define DIO_E_PARAM_INVALID_PORT_ID    0x14u /*!< *!< Invalid Port ID */
#define DIO_E_PARAM_INVALID_GROUP      0x1Fu /*!< *!< Invalid Group */
#define DIO_E_PARAM_POINTER            0x20u /*!< *!< Invalid Pointer */
/**
 * @} */

/**
 * @brief Parameters of type Dio_ChannelType contain the numeric ID of a DIO channel.
 *
 * The mapping of the ID is implementation specific but not configurable.
 * Range: This is implementation specific but not all values may be valid within the
 * type. Shall cover all available DIO channels.
 *
 * @reqs  SWS_Dio_00182
 */
typedef uint8 Dio_ChannelType;

/**
 * @brief Parameters of type Dio_PortType contain the numeric ID of a DIO port.
 *
 * The mapping of ID is implementation specific but not configurable.
 * Range: 0 - number of ports. Shall cover all available DIO Ports.
 *
 * @reqs  SWS_Dio_00183
 */
typedef uint8 Dio_PortType;

/**
 * @brief The type for the possible levels that a DIO channel can have (input or output).
 *
 * Range: STD_LOW 0x00 Physical state 0V. STD_HIGH 0x01 Physical state 5V or 3.3V.
 *
 * @reqs  SWS_Dio_00185
 */
typedef uint8 Dio_LevelType;

/**
 * @brief The type for the value of a DIO port.
 *
 * If the µC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_PortLevelType inherits
 * the size of the largest port.
 * Range: 0...xxx.
 *
 * @reqs  SWS_Dio_00186
 */
typedef uint32 Dio_PortLevelType;

/**
 * @brief Type for the definition of a channel group, which consists of several adjoining
 * channels within a port.
 *
 * @reqs  SWS_Dio_00184
 */
typedef struct
{
    uint8 mask;        /*!< This element mask which defines the positions of the
                            channel group. */
    uint8 offset;      /*!< This element shall be the position of the Channel Group
                           on the port, counted from the LSB. */
    Dio_PortType port; /*!< This shall be the port on which the Channel group is
                            defined. */
} Dio_ChannelGroupType;

/**
 * @brief Type for the definitions of a Pin wicch is made of port and pin number.
 */
typedef struct _Dio_PinType
{
    uint8 Pin;         /*!< This element shall be the position of the pin ion a port */
    Dio_PortType Port; /*!< This shall be the port on which the pin is defined */
} Dio_PinType;

/**
 * @brief Global configuration structures with all the channels and groups.
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef struct _Dio_ConfigType
{                                       /* cppcheck-suppress misra-c2012-2.4 ; the enum name it is neccesary */
    uint8 NumberOfPorts;                /*!< The number of ports */
    const Dio_PinType *Channels;        /*!< Pointer to array of individual pin channels */
    uint8 NumberOfChannels;             /*!< The number of pin channels */
    const Dio_ChannelGroupType *Groups; /*!< Pointer to array of port groups */
    uint8 NumberOfGroups;               /*!< The number of port groups */
} Dio_ConfigType;

#endif /* DIO_TYPES_H__ */

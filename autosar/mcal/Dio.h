/**
 * @file Dio.h
 * @brief Dio driver configuration.
 *
 * This is the file for the Dio driver, it provides functions for accessing the hardware
 * pins of the microcontroller. It also allows the grouping of those pins.
 *
 * The DIO driver provides services for reading and writing to/from:
 * DIO Channels (Pins)
 * DIO Ports
 * DIO Channel Groups
 *
 * This module operates on pins and ports configured by the PORT driver for this purpose.
 * For this reason, there is no configuration and initialization of this port structure in
 * the DIO driver.
 *
 * The DIO driver provides the following functions:
 * The Dio controller will define functions to modify the output channel levels individually,
 * for a port or for a channel group.
 * The Dio driver will define functions to read the level of the input and output channels
 * individually, for a port or for a group of channels.
 *
 * @note Dio module will use the definitions that have been created during the configuration
 * process in the Dio_Cfg.h file.
 */
#ifndef DIO_H__
#define DIO_H__

/**
 * @brief Parameters of type Dio_ChannelType contain the numeric ID of a DIO channel. The
 *        mapping of the ID is implementation specific but not configurable.
 *        Range: This is implementation specific but not all values may be valid within the
 *               type. Shall cover all available DIO channels.
 *
 * @reqs  SWS_Dio_00182
 */
typedef uint8 Dio_ChannelType;

/**
 * @brief Parameters of type Dio_PortType contain the numeric ID of a DIO port. The mapping
 *        of ID is implementation specific but not configurable.
 *        Range: 0 - number of ports. Shall cover all available DIO Ports.
 *
 * @reqs  SWS_Dio_00183
 */
typedef uint8 Dio_PortType;

/**
 * @brief The type for the possible levels that a DIO channel can have (input or output).
 *        Range: STD_LOW 0x00 Physical state 0V. STD_HIGH 0x01 Physical state 5V or 3.3V.
 *
 * @reqs  SWS_Dio_00185
 */
typedef uint8 Dio_LevelType;

/**
 * @brief The type for the value of a DIO port. If the µC owns ports of different port
 *        widths (e.g. 4, 8,16...Bit) Dio_PortLevelType inherits the size of the
 *        largest port.
 *        Range: 0...xxx.
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
  * @defgroup DIOA pine values
  *
  * Symbols to specify the values of the DIO pins on port A, the 4 most significant
  * bits represent the pin port and the 4 least significant bits represent the pin.
  @{ */
#define DIO_PIN_PA_00 (Dio_ChannelType)0x00u /*!< Dio A pin 0 value */
#define DIO_PIN_PA_01 (Dio_ChannelType)0x01u /*!< Dio A pin 1 value */
#define DIO_PIN_PA_02 (Dio_ChannelType)0x02u /*!< Dio A pin 2 value */
#define DIO_PIN_PA_03 (Dio_ChannelType)0x03u /*!< Dio A pin 3 value */
#define DIO_PIN_PA_04 (Dio_ChannelType)0x04u /*!< Dio A pin 4 value */
#define DIO_PIN_PA_05 (Dio_ChannelType)0x05u /*!< Dio A pin 5 value */
#define DIO_PIN_PA_06 (Dio_ChannelType)0x06u /*!< Dio A pin 6 value */
#define DIO_PIN_PA_07 (Dio_ChannelType)0x07u /*!< Dio A pin 7 value */
#define DIO_PIN_PA_08 (Dio_ChannelType)0x08u /*!< Dio A pin 8 value */
#define DIO_PIN_PA_09 (Dio_ChannelType)0x09u /*!< Dio A pin 9 value */
#define DIO_PIN_PA_10 (Dio_ChannelType)0x0Au /*!< Dio A pin 10 value */
#define DIO_PIN_PA_11 (Dio_ChannelType)0x0Bu /*!< Dio A pin 11 value */
#define DIO_PIN_PA_12 (Dio_ChannelType)0x0Cu /*!< Dio A pin 12 value */
#define DIO_PIN_PA_13 (Dio_ChannelType)0x0Du /*!< Dio A pin 13 value */
#define DIO_PIN_PA_14 (Dio_ChannelType)0x0Eu /*!< Dio A pin 14 value */
#define DIO_PIN_PA_15 (Dio_ChannelType)0x0Fu /*!< Dio A pin 15 value */
/**
  @} */

/**
  * @defgroup DIOB pine values
  *
  * Symbols to specify the values of the DIO pins on port B, the 4 most significant
  * bits represent the pin port and the 4 least significant bits represent the pin.
  @{ */
#define DIO_PIN_PB_00 (Dio_ChannelType)0x10u /*!< Dio B pin 0 value */
#define DIO_PIN_PB_01 (Dio_ChannelType)0x11u /*!< Dio B pin 1 value */
#define DIO_PIN_PB_02 (Dio_ChannelType)0x12u /*!< Dio B pin 2 value */
#define DIO_PIN_PB_03 (Dio_ChannelType)0x13u /*!< Dio B pin 3 value */
#define DIO_PIN_PB_04 (Dio_ChannelType)0x14u /*!< Dio B pin 4 value */
#define DIO_PIN_PB_05 (Dio_ChannelType)0x15u /*!< Dio B pin 5 value */
#define DIO_PIN_PB_06 (Dio_ChannelType)0x16u /*!< Dio B pin 6 value */
#define DIO_PIN_PB_07 (Dio_ChannelType)0x17u /*!< Dio B pin 7 value */
#define DIO_PIN_PB_08 (Dio_ChannelType)0x18u /*!< Dio B pin 8 value */
#define DIO_PIN_PB_09 (Dio_ChannelType)0x19u /*!< Dio B pin 9 value */
#define DIO_PIN_PB_10 (Dio_ChannelType)0x1Au /*!< Dio B pin 10 value */
#define DIO_PIN_PB_11 (Dio_ChannelType)0x1Bu /*!< Dio B pin 11 value */
#define DIO_PIN_PB_12 (Dio_ChannelType)0x1Cu /*!< Dio B pin 12 value */
#define DIO_PIN_PB_13 (Dio_ChannelType)0x1Du /*!< Dio B pin 13 value */
#define DIO_PIN_PB_14 (Dio_ChannelType)0x1Eu /*!< Dio B pin 14 value */
#define DIO_PIN_PB_15 (Dio_ChannelType)0x1Fu /*!< Dio B pin 15 value */
/**
  @} */

/**
  * @defgroup DIOC pine values
  *
  * Symbols to specify the values of the DIO pins on port C, the 4 most significant
  * bits represent the pin port and the 4 least significant bits represent the pin.
  @{ */
#define DIO_PIN_PC_00 (Dio_ChannelType)0x20u /*!< Dio C pin 0 value */
#define DIO_PIN_PC_01 (Dio_ChannelType)0x21u /*!< Dio C pin 1 value */
#define DIO_PIN_PC_02 (Dio_ChannelType)0x22u /*!< Dio C pin 2 value */
#define DIO_PIN_PC_03 (Dio_ChannelType)0x23u /*!< Dio C pin 3 value */
#define DIO_PIN_PC_04 (Dio_ChannelType)0x24u /*!< Dio C pin 4 value */
#define DIO_PIN_PC_05 (Dio_ChannelType)0x25u /*!< Dio C pin 5 value */
#define DIO_PIN_PC_06 (Dio_ChannelType)0x26u /*!< Dio C pin 6 value */
#define DIO_PIN_PC_07 (Dio_ChannelType)0x27u /*!< Dio C pin 7 value */
#define DIO_PIN_PC_08 (Dio_ChannelType)0x28u /*!< Dio C pin 8 value */
#define DIO_PIN_PC_09 (Dio_ChannelType)0x29u /*!< Dio C pin 9 value */
#define DIO_PIN_PC_10 (Dio_ChannelType)0x2Au /*!< Dio C pin 10 value */
#define DIO_PIN_PC_11 (Dio_ChannelType)0x2Bu /*!< Dio C pin 11 value */
#define DIO_PIN_PC_12 (Dio_ChannelType)0x2Cu /*!< Dio C pin 12 value */
#define DIO_PIN_PC_13 (Dio_ChannelType)0x2Du /*!< Dio C pin 13 value */
#define DIO_PIN_PC_14 (Dio_ChannelType)0x2Eu /*!< Dio C pin 14 value */
#define DIO_PIN_PC_15 (Dio_ChannelType)0x2Fu /*!< Dio C pin 15 value */
/**
  @} */

/**
  * @defgroup DIOD pine values
  *
  * Symbols to specify the values of the DIO pins on port D, the 4 most significant
  * bits represent the pin port and the 4 least significant bits represent the pin.
  @{ */
#define DIO_PIN_PD_00 (Dio_ChannelType)0x30u /*!< Dio D pin 0 value */
#define DIO_PIN_PD_01 (Dio_ChannelType)0x31u /*!< Dio D pin 1 value */
#define DIO_PIN_PD_02 (Dio_ChannelType)0x32u /*!< Dio D pin 2 value */
#define DIO_PIN_PD_03 (Dio_ChannelType)0x33u /*!< Dio D pin 3 value */
#define DIO_PIN_PD_04 (Dio_ChannelType)0x34u /*!< Dio D pin 4 value */
#define DIO_PIN_PD_05 (Dio_ChannelType)0x35u /*!< Dio D pin 5 value */
#define DIO_PIN_PD_06 (Dio_ChannelType)0x36u /*!< Dio D pin 6 value */
#define DIO_PIN_PD_08 (Dio_ChannelType)0x38u /*!< Dio D pin 8 value */
#define DIO_PIN_PD_09 (Dio_ChannelType)0x39u /*!< Dio D pin 9 value */
/**
  @} */

/**
  * @defgroup DIOF pine values
  *
  * Symbols to specify the values of the DIO pins on port F, the 4 most significant
  * bits represent the pin port and the 4 least significant bits represent the pin.
  @{ */
#define DIO_PIN_PF_00 (Dio_ChannelType)0x50u /*!< Dio F pin 0 value */
#define DIO_PIN_PF_01 (Dio_ChannelType)0x51u /*!< Dio F pin 1 value */
#define DIO_PIN_PF_02 (Dio_ChannelType)0x52u /*!< Dio F pin 2 value */
#define DIO_PIN_PF_03 (Dio_ChannelType)0x53u /*!< Dio F pin 3 value */
#define DIO_PIN_PF_04 (Dio_ChannelType)0x54u /*!< Dio F pin 4 value */
/**
  @} */

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId );
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr );
void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level );
Dio_PortLevelType Dio_GetVersionInfo( Std_VersionInfoType *versioninfo );
void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask );

#endif /* DIO_H_ */
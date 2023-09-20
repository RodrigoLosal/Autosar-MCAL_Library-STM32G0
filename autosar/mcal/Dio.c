/**
 * @file Dio.c
 * @brief Port driver configuration.
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
#include "Std_Types.h"
#include "Registers.h"
#include "Bfx.h"
#include "Dio_Cfg.h"
#include "Dio.h"

/**
  * @defgroup Values-Dio to represent repeating numbers or replace numbers by definitions.
  @{ */
#define VALUE_F (Dio_LevelType)0xF /*!< Defines the value 0xF */
#define SIX     6u                 /*!< Defines the value of 6 */
#define FOUR    4u                 /*!< Defines the value of 4 */
/**
  @} */

/**
 * @brief  Pointer type variable to define the Ports.
 */
static Dio_RegisterType *Dios_Port[ SIX ] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

/**
 * @brief Read Channel
 *
 * The function will return the value of the specified DIO channel, taking the MSB bit as
 * the port and the LSB bit as the pin.
 *
 * @param ChannelId ID of DIO channel.
 *
 * @retval Returns the value of the specified DIO channel.
 */
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_LevelType Pin     = ChannelId & VALUE_F;

    return Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );
}

/**
 * @brief Write Channel
 *
 * This function will write the specified Level to the output if the specified channel is
 * configured as output channel, in this case the function will set the specified Level
 * for the specified channel. Taking the MSB bit as the port and the LSB bit as the pin.
 *
 * @param ChannelId ID of DIO channel.
 * @param Level Value to be written.
 */
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_PortType Pin      = ChannelId & VALUE_F;

    Bfx_PutBit_u32u8u8( (uint32 *)&Dio->ODR, Pin, Level );
}

/**
 * @brief Flip Channel
 *
 * This function is used when the specified channel is configured as output channel, the
 * Dio_FlipChannel function will read the channel level and invert it, then write the
 * inverted level to the channel. The return value will be the inverted level of the
 * specified channel.
 *
 * @param ChannelId ID of DIO channel.
 *
 * @retval Returns the level of a channel after flipping the level.
 */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
    Dio_RegisterType *Dio = Dios_Port[ ChannelId >> FOUR ];
    Dio_PortType Pin      = ChannelId & VALUE_F;

    Bfx_ToggleBitMask_u32u32( (uint32 *)&Dio->ODR, ( 1u << Pin ) );

    return Bfx_GetBit_u32u8_u8( (uint32 *)&Dio->IDR, Pin );
}

/**
 * @brief Read Port
 *
 * The function will return the level of all channels on that port, taking the MSB bit as
 * the port and the LSB bit as the pin.
 *
 * @param PortId ID of DIO Port.
 *
 * @retval Returns the level of all channels on that port.
 */
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
    return (Dio_PortLevelType)Dios_Port[ PortId ];
}

/**
 * @brief Write Port
 *
 * This function is used to set the value specified by the Level parameter for the port
 * specified in the parameters.
 *
 * @param PortId ID of DIO Port.
 * @param Level Value to be written.
 */
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    Dios_Port[ PortId ] = (Dio_RegisterType *)Level;
}

/**
 * @brief Read Channel Group
 *
 * This function will read a subset of the contiguous bits of a port (channel group). It will
 * also perform masking of the channel group and the function will perform the offset so that
 * the values read by the function are aligned with the LSB.
 *
 * @param ChannelGroupIdPtr Pointer to ChannelGroup.
 *
 * @retval Returns the level of a subset of the adjacent bits of a port (channel group).
 */
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = 0;
    const Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    GroupLevel = ( Port->IDR ) & ( ChannelGroupIdPtr->mask );

    Bfx_ShiftBitRt_u32u8( (uint32 *)GroupLevel, ChannelGroupIdPtr->offset );

    return GroupLevel;
}

/**
 * @brief Write Channel Group
 *
 * This function will set a subset of the adjacent bits of a port (channel group) to a
 * specified level. The function will not change the remaining channels of the port or
 * the channels configured as input. Also this function will perform the masking of the
 * channel group and in addition the function will perform the shift so that the values
 * written by the function are aligned with the LSB.
 *
 * @param ChannelGroupIdPtr Pointer to ChannelGroup.
 * @param Level Value to be written.
 */
void Dio_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port = Dios_Port[ ChannelGroupIdPtr->port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&Port->ODR, ChannelGroupIdPtr->offset, ChannelGroupIdPtr->mask, Level );
}

/**
 * @brief Get Version Info
 *
 * This function is used to define DIO driver version information.
 *
 * @param versioninfo Pointer to where to store the version information of this module.
 *
 * @retval Returns a variable for testing purposes .
 */
Dio_PortLevelType Dio_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    Dio_PortLevelType Level = 0;

    versioninfo->vendorID         = DIO_VENDOR_ID;
    versioninfo->moduleID         = DIO_MODULE_ID;
    versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;

    return Level;
}

/**
 * @brief Masked Write Port
 *
 * This function will set the specified value for the channels on the specified port if the
 * corresponding bit in Mask is '1'.
 *
 * @param PortId ID of DIO Port.
 * @param Level Value to be written.
 * @param Mask Channels to be masked in the port.
 */
void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
    Dio_RegisterType *Port = Dios_Port[ PortId ];

    Port->ODR = Mask & ( ( Port->ODR ) | Level );
}
/**
 * @file Dio.c
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
#include "Std_Types.h"
#include "Dio.h"
#include "Dio_Arch.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at dio_Cfg.h */
#if DIO_DEV_ERROR_DETECT == STD_OFF
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
    Dio_LevelType Value = STD_OFF;

    if( ChannelId < DioConfig.NumberOfChannels )
    {
        Value = Dio_Arch_ReadChannel( DioConfig.Channels[ ChannelId ].Port, DioConfig.Channels[ ChannelId ].Pin );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_READ_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID );
    }

    return Value;
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
    if( ChannelId < DioConfig.NumberOfChannels )
    {
        Dio_Arch_WriteChannel( DioConfig.Channels[ ChannelId ].Port, DioConfig.Channels[ ChannelId ].Pin, Level );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_WRITE_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID );
    }
}

#if DIO_FLIP_CHANNEL_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
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
    Dio_LevelType Value = STD_OFF;

    if( ChannelId < DioConfig.NumberOfChannels )
    {
        Value = Dio_Arch_FlipChannel( DioConfig.Channels[ ChannelId ].Port, DioConfig.Channels[ ChannelId ].Pin );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_FLIP_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID );
    }

    return Value;
}
#endif

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
    Dio_PortLevelType Value = STD_OFF;

    if( PortId < DioConfig.NumberOfPorts )
    {
        Value = Dio_Arch_ReadPort( PortId );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_READ_PORT, DIO_E_PARAM_INVALID_PORT_ID );
    }

    return Value;
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
    if( PortId < DioConfig.NumberOfPorts )
    {
        Dio_Arch_WritePort( PortId, Level );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_WRITE_PORT, DIO_E_PARAM_INVALID_PORT_ID );
    }
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

    if( ( ChannelGroupIdPtr != NULL_PTR ) || ( ChannelGroupIdPtr->port < DioConfig.NumberOfPorts ) )
    {
        GroupLevel = Dio_Arch_ReadChannelGroup( ChannelGroupIdPtr );
    }
    else
    {
        /* If development error detection is enabled, the functions Dio_ReadChannelGroup shall check
        the “ChannelGroupIdPtr” parameter to be valid within the current configuration.
        If the “ChannelGroupIdPtr” parameter is invalid, the functions shall report the error code
        DIO_E_PARAM_INVALID_GROUP to the DET*/
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_READ_CHANNEL_GRP, DIO_E_PARAM_INVALID_GROUP );
    }

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
    if( ( ChannelGroupIdPtr != NULL_PTR ) || ( ChannelGroupIdPtr->port < DioConfig.NumberOfPorts ) )
    {
        Dio_Arch_WriteChannelGroup( ChannelGroupIdPtr, Level );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_WRITE_CHANNEL_GRP, DIO_E_PARAM_INVALID_GROUP );
    }
}

/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if DIO_GET_VERSION_INFO_API == STD_ON
/**
 * @brief Get Version Info
 *
 * This function is used to define DIO driver version information.
 *
 * @param versioninfo Pointer to where to store the version information of this module.
 *
 * @retval Returns a variable for testing purposes .
 */
void Dio_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo != NULL_PTR )
    {
        versioninfo->vendorID         = 0;
        versioninfo->moduleID         = 0;
        versioninfo->sw_major_version = 0;
        versioninfo->sw_minor_version = 0;
        versioninfo->sw_patch_version = 0;
    }
    else
    {
        /* If DET is enabled for the DIO Driver module, the function Dio_GetVersionInfo shall raise
        DIO_E_PARAM_POINTER, if the argument is NULL pointer and return without any action */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_GET_VERSION_INFO, DIO_E_PARAM_POINTER );
    }
}
#endif

/* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if DIO_MASKED_WRITE_PORT_API == STD_ON
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
    if( PortId < DioConfig.NumberOfPorts )
    {
        Dio_Arch_MaskedWritePort( PortId, Level, Mask );
    }
    else
    {
        /* If development error detection is enabled, the services Dio_ReadChannel, shall check
        the “ChannelId” parameter to be valid within the current configuration. If the “ChannelId”
        parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID
        to the DET */
        Det_ReportError( DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_ID_MASKED_WRITE_PORT, DIO_E_PARAM_INVALID_PORT_ID );
    }
}
#endif

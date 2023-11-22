/**
 * @file    Dio_Arch.c
 * @brief   **Dio Specific Arquitecture Driver**
 * @author  Diego Perez
 *
 * Dio driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Dio driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Bfx.h"
#include "Dio_Arch.h"

#define GPIOx_BSRR_OFFSET 8u

/**
 * @brief  Pointer type variable to define the Ports.
 */
static Dio_RegisterType *DiosPeripherals[] = { DIOA, DIOB, DIOC, DIOD, DIOE, DIOF };

/**
 * @brief Read Channel
 *
 * The function will return the bit from register IDR speficied by paramter Pin. from the
 * port specified by the parameter Port.
 *
 * @param Port Port ID.
 * @param Pin Pin ID.
 *
 * @retval Returns the value of the specified DIO channel.
 * 
 * @reqs  SWS_Dio_00027, SWS_Dio_00074
 */
Dio_LevelType Dio_Arch_ReadChannel( Dio_PortType Port, uint8 Pin )
{
    return Bfx_GetBit_u32u8_u8( DiosPeripherals[ Port ]->IDR, Pin );
}

/**
 * @brief Write Channel
 *
 * This function will write the specified value to register ODR speficied by parameter Pin.
 * from the port specified by the parameter Port.
 *
 * @param Port Port ID.
 * @param Pin Pin ID.
 * @param Level Value to be written.
 * 
 * @reqs  SWS_Dio_00028, SWS_Dio_00029, SWS_Dio_00079
 */
void Dio_Arch_WriteChannel( Dio_PortType Port, uint8 Pin, Dio_LevelType Level )
{
    Bfx_PutBit_u32u8u8( (uint32 *)&DiosPeripherals[ Port ]->ODR, Pin, Level );
}

/**
 * @brief Flip Channel
 *
 * This function will flip the level of the specified channel writting the opposite value in
 * the register ODR speficied by parameter Pin. from the port specified by the parameter Port.
 * the fucntion will also return the level of the channel after flipping it reading the value
 * from the register IDR.
 *
 * @param Port Port ID.
 * @param Pin Pin ID.
 *
 * @retval Returns the level of a channel after flipping the level.
 * 
 * @reqs  SWS_Dio_00191, SWS_Dio_00192, SWS_Dio_00193
 */
Dio_LevelType Dio_Arch_FlipChannel( Dio_PortType Port, uint8 Pin )
{
    /*read the actual bit status*/
    uint8 Bit = Bfx_GetBit_u32u8_u8( DiosPeripherals[ Port ]->IDR, Pin );
    /*flip its value*/
    Bfx_SetBit_u32u8( (uint32 *)&DiosPeripherals[ Port ]->BSRR, ( Pin + ( GPIOx_BSRR_OFFSET * Bit ) ) );

    return Bit;
}

/**
 * @brief Read Port
 *
 * The function will return the level of all pins of the port specified by the parameter Port.
 * The function will read the value from the register IDR.
 *
 * @param Port ID of DIO Port.
 *
 * @retval Returns the level of all channels on that port.
 * 
 * @reqs  SWS_Dio_00031, SWS_Dio_00104, SWS_Dio_00075
 */
Dio_PortLevelType Dio_Arch_ReadPort( Dio_PortType Port )
{
    return DiosPeripherals[ Port ]->IDR;
}

/**
 * @brief Write Port
 *
 * This function is used to write a value to all channels of the specified port. The function
 * will write the value to the register ODR.
 *
 * @param Port ID of DIO Port.
 * @param Level Value to be written.
 * 
 * @reqs  SWS_Dio_00034, SWS_Dio_00035, SWS_Dio_00105, SWS_Dio_00108
 */
void Dio_Arch_WritePort( Dio_PortType Port, Dio_PortLevelType Level )
{
    DiosPeripherals[ Port ]->ODR = Level;
}

/**
 * @brief Read Channel Group
 *
 * This function will read a subset of the contiguous bits of register IDR of a port (channel
 * group). The function will not change the remaining channels of the port or the channels
 *
 * @param ChannelGroupIdPtr Pointer to ChannelGroup.
 *
 * @retval Returns the level of a subset of the adjacent bits of a port (channel group).
 * 
 * @reqs  SWS_Dio_00037, SWS_Dio_00092, SWS_Dio_00093, SWS_Dio_00114 
 */
Dio_PortLevelType Dio_Arch_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr )
{
    Dio_PortLevelType GroupLevel = DiosPeripherals[ ChannelGroupIdPtr->port ]->IDR;

    /*clear the values outside the mask*/
    Bfx_ClrBitMask_u32u32( (uint32 *)&GroupLevel, ~ChannelGroupIdPtr->mask );
    /*rotate offset to extract the actual value marked by the mask */
    Bfx_ShiftBitRt_u32u8( (uint32 *)&GroupLevel, ChannelGroupIdPtr->offset );

    return GroupLevel;
}

/**
 * @brief Write Channel Group
 *
 * This function will set a subset of the adjacent bits of a port (channel group) writting the
 * specified value to the register ODR. The function will not change the remaining channels of
 * the port or the channels
 *
 * @param ChannelGroupIdPtr Pointer to ChannelGroup.
 * @param Level Value to be written.
 * 
 * @reqs  SWS_Dio_00039, SWS_Dio_00040, SWS_Dio_00090, SWS_Dio_00091 
 */
void Dio_Arch_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level )
{
    Dio_RegisterType *Port = DiosPeripherals[ ChannelGroupIdPtr->port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&Port->ODR, ChannelGroupIdPtr->offset, ChannelGroupIdPtr->mask, Level );
}

/**
 * @brief Masked Write Port
 *
 * This function will set the specified value for the channels on the specified port if the
 * corresponding bit in Mask is '1'.
 *
 * @param Port ID of DIO Port.
 * @param Level Value to be written.
 * @param Mask Channels to be masked in the port.
 * 
 * @reqs  SWS_Dio_00202, SWS_Dio_00203, SWS_Dio_00204
 */
void Dio_Arch_MaskedWritePort( Dio_PortType Port, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
    Bfx_PutBitsMask_u32u32u32( (uint32 *)&DiosPeripherals[ Port ]->ODR, Mask, Level );
}

#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h"


typedef uint8 Dio_ChannelType;

typedef uint8 Dio_PortType;

typedef uint8 Dio_LevelType;

typedef uint8 Dio_PortLevelType;


typedef struct
{
    uint8 mask;
    uint8 offset;
    Dio_PortType port;
} Dio_ChannelGroupType;


#define VALUE_F       (Dio_LevelType)0xF

#define NULL          ( (void *)0 )

#define SIX           6u
#define FOUR          4u


#define DIO_PIN_PA_00 (Dio_ChannelType)0x00u
#define DIO_PIN_PA_01 (Dio_ChannelType)0x01u
#define DIO_PIN_PA_02 (Dio_ChannelType)0x02u
#define DIO_PIN_PA_03 (Dio_ChannelType)0x03u
#define DIO_PIN_PA_04 (Dio_ChannelType)0x04u
#define DIO_PIN_PA_05 (Dio_ChannelType)0x05u
#define DIO_PIN_PA_06 (Dio_ChannelType)0x06u
#define DIO_PIN_PA_07 (Dio_ChannelType)0x07u
#define DIO_PIN_PA_08 (Dio_ChannelType)0x08u
#define DIO_PIN_PA_09 (Dio_ChannelType)0x09u
#define DIO_PIN_PA_10 (Dio_ChannelType)0x0Au
#define DIO_PIN_PA_11 (Dio_ChannelType)0x0Bu
#define DIO_PIN_PA_12 (Dio_ChannelType)0x0Cu
#define DIO_PIN_PA_13 (Dio_ChannelType)0x0Du
#define DIO_PIN_PA_14 (Dio_ChannelType)0x0Eu
#define DIO_PIN_PA_15 (Dio_ChannelType)0x0Fu


#define DIO_PIN_PB_00 (Dio_ChannelType)0x10u
#define DIO_PIN_PB_01 (Dio_ChannelType)0x11u
#define DIO_PIN_PB_02 (Dio_ChannelType)0x12u
#define DIO_PIN_PB_03 (Dio_ChannelType)0x13u
#define DIO_PIN_PB_04 (Dio_ChannelType)0x14u
#define DIO_PIN_PB_05 (Dio_ChannelType)0x15u
#define DIO_PIN_PB_06 (Dio_ChannelType)0x16u
#define DIO_PIN_PB_07 (Dio_ChannelType)0x17u
#define DIO_PIN_PB_08 (Dio_ChannelType)0x18u
#define DIO_PIN_PB_09 (Dio_ChannelType)0x19u
#define DIO_PIN_PB_10 (Dio_ChannelType)0x1Au
#define DIO_PIN_PB_11 (Dio_ChannelType)0x1Bu
#define DIO_PIN_PB_12 (Dio_ChannelType)0x1Cu
#define DIO_PIN_PB_13 (Dio_ChannelType)0x1Du
#define DIO_PIN_PB_14 (Dio_ChannelType)0x1Eu
#define DIO_PIN_PB_15 (Dio_ChannelType)0x1Fu


#define DIO_PIN_PC_00 (Dio_ChannelType)0x20u
#define DIO_PIN_PC_01 (Dio_ChannelType)0x21u
#define DIO_PIN_PC_02 (Dio_ChannelType)0x22u
#define DIO_PIN_PC_03 (Dio_ChannelType)0x23u
#define DIO_PIN_PC_04 (Dio_ChannelType)0x24u
#define DIO_PIN_PC_05 (Dio_ChannelType)0x25u
#define DIO_PIN_PC_06 (Dio_ChannelType)0x26u
#define DIO_PIN_PC_07 (Dio_ChannelType)0x27u
#define DIO_PIN_PC_08 (Dio_ChannelType)0x28u
#define DIO_PIN_PC_09 (Dio_ChannelType)0x29u
#define DIO_PIN_PC_10 (Dio_ChannelType)0x2Au
#define DIO_PIN_PC_11 (Dio_ChannelType)0x2Bu
#define DIO_PIN_PC_12 (Dio_ChannelType)0x2Cu
#define DIO_PIN_PC_13 (Dio_ChannelType)0x2Du
#define DIO_PIN_PC_14 (Dio_ChannelType)0x2Eu
#define DIO_PIN_PC_15 (Dio_ChannelType)0x2Fu


#define DIO_PIN_PD_00 (Dio_ChannelType)0x30u
#define DIO_PIN_PD_01 (Dio_ChannelType)0x31u
#define DIO_PIN_PD_02 (Dio_ChannelType)0x32u
#define DIO_PIN_PD_03 (Dio_ChannelType)0x33u
#define DIO_PIN_PD_04 (Dio_ChannelType)0x34u
#define DIO_PIN_PD_05 (Dio_ChannelType)0x35u
#define DIO_PIN_PD_06 (Dio_ChannelType)0x36u
#define DIO_PIN_PD_08 (Dio_ChannelType)0x38u
#define DIO_PIN_PD_09 (Dio_ChannelType)0x39u


#define DIO_PIN_PF_00 (Dio_ChannelType)0x50u
#define DIO_PIN_PF_01 (Dio_ChannelType)0x51u
#define DIO_PIN_PF_02 (Dio_ChannelType)0x52u
#define DIO_PIN_PF_03 (Dio_ChannelType)0x53u
#define DIO_PIN_PF_04 (Dio_ChannelType)0x54u


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
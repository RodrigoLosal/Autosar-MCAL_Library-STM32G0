#ifndef DIO_H__
#define DIO_H__


typedef uint8 Dio_ChannelType;

typedef uint8 Dio_PortType;

typedef uint8 Dio_LevelType;

typedef uint32 Dio_PortLevelType;


typedef struct
{
    uint8 mask;
    uint8 offset;
    Dio_PortType port;
} Dio_ChannelGroupType;


#define DIO_PIN_PA_00 (Dio_ChannelType)0x00u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_01 (Dio_ChannelType)0x01u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_02 (Dio_ChannelType)0x02u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_03 (Dio_ChannelType)0x03u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_04 (Dio_ChannelType)0x04u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_05 (Dio_ChannelType)0x05u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_06 (Dio_ChannelType)0x06u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_07 (Dio_ChannelType)0x07u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_08 (Dio_ChannelType)0x08u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_09 (Dio_ChannelType)0x09u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_10 (Dio_ChannelType)0x0Au /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_11 (Dio_ChannelType)0x0Bu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_12 (Dio_ChannelType)0x0Cu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_13 (Dio_ChannelType)0x0Du /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_14 (Dio_ChannelType)0x0Eu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PA_15 (Dio_ChannelType)0x0Fu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */


#define DIO_PIN_PB_00 (Dio_ChannelType)0x10u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_01 (Dio_ChannelType)0x11u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_02 (Dio_ChannelType)0x12u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_03 (Dio_ChannelType)0x13u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_04 (Dio_ChannelType)0x14u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_05 (Dio_ChannelType)0x15u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_06 (Dio_ChannelType)0x16u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_07 (Dio_ChannelType)0x17u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_08 (Dio_ChannelType)0x18u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_09 (Dio_ChannelType)0x19u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_10 (Dio_ChannelType)0x1Au /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_11 (Dio_ChannelType)0x1Bu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_12 (Dio_ChannelType)0x1Cu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_13 (Dio_ChannelType)0x1Du /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_14 (Dio_ChannelType)0x1Eu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PB_15 (Dio_ChannelType)0x1Fu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */


#define DIO_PIN_PC_00 (Dio_ChannelType)0x20u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_01 (Dio_ChannelType)0x21u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_02 (Dio_ChannelType)0x22u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_03 (Dio_ChannelType)0x23u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_04 (Dio_ChannelType)0x24u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_05 (Dio_ChannelType)0x25u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_06 (Dio_ChannelType)0x26u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_07 (Dio_ChannelType)0x27u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_08 (Dio_ChannelType)0x28u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_09 (Dio_ChannelType)0x29u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_10 (Dio_ChannelType)0x2Au /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_11 (Dio_ChannelType)0x2Bu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_12 (Dio_ChannelType)0x2Cu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_13 (Dio_ChannelType)0x2Du /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_14 (Dio_ChannelType)0x2Eu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PC_15 (Dio_ChannelType)0x2Fu /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */


#define DIO_PIN_PD_00 (Dio_ChannelType)0x30u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_01 (Dio_ChannelType)0x31u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_02 (Dio_ChannelType)0x32u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_03 (Dio_ChannelType)0x33u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_04 (Dio_ChannelType)0x34u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_05 (Dio_ChannelType)0x35u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_06 (Dio_ChannelType)0x36u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_08 (Dio_ChannelType)0x38u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PD_09 (Dio_ChannelType)0x39u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */


#define DIO_PIN_PF_00 (Dio_ChannelType)0x50u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PF_01 (Dio_ChannelType)0x51u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PF_02 (Dio_ChannelType)0x52u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PF_03 (Dio_ChannelType)0x53u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */
#define DIO_PIN_PF_04 (Dio_ChannelType)0x54u /* cppcheck-suppress misra-c2012-2.5 ; This define is used to indicate the pin value */


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
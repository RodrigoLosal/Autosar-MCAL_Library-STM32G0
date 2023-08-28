#ifndef PORT_H__
#define PORT_H__

typedef struct _Port_ConfigType
{
    uint8 Port;          /*!<Port where the pin to config is grouped*/
    uint16 Pins;         /*!<Pins to configured*/
    uint8 Pull;          /*!<Pullup, pull down or no pull ressitor*/
    uint8 OutputDrive;   /*!<Pus-Pull or Open conlector*/
    uint8 Speed;         /*!<Speed of the pin*/
    uint8 Mode;          /*!<Input, Output, analog or altern mode*/
    uint8 Altern;        /*!<ther altern mode to config (pwm, spi, can, etc..)*/
    uint8 Pin_direction; /*!<pin direction changeable during runtime*/
} Port_ConfigType;

typedef uint32 Port_PinType; /*!< Data type for the symbolic name of a port pin.*/

typedef uint8 Port_PinDirectionType; /*!< Data type for the symbolic direction of a pin.*/

typedef uint8 Port_PinModeType; /*!< Data type for the symbolic mode of a pin.*/

#define PORTS_A               0u /*!< Port A value */
#define PORTS_B               1u /*!< Port B value */
#define PORTS_C               2u /*!< Port C value */
#define PORTS_D               3u /*!< Port D value */
#define PORTS_E               4u /*!< Port E value */
#define PORTS_F               5u /*!< Port F value */

#define PORTS_PIN_0           ( 1U )       /*!< Pin 0 value */
#define PORTS_PIN_1           ( 1 << 1U )  /*!< Pin 1 value */
#define PORTS_PIN_2           ( 1 << 2U )  /*!< Pin 2 value */
#define PORTS_PIN_3           ( 1 << 3U )  /*!< Pin 3 value */
#define PORTS_PIN_4           ( 1 << 4U )  /*!< Pin 4 value */
#define PORTS_PIN_5           ( 1 << 5U )  /*!< Pin 5 value */
#define PORTS_PIN_6           ( 1 << 6U )  /*!< Pin 6 value */
#define PORTS_PIN_7           ( 1 << 7U )  /*!< Pin 7 value */
#define PORTS_PIN_8           ( 1 << 8U )  /*!< Pin 8 value */
#define PORTS_PIN_9           ( 1 << 9U )  /*!< Pin 9 value */
#define PORTS_PIN_10          ( 1 << 10U ) /*!< Pin 10 value */
#define PORTS_PIN_11          ( 1 << 11U ) /*!< Pin 11 value */
#define PORTS_PIN_12          ( 1 << 12U ) /*!< Pin 12 value */
#define PORTS_PIN_13          ( 1 << 13U ) /*!< Pin 13 value */
#define PORTS_PIN_14          ( 1 << 14U ) /*!< Pin 14 value */
#define PORTS_PIN_15          ( 1 << 15U ) /*!< Pin 15 value */

#define PORTS_CHANGEABLE      0x00u /*!< Port can be changed during runtime */
#define PORTS_NON_CHANGEABLE  0x01u /*!< Port can not be changed during runtime */

#define PORTS_MODE_INPUT      0x00u /*!< Input mode value */
#define PORTS_MODE_OUTPUT     0x01u /*!< General purpose output mode value */
#define PORTS_MODE_ALT        0b10u /*!< Alternate function mode value */
#define PORTS_MODE_ANALOG     0b11u /*!< Analog mode (reset state) value */

#define PORTS_NOPULL          0x00u /*!< No pull-up, pull-down value */
#define PORTS_PULLUP          0x01u /*!< Pull-up */
#define PORTS_PULLDOWN        0b10u /*!< Pull-down */

#define PORTS_PUSH_PULL       0x00u /*!< Output push-pull (reset state) value */
#define PORTS_OPEN_COLECTOR   0x01u /*!< Output open-drain */

#define PORTS_VERY_LOW_SPEED  0x00u /*!< Very low speed value */
#define PORTS_LOW_SPEED       0x01u /*!< Low speed value */
#define PORTS_HIGH_SPEED      0b10u /*!< High speed value */
#define PORTS_VERY_HIGH_SPEED 0b11u /*!< Very high speed value */

#define PORT_PIN_MODE_AF0     (Port_PinModeType)0x00u /*!< Alternarive funcion 0 */
#define PORT_PIN_MODE_AF1     (Port_PinModeType)0x01u /*!< Alternarive funcion 1 */
#define PORT_PIN_MODE_AF2     (Port_PinModeType)0x02u /*!< Alternarive funcion 2 */
#define PORT_PIN_MODE_AF3     (Port_PinModeType)0x03u /*!< Alternarive funcion 3 */
#define PORT_PIN_MODE_AF4     (Port_PinModeType)0x04u /*!< Alternarive funcion 4 */
#define PORT_PIN_MODE_AF5     (Port_PinModeType)0x05u /*!< Alternarive funcion 5 */
#define PORT_PIN_MODE_AF6     (Port_PinModeType)0x06u /*!< Alternarive funcion 6 */
#define PORT_PIN_MODE_AF7     (Port_PinModeType)0x07u /*!< Alternarive funcion 7 */

#define PORT_PIN_PA_00        (Port_PinType)0x00u /*!< Port A pin 0 value */
#define PORT_PIN_PA_01        (Port_PinType)0x01u /*!< Port A pin 1 value */
#define PORT_PIN_PA_02        (Port_PinType)0x02u /*!< Port A pin 2 value */
#define PORT_PIN_PA_03        (Port_PinType)0x03u /*!< Port A pin 3 value */
#define PORT_PIN_PA_04        (Port_PinType)0x04u /*!< Port A pin 4 value */
#define PORT_PIN_PA_05        (Port_PinType)0x05u /*!< Port A pin 5 value */
#define PORT_PIN_PA_06        (Port_PinType)0x06u /*!< Port A pin 6 value */
#define PORT_PIN_PA_07        (Port_PinType)0x07u /*!< Port A pin 7 value */
#define PORT_PIN_PA_08        (Port_PinType)0x08u /*!< Port A pin 8 value */
#define PORT_PIN_PA_09        (Port_PinType)0x09u /*!< Port A pin 9 value */
#define PORT_PIN_PA_10        (Port_PinType)0x0Au /*!< Port A pin 10 value */
#define PORT_PIN_PA_11        (Port_PinType)0x0Bu /*!< Port A pin 11 value */
#define PORT_PIN_PA_12        (Port_PinType)0x0Cu /*!< Port A pin 12 value */
#define PORT_PIN_PA_13        (Port_PinType)0x0Du /*!< Port A pin 13 value */
#define PORT_PIN_PA_14        (Port_PinType)0x0Eu /*!< Port A pin 14 value */
#define PORT_PIN_PA_15        (Port_PinType)0x0Fu /*!< Port A pin 15 value */

#define PORT_PIN_PB_00        (Port_PinType)0x10u /*!< Port B pin 0 value */
#define PORT_PIN_PB_01        (Port_PinType)0x11u /*!< Port B pin 1 value */
#define PORT_PIN_PB_02        (Port_PinType)0x12u /*!< Port B pin 2 value */
#define PORT_PIN_PB_03        (Port_PinType)0x13u /*!< Port B pin 3 value */
#define PORT_PIN_PB_04        (Port_PinType)0x14u /*!< Port B pin 4 value */
#define PORT_PIN_PB_05        (Port_PinType)0x15u /*!< Port B pin 5 value */
#define PORT_PIN_PB_06        (Port_PinType)0x16u /*!< Port B pin 6 value */
#define PORT_PIN_PB_07        (Port_PinType)0x17u /*!< Port B pin 7 value */
#define PORT_PIN_PB_08        (Port_PinType)0x18u /*!< Port B pin 8 value */
#define PORT_PIN_PB_09        (Port_PinType)0x19u /*!< Port B pin 9 value */
#define PORT_PIN_PB_10        (Port_PinType)0x1Au /*!< Port B pin 10 value */
#define PORT_PIN_PB_11        (Port_PinType)0x1Bu /*!< Port B pin 11 value */
#define PORT_PIN_PB_12        (Port_PinType)0x1Cu /*!< Port B pin 12 value */
#define PORT_PIN_PB_13        (Port_PinType)0x1Du /*!< Port B pin 13 value */
#define PORT_PIN_PB_14        (Port_PinType)0x1Eu /*!< Port B pin 14 value */
#define PORT_PIN_PB_15        (Port_PinType)0x1Fu /*!< Port B pin 15 value */

#define PORT_PIN_PC_00        (Port_PinType)0x20u /*!< Port C pin 0 value */
#define PORT_PIN_PC_01        (Port_PinType)0x21u /*!< Port C pin 1 value */
#define PORT_PIN_PC_02        (Port_PinType)0x22u /*!< Port C pin 2 value */
#define PORT_PIN_PC_03        (Port_PinType)0x23u /*!< Port C pin 3 value */
#define PORT_PIN_PC_04        (Port_PinType)0x24u /*!< Port C pin 4 value */
#define PORT_PIN_PC_05        (Port_PinType)0x25u /*!< Port C pin 5 value */
#define PORT_PIN_PC_06        (Port_PinType)0x26u /*!< Port C pin 6 value */
#define PORT_PIN_PC_07        (Port_PinType)0x27u /*!< Port C pin 7 value */
#define PORT_PIN_PC_08        (Port_PinType)0x28u /*!< Port C pin 8 value */
#define PORT_PIN_PC_09        (Port_PinType)0x29u /*!< Port C pin 9 value */
#define PORT_PIN_PC_10        (Port_PinType)0x2Au /*!< Port C pin 10 value */
#define PORT_PIN_PC_11        (Port_PinType)0x2Bu /*!< Port C pin 11 value */
#define PORT_PIN_PC_12        (Port_PinType)0x2Cu /*!< Port C pin 12 value */
#define PORT_PIN_PC_13        (Port_PinType)0x2Du /*!< Port C pin 13 value */
#define PORT_PIN_PC_14        (Port_PinType)0x2Eu /*!< Port C pin 14 value */
#define PORT_PIN_PC_15        (Port_PinType)0x2Fu /*!< Port C pin 15 value */

#define PORT_PIN_PD_00        (Port_PinType)0x30u /*!< Port D pin 0 value */
#define PORT_PIN_PD_01        (Port_PinType)0x31u /*!< Port D pin 1 value */
#define PORT_PIN_PD_02        (Port_PinType)0x32u /*!< Port D pin 2 value */
#define PORT_PIN_PD_03        (Port_PinType)0x33u /*!< Port D pin 3 value */
#define PORT_PIN_PD_04        (Port_PinType)0x34u /*!< Port D pin 4 value */
#define PORT_PIN_PD_05        (Port_PinType)0x35u /*!< Port D pin 5 value */
#define PORT_PIN_PD_06        (Port_PinType)0x36u /*!< Port D pin 6 value */
#define PORT_PIN_PD_07        (Port_PinType)0x37u /*!< Port D pin 7 value */
#define PORT_PIN_PD_08        (Port_PinType)0x38u /*!< Port D pin 8 value */
#define PORT_PIN_PD_09        (Port_PinType)0x39u /*!< Port D pin 9 value */
#define PORT_PIN_PD_10        (Port_PinType)0x3Au /*!< Port D pin 10 value */
#define PORT_PIN_PD_11        (Port_PinType)0x3Bu /*!< Port D pin 11 value */
#define PORT_PIN_PD_12        (Port_PinType)0x3Cu /*!< Port D pin 12 value */
#define PORT_PIN_PD_13        (Port_PinType)0x3Du /*!< Port D pin 13 value */
#define PORT_PIN_PD_14        (Port_PinType)0x3Eu /*!< Port D pin 14 value */
#define PORT_PIN_PD_15        (Port_PinType)0x3Fu /*!< Port D pin 15 value */

#define PORT_PIN_PE_00        (Port_PinType)0x40u /*!< Port E pin 0 value */
#define PORT_PIN_PE_01        (Port_PinType)0x41u /*!< Port E pin 1 value */
#define PORT_PIN_PE_02        (Port_PinType)0x42u /*!< Port E pin 2 value */
#define PORT_PIN_PE_03        (Port_PinType)0x43u /*!< Port E pin 3 value */
#define PORT_PIN_PE_04        (Port_PinType)0x44u /*!< Port E pin 4 value */
#define PORT_PIN_PE_05        (Port_PinType)0x45u /*!< Port E pin 5 value */
#define PORT_PIN_PE_06        (Port_PinType)0x46u /*!< Port E pin 6 value */
#define PORT_PIN_PE_07        (Port_PinType)0x47u /*!< Port E pin 7 value */
#define PORT_PIN_PE_08        (Port_PinType)0x48u /*!< Port E pin 8 value */
#define PORT_PIN_PE_09        (Port_PinType)0x49u /*!< Port E pin 9 value */
#define PORT_PIN_PE_10        (Port_PinType)0x4Au /*!< Port E pin 10 value */
#define PORT_PIN_PE_11        (Port_PinType)0x4Bu /*!< Port E pin 11 value */
#define PORT_PIN_PE_12        (Port_PinType)0x4Cu /*!< Port E pin 12 value */
#define PORT_PIN_PE_13        (Port_PinType)0x4Du /*!< Port E pin 13 value */
#define PORT_PIN_PE_14        (Port_PinType)0x4Eu /*!< Port E pin 14 value */
#define PORT_PIN_PE_15        (Port_PinType)0x4Fu /*!< Port E pin 15 value */

#define PORT_PIN_PF_00        (Port_PinType)0x50u /*!< Port F pin 0 value */
#define PORT_PIN_PF_01        (Port_PinType)0x51u /*!< Port F pin 1 value */
#define PORT_PIN_PF_02        (Port_PinType)0x52u /*!< Port F pin 2 value */
#define PORT_PIN_PF_03        (Port_PinType)0x53u /*!< Port F pin 3 value */
#define PORT_PIN_PF_04        (Port_PinType)0x54u /*!< Port F pin 4 value */
#define PORT_PIN_PF_05        (Port_PinType)0x55u /*!< Port F pin 5 value */
#define PORT_PIN_PF_06        (Port_PinType)0x56u /*!< Port F pin 6 value */
#define PORT_PIN_PF_07        (Port_PinType)0x57u /*!< Port F pin 7 value */
#define PORT_PIN_PF_08        (Port_PinType)0x58u /*!< Port F pin 8 value */
#define PORT_PIN_PF_09        (Port_PinType)0x59u /*!< Port F pin 9 value */
#define PORT_PIN_PF_10        (Port_PinType)0x5Au /*!< Port F pin 10 value */
#define PORT_PIN_PF_11        (Port_PinType)0x5Bu /*!< Port F pin 11 value */
#define PORT_PIN_PF_12        (Port_PinType)0x5Cu /*!< Port F pin 12 value */
#define PORT_PIN_PF_13        (Port_PinType)0x5Du /*!< Port F pin 13 value */
#define PORT_PIN_PF_14        (Port_PinType)0x5Eu /*!< Port F pin 14 value */
#define PORT_PIN_PF_15        (Port_PinType)0x5Fu /*!< Port F pin 15 value */

#define PORT_PIN_IN           (Port_PinDirectionType)0x00u /*!< Input mode value */
#define PORT_PIN_OUT          (Port_PinDirectionType)0x01u /*!< General purpose output mode value */

void Port_Init( const Port_ConfigType *ConfigPtr );
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo );
void Port_RefreshPortDirection (void);

#endif
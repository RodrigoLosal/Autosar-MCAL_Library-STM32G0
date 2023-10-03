#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#define PORT_PIN_NUMBER_OF_PORTS   4

#define PORT_TEST_ON_PORT_C_PIN_0  ( Port_PinType )( 0x0000 | PORTS_PIN_00_VAL )
#define PORT_TEST_ON_PORT_C_PIN_1  ( Port_PinType )( 0x0000 | PORTS_PIN_01_VAL )

#define PORT_TEST_ON_PORT_A_PIN_4  ( Port_PinType )( 0x0100 | PORTS_PIN_04_VAL )
#define PORT_TEST_ON_PORT_A_PIN_5  ( Port_PinType )( 0x0100 | PORTS_PIN_05_VAL )

#define PORT_TEST_ON_PORT_B_PIN_13 ( Port_PinType )( 0x0200 | PORTS_PIN_13_VAL )
#define PORT_TEST_ON_PORT_B_PIN_10 ( Port_PinType )( 0x0200 | PORTS_PIN_10_VAL )
#define PORT_TEST_ON_PORT_B_PIN_5  ( Port_PinType )( 0x0200 | PORTS_PIN_05_VAL )

#define PORT_TEST_ON_PORT_D_PIN_1  ( Port_PinType )( 0x0300 | PORTS_PIN_01_VAL )

/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/

#define PORT_SET_PIN_DIRECTION_API STD_ON
#define PORT_SET_PIN_MODE_API      STD_ON
#define PORT_VERSION_INFO_API      STD_ON

extern const Port_ConfigType PortsConfig[ PORT_PIN_NUMBER_OF_PORTS ];

#endif /* PORT_CFG_H_ */

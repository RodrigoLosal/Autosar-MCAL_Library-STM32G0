#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#define PORT_PIN_NUMBER_OF_PORTS   1

#define PORT_TEST_ON_PORT_C_PIN_0  ( Port_PinType )( 0x0000 | PORTS_PIN_00_VAL )
#define PORT_TEST_ON_PORT_C_PIN_1  ( Port_PinType )( 0x0000 | PORTS_PIN_01_VAL )
#define PORT_TEST_ON_PORT_C_PIN_2  ( Port_PinType )( 0x0000 | PORTS_PIN_02_VAL )
#define PORT_TEST_ON_PORT_C_PIN_3  ( Port_PinType )( 0x0000 | PORTS_PIN_03_VAL )
#define PORT_TEST_ON_PORT_C_PIN_4  ( Port_PinType )( 0x0000 | PORTS_PIN_04_VAL )
#define PORT_TEST_ON_PORT_C_PIN_5  ( Port_PinType )( 0x0000 | PORTS_PIN_05_VAL )
#define PORT_TEST_ON_PORT_C_PIN_6  ( Port_PinType )( 0x0000 | PORTS_PIN_06_VAL )
#define PORT_TEST_ON_PORT_C_PIN_7  ( Port_PinType )( 0x0000 | PORTS_PIN_07_VAL )


/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/

#define PORT_SET_PIN_DIRECTION_API STD_ON
#define PORT_SET_PIN_MODE_API      STD_ON
#define PORT_VERSION_INFO_API      STD_ON

/*external reference to Port_Config array*/
extern const Port_ConfigType PortConfig[ PORT_PIN_NUMBER_OF_PORTS ];

#endif /* PORT_CFG_H_ */
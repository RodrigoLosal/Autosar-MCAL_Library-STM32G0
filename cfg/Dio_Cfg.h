#ifndef DIO_CFG_H_
#define DIO_CFG_H_


/*ports in use by the driver, in this case is port C
identified with a constant value of 2*/
#define DIO_PORT_LEDS               ( Dio_PortType ) 2


/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/
#define DIO_LED_RED                 ( Dio_ChannelType ) 00
#define DIO_LED_BLUE                ( Dio_ChannelType ) 01
#define DIO_LED_GREEN               ( Dio_ChannelType ) 02
#define DIO_BTN_0                   ( Dio_ChannelType ) 03
#define DIO_BOARD_LED               ( Dio_ChannelType ) 05


#endif /* DIO_CFG_H_ */
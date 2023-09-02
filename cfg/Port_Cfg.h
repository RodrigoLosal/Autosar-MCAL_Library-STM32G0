#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#define PORT_PIN_NUMBER_OF_PORTS        1

/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/

#define PORT_SET_PIN_DIRECTION_API      STD_ON
#define PORT_SET_PIN_MODE_API           STD_ON
#define PORT_VERSION_INFO_API           STD_ON

/*external reference to Port_Config array*/
extern const Port_ConfigType PortConfig[ PORT_PIN_NUMBER_OF_PORTS ];

#endif /* PORT_CFG_H_ */
#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#define PORT_PIN_NUMBER_OF_PORTS   4

/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/

#define PORT_SET_PIN_DIRECTION_API STD_ON
#define PORT_SET_PIN_MODE_API      STD_ON
#define PORT_VERSION_INFO_API      STD_ON

extern const Port_ConfigType PortsConfig[ PORT_PIN_NUMBER_OF_PORTS ];

#endif /* PORT_CFG_H_ */
/**
 * @file    Dio_Arch.h
 * @brief   **Dio Specific Arquitecture Driver**
 * @author  Diego Perez
 *
 * Dio driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Dio driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef DIO_ARCH_H__
#define DIO_ARCH_H__

#include "Dio_Types.h"

/**
 * @defgroup    PORTS values.
 *
 * Symbols to specify ports values.
 *
 * @{ */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_A 0u /*!< Port A value */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_B 1u /*!< Port B value */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_C 2u /*!< Port C value */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_D 3u /*!< Port D value */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_E 4u /*!< Port E value */
/* cppcheck-suppress misra-c2012-2.5 ; these defines have been use in Dio_Lcfg.c */
#define DIO_PORT_F 5u /*!< Port F value */
/**
 * @}*/


Dio_LevelType Dio_Arch_ReadChannel( Dio_PortType Port, uint8 Pin );
void Dio_Arch_WriteChannel( Dio_PortType Port, uint8 Pin, Dio_LevelType Level );
Dio_LevelType Dio_Arch_FlipChannel( Dio_PortType Port, uint8 Pin );
Dio_PortLevelType Dio_Arch_ReadPort( Dio_PortType Port );
void Dio_Arch_WritePort( Dio_PortType Port, Dio_PortLevelType Level );
Dio_PortLevelType Dio_Arch_ReadChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr );
void Dio_Arch_WriteChannelGroup( const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level );
void Dio_Arch_MaskedWritePort( Dio_PortType Port, Dio_PortLevelType Level, Dio_PortLevelType Mask );

#endif /* DIO_ARCH_H__ */

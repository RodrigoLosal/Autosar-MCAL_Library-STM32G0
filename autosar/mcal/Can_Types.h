/**
 * @file    Can_Types.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The header contains the type definitions that are used by the Can module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef CAN_TYPES_H__
#define CAN_TYPES_H__

#include "Registers.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/**
 * @brief **CAN Controller Tiemstamp**
 *
 * Variables of this type are used to express time stamps based on relative time.
 * Value range: * Seconds: 0 .. 4.294.967.295 s (circa 136 years) * Nanoseconds: 0 ..
 * 999.999.999 ns
 */
typedef struct _Can_TimeStampType
{
    uint32 nanoseconds; /*!< nanoseconds part of the timestamp */
    uint32 seconds;     /*!< seconds part of the timestamp */
} Can_TimeStampType;


/**
 * @brief **Hardware unit configuration structure**
 *
 * This structure contains the paramters to configure the hardware unit incuding the controllers and the
 * hardware objects
 */
typedef struct _Can_ConfigType
{
    uint32 dummy; /*!< dummy element */
} Can_ConfigType;


#endif /* CAN_TYPES_H__ */

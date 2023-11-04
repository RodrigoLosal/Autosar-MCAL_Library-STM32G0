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
 * @brief **Hardware unit configuration structure**
 *
 * This structure contains the paramters to configure the hardware unit incuding the controllers and the
 * hardware objects
 *
 * @reqs    SWS_Can_00413
 */
typedef struct _Can_ConfigType
{
    uint32 dummy; /*!< dummy element */
} Can_ConfigType;


#endif /* CAN_TYPES_H__ */

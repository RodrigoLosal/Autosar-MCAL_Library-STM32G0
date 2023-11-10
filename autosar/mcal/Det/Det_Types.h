/**
 * @file    Det.h
 * @brief   **DET driver configuration**
 * @author  Oscar Gonzalez
 *
 * The header contains the type definitions that are used by the Det module. The file is implemented
 * as a means of abstraction from the hardware, making the low level interfaces available for upper layers.
 *
 */

#ifndef DET_TYPES_H__
#define DET_TYPES_H__

#include "Registers.h"

/**
 * @brief **Det Config type**
 *
 * 	Configuration data structure of the Det module
 *
 * @reqs SWS_Pwm_00111
 */
typedef struct _Det_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Det_ConfigType;


#endif
/**
 * @file    Pwm_Types.h
 * @brief   **Pwm Driver Types**
 * @author  Jazmin Melendrez
 *
 * The header contains the type definitions that are used by the Pwm module. The file is implemented
 * as a means of abstraction from the hardware, making the low level interfaces available for upper layers.
 */
#ifndef PWM_TYPES_H__
#define PWM_TYPES_H__

#include "Registers.h"
#include "Pwm_GeneralTypes.h"

/**
 * @brief **Hardware unit configuration structure**
 *
 * This is the type of data structure containing the initialization data for the PWM driver. The
 * contents of the initialization data structure are hardware specific.
 *
 * @reqs SWS_Pwm_00111
 */
typedef struct _Pwm_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Pwm_ConfigType;

#endif /* PWM_TYPES_H__ */
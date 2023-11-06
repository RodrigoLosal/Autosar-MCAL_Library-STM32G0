#ifndef Pwm_TYPES_H__
#define Pwm_TYPES_H__

#include "Registers.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/**
 * @brief **Hardware unit configuration structure**
 *
 * This structure contains the paramters to configure the hardware unit incuding the controllers and the
 * hardware objects
 *
 * @reqs SWS_Pwm_00111
 */
typedef struct _Pwm_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Pwm_ConfigType;

#endif /* PWM_TYPES_H__ */
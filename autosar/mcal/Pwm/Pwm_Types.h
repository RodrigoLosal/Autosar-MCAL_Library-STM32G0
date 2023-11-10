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

/**
 * @brief   Numeric identifier of a PWM channel.
 *
 * @reqs    SWS_Pwm_00106
 */
typedef uint32 Pwm_ChannelType;

/**
 * @brief   Definition of the period of a PWM channel.
 *
 * @reqs    SWS_Pwm_00107
 */
typedef uint32 Pwm_PeriodType;

/**
 * @brief   Output state of a PWM channel
 *
 * @reqs    SWS_Pwm_00108
 */
typedef enum _Pwm_OutputStateType
{
    PWM_HIGH = 0x00, /*!< The PWM channel is in high state */
    PWM_LOW          /*!< The PWM channel is in low state */
} Pwm_OutputStateType;

/**
 * @brief   Definition of the type of edge notification of a PWM channel.
 *
 * @reqs    SWS_Pwm_00109
 */
typedef enum _Pwm_EdgeNotificationType
{
    PWM_RISING_EDGE = 0x00, /*!< Notification will be called when a rising edge occurs on the PWM output signal. */
    PWM_FALLING_EDGE,       /*!< Notification will be called when a falling edge occurs on the PWM output signal. */
    PWM_BOTH_EDGES          /*!<Notification will be called when either a rising edge or falling edge occur on the PWM output signal.*/
} Pwm_EdgeNotificationType;

/**
 * @brief   Defines the class of a PWM channel.
 *
 * @reqs    SWS_Pwm_00110
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef enum _Pwm_ChannelClassType
{                               /* cppcheck-suppress misra-c2012-2.4 ; this macro is neccesary */
    PWM_VARIABLE_PERIOD = 0x00, /*!< Variable Period. The duty cycle and the period can be changed.*/
    PWM_FIXED_PERIOD,           /*!< Fixed Period. Only the duty cycle can be changed. */
    PWM_FIXED_PERIOD_SHIFTED    /*!<TFixed Shifted Period. Impossible to change it*/
} Pwm_ChannelClassType;

/**
 * @brief   Result of the requests related to power state transitions.
 *
 * @reqs    SWS_Pwm_00165
 */
typedef enum _Pwm_PowerStateRequestResultType
{
    PWM_SERVICE_ACCEPTED = 0x00, /*!< Power state change executed. */
    PWM_NOT_INIT,                /*!< PWM Module not initialized. */
    PWM_SEQUENCE_ERROR,          /*!<Wrong API call sequence.*/
    PWM_HW_FAILURE,              /*!< Hardware failure prevents state change.*/
    PWM_POWER_STATE_NOT_SUPP,    /*!< Power State not supported.  */
    PWM_TRANS_NOT_POSSIBLE       /*!< Transition not possible or HW busy.*/
} Pwm_PowerStateRequestResultType;

/**
 * @brief   Power state currently active or set as target power state.
 *
 * @reqs    SWS_Pwm_00197
 */
typedef enum _Pwm_PowerStateType
{
    PWM_FULL_POWER = 0x00 /*!< Full Power */
} Pwm_PowerStateType;

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

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Pwm_HwUnit
{
    const Pwm_ConfigType *Config; /*!< Pointer to the configuration structure */
} Pwm_HwUnit;

#endif /* PWM_TYPES_H__ */
/**
 * @file    Pwm_GeneralTypes.h
 * @brief   **Pwm Stack Types**
 * @author  Jazmin Melendrez
 *
 * This is the implementation of the Pwm Stack types
 */
#ifndef PWM_GENERAL_TYPES_H__
#define PWM_GENERAL_TYPES_H__

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
typedef enum _Pwm_ChannelClassType
{
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

#endif
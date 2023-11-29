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
 * @defgroup PWM_Ids Pwm Id number for module and each API
 *
 * @{ */
#define PWM_ID_INIT                     0x00u /*!< Pwm_Init() api service id */
#define PWM_ID_DE_INIT                  0x01u /*!< Pwm_DeInit() api service id */
#define PWM_ID_SET_DUTY_CYCLE           0x02u /*!< Pwm_SetDutyCycle() api service id */
#define PWM_ID_SET_PERIOD_AND_DUTY      0x03u /*!< Pwm_SetPeridoAndDuty() api service id */
#define PWM_ID_SET_OUTPUT_TO_IDLE       0x04u /*!< Pwm_SetOutputToIdle() api service id */
#define PWM_ID_GET_OUTPUT_STATE         0x05u /*!< Pwm_GetOutputState() api service id */
#define PWM_ID_DISABLE_NOTIFICATION     0x06u /*!< Pwm_DisableNotification() api service id */
#define PWM_ID_ENABLE_NOTIFICATION      0x07u /*!< Pwm_EnableNotification() api service id */
#define PWM_ID_SET_POWER_STATE          0x09u /*!< Pwm_SetPowerState() api service id */
#define PWM_ID_GET_CURRENT_POWER_STATE  0x0Au /*!< Pwm_GetCurrentPowerState() api service id */
#define PWM_ID_GET_TARGET_POWER_STATE   0x0Bu /*!< Pwm_GetTargetPowerState() api service id */
#define PWM_ID_PREPARE_POWER_STATE      0x0Cu /*!< Pwm_PreparePowerState() api service id */
#define PWM_ID_GET_VERSION_INFO         0x0Du /*!< Pwm_GetVersionInfo() api service id */
/**
 * @} */

/**
 * @defgroup PWM_Error_Type Pwm Developtment Error Types
 *
 * @{ */
#define PWM_E_INIT_FAILED               0x00u /*!< API Pwm_Init service called with wrong parameter */
#define PWM_E_UNINIT                    0x01u /*!< API service used without module initialization */
#define PWM_E_PARAM_CHANNEL             0x02u /*!< API service used with an invalid channel Identifier */
#define PWM_E_PERIOD_UNCHANGEABLE       0x03u /*!< Usage of unauthorized PWM service on PWM channel configured a fixed period */
#define PWM_E_ALREADY_INITIALIZED       0x04u /*!< API Pwm_Init service called while the PWM driver has already been initialised */
#define PWM_E_PARAM_POINTER             0x05u /*!< API Pwm_GetVersionInfo is called with a NULL parameter. */
#define PWM_E_POWER_STATE_NOT_SUPPORTED 0x06u /*!< The requested power state is not supported by the PWM module. */
#define PWM_E_TRANSITION_NOT_POSSIBLE   0x07u /*!< The requested power state is not reachable from the current one. */
#define PWM_E_PERIPHERAL_NOT_PREPARED   0x08u /*!< PWM_E_PERIPHERAL_NOT_PREPARED. */
#define PWM_E_NOT_DISENGAGED            0x09u /*!< API Pwm_SetPowerState is called while the PWM module is still in use.*/
/**
 * @} */

/**
 * @defgroup PWM_STATIC PWM static define for testing purposes
 *
 * @{ */
#ifndef UTEST
#define PWM_STATIC static /*!< Add static when no testing */
#else
#define PWM_STATIC /*!< remove static for testing purposes */
#endif
/**
 * @} */

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
    PWM_SEQUENCE_ERROR,          /*!< Wrong API call sequence.*/
    PWM_HW_FAILURE,              /*!< Hardware failure prevents state change.*/
    PWM_POWER_STATE_NOT_SUPP,    /*!< Power State not supported.  */
    PWM_TRANS_NOT_POSSIBLE,      /*!< Transition not possible or HW busy.*/
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
 * @brief **PWM driver Status**
 *
 * This is the type of data structure containing the module state for the PWM driver.
 *
 */
typedef enum
{
    PWM_STATE_UNINIT, /*!< Pwm State Uninitialized */
    PWM_STATE_INIT    /*!< Pwm State Initialized */
} Pwm_StatusType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Pwm_HwUnit
{
    const Pwm_ConfigType *Config;          /*!< Pointer to the configuration structure */
    Pwm_StatusType HwUnitState;            /*!< Pwm hardware unit state */
    Pwm_ChannelClassType Pwm_ChannelClass; /*!< Pwm channel class*/
    uint8 Pwm_channelNumber;               /*!< Pwm channel number */
    uint16 Duty_Cycle;                     /*!< Pwm Duty Cycle */
    Pwm_PeriodType Period;                 /*!< Pwm Period */
} Pwm_HwUnit;

#endif /* PWM_TYPES_H__ */
/**
 * @file    Adc_Types.h
 * @brief   **Adc Driver**
 * @author  Naim Leon
 *
 * The header contains the type definitions for the Adc module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef ADC_TYPES_H__
#define ADC_TYPES_H__

#include "Registers.h"
#include "Std_Types.h"

/**
 * @defgroup Adc_Ids Adc Id number for module and each API
 *
 * @{ */
#define ADC_ID_INIT                       0x00u /*!< ADC_Init() api service id */
#define ADC_RESULT_BUFFER                 0x0Cu /*!< Adc_SetupResultBuffer() api service id */
#define ADC_ID_DE_INIT                    0x01u /*!< Adc_DeInit() api service id */
#define ADC_START_GROUP_CONVERSION        0x02u /*!< Adc_StartGroupConversion() api service id */
#define ADC_STOP_GROUP_CONVERSION         0x03u /*!< Adc_StopGroupConversion() api service id */
#define ADC_READ_GROUP                    0x04u /*!< Adc_ReadGroup() api service id */
#define ADC_ENABLE_HARDWARE_TRIGGER       0x05u /*!< Adc_EnableHardwareTrigger() api service id */
#define ADC_DISABLE_HARDWARE_TRIGGER      0x06u /*!< Adc_DisableHardwareTrigger() api service id */
#define ADC_ENABLE_GROUP_NOTIFICATION     0x07u /*!< Adc_EnableGroupNotification() api service id */
#define ADC_DISABLE_GROUP_NOTIFICATION    0x08u /*!< Adc_DisableGroupNotification() api service id*/
#define ADC_GET_GROUP_STATUS              0x09u /*!< Adc_GetGroupStatus() api service id */
#define ADC_GET_STREAM_LAST_POINTER       0x0Bu /*!< Adc_GetStreamLastPointer() api service id */
#define ADC_GET_VERSION_INFO              0x0Au /*!< Adc_GetVersionInfo() api service id */
#define ADC_SET_POWER_STATE               0x10u /*!< Adc_SetPowerState() api service id */
#define ADC_GET_CURRENT_POWER_STATE       0x11u /*!< Adc_GetCurrentPowerState() api service id */
#define ADC_GET_TARGET_POWER_STATE        0x12u /*!< Adc_GetTargetPowerState() api service id */
#define ADC_PREPARE_POWER_STATE           0x13u /*!< Adc_PreparePowerState() api service id */
#define ADC_MAIN_POWER_TRANSITION_MANAGER 0x14u /*!< Adc_Main_PowerTransitionManager api service id */
/**
 * @} */

/**
 * @defgroup Adc_Error_Types Adc Development and Runtime Error Types
 *
 * @{ */
#define ADC_E_UNINIT                      0x0Au /*!< API is called prior to initialization. */
#define ADC_E_ALREADY_INITIALIZED         0x0Du /*!< API called while ADC is already initialized.*/
#define ADC_E_PARAM_POINTER               0x14u /*!< API called with incorrect buffer pointer.*/
#define ADC_E_PARAM_GROUP                 0x15u /*!< API called with non existing group.*/
#define ADC_E_WRONG_CONV_MODE             0x16u /*!< API called for a group configured for \
                                                continuous conversion mode. */
#define ADC_E_WRONG_TRIGG_SRC             0x17u /*!< API call not allowed according group \
                                                configuration. */
#define ADC_E_NOTIF_CAPABILITY            0x18u /*!< API called and notification function pointer \
                                                is NULL. */
#define ADC_E_BUFFER_UNINIT               0x19u /*!< API called while result buffer pointer is not \
                                                initialized. */
#define ADC_E_POWER_STATE_NOT_SUPPORTED   0x1Bu /*!< API call with unsupported power state request.*/
#define ADC_E_PERIPHERAL_NOT_PREPARED     0x1Du /*!< ADC not prepared for requested target power \
                                                state. */
#define ADC_E_BUSY                        0x0Bu /*!< API is called while another conversion is      \
                                                already running, a HW trigger is already enabled, a \
                                                request is already stored in the queue. */
#define ADC_E_IDLE                        0x0Cu /*!< API is called while group is in state ADC_IDLE \
                                                or non enabled group. */
#define ADC_E_NOT_DISENGAGED              0x1Au /*!< API called while one or more ADC groups are \
                                                not in IDLE state. */
#define ADC_E_TRANSITION_NOT_POSSIBLE     0x1Cu /*!< Requested power state can not be reached.  */
/**
 * @} */

/**
 * @brief **Adc configuration structure**
 *
 * Data structure containing the set of configuration parameters required for initializing the ADC
 * Driver and ADC HW Unit(s). (Elements tbd)
 *
 * @reqs    SWS_Adc_00505
 */
typedef struct
{
    Adc_TriggerSourceType Adc_TriggerSource; /*Type for configuring the trigger source for an ADC
                                               Channel group*/
    Adc_GroupConvModeType Adc_GroupConvMode; /*Type for configuring the conversion mode of an ADC
                                               Channel group*/
} Adc_ConfigType;

/**
 * @brief   Numeric ID of an ADC channel. (Size tbd)
 *
 * @reqs    SWS_Adc_00506
 */
typedef uint8 Adc_ChannelType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Numeric ID of an ADC channel group. (Size tbd)
 *
 * @reqs    SWS_Adc_00507
 */
typedef uint8 Adc_GroupType;

/**
 * @brief   Type for reading the converted values of a channel group (raw, without further scaling,
 *          alignment according precompile switch ADC_RESULT_ALIGNMENT). (Size tbd)
 *
 * @reqs    SWS_Adc_00508
 */
typedef uint8 Adc_ValueGroupType;

/**
 * @brief   Type of clock prescaler factor. (Size tbd)
 *
 * @reqs    SWS_Adc_00509
 */
typedef uint8 Adc_PrescaleType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Type of conversion time, i.e. the time during which the sampled analogue value is
 *          converted into digital representation. (Size tbd)
 *
 * @reqs    SWS_Adc_00510
 */
typedef uint8 Adc_ConversionTimeType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Type of sampling time, i.e. the time during which the value is sampled, (in
 *          clock-cycles). (Size tbd)
 *
 * @reqs    SWS_Adc_00511
 */
typedef uint8 Adc_SamplingTimeType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Type of channel resolution in number of bits.
 *
 * @reqs    SWS_Adc_00512
 */
typedef uint8 Adc_ResolutionType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief Current status of the conversion of the requested ADC Channel group.
 *
 * @reqs  SWS_Adc_00513
 */
typedef enum
{
    ADC_IDLE = 0,        /*!< The conversion of the specified group has not been started. No result
                            is available.*/
    ADC_BUSY,            /*!< The conversion of the specified group has been started and is still
                            going on. So far no result is available.*/
    ADC_COMPLETED,       /*!< A conversion round (which is not the final one) of the specified
                            group has been finished. A result is available for all channels of the group.*/
    ADC_STREAM_COMPLETED /*!< The result buffer is completely filled. For each channel of the
                            selected group the number of samples to be acquired is available*/
} Adc_StatusType;

/**
 * @brief Type for configuring the trigger source for an ADC Channel group.
 *
 * @reqs  SWS_Adc_00514
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_TRIGG_SRC_SW = 0, /*!< Group is triggered by a software API call.*/
    ADC_TRIGG_SRC_HW      /*!< Group is triggered by a hardware event.*/
} Adc_TriggerSourceType;

/**
 * @brief Type for configuring the conversion mode of an ADC Channel group.
 *
 * @reqs  SWS_Adc_00515
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_CONV_MODE_ONESHOT = 0, /*!< Exactly one conversion of each channel in an ADC channel group
                                    is performed after the configured trigger event. In case of
                                    ’group trigger source software’, a started One-Shot conversion
                                    can be stopped by a software API call. In case of ’group
                                    trigger source hardware’, a started One-Shot conversion can be
                                    stopped by disabling the trigger event (if supported by
                                    hardware).*/
    ADC_CONV_MODE_CONTINUOUS   /*!< Repeated conversions of each ADC channel in an ADC channel
                                    group are performed. ’Continuous conversion mode’ is only
                                    available for ’group trigger source software’. A started
                                    ’Continuous conversion’ can be stopped by a software API call.*/
} Adc_GroupConvModeType;

/**
 * @brief   Priority level of the channel. Lowest priority is 0.
 *
 * @reqs    SWS_Adc_00516
 */
typedef uint8 Adc_GroupPriorityType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Type for assignment of channels to a channel group. (size tbd)
 *
 * @reqs    SWS_Adc_00517
 */
typedef uint8 Adc_GroupDefType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief   Type for configuring the number of group conversions in streaming access mode (in
 *          single access mode, parameter is 1).
 *
 * @reqs    SWS_Adc_00518
 */
typedef uint8 Adc_StreamNumSampleType;

/**
 * @brief Type for configuring the streaming access mode buffer type.
 *
 * @reqs  SWS_Adc_00519
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_STREAM_BUFFER_LINEAR = 0, /*!< The ADC Driver stops the conversion as soon as the stream
                                    buffer is full (number of samples reached).*/
    ADC_STREAM_BUFFER_CIRCULAR    /*!< The ADC Driver continues the conversion even if the stream
                                    buffer is full (number of samples reached) by wrapping around
                                    the stream buffer itself.*/
} Adc_StreamBufferModeType;

/**
 * @brief Type for configuring the access mode to group conversion results.
 *
 * @reqs  SWS_Adc_00528
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_ACCESS_MODE_SINGLE = 0, /*!< Single value access mode.*/
    ADC_ACCESS_MODE_STREAMING   /*!< Streaming access mode.*/
} Adc_GroupAccessModeType;

/**
 * @brief Type for configuring on which edge of the hardware trigger signal the driver should
 *        react, i.e. start the conversion (only if supported by the ADC hardware)
 *
 * @reqs  SWS_Adc_00520
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_HW_TRIG_RISING_EDGE = 0, /*!< React on the rising edge of the hardware trigger signal (only
                                    if supported by the ADC hardware).*/
    ADC_HW_TRIG_FALLING_EDGE,    /*!< React on the falling edge of the hardware trigger signal
                                    (only if supported by the ADC hardware).*/
    ADC_HW_TRIG_BOTH_EDGES       /*!< React on both edges of the hardware trigger signal (only if
                                    supported by the ADC hardware).*/
} Adc_HwTriggerSignalType;

/**
 * @brief   Type for the reload value of the ADC module embedded timer (only if supported by the
 *          ADC hardware). (size tbd)
 *
 * @reqs    SWS_Adc_00521
 */
typedef uint8 Adc_HwTriggerTimerType; /* cppcheck-suppress misra-c2012-2.3 ; it is fot future use */

/**
 * @brief Type for configuring the prioritization mechanism.
 *
 * @reqs  SWS_Adc_00522
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_PRIORITY_NONE = 0, /*!< Priority mechanism is not available*/
    ADC_PRIORITY_HW,       /*!< Hardware priority mechanism is available only*/
    ADC_PRIORITY_HW_SW     /*!< Hardware and software priority mechanism is available*/
} Adc_PriorityImplementationType;

/**
 * @brief Replacement mechanism, which is used on ADC group level, if a group conversion is
 *        interrupted by a group which has a higher priority.
 *
 * @reqs  SWS_Adc_00523
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_GROUP_REPL_ABORT_RESTART = 0, /*!< Abort/Restart mechanism is used on group level, if a
                                        group is interrupted by a higher priority group. The
                                        complete conversion round of the interrupted group (all
                                        group channels)is restarted after the higher priority group
                                        conversion is finished. If the group is configured in
                                        streaming access mode, only the results of the interrupted
                                        conversion round are discarded. Results of previous
                                        conversion rounds which are already written to the result
                                        buffer are not affected.*/
    ADC_GROUP_REPL_SUSPEND_RESUME     /*!< Suspend/Resume mechanism is used on group level, if a
                                        group is interrupted by a higher priority group. The
                                        conversion round of the interrupted group is completed
                                        after the higher priority group conversion is finished.
                                        Results of previous conversion rounds which are already
                                        written to the result buffer are not affected.*/
} Adc_GroupReplacementType;

/**
 * @brief In case of active limit checking: defines which conversion values are taken into account
 *        related to the boardes defineed with AdcChannelLowLimit and AdcChannelHighLimit.
 *
 * @reqs  SWS_Adc_00524
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_RANGE_UNDER_LOW = 0, /*!< Range below low limit - low limit value included*/
    ADC_RANGE_BETWEEN,       /*!< Range between low limit and high limit - high limit value
                                included*/
    ADC_RANGE_OVER_HIGH,     /*!< Range above high limit*/
    ADC_RANGE_ALWAYS,        /*!< Complete range - independent from channel limit settings*/
    ADC_RANGE_NOT_UNDER_LOW, /*!< Range above low limit*/
    ADC_RANGE_NOT_BETWEEN,   /*!< Range above high limit or below low limit - low limit value
                                included*/
    ADC_RANGE_NOT_OVER_HIGH  /*!< Range below high limit - high limit value included*/
} Adc_ChannelRangeSelectType;

/**
 * @brief Type for alignment of ADC raw results in ADC result buffer (left/right alignment).
 *
 * @reqs  SWS_Adc_00525
 */
/* cppcheck-suppress misra-c2012-2.4 ; it is fot future use */
typedef enum
{
    ADC_ALIGN_LEFT = 0, /*!< left alignment*/
    ADC_ALIGN_RIGHT     /*!< right alignment*/
} Adc_ResultAlignmentType;

/**
 * @brief Power state currently active or set as target power state.
 *
 * @reqs  SWS_Adc_00526
 */
typedef enum
{
    ADC_FULL_POWER = 0, /*!< Full Power*/
    DECREASING_POWER    /*!< Power modes with decreasing power consumptions. Other 254 values tdb*/
} Adc_PowerStateType;

/**
 * @brief Result of the requests related to power state transitions.
 *
 * @reqs  SWS_Adc_00527
 */
typedef enum
{
    ADC_SERVICE_ACCEPTED = 0, /*!< Power state change executed.*/
    ADC_NOT_INIT,             /*!< ADC Module not initialized.*/
    ADC_SEQUENCE_ERROR,       /*!< Wrong API call sequence.*/
    ADC_HW_FAILURE,           /*!< The HW module has a failure which prevents it to enter the
                                required power state.*/
    ADC_POWER_STATE_NOT_SUPP, /*!< ADC Module does not support the requested power state.*/
    ADC_TRANS_NOT_POSSIBLE    /*!< ADC Module cannot transition directly from the current power
                                state to the requested power state or the HW peripheral is still
                                busy.*/
} Adc_PowerStateRequestResultType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware unit
 * pointers to control structures.
 */
typedef struct _Adc_HwUnit
{
    const Adc_ConfigType *Config; /*!< Pointer to the configuration structure */
} Adc_HwUnit;

/**
 * @brief **DET structure**
 *
 * This structure contains the variables for the control of development error tracings for the Adc
 * module.
 */
typedef struct _Adc_Det_Str
{
    boolean *Adc_InitState;
    uint8 *Adc_ModuleID;
    boolean *Adc_SetupResltBuffer;
    uint8 *GroupNotifFunctionPtr;
    uint8 *PwrState;
    boolean *PreparePwrStateFlag;
} Adc_Det_Str;

#endif /* ADC_TYPES_H__ */
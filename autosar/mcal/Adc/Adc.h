/**
 * @file    Adc.h
 * @brief   **ADC Driver**
 * @author  Naim Leon
 *
 * The ADC module provides the functionality API and the configuration of the AUTOSAR Basic
 * Software module ADC Driver. The ADC driver is targeting Successive Approximation ADC Hardware.
 * Delta Sigma ADC conversion use cases are out of scope of this module.
 *
 */
#ifndef ADC_H__
#define ADC_H__

#include "Adc_Cfg.h"
#include "Adc_Types.h"

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
#define ADC_MAIN_POWER_TRANSITION_MANAGER 0x14u /*!< Adc_Main_PowerTransitionManager() api service
                                                id */
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
#define ADC_E_WRONG_CONV_MODE             0x16u /*!< API called for a group configured for
                                                continuous conversion mode. */
#define ADC_E_WRONG_TRIGG_SRC             0x17u /*!< API call not allowed according group
                                                configuration. */
#define ADC_E_NOTIF_CAPABILITY            0x18u /*!< API called and notification function pointer
                                                is NULL. */
#define ADE_E_BUFFER_UNINIT               0x19u /*!< API called while result buffer pointer is not
                                                initialized. */
#define ADE_E_POWER_STATE_NOT_SUPPORTED   0x1Bu /*!< API call with unsupported power state request.*/
#define ADC_E_PERIPHERAL_NOT_PREPARED     0x1Du /*!< ADC not prepared for requested target power
                                                state. */
#define ADC_E_BUSY                        0x0Bu /*!< API is called while another conversion is
                                                already running, a HW trigger is already enabled, a
                                                request is already stored in the queue. */
#define ADC_E_IDLE                        0x0Cu /*!< API is called while group is in state ADC_IDLE
                                                or non enabled group. */
#define ADC_E_NOT_DISENGAGED              0x1Au /*!< API called while one or more ADC groups are
                                                not in IDLE state. */
#define ADC_E_TRANSITION_NOT_POSSIBLE     0x1Cu /*!< Requested power state can not be reached.  */
/**
 * @} */

void Adc_Init( const Adc_ConfigType *ConfigPtr );
Std_ReturnType Adc_SetupResultBuffer( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
void Adc_DeInit( void );
void Adc_StartGroupConversion( Adc_GroupType Group );
void Adc_StopGroupConversion( Adc_GroupType Group );
Std_ReturnType Adc_ReadGroup( Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr );
void Adc_EnableHardwareTrigger( Adc_GroupType Group );
void Adc_DisableHardwareTrigger( Adc_GroupType Group );
void Adc_EnableGroupNotification( Adc_GroupType Group );
void Adc_DisableGroupNotification( Adc_GroupType Group );
Adc_StatusType Adc_GetGroupStatus( Adc_GroupType Group );
Adc_StreamNumSampleType Adc_GetStreamLastPointer( Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr );
void Adc_GetVersionInfo( Std_VersionInfoType *versioninfo );
Std_ReturnType Adc_SetPowerState( Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_GetCurrentPowerState( Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_GetTargetPowerState( Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result );
Std_ReturnType Adc_PreparePowerState( Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result );

#endif /* ADC_H__ */
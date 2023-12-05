/**
 * @file    Det.h
 * @brief   **DET driver configuration**
 * @author  Oscar Gonzalez
 *
 * The driver Default Error Tracer serve as a mechanisim for reporting and tracing
 * development and runtime errors within the Basic Software.
 */
#include "Std_Types.h"
#include "Det.h"
#include <stdio.h> /* cppcheck-suppress misra-c2012-21.6 ; Necessary for using semihosting  */
#include "Pwm.h"
#include "Fls.h"
#include "Port.h"
#include "Spi.h"
#include "Gpt.h"
#include "Can.h"
#include "Adc.h"
#include "Nvic.h"
#include "Mcu.h"
#include "Dio.h"

extern void initialise_monitor_handles( void );

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *ModuleName[] = {
"SPI",
"PWM",
"GPT",
"DET",
"CAN",
"ADC",
"NVIC",
"MCU",
"DIO",
"PORT",
"FLS",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *SpiApiName[] = {
[SPI_ID_INIT]                = "Spi_Init()",
[SPI_ID_DE_INIT]             = "Spi_DeInit()",
[SPI_ID_WRITE_IB]            = "Spi_WriteIB()",
[SPI_ID_ASYNC_TRANSMIT]      = "Spi_AsyncTransmit()",
[SPI_ID_READ_IB]             = "Spi_ReadIB()",
[SPI_ID_SET_UP_EB]           = "Spi_SetupEB()",
[SPI_ID_GET_STATUS]          = "Spi_GetStatus()",
[SPI_ID_GET_JOB_RESULT]      = "Spi_GetJobResult()",
[SPI_ID_GET_SEQUENCE_RESULT] = "Spi_GetSequenceResult()",
[SPI_ID_GET_VERSION_INFO]    = "Spi_GetVersionInfo()",
[SPI_ID_SYNC_TRANSMIT]       = "Spi_SyncTransmit()",
[SPI_ID_GET_HWUNIT_STATUS]   = "Spi_GetHWUnitStatus()",
[SPI_ID_CANCEL]              = "Spi_Cancel()",
[SPI_ID_SET_ASYNC_MODE]      = "Spi_SetAsyncMode()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *SpiErrorName[] = {
[SPI_E_PARAM_CHANNEL]       = "SPI_E_PARAM_CHANNEL",
[SPI_E_PARAM_JOB]           = "SPI_E_PARAM_JOB",
[SPI_E_PARAM_SEQ]           = "SPI_E_PARAM_SEQ",
[SPI_E_PARAM_LENGTH]        = "SPI_E_PARAM_LENGTH",
[SPI_E_PARAM_UNIT]          = "SPI_E_PARAM_UNIT",
[SPI_E_PARAM_POINTER]       = "SPI_E_PARAM_POINTER",
[SPI_E_UNINIT]              = "SPI_E_UNINIT",
[SPI_E_ALREADY_INITIALIZED] = "SPI_E_ALREADY_INITIALIZED",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *PwmApiName[] = {
[PWM_ID_INIT]                    = "Pwm_Init()",
[PWM_ID_DE_INIT]                 = "Pwm_DeInit()",
[PWM_ID_SET_DUTY_CYCLE]          = "Pwm_SetDutyCycle()",
[PWM_ID_SET_PERIOD_AND_DUTY]     = "Pwm_SetPeridoAndDuty()",
[PWM_ID_SET_OUTPUT_TO_IDLE]      = "Pwm_SetOutputToIdle()",
[PWM_ID_GET_OUTPUT_STATE]        = "Pwm_GetOutputState()",
[PWM_ID_DISABLE_NOTIFICATION]    = "Pwm_DisableNotification()",
[PWM_ID_ENABLE_NOTIFICATION]     = "Pwm_EnableNotification()",
[PWM_ID_SET_POWER_STATE]         = "Pwm_SetPowerState()",
[PWM_ID_GET_CURRENT_POWER_STATE] = "Pwm_GetCurrentPowerState()",
[PWM_ID_GET_TARGET_POWER_STATE]  = "Pwm_GetTargetPowerState()",
[PWM_ID_PREPARE_POWER_STATE]     = "Pwm_PreparePowerState()",
[PWM_ID_GET_VERSION_INFO]        = "Pwm_GetVersionInfo()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *PwmErrorName[] = {
[PWM_E_INIT_FAILED]               = "PWM_E_INIT_FAILED",
[PWM_E_UNINIT]                    = "PWM_E_UNINIT",
[PWM_E_PARAM_CHANNEL]             = "PWM_E_PARAM_CHANNEL",
[PWM_E_PERIOD_UNCHANGEABLE]       = "PWM_E_PERIOD_UNCHANGEABLE",
[PWM_E_ALREADY_INITIALIZED]       = "PWM_E_ALREADY_INITIALIZED",
[PWM_E_PARAM_POINTER]             = "PWM_E_PARAM_POINTER",
[PWM_E_POWER_STATE_NOT_SUPPORTED] = "PWM_E_POWER_STATE_NOT_SUPPORTED",
[PWM_E_TRANSITION_NOT_POSSIBLE]   = "PWM_E_TRANSITION_NOT_POSSIBLE",
[PWM_E_PERIPHERAL_NOT_PREPARED]   = "PWM_E_PERIPHERAL_NOT_PREPARED",
[PWM_E_NOT_DISENGAGED]            = "PWM_E_NOT_DISENGAGED",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *GptApiName[] = {
[GPT_ID_GET_VERSION_INFO]     = "Gpt_GetVersionInfo()",
[GPT_ID_INIT]                 = "Gpt_Init()",
[GPT_ID_DEINIT]               = "Gpt_DeInit()",
[GPT_ID_GET_TIME_ELAPSED]     = "Gpt_GetTimeElapsed()",
[GPT_ID_GET_TIME_REMAINING]   = "Gpt_GetTimeRemaining()",
[GPT_ID_START_TIMER]          = "Gpt_StartTimer()",
[GPT_ID_STOP_TIMER]           = "Gpt_StopTimer()",
[GPT_ID_ENABLE_NOTIFICATION]  = "Gpt_EnableNotification()",
[GPT_ID_DISABLE_NOTIFICATION] = "Gpt_DisableNotification()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *GptErrorName[] = {
[GPT_E_UNINIT]              = "GPT_E_UNINIT",
[GPT_E_ALREADY_INITIALIZED] = "GPT_E_ALREADY_INITIALIZED",
[GPT_E_INIT_FAILED]         = "GPT_E_INIT_FAILED",
[GPT_E_PARAM_CHANNEL]       = "GPT_E_PARAM_CHANNEL",
[GPT_E_PARAM_VALUE]         = "GPT_E_PARAM_VALUE",
[GPT_E_PARAM_POINTER]       = "GPT_E_PARAM_POINTER",
[GPT_E_PARAM_PREDEF_TIMER]  = "GPT_E_PARAM_PREDEF_TIMER",
[GPT_E_PARAM_MODE]          = "GPT_E_PARAM_MODE",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *DetApiName[ 6 ] = {
[DET_ID_INIT]                   = "Det_Init()",
[DET_ID_REPORT_ERROR]           = "Det_ReportError()",
[DET_ID_DE_START]               = "Det_Start()",
[DET_ID_GET_VERSION_INFO]       = "Det_GetVersionInfo()",
[DET_ID_REPORT_RUNTIME_ERROR]   = "Det_ReportRuntimeError()",
[DET_ID_REPORT_TRANSIENT_FAULT] = "Det_ReportTransientFault()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *DetErrorName[ 2 ] = {
[DET_E_PARAM_POINTER] = "DET_E_PARAM_POINTER",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *CanApiName[] = {
[CAN_ID_INIT]                = "Can_Init()",
[CAN_ID_DE_INIT]             = "Can_DeInit()",
[CAN_ID_SET_BAUDRATE]        = "Can_ChangeBaudrate()",
[CAN_ID_SET_CTRL_MODE]       = "Can_SetControllerMode()",
[CAN_ID_DISABLE_CTRL_INT]    = "Can_DisableControllerInterrupts()",
[CAN_ID_ENABLE_CTRL_INT]     = "Can_EnableControllerInterrupts()",
[CAN_ID_CHECK_WAKEUP]        = "Can_CheckWakeup()",
[CAN_ID_GET_CTRL_MODE]       = "Can_GetControllerState()",
[CAN_ID_GET_CTRL_ERR_STATE]  = "Can_GetControllerErrorState()",
[CAN_ID_GET_CTRL_RX_ERR_CNT] = "Can_GetControllerRxErrorCounter()",
[CAN_ID_GET_CTRL_TX_ERR_CNT] = "Can_GetControllerTxErrorCounter()",
[CAN_ID_WRITE]               = "Can_Write()",
[CAN_ID_MF_WRITE]            = "Can_MainFunction_Write()",
[CAN_ID_MF_READ]             = "Can_MainFunction_Read()",
[CAN_ID_MF_BUSOFF]           = "Can_MainFunction_BusOff()",
[CAN_ID_MF_WAKEUP]           = "Can_MainFunction_Wakeup()",
[CAN_ID_MF_MODE]             = "Can_MainFunction_MODE()",
[CAN_ID_GET_VERSION_INFO]    = "Can_GetVersionInfo()",
[CAN_ID_GET_CURRENT_TIME]    = "Can_GetCurrentTime()",
[CAN_ID_ENABLE_EGRESS_TS]    = "Can_EnableEgressTimeStamp()",
[CAN_ID_GET_EGRESS_TS]       = "Can_GetEgressTimeStamp()",
[CAN_ID_GET_INGRESS_TS]      = "Can_GetIngressTimeStamp()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *CanErrorName[] = {
[CAN_E_PARAM_POINTER]     = "CAN_E_PARAM_POINTER",
[CAN_E_PARAM_HANDLE]      = "CAN_E_PARAM_HANDLE",
[CAN_E_PARAM_DATA_LENGTH] = "CAN_E_PARAM_DATA_LENGTH",
[CAN_E_PARAM_CONTROLLER]  = "CAN_E_PARAM_CONTROLLER",
[CAN_E_UNINIT]            = "CAN_E_UNINIT",
[CAN_E_TRANSITION]        = "CAN_E_TRANSITION",
[CAN_E_PARAM_BAUDRATE]    = "CAN_E_PARAM_BAUDRATE",
[CAN_E_INIT_FAILED]       = "CAN_E_INIT_FAILED",
[CAN_E_PARAM_LPDU]        = "CAN_E_PARAM_LPDU",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *AdcApiName[] = {
[ADC_ID_INIT]                       = "Adc_Init()",
[ADC_RESULT_BUFFER]                 = "Adc_SetupResultBuffer()",
[ADC_ID_DE_INIT]                    = "Adc_DeInit()",
[ADC_START_GROUP_CONVERSION]        = "Adc_StartGroupConversion()",
[ADC_STOP_GROUP_CONVERSION]         = "Adc_StopGroupConversion()",
[ADC_READ_GROUP]                    = "Adc_ReadGroup()",
[ADC_ENABLE_HARDWARE_TRIGGER]       = "Adc_EnableHardwareTrigger()",
[ADC_DISABLE_HARDWARE_TRIGGER]      = "Adc_DisableHardwareTrigger()",
[ADC_ENABLE_GROUP_NOTIFICATION]     = "Adc_EnableGroupNotification()",
[ADC_DISABLE_GROUP_NOTIFICATION]    = "Adc_DisableGroupNotification()",
[ADC_GET_GROUP_STATUS]              = "Adc_GetGroupStatus()",
[ADC_GET_STREAM_LAST_POINTER]       = "Adc_GetStreamLastPointer()",
[ADC_GET_VERSION_INFO]              = "Adc_GetVersionInfo()",
[ADC_SET_POWER_STATE]               = "Adc_SetPowerState()",
[ADC_GET_CURRENT_POWER_STATE]       = "Adc_GetCurrentPowerState()",
[ADC_GET_TARGET_POWER_STATE]        = "Adc_GetTargetPowerState()",
[ADC_PREPARE_POWER_STATE]           = "Adc_PreparePowerState()",
[ADC_MAIN_POWER_TRANSITION_MANAGER] = "Adc_Main_PowerTransitionManager()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *AdcErrorName[] = {
[ADC_E_UNINIT]                    = "ADC_E_UNINIT",
[ADC_E_ALREADY_INITIALIZED]       = "ADC_E_ALREADY_INITIALIZED",
[ADC_E_PARAM_POINTER]             = "ADC_E_PARAM_POINTER",
[ADC_E_PARAM_GROUP]               = "ADC_E_PARAM_GROUP",
[ADC_E_WRONG_CONV_MODE]           = "ADC_E_WRONG_CONV_MODE",
[ADC_E_WRONG_TRIGG_SRC]           = "ADC_E_WRONG_TRIGG_SRC",
[ADC_E_NOTIF_CAPABILITY]          = "ADC_E_NOTIF_CAPABILITY",
[ADC_E_BUFFER_UNINIT]             = "ADE_E_BUFFER_UNINIT",
[ADC_E_POWER_STATE_NOT_SUPPORTED] = "ADE_E_POWER_STATE_NOT_SUPPORTED",
[ADC_E_PERIPHERAL_NOT_PREPARED]   = "ADC_E_PERIPHERAL_NOT_PREPARED",
[ADC_E_BUSY]                      = "ADC_E_BUSY",
[ADC_E_IDLE]                      = "ADC_E_IDLE",
[ADC_E_NOT_DISENGAGED]            = "ADC_E_NOT_DISENGAGED",
[ADC_E_TRANSITION_NOT_POSSIBLE]   = "ADC_E_TRANSITION_NOT_POSSIBLE",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *NvicApiName[] = {
[NVIC_ID_SET_PRIORITY]      = "CDD_Nvic_SetPriority()",
[NVIC_ID_GET_PRIORITY]      = "CDD_Nvic_GetPriority()",
[NVIC_ID_ENABLE_IRQ]        = "CDD_Nvic_EnableIrq()",
[NVIC_ID_DISABLE_IRQ]       = "CDD_Nvic_DisableIrq()",
[NVIC_ID_GET_PENDING_IRQ]   = "CDD_Nvic_GetPendingIrq()",
[NVIC_ID_SET_PENDING_IRQ]   = "CDD_Nvic_SetPendingIrq()",
[NVIC_ID_CLEAR_PENDING_IRQ] = "CDD_Nvic_ClearPendingIrq()",
[NVIC_ID_NMI_HANDLER]       = "NMI_Handler",
[NVIC_ID_HARDFAULT_HANDLER] = "HardFault_Handler",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *NvicErrorName[] = {
[NVIC_E_PARAM_IRQ]       = "NVIC_E_PARAM_IRQ",
[NVIC_E_PARAM_PRIORITY]  = "NVIC_E_PARAM_PRIORITY",
[NVIC_E_NMI_ENTRY]       = "NVIC_E_NMI_ENTRY",
[NVIC_E_HARDFAULT_ENTRY] = "NVIC_E_HARDFAULT_ENTRY",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *McuApiName[] = {
[MCU_ID_INIT]                 = "Mcu_Init()",
[MCU_ID_INIT_RAM]             = "Mcu_InitRamSection()",
[MCU_ID_INIT_CLOCK]           = "Mcu_InitClock()",
[MCU_ID_DISTRIBUTE_PLL_CLOCK] = "Mcu_DistributePllClock()",
[MCU_ID_GET_PLL_STATUS]       = "Mcu_GetPllStatus()",
[MCU_ID_GET_RESET_REASON]     = "Mcu_GetResetReason()",
[MCU_ID_GET_RESET_RAW_VALUE]  = "Mcu_GetResetRawValue()",
[MCU_ID_PERFORM_RESET]        = "Mcu_PerformReset()",
[MCU_ID_SET_MODE]             = "Mcu_SetMode()",
[MCU_ID_GET_VERSION_INFO]     = "Mcu_GetVersionInfo()",
[MCU_ID_GET_RAM_STATE]        = "Mcu_GetRamState()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *McuErrorName[] = {
[MCU_E_PARAM_CONFIG]     = "MCU_E_PARAM_CONFIG",
[MCU_E_PARAM_CLOCK]      = "MCU_E_PARAM_CLOCK",
[MCU_E_PARAM_MODE]       = "MCU_E_PARAM_MODE",
[MCU_E_PARAM_RAMSECTION] = "MCU_E_PARAM_RAMSECTION",
[MCU_E_PLL_NOT_LOCKED]   = "MCU_E_PLL_NOT_LOCKED",
[MCU_E_UNINIT]           = "MCU_E_UNINIT",
[MCU_E_PARAM_POINTER]    = "MCU_E_PARAM_POINTER",
[MCU_E_INIT_FAILED]      = "MCU_E_INIT_FAILED",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *DioApiName[] = {
[DIO_ID_READ_CHANNEL]      = "Dio_ReadChannel()",
[DIO_ID_WRITE_CHANNEL]     = "Dio_WriteChannel()",
[DIO_ID_READ_PORT]         = "Dio_ReadPort()",
[DIO_ID_WRITE_PORT]        = "Dio_WritePort()",
[DIO_ID_READ_CHANNEL_GRP]  = "Dio_ReadChannelGroup()",
[DIO_ID_WRITE_CHANNEL_GRP] = "Dio_WriteChannelGroup()",
[DIO_ID_GET_VERSION_INFO]  = "Dio_GetVersionInfo()",
[DIO_ID_FLIP_CHANNEL]      = "Dio_FlipChannel()",
[DIO_ID_MASKED_WRITE_PORT] = "Dio_MaskedWritePort()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *DioErrorName[] = {
[DIO_E_PARAM_INVALID_CHANNEL_ID] = "DIO_E_PARAM_INVALID_CHANNEL_ID",
[DIO_E_PARAM_INVALID_PORT_ID]    = "DIO_E_PARAM_INVALID_PORT_ID",
[DIO_E_PARAM_INVALID_GROUP]      = "DIO_E_PARAM_INVALID_GROUP",
[DIO_E_PARAM_POINTER]            = "DIO_E_PARAM_POINTER",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *PortApiName[] = {
[PORT_ID_INIT]                   = "Port_Init()",
[PORT_ID_SET_PIN_DIRECTION]      = "Port_SetPinDirection()",
[PORT_ID_SET_PIN_MODE]           = "Port_SetPinMode()",
[PORT_ID_GET_VERSION_INFO]       = "Port_GetVersionInfo()",
[PORT_ID_REFRESH_PORT_DIRECTION] = "Port_RefreshPortDirection()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *PortErrorName[] = {
[PORT_E_PARAM_PIN]              = "PORT_E_PARAM_PIN",
[PORT_E_DIRECTION_UNCHANGEABLE] = "PORT_E_DIRECTION_UNCHANGEABLE",
[PORT_E_INIT_FAILED]            = "PORT_E_INIT_FAILED",
[PORT_E_PARAM_INVALID_MODE]     = "PORT_E_PARAM_INVALID_MODE",
[PORT_E_MODE_UNCHANGEABLE]      = "PORT_E_MODE_UNCHANGEABLE",
[PORT_E_UNINIT]                 = "PORT_E_UNINIT",
[PORT_E_PARAM_POINTER]          = "PORT_E_PARAM_POINTER",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *FlsApiName[] = {
[FLS_ID_INIT]           = "Fls_Init()",
[FLS_ID_ERASE]          = "Fls_Erase()",
[FLS_ID_WRITE]          = "Fls_Write()",
[FLS_ID_CANCEL]         = "Fls_Cancel()",
[FLS_ID_GETSTATUS]      = "Fls_GetStatus()",
[FLS_ID_GETJOBRESULT]   = "Fls_GetJobResults()",
[FLS_ID_READ]           = "Fls_Read()",
[FLS_ID_COMPARE]        = "Fls_Compare()",
[FLS_ID_SETMODE]        = "Fls_SetMode()",
[FLS_ID_GETVERSIONINFO] = "Fls_GetVersionInfo()",
[FLS_ID_BLANKCHECK]     = "Fls_BlankCheck()",
};

/* cppcheck-suppress misra-c2012-8.9 ; Has to be global due to the compiler can place them in the Flash Memory*/
static const char *FlsErrorName[] = {
[FLS_E_PARAM_CONFIG]        = "FLS_E_PARAM_CONFIG",
[FLS_E_PARAM_ADDRESS]       = "FLS_E_PARAM_ADDRESS",
[FLS_E_PARAM_LENGTH]        = "FLS_E_PARAM_LENGTH",
[FLS_E_PARAM_DATA]          = "FLS_E_PARAM_DATA",
[FLS_E_UNINIT]              = "FLS_E_UNINIT",
[FLS_E_PARAM_POINTER]       = "FLS_E_PARAM_POINTER",
[FLS_E_ALREADY_INITIALIZED] = "FLS_E_ALREADY_INITIALIZED",
};

/**
 * @brief    **Det Initialization**
 *
 * Service to initialize the Default Error Tracer.
 *
 * @param    ConfigPtr 	Pointer to the selected configuration set.
 *
 * @reqs    SWS_Det_00008
 */
void Det_Init( const Det_ConfigType *ConfigPtr )
{
    (void)ConfigPtr;
}

/**
 * @brief    **Det Report Error**
 *
 * Service to report development errors.
 *
 * @param   ModuleId   ID of calling module.
 * @param   InstanceId The identifier of the index based instance of a module, starting from 0,
 *                     If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param   ApiId      ID of API service in which error is detected (defined in SWS of calling module).
 * @param   ErrorId    ID of detected development error (defined in SWS of calling module).
 *
 * @retval Std_ReturnType: never returns a value, but has a return type for compatibility with services and hooks.
 *
 * @note    Det_ReportError may be callable in interrupt context. Since the DET can be called in normal mode or in
 *          interrupt context from stack or integration) this has to be considered during implementation of the hook
 *          functions:Det_ReportError can be called in interrupt context; this should be considered when halting the
 *          system.
 *
 * @reqs    SWS_Det_00009
 */
Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
{
    if( ( ModuleId <= MAX_MODULE_ID ) )
    {
        Module modules[] = {
        { SpiApiName, SpiErrorName },
        { PwmApiName, PwmErrorName },
        { GptApiName, GptErrorName },
        { DetApiName, DetErrorName },
        { CanApiName, CanErrorName },
        { AdcApiName, AdcErrorName },
        { NvicApiName, NvicErrorName },
        { McuApiName, McuErrorName },
        { DioApiName, DioErrorName },
        { PortApiName, PortErrorName },
        { FlsApiName, FlsErrorName } };

        (void)printf( "Error: %s In %s Module in function %s with the Instance %s\n", modules[ ModuleId ].errorName[ ErrorId ],
                      ModuleName[ ModuleId ], modules[ ModuleId ].apiName[ ApiId ], ModuleName[ InstanceId ] );
    }
    else
    {
        (void)printf( "Other error" );
    }

    return E_OK;
}

/**
 * @brief    **Det Start**
 *
 * Service to initialize the Default Error Tracer.
 *
 * @reqs    SWS_Det_00010
 */
void Det_Start( void )
{
    initialise_monitor_handles( );
}

/**
 * @brief    **Det Report Runtime Error**
 *
 * Service to report runtime errors. If a callout has been configured then this callout shall be called.
 *
 * @param   ModuleId   ID of calling module.
 * @param   InstanceId The identifier of the index based instance of a module, starting from 0,
 *                     If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param   ApiId      ID of API service in which error is detected (defined in SWS of calling module).
 * @param   ErrorId    ID of detected development error (defined in SWS of calling module).
 *
 * @retval Std_ReturnType: returns always E_OK (is required for services)
 *
 * @note    Det_ReportRuntime Error may be callable in interrupt context. Since the DET can be called in normal mode
 *          or in interrupt context (from stack or integration) this has to be considered during implementation of
 *          the hook functions:Det_ReportRuntimeError can be called in interrupt context; this hook should be reentrant
 *          and sufficiently performant.
 *
 * @reqs    SWS_Det_01001
 */
Std_ReturnType Det_ReportRuntimeError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;

    return E_OK;
}

/**
 * @brief    **Det Report Transient Fault**
 *
 * Service to report transient faults. If a callout has been configured than this callout shall be called
 * and the returned value of the callout shall be returned. Otherwise it returns immediately with E_OK.
 *
 * @param   ModuleId   ID of calling module.
 * @param   InstanceId The identifier of the index based instance of a module, starting from 0,
 *                     If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param   ApiId      ID of API service in which error is detected (defined in SWS of calling module).
 * @param   FaultId    ID of detected transient fault (defined in SWS of calling module).
 *
 * @retval  If no callout exists it shall return E_OK, otherwise it shall return the value of the configured callout.
 *          In case several callouts are configured the logical or (sum) of the callout return values shall be returned.
 *          Rationale: since E_OK=0, E_OK will be only returned if all are E_OK, and for multiple error codes there is a
 *          good chance to detect several of them.
 *
 * @note    Det_ReportTransient Fault may be callable in interrupt context. Since the DET can be called in normal mode
 *          or in interrupt context (from stack or integration) this has to be considered during implementation of the
 *          hook functions: Det_ReportTransientFault can be called in interrupt context; his hook should be reentrant
 *          and sufficiently performant.
 *
 * @reqs    SWS_Det_01003
 */
Std_ReturnType Det_ReportTransientFault( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId )
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)FaultId;

    return E_OK;
}

#if DET_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Det Get Version Info**
 *
 * Returns the version information of this module.
 *
 * @param versioninfo 	Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Det_00011
 */
void Det_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void)versioninfo;
}
#endif

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
    static const char *ModuleName[] = {
    [SPI_MODULE_ID]  = "SPI_MODULE_ID",
    [GPT_MODULE_ID]  = "GPT_MODULE_ID",
    [DET_MODULE_ID]  = "DET_MODULE_ID",
    [CAN_MODULE_ID]  = "CAN_MODULE_ID",
    [ADC_MODULE_ID]  = "ADC_MODULE_ID",
    [NVIC_MODULE_ID] = "NVIC_MODULE_ID",
    [MCU_MODULE_ID]  = "MCU_MODULE_ID",
    [DIO_MODULE_ID]  = "DIO_MODULE_ID",
    };

    static const char *InstanceName[] = {
    [SPI_INSTANCE_ID]  = "SPI_INSTANCE_ID",
    [DET_INSTANCE_ID]  = "DET_INSTANCE_ID",
    [CAN_INSTANCE_ID]  = "CAN_INSTANCE_ID",
    [ADC_INSTANCE_ID]  = "ADC_INSTANCE_ID",
    [NVIC_INSTANCE_ID] = "NVIC_INSTANCE_ID",
    [MCU_INSTANCE_ID]  = "MCU_INSTANCE_ID",
    [DIO_INSTANCE_ID]  = "DIO_INSTANCE_ID",
    };

    /* cppcheck-suppress misra-c2012-9.5 ; Currently in development*/
    static const char *ApiName[] = {
    /*Det Api*/
    [DET_ID_INIT]                   = "DET_ID_INIT",
    [DET_ID_REPORT_ERROR]           = "DET_ID_REPORT_ERROR",
    [DET_ID_DE_START]               = "DET_ID_DE_START",
    [DET_ID_GET_VERSION_INFO]       = "DET_ID_GET_VERSION_INFO",
    [DET_ID_REPORT_RUNTIME_ERROR]   = "DET_ID_REPORT_RUNTIME_ERROR",
    [DET_ID_REPORT_TRANSIENT_FAULT] = "DET_ID_REPORT_TRANSIENT_FAULT",
    /*Spi Api*/
    [SPI_ID_INIT]                = "SPI_ID_INIT",
    [SPI_ID_DE_INIT]             = "SPI_ID_DE_INIT",
    [SPI_ID_WRITE_IB]            = "SPI_ID_WRITE_IB",
    [SPI_ID_ASYNC_TRANSMIT]      = "SPI_ID_ASYNC_TRANSMIT",
    [SPI_ID_READ_IB]             = "SPI_ID_READ_IB",
    [SPI_ID_SET_UP_EB]           = "SPI_ID_SET_UP_EB",
    [SPI_ID_GET_STATUS]          = "SPI_ID_GET_STATUS",
    [SPI_ID_GET_JOB_RESULT]      = "SPI_ID_GET_JOB_RESULT",
    [SPI_ID_GET_SEQUENCE_RESULT] = "SPI_ID_GET_SEQUENCE_RESULT",
    [SPI_ID_GET_VERSION_INFO]    = "SPI_ID_GET_VERSION_INFO",
    [SPI_ID_SYNC_TRANSMIT]       = "SPI_ID_SYNC_TRANSMIT",
    [SPI_ID_GET_HWUNIT_STATUS]   = "SPI_ID_GET_HWUNIT_STATUS",
    [SPI_ID_CANCEL]              = "SPI_ID_CANCEL",
    [SPI_ID_SET_ASYNC_MODE]      = "SPI_ID_SET_ASYNC_MODE",
    /*Nvic Api*/
    [NVIC_ID_SET_PRIORITY]      = "NVIC_ID_SET_PRIORITY",
    [NVIC_ID_GET_PRIORITY]      = "NVIC_ID_GET_PRIORITY",
    [NVIC_ID_ENABLE_IRQ]        = "NVIC_ID_ENABLE_IRQ",
    [NVIC_ID_DISABLE_IRQ]       = "NVIC_ID_DISABLE_IRQ",
    [NVIC_ID_GET_PENDING_IRQ]   = "NVIC_ID_GET_PENDING_IRQ",
    [NVIC_ID_SET_PENDING_IRQ]   = "NVIC_ID_SET_PENDING_IRQ",
    [NVIC_ID_CLEAR_PENDING_IRQ] = "NVIC_ID_CLEAR_PENDING_IRQ",
    [NVIC_ID_NMI_HANDLER]       = "NVIC_ID_NMI_HANDLER",
    [NVIC_ID_HARDFAULT_HANDLER] = "NVIC_ID_HARDFAULT_HANDLER",
    /*Pwm Api*/
    [PWM_ID_INIT]                    = "PWM_ID_INIT",
    [PWM_ID_DE_INIT]                 = "PWM_ID_DE_INIT",
    [PWM_ID_SET_DUTY_CYCLE]          = "PWM_ID_SET_DUTY_CYCLE",
    [PWM_ID_SET_PERIOD_AND_DUTY]     = "PWM_ID_SET_PERIOD_AND_DUTY",
    [PWM_ID_SET_OUTPUT_TO_IDLE]      = "PWM_ID_SET_OUTPUT_TO_IDLE",
    [PWM_ID_GET_OUTPUT_STATE]        = "PWM_ID_GET_OUTPUT_STATE",
    [PWM_ID_DISABLE_NOTIFICATION]    = "PWM_ID_DISABLE_NOTIFICATION",
    [PWM_ID_ENABLE_NOTIFICATION]     = "PWM_ID_ENABLE_NOTIFICATION",
    [PWM_ID_GET_CURRENT_POWER_STATE] = "PWM_ID_GET_CURRENT_POWER_STATE",
    [PWM_ID_GET_TARGET_POWER_STATE]  = "PWM_ID_GET_TARGET_POWER_STATE",
    [PWM_ID_PREPARE_POWER_STATE]     = "PWM_ID_PREPARE_POWER_STATE",
    [PWM_ID_GET_VERSION_INFO]        = "PWM_ID_GET_VERSION_INFO",
    /*MCU Api*/
    [MCU_ID_INIT]                 = "MCU_ID_INIT",
    [MCU_ID_INIT_RAM]             = "MCU_ID_INIT_RAM",
    [MCU_ID_INIT_CLOCK]           = "MCU_ID_INIT_CLOCK",
    [MCU_ID_DISTRIBUTE_PLL_CLOCK] = "MCU_ID_DISTRIBUTE_PLL_CLOCK",
    [MCU_ID_GET_PLL_STATUS]       = "MCU_ID_GET_PLL_STATUS",
    [MCU_ID_GET_RESET_REASON]     = "MCU_ID_GET_RESET_REASON",
    [MCU_ID_GET_RESET_RAW_VALUE]  = "MCU_ID_GET_RESET_RAW_VALUE",
    [MCU_ID_PERFORM_RESET]        = "MCU_ID_PERFORM_RESET",
    [MCU_ID_SET_MODE]             = "MCU_ID_SET_MODE",
    [MCU_ID_GET_VERSION_INFO]     = "MCU_ID_GET_VERSION_INFO",
    [MCU_ID_GET_RAM_STATE]        = "MCU_ID_GET_RAM_STATE",
    /*Fls Api*/
    [FLS_ID_INIT]           = "FLS_ID_INIT",
    [FLS_ID_ERASE]          = "FLS_ID_ERASE",
    [FLS_ID_WRITE]          = "FLS_ID_WRITE",
    [FLS_ID_CANCEL]         = "FLS_ID_CANCEL",
    [FLS_ID_GETSTATUS]      = "FLS_ID_GETSTATUS",
    [FLS_ID_GETJOBRESULT]   = "FLS_ID_GETJOBRESULT",
    [FLS_ID_READ]           = "FLS_ID_READ",
    [FLS_ID_COMPARE]        = "FLS_ID_COMPARE",
    [FLS_ID_SETMODE]        = "FLS_ID_SETMODE",
    [FLS_ID_GETVERSIONINFO] = "FLS_ID_GETVERSIONINFO",
    [FLS_ID_BLANKCHECK]     = "FLS_ID_BLANKCHECK",
    /*Dio Api*/
    [DIO_ID_READ_CHANNEL]      = "DIO_ID_READ_CHANNEL",
    [DIO_ID_WRITE_CHANNEL]     = "DIO_ID_WRITE_CHANNEL",
    [DIO_ID_READ_PORT]         = "DIO_ID_READ_PORT",
    [DIO_ID_WRITE_PORT]        = "DIO_ID_WRITE_PORT",
    [DIO_ID_READ_CHANNEL_GRP]  = "DIO_ID_READ_CHANNEL_GRP",
    [DIO_ID_WRITE_CHANNEL_GRP] = "DIO_ID_WRITE_CHANNEL_GRP",
    [DIO_ID_GET_VERSION_INFO]  = "DIO_ID_GET_VERSION_INFO",
    [DIO_ID_FLIP_CHANNEL]      = "DIO_ID_FLIP_CHANNEL",
    [DIO_ID_MASKED_WRITE_PORT] = "DIO_ID_MASKED_WRITE_PORT",
    };

    /* cppcheck-suppress misra-c2012-9.5 ; Currently in development*/
    static const char *ErrorName[] = {
    /*Det Error*/
    [DET_E_PARAM_POINTER] = "DET_E_PARAM_POINTER",
    /*Spi Error*/
    [SPI_E_PARAM_CHANNEL]       = "SPI_E_PARAM_CHANNEL",
    [SPI_E_PARAM_JOB]           = "SPI_E_PARAM_JOB",
    [SPI_E_PARAM_SEQ]           = "SPI_E_PARAM_SEQ",
    [SPI_E_PARAM_LENGTH]        = "SPI_E_PARAM_LENGTH",
    [SPI_E_PARAM_UNIT]          = "SPI_E_PARAM_UNIT",
    [SPI_E_PARAM_POINTER]       = "SPI_E_PARAM_POINTER",
    [SPI_E_UNINIT]              = "SPI_E_UNINIT",
    [SPI_E_ALREADY_INITIALIZED] = "SPI_E_ALREADY_INITIALIZED",
    /*Nvic Error*/
    [NVIC_E_PARAM_IRQ]       = "NVIC_E_PARAM_IRQ",
    [NVIC_E_PARAM_PRIORITY]  = "NVIC_E_PARAM_PRIORITY",
    [NVIC_E_NMI_ENTRY]       = "NVIC_E_NMI_ENTRY",
    [NVIC_E_HARDFAULT_ENTRY] = "NVIC_E_HARDFAULT_ENTRY",
    /*Pwm Error*/
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
    /*Port Error*/
    [PORT_E_PARAM_PIN]              = "PORT_E_PARAM_PIN",
    [PORT_E_DIRECTION_UNCHANGEABLE] = "PORT_E_DIRECTION_UNCHANGEABLE",
    [PORT_E_INIT_FAILED]            = "PORT_E_INIT_FAILED",
    [PORT_E_PARAM_INVALID_MODE]     = "PORT_E_PARAM_INVALID_MODE",
    [PORT_E_MODE_UNCHANGEABLE]      = "PORT_E_MODE_UNCHANGEABLE",
    [PORT_E_UNINIT]                 = "PORT_E_UNINIT",
    [PORT_E_PARAM_POINTER]          = "PORT_E_PARAM_POINTER",
    /*MCU Error*/
    [MCU_E_PARAM_CONFIG]     = "MCU_E_PARAM_CONFIG",
    [MCU_E_PARAM_CLOCK]      = "MCU_E_PARAM_CLOCK",
    [MCU_E_PARAM_MODE]       = "MCU_E_PARAM_MODE",
    [MCU_E_PARAM_RAMSECTION] = "MCU_E_PARAM_RAMSECTION",
    [MCU_E_PLL_NOT_LOCKED]   = "MCU_E_PLL_NOT_LOCKED",
    [MCU_E_UNINIT]           = "MCU_E_UNINIT",
    [MCU_E_PARAM_POINTER]    = "MCU_E_PARAM_POINTER",
    [MCU_E_INIT_FAILED]      = "MCU_E_INIT_FAILED",
    /*Fls Error*/
    [FLS_E_PARAM_CONFIG]        = "FLS_E_PARAM_CONFIG",
    [FLS_E_PARAM_ADDRESS]       = "FLS_E_PARAM_ADDRESS",
    [FLS_E_PARAM_LENGTH]        = "FLS_E_PARAM_LENGTH",
    [FLS_E_PARAM_DATA]          = "FLS_E_PARAM_DATA",
    [FLS_E_UNINIT]              = "FLS_E_UNINIT",
    [FLS_E_PARAM_POINTER]       = "FLS_E_PARAM_POINTER",
    [FLS_E_ALREADY_INITIALIZED] = "FLS_E_ALREADY_INITIALIZED",
    /*Dio Error*/
    [DIO_E_PARAM_INVALID_CHANNEL_ID] = "DIO_E_PARAM_INVALID_CHANNEL_ID",
    [DIO_E_PARAM_INVALID_PORT_ID]    = "DIO_E_PARAM_INVALID_PORT_ID",
    [DIO_E_PARAM_INVALID_GROUP]      = "DIO_E_PARAM_INVALID_GROUP",
    [DIO_E_PARAM_POINTER]            = "DIO_E_PARAM_POINTER",
    };

    DetError ReportError;

    ReportError.Module   = ModuleName[ ModuleId ];
    ReportError.Instance = InstanceName[ InstanceId ];
    ReportError.Api      = ApiName[ ApiId ];
    ReportError.Error    = ErrorName[ ErrorId ];

    (void)printf( "ERROR %s in: %s Module with the function %s detected in %s\n" , ReportError.Error,ReportError.Module
                  ,ReportError.Instance,ReportError.Api);
                  
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

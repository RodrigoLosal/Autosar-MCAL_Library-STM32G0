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

    static const char *InstanceName[] = {
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

    static const char *SpiApiName[] = {
    "Spi_Init()",
    "Spi_DeInit()",
    "Spi_WriteIB()",
    "Spi_AsyncTransmit()",
    "Spi_ReadIB()",
    "Spi_SetupEB()",
    "Spi_GetStatus()",
    "Spi_GetJobResult()",
    "Spi_GetSequenceResult()",
    "Spi_GetVersionInfo()",
    "Spi_SyncTransmit()",
    "Spi_GetHWUnitStatus()",
    "Spi_Cancel()",
    "Spi_SetAsyncMode()",
    };

    static const char *PwmApiName[] = {
    "Pwm_Init()",
    "Pwm_DeInit()",
    "Pwm_SetDutyCycle()",
    "Pwm_SetPeridoAndDuty()",
    "Pwm_SetOutputToIdle()",
    "Pwm_GetOutputState()",
    "Pwm_DisableNotification()",
    "Pwm_EnableNotification()",
    "Pwm_SetPowerState()",
    "Pwm_GetCurrentPowerState()",
    "Pwm_GetTargetPowerState()",
    "Pwm_PreparePowerState()",
    "Pwm_GetVersionInfo()",
    };

    static const char *GptApiName[] = {
    "Gpt_GetVersionInfo()",
    "Gpt_Init()",
    "Gpt_DeInit()",
    "Gpt_GetTimeElapsed()",
    "Gpt_GetTimeRemaining()",
    "Gpt_StartTimer()",
    "Gpt_StopTimer()",
    "Gpt_EnableNotification()",
    "Gpt_DisableNotification()",
    };

    static const char *DetApiName[] = {
    "Det_Init()",
    "Det_ReportError()",
    "Det_Start()",
    "Det_GetVersionInfo()",
    "Det_ReportRuntimeError()",
    "Det_ReportTransientFault()",
    };

    static const char *CanApiName[] = {
    "Can_Init()",
    "Can_DeInit()",
    "Can_ChangeBaudrate()",
    "Can_SetControllerMode()",
    "Can_DisableControllerInterrupts()",
    "Can_EnableControllerInterrupts()",
    "Can_CheckWakeup()",
    "Can_GetControllerState()",
    "Can_GetControllerErrorState()",
    "Can_GetControllerRxErrorCounter()",
    "Can_GetControllerTxErrorCounter()",
    "Can_Write()",
    "Can_MainFunction_Write()",
    "Can_MainFunction_Read()",
    "Can_MainFunction_BusOff()",
    "Can_MainFunction_Wakeup()",
    "Can_MainFunction_MODE()",
    "Can_GetVersionInfo()",
    "Can_GetCurrentTime()",
    "Can_EnableEgressTimeStamp()",
    "Can_GetEgressTimeStamp()",
    "Can_GetIngressTimeStamp()",
    };

    static const char *AdcApiName[] = {
    "Adc_Init()",
    "Adc_SetupResultBuffer()",
    "Adc_DeInit()",
    "Adc_StartGroupConversion()",
    "Adc_StopGroupConversion()",
    "Adc_ReadGroup()",
    "Adc_EnableHardwareTrigger()",
    "Adc_DisableHardwareTrigger()",
    "Adc_EnableGroupNotification()",
    "Adc_DisableGroupNotification()",
    "Adc_GetGroupStatus()",
    "Adc_GetStreamLastPointer()",
    "Adc_GetVersionInfo()",
    "Adc_SetPowerState()",
    "Adc_GetCurrentPowerState()",
    "Adc_GetTargetPowerState()",
    "Adc_PreparePowerState()",
    "Adc_Main_PowerTransitionManager()",
    };

    static const char *NvicApiName[] = {
    "CDD_Nvic_SetPriority()",
    "CDD_Nvic_GetPriority()",
    "CDD_Nvic_EnableIrq()",
    "CDD_Nvic_DisableIrq()",
    "CDD_Nvic_GetPendingIrq()",
    "CDD_Nvic_SetPendingIrq()",
    "CDD_Nvic_ClearPendingIrq()",
    "NMI_Handler",
    "HardFault_Handler",
    };

    static const char *McuApiName[] = {
    "Mcu_Init()",
    "Mcu_InitRamSection()",
    "Mcu_InitClock()",
    "Mcu_DistributePllClock()",
    "Mcu_GetPllStatus()",
    "Mcu_GetResetReason()",
    "Mcu_GetResetRawValue()",
    "Mcu_PerformReset()",
    "Mcu_SetMode()",
    "Mcu_GetVersionInfo()",
    "Mcu_GetRamState()",
    };

    static const char *DioApiName[] = {
    "Dio_ReadChannel()",
    "Dio_WriteChannel()",
    "Dio_ReadPort()",
    "Dio_WritePort()",
    "Dio_ReadChannelGroup()",
    "Dio_WriteChannelGroup()",
    "Dio_GetVersionInfo()",
    "Dio_FlipChannel()",
    "Dio_MaskedWritePort()",
    };

    static const char *PortApiName[] = {
    "Port_Init()",
    "Port_SetPinDirection()",
    "Port_SetPinMode()",
    "Port_GetVersionInfo()",
    "Port_RefreshPortDirection()",
    };

    static const char *FlsApiName[] = {
    "Fls_Init()",
    "Fls_Erase()",
    "Fls_Write()",
    "Fls_Cancel()",
    "Fls_GetStatus()",
    "Fls_GetJobResults()",
    "Fls_Read()",
    "Fls_Compare()",
    "Fls_SetMode()",
    "Fls_GetVersionInfo()",
    "Fls_BlankCheck()",
    };

    static const char *SpiErrorName[] = {
    "SPI_E_PARAM_CHANNEL",
    "SPI_E_PARAM_JOB",
    "SPI_E_PARAM_SEQ",
    "SPI_E_PARAM_LENGTH",
    "SPI_E_PARAM_UNIT",
    "SPI_E_PARAM_POINTER",
    "SPI_E_UNINIT",
    "SPI_E_ALREADY_INITIALIZED",
    };

    static const char *PwmErrorName[] = {
    "PWM_E_INIT_FAILED",
    "PWM_E_UNINIT",
    "PWM_E_PARAM_CHANNEL",
    "PWM_E_PERIOD_UNCHANGEABLE",
    "PWM_E_ALREADY_INITIALIZED",
    "PWM_E_PARAM_POINTER",
    "PWM_E_POWER_STATE_NOT_SUPPORTED",
    "PWM_E_TRANSITION_NOT_POSSIBLE",
    "PWM_E_PERIPHERAL_NOT_PREPARED",
    "PWM_E_NOT_DISENGAGED",
    };

    static const char *DetErrorName[] = {
    "DET_E_PARAM_POINTER",
    };

    static const char *CanErrorName[] = {
    "CAN_E_PARAM_POINTER",
    "CAN_E_PARAM_HANDLE",
    "CAN_E_PARAM_DATA_LENGTH",
    "CAN_E_PARAM_CONTROLLER",
    "CAN_E_UNINIT",
    "CAN_E_TRANSITION",
    "CAN_E_PARAM_BAUDRATE",
    "CAN_E_INIT_FAILED",
    "CAN_E_PARAM_LPDU",
    };

    static const char *AdcErrorName[] = {
    "ADC_E_UNINIT",
    "ADC_E_ALREADY_INITIALIZED",
    "ADC_E_PARAM_POINTER",
    "ADC_E_PARAM_GROUP",
    "ADC_E_WRONG_CONV_MODE",
    "ADC_E_WRONG_TRIGG_SRC",
    "ADC_E_NOTIF_CAPABILITY",
    "ADE_E_BUFFER_UNINIT",
    "ADE_E_POWER_STATE_NOT_SUPPORTED",
    "ADC_E_PERIPHERAL_NOT_PREPARED",
    "ADC_E_BUSY",
    "ADC_E_IDLE",
    "ADC_E_NOT_DISENGAGED",
    "ADC_E_TRANSITION_NOT_POSSIBLE",
    };

    static const char *NvicErrorName[] = {
    "NVIC_E_PARAM_IRQ",
    "NVIC_E_PARAM_PRIORITY",
    "NVIC_E_NMI_ENTRY",
    "NVIC_E_HARDFAULT_ENTRY",
    };

    static const char *McuErrorName[] = {
    "MCU_E_PARAM_CONFIG",
    "MCU_E_PARAM_CLOCK",
    "MCU_E_PARAM_MODE",
    "MCU_E_PARAM_RAMSECTION",
    "MCU_E_PLL_NOT_LOCKED",
    "MCU_E_UNINIT",
    "MCU_E_PARAM_POINTER",
    "MCU_E_INIT_FAILED",
    };

    static const char *DioErrorName[] = {
    "DIO_E_PARAM_INVALID_CHANNEL_ID",
    "DIO_E_PARAM_INVALID_PORT_ID",
    "DIO_E_PARAM_INVALID_GROUP",
    "DIO_E_PARAM_POINTER",
    };

    static const char *PortErrorName[] = {
    "PORT_E_PARAM_PIN",
    "PORT_E_DIRECTION_UNCHANGEABLE",
    "PORT_E_INIT_FAILED",
    "PORT_E_PARAM_INVALID_MODE",
    "PORT_E_MODE_UNCHANGEABLE",
    "PORT_E_UNINIT",
    "PORT_E_PARAM_POINTER",
    };

    static const char *GptErrorName[] = {
    "GPT_E_UNINIT",
    "GPT_E_ALREADY_INITIALIZED",
    "GPT_E_INIT_FAILED",
    "GPT_E_PARAM_CHANNEL",
    "GPT_E_PARAM_VALUE",
    "GPT_E_PARAM_POINTER",
    "GPT_E_PARAM_PREDEF_TIMER",
    "GPT_E_PARAM_MODE",
    };

    static const char *FlsErrorName[] = {
    "FLS_E_PARAM_CONFIG",
    "FLS_E_PARAM_ADDRESS",
    "FLS_E_PARAM_LENGTH",
    "FLS_E_PARAM_DATA",
    "FLS_E_UNINIT",
    "FLS_E_PARAM_POINTER",
    "FLS_E_ALREADY_INITIALIZED",
    };

    const char *api   = NULL;
    const char *error = NULL;
    if( ModuleId == 0 )
    {
        api   = SpiApiName[ ApiId ];
        error = SpiErrorName[ ErrorId ];
    }
    else if( ModuleId == 1 )
    {
        api   = PwmApiName[ ApiId ];
        error = PwmErrorName[ ErrorId ];
    }
    else if( ModuleId == 2 )
    {
        api   = GptApiName[ ApiId ];
        error = GptErrorName[ ErrorId ];
    }
    else if( ModuleId == 3 )
    {
        api   = DetApiName[ ApiId ];
        error = DetErrorName[ ErrorId ];
    }
    else if( ModuleId == 4 )
    {
        api   = CanApiName[ ApiId ];
        error = CanErrorName[ ErrorId ];
    }
    else if( ModuleId == 5 )
    {
        api   = AdcApiName[ ApiId ];
        error = AdcErrorName[ ErrorId ];
    }
    else if( ModuleId == 6 )
    {
        api   = NvicApiName[ ApiId ];
        error = NvicErrorName[ ErrorId ];
    }
    else if( ModuleId == 7 )
    {
        api   = McuApiName[ ApiId ];
        error = McuErrorName[ ErrorId ];
    }
    else if( ModuleId == 8 )
    {
        api   = DioApiName[ ApiId ];
        error = DioErrorName[ ErrorId ];
    }
    else if( ModuleId == 9 )
    {
        api   = PortApiName[ ApiId ];
        error = PortErrorName[ ErrorId ];
    }
    else if( ModuleId == 10 )
    {
        api   = FlsApiName[ ApiId ];
        error = FlsErrorName[ ErrorId ];
    }
    else
    {
        (void)printf( "Other error" );
    }

    (void)printf( "Module: %s\n", ModuleName[ ModuleId ] );
    (void)printf( "Instance: %s\n", InstanceName[ InstanceId ] );
    (void)printf( "Api: %s\n", api );
    (void)printf( "Error: %s\n", error );

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

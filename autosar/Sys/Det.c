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
    initialise_monitor_handles( );

    static const char *ModuleName[]   = { "PWM_MODULE_ID" }; // Tablas que traduzcan los defines a strings
    static const char *InstanceName[] = { "Pwm_DisableNotification" };
    static const char *ApiName[]      =
    {
        /*Pwm Api*/
        "PWM_ID_INIT",
        "PWM_ID_DE_INIT",
        "PWM_ID_SET_DUTY_CYCLE",
        "PWM_ID_SET_PERIOD_AND_DUTY",
        "PWM_ID_SET_OUTPUT_TO_IDLE",
        "PWM_ID_GET_OUTPUT_STATE",
        "PWM_ID_DISABLE_NOTIFICATION",
        "PWM_ID_ENABLE_NOTIFICATION",
        "PWM_ID_GET_CURRENT_POWER_STATE",
        "PWM_ID_GET_TARGET_POWER_STATE",
        "PWM_ID_PREPARE_POWER_STATE",
        "PWM_ID_GET_VERSION_INFO",
        /*MCU Api*/
        "MCU_ID_INIT",
        "MCU_ID_INIT_RAM",
        "MCU_ID_INIT_CLOCK",
        "MCU_ID_DISTRIBUTE_PLL_CLOCK",
        "MCU_ID_GET_PLL_STATUS",
        "MCU_ID_GET_RESET_REASON",
        "MCU_ID_GET_RESET_RAW_VALUE",
        "MCU_ID_PERFORM_RESET",
        "MCU_ID_SET_MODE",
        "MCU_ID_GET_VERSION_INFO",
        "MCU_ID_GET_RAM_STATE",
    };
    static const char *ErrorName[] =
    {
        /*Pwm Error*/
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
        /*Port Error*/
        "PORT_E_PARAM_PIN",
        "PORT_E_DIRECTION_UNCHANGEABLE",
        "PORT_E_INIT_FAILED",
        "PORT_E_PARAM_INVALID_MODE",
        "PORT_E_MODE_UNCHANGEABLE",
        "PORT_E_UNINIT",
        "PORT_E_PARAM_POINTER",
        /*MCU Error*/
        "MCU_E_PARAM_CONFIG",
        "MCU_E_PARAM_CLOCK",
        "MCU_E_PARAM_MODE",
        "MCU_E_PARAM_RAMSECTION",
        "MCU_E_PLL_NOT_LOCKED",
        "MCU_E_UNINIT",
        "MCU_E_PARAM_POINTER",
        "MCU_E_INIT_FAILED",
    };

    DetError ReportError;

    ReportError.Module   = ModuleName[ ModuleId ];
    ReportError.Instance = InstanceName[ InstanceId ];
    ReportError.Api      = ApiName[ ApiId ];
    ReportError.Error    = ErrorName[ ErrorId ];

    (void)printf( "ERROR: In %s in function %s Driver not initialized detected in %s. Error code: %s\n\r", ReportError.Module,
                  ReportError.Instance, ReportError.Api, ReportError.Error );

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

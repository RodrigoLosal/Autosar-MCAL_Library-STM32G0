/**
 * @file    Can.c
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The Can module provides services for initiating transmissions and calls the callback functions of
 * the CanIf module for notifying events, independently from the hardware. Furthermore, it provides
 * services to control the behavior and state of the CAN controllers that are belonging to the same
 * CAN Hardware Unit. Several CAN controllers can be controlled by a single Can module as long as
 * they belong to the same CAN Hardware Unit.
 */
#include "Std_Types.h"
#include "Can.h"
#include "Can_Arch.h"
#include "Bfx.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Can_Cfg.h */
#if CAN_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/* cppcheck-suppress misra-c2012-8.4 ; qualifier is declared at Can.h */
/* cppcheck-suppress misra-config ; this is declared at Can_Cfg.h */
/* clang-format off */
CAN_STATIC Can_ControllerStateType CtrlState[ CAN_NUMBER_OF_CONTROLLERS ] =
{
    CAN_CS_UNINIT,
    CAN_CS_UNINIT 
};
/* clang-format on */

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
/* clang-format off */
/* cppcheck-suppress misra-c2012-8.4 ; qualifier is declared at Can.h */
CAN_STATIC Can_HwUnit HwUnit =
{
    .HwUnitState     = CAN_CS_UNINIT,
    .Config          = &CanConfig,
    .ControllerState = CtrlState
};
/* clang-format on */

/**
 * @brief    **Can Initialization**
 *
 * This function initializes the module and the CAN controller. The CAN controller is initialized
 * according to the parameter Config.
 *
 * @param    Config Pointer to driver configuration
 *
 * @reqs    SWS_Can_00223, SWS_Can_00174, SWS_Can_00408
 */
void Can_Init( const Can_ConfigType *Config )
{
    if( ( HwUnit.HwUnitState != CAN_CS_UNINIT ) || ( HwUnit.ControllerState[ CAN_CONTROLLER_0 ] != CAN_CS_UNINIT ) || ( HwUnit.ControllerState[ CAN_CONTROLLER_1 ] != CAN_CS_UNINIT ) )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_Init shall raise the error CAN_E_TRANSITION if the driver is not in state
        CAN_UNINIT or the CAN controllers are not in state UNINIT */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_INIT, CAN_E_TRANSITION );
    }
    else
    {
        for( uint8 Controller = 0; Controller < CAN_NUMBER_OF_CONTROLLERS; Controller++ )
        {
            /*Init driver */
            Can_Arch_Init( &HwUnit, Config, Controller );
            /*set configured state*/
            HwUnit.ControllerState[ Controller ] = CAN_CS_STOPPED;
        }

        /*update Hardware init state*/
        HwUnit.HwUnitState = CAN_CS_READY;
        /* make the configuration available */
        HwUnit.Config = Config;
    }
}

/**
 * @brief    **Can Deinitialization**
 *
 * This function de-initializes the module.
 *
 * @reqs    SWS_Can_91002, SWS_Can_91011, SWS_Can_9101
 */
void Can_DeInit( void )
{
    if( ( HwUnit.HwUnitState != CAN_CS_READY ) || ( HwUnit.ControllerState[ CAN_CONTROLLER_0 ] != CAN_CS_STOPPED ) || ( HwUnit.ControllerState[ CAN_CONTROLLER_1 ] != CAN_CS_STOPPED ) )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_DeInit shall raise the error CAN_E_TRANSITION if the driver is not in state
        CAN_READY or any of the CAN controllers is in state STARTED */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_DE_INIT, CAN_E_TRANSITION );
    }
    else
    {
        for( uint8 Controller = 0; Controller < CAN_NUMBER_OF_CONTROLLERS; Controller++ )
        {
            /*Init driver */
            Can_Arch_DeInit( &HwUnit, Controller );
            /* Change CAN peripheral state */
            HwUnit.ControllerState[ Controller ] = CAN_CS_UNINIT;
        }

        /*change CAn hardware unit state to uninit*/
        HwUnit.HwUnitState = CAN_CS_UNINIT;
    }
}

#if CAN_SET_BAUDRATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Can Set Baudrate**
 *
 * This service shall set the baud rate configuration of the CAN controller. Depending on necessary
 * baud rate modifications the controller might have to reset.
 *
 * @param    Controller CAN controller for which the baud rate shall be set.
 * @param    BaudRateConfigID references a baud rate configuration by ID
 *
 * @retval  E_OK: Service request accepted, setting of (new) baud rate started E_NOT_OK: Service
 *          request not accepted
 *
 * @reqs    SWS_CAN_00491, SWS_Can_00492,SWS_Can_00493, SWS_Can_00494
 */
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_SetBaudrate shall raise the error CAN_E_UNINIT if the driver is not yet
        initialized.⌋*/
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_BAUDRATE, CAN_E_UNINIT );
    }
    else if( BaudRateConfigID >= HwUnit.Config->Controllers[ Controller ].BaudrateConfigsCount )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_SetBaudrate shall raise the error CAN_E_PARAM_BAUDRATE if the parameter
        BaudRateConfigID has an invalid value.⌋ */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_BAUDRATE, CAN_E_PARAM_BAUDRATE );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        the function Can_SetBaudrate shall raise the error CAN_E_PARAM_CONTROLLER if the parameter
        Controller is out of range.⌋*/
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_BAUDRATE, CAN_E_PARAM_CONTROLLER );
    }
    else
    {
        /* Set the new baud rate */
        ReturnValue = Can_Arch_SetBaudrate( &HwUnit, Controller, BaudRateConfigID );
    }

    return ReturnValue;
}
#endif

/**
 * @brief    **Can Set Controller Mode**
 *
 * This function performs software triggered state transitions of the CAN controller State machine.
 *
 * @param    Controller CAN controller for which the status shall be changed.
 * @param    Transition Transition value to request new state.
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 *
 * @reqs    SWS_Can_00230, SWS_Can_00198, SWS_Can_00199, SWS_Can_00200
 */
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        if the module is not yet initialized, the function Can_SetControllerMode shall raise development
        error CAN_E_UNINIT */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_CTRL_MODE, CAN_E_UNINIT );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter Controller is out of range, the function Can_SetControllerMode shall raise
        development error CAN_E_PARAM_CONTROLLER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_CTRL_MODE, CAN_E_PARAM_CONTROLLER );
    }
    else if( ( Transition < CAN_CS_STARTED ) || ( Transition > CAN_CS_SLEEP ) )
    {
        /* If development error detection for the Can module is enabled:
        if an invalid transition has been requested, the function Can_SetControllerMode shall raise
        the error CAN_E_TRANSITION */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_SET_CTRL_MODE, CAN_E_TRANSITION );
    }
    else
    {
        /* Set the new baud rate */
        ReturnValue = Can_Arch_SetControllerMode( &HwUnit, Controller, Transition );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Enable Controller Interrupts**
 *
 * This function enables all interrupts for this CAN controller.
 *
 * @param    Controller CAN controller for which interrupts shall be enabled.
 *
 * @reqs    SWS_Can_00232, SWS_Can_00209, SWS_Can_00210
 */
void Can_EnableControllerInterrupts( uint8 Controller )
{
    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_EnableControllerInterrupts shall raise the error CAN_E_UNINIT if the
        driver not yet initialized */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ENABLE_CTRL_INT, CAN_E_UNINIT );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_EnableControllerInterrupts shall raise the error CAN_E_PARAM_CONTROLLER if
        the parameter Controller is out of range */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ENABLE_CTRL_INT, CAN_E_PARAM_CONTROLLER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        Can_Arch_EnableControllerInterrupts( &HwUnit, Controller );
    }
}

/**
 * @brief    **Can Disable Controller Interrupts**
 *
 * This function disables all interrupts for this CAN controller.
 *
 * @param    Controller CAN controller for which interrupts shall be disabled.
 *
 * @reqs    SWS_Can_00231, SWS_Can_00205, SWS_Can_00206
 */
void Can_DisableControllerInterrupts( uint8 Controller )
{
    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_DisableControllerInterrupts shall raise the error CAN_E_UNINIT if the
        driver not yet initialized */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_DISABLE_CTRL_INT, CAN_E_UNINIT );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_DisableControllerInterrupts shall raise the error CAN_E_PARAM_CONTROLLER if
        the parameter Controller is out of range */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_DISABLE_CTRL_INT, CAN_E_PARAM_CONTROLLER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        Can_Arch_DisableControllerInterrupts( &HwUnit, Controller );
    }
}

/**
 * @brief    **Can wakeup check**
 *
 * This function checks if a wakeup has occurred for the given controller.
 *
 * @param    Controller CAN controller for which the wakeup shall be checked.
 *
 * @retval  E_OK: wakeup detected
 *          E_NOT_OK: no wakeup detected
 *
 * @reqs    SWS_Can_00360, SWS_Can_00362, SWS_Can_00363
 */
Std_ReturnType Can_CheckWakeup( uint8 Controller )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_CheckWakeup shall raise the error CAN_E_UNINIT if the driver is not yet
        initialized */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_CHECK_WAKEUP, CAN_E_UNINIT );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_CheckWakeup shall raise the error CAN_E_PARAM_CONTROLLER if the parameter
        Controller is out of range */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_CHECK_WAKEUP, CAN_E_PARAM_CONTROLLER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_CheckWakeup( &HwUnit, Controller );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Get Controller Error State**
 *
 * This function returns the error state of the CAN controller.
 *
 * @param    ControllerId CanIf ControllerId which is assigned to a CAN controller, which is
 *                          requested for ErrorState.
 * @param    ErrorStatePtr Pointer to a memory location, where the error state of the CAN
 *                          controller will be stored.
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 *
 * @reqs    SWS_Can_91004, SWS_Can_91005, SWS_Can_91006, SWS_Can_91007
 */
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        if the module is not yet initialized, the function Can_GetControllerErrorState shall raise
        development error CAN_E_UNINIT */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_ERR_STATE, CAN_E_UNINIT );
    }
    else if( ControllerId >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter ControllerId is out of range, the function Can_GetControllerErrorState shall
        raise development error CAN_E_PARAM_CONTROLLER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_ERR_STATE, CAN_E_PARAM_CONTROLLER );
    }
    else if( ErrorStatePtr == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter ErrorStatePtr is a null pointer, the function Can_GetControllerErrorState
        shall raise development error CAN_E_PARAM_POINTER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_ERR_STATE, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetControllerErrorState( &HwUnit, ControllerId, ErrorStatePtr );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Get Controller Mode**
 *
 * This service reports about the current status of the requested CAN controller.
 *
 * @param    Controller CAN controller for which the status shall be read.
 * @param    ControllerModePtr Pointer to a memory location, where the current mode of the CAN
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 *
 * @reqs    SWS_Can_91014, SWS_Can_91016, SWS_Can_91017, SWS_Can_91018
 */
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType *ControllerModePtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_GetControllerMode shall raise the error CAN_E_UNINIT and if the driver is
        not yet initialized.⌋ */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_MODE, CAN_E_UNINIT );
    }
    else if( Controller >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If parameter Controller of Can_GetControllerMode() has an invalid value, the CanDrv shall
        report development error code CAN_E_PARAM_CONTROLLER to the Det_ReportError service of the DET. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_MODE, CAN_E_PARAM_CONTROLLER );
    }
    else if( ControllerModePtr == NULL_PTR )
    {
        /* If parameter ControllerModePtr of Can_GetControllerMode() has an null pointer, the CanDrv
        shall report development error code CAN_E_PARAM_POINTER to the Det_ReportError service of
        the DET. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_MODE, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetControllerMode( &HwUnit, Controller, ControllerModePtr );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Get Controller Rx Error Counter**
 *
 * Returns the Rx error counter for a CAN controller. This value might not be available for all CAN
 * controllers, in which case E_NOT_OK would be returned. Please note that the value of the counter
 * might not be correct at the moment the API returns it, because the Rx counter is handled
 * asynchronously in hardware. Applications should not trust this value for any assumption about the
 * current bus state.
 *
 * @param    ControllerId CAN controller, whose current Rx error counter shall be acquired.
 * @param    RxErrorCounterPtr Pointer to a memory location, where the current Rx error counter
 *                              of the CAN controller will be stored.
 *
 * @retval  E_OK: Rx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 *
 * @reqs    SWS_Can_00511, SWS_Can_00512, SWS_Can_00513, SWS_Can_00514
 */
Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        if the module is not yet initialized, the function Can_GetControllerRxErrorCounter shall
        raise development error CAN_E_UNINIT and return E_NOT_OK. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_RX_ERR_CNT, CAN_E_UNINIT );
    }
    else if( ControllerId >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter ControllerId is out of range, the function Can_GetControllerRxErrorCounter
        shall raise development error CAN_E_PARAM_CONTROLLER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_RX_ERR_CNT, CAN_E_PARAM_CONTROLLER );
    }
    else if( RxErrorCounterPtr == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter RxErrorCounterPtr is a null pointer, the function
        Can_GetControllerRxErrorCounter shall raise development error CAN_E_PARAM_POINTER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_RX_ERR_CNT, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetControllerRxErrorCounter( &HwUnit, ControllerId, RxErrorCounterPtr );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Get Controller Tx Error Counter**
 *
 * Returns the Tx error counter for a CAN controller. This value might not be available for all CAN
 * controllers, in which case E_NOT_OK would be returned. Please note that the value of the counter
 * might not be correct at the moment the API returns it, because the Tx counter is handled
 * asynchronously in hardware. Applications should not trust this value for any assumption about the
 * current bus state.
 *
 * @param    ControllerId CAN controller, whose current Tx error counter shall be acquired.
 * @param    TxErrorCounterPtr Pointer to a memory location, where the current Tx error counter
 *
 * @retval  E_OK: Tx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Tx error counter not
 *
 * @reqs    SWS_Can_00516, SWS_Can_00517, SWS_Can_00518, SWS_Can_00519
 */
Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        if the module is not yet initialized, the function Can_GetControllerTxErrorCounter shall
        raise development error CAN_E_UNINIT */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_TX_ERR_CNT, CAN_E_UNINIT );
    }
    else if( ControllerId >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter ControllerId is out of range, the function Can_GetControllerTxErrorCounter
        shall raise development error CAN_E_PARAM_CONTROLLER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_TX_ERR_CNT, CAN_E_PARAM_CONTROLLER );
    }
    else if( TxErrorCounterPtr == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        if the parameter TxErrorCounterPtr is a null pointer, the function
        Can_GetControllerTxErrorCounter shall raise development error CAN_E_PARAM_POINTER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CTRL_TX_ERR_CNT, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetControllerTxErrorCounter( &HwUnit, ControllerId, TxErrorCounterPtr );
    }

    return ReturnValue;
}

#if CAN_GLOBAL_TIME_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Can Get Current Time**
 *
 * Returns a time value out of the HW registers according to the capability of the  HW
 *
 * @param    ControllerId CAN controller, whose current time shall be acquired.
 * @param    timeStampPtr Pointer to a memory location, where the current time of the CAN
 *
 * @retval  E_OK: successful
 *          E_NOT_OK: failed
 *
 * @reqs    SWS_CAN_91026, SWS_CAN_00521, SWS_CAN_00522, SWS_CAN_00523
 */
Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection is enabled:
        the function shall check that the service Can_Init was previously called. If the check
        fails, the function shall raise the development error CAN_E_UNINIT. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CURRENT_TIME, CAN_E_UNINIT );
    }
    else if( ControllerId >= CAN_NUMBER_OF_CONTROLLERS )
    {
        /* If development error detection is enabled:
        the function shall check the parameter ControllerId for being valid. If the check fails,
        the function shall raise the development error CAN_E_PARAM_CONTROLLER. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CURRENT_TIME, CAN_E_PARAM_CONTROLLER );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /* If development error detection is enabled:
        the function shall check the parameter timeStampPtr for being valid. If the check fails,
        the function shall raise the development error CAN_E_PARAM_POINTER.⌋()*/
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_CURRENT_TIME, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetCurrentTime( &HwUnit, ControllerId, timeStampPtr );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Enable Egress TimeStamp**
 *
 * Activates egress time stamping on a dedicated HTH. Some HW does store once the egress time stamp
 * marker and some HW needs it always before transmission. There will be no "disable" functionality,
 * due to the fact, that the message type is always "time stamped" by network design.
 *
 * @param    Hth information which HW-transmit handle shall be used for enabling the time stamp.
 *
 * @note    This is the smallest granularity which can be added for enabling the
 *          timestamp, at HTH level, without affecting the performance.
 *
 * @reqs    SWS_CAN_91025, SWS_CAN_00525, SWS_CAN_00526
 */
void Can_EnableEgressTimeStamp( Can_HwHandleType Hth )
{
    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection is enabled:
        the function shall check that the service Can_Init was previously called. If the check fails,
        the function shall raise the development error CAN_E_UNINIT. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ENABLE_EGRESS_TS, CAN_E_UNINIT );
    }
    else if( HwUnit.Config->Hohs[ Hth ].ObjectType != CAN_HOH_TYPE_TRANSMIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_Write shall raise the error CAN_E_PARAM_HANDLE if the parameter Hth is not
        a configured Hardware Transmit Handle */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ENABLE_EGRESS_TS, CAN_E_PARAM_HANDLE );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        Can_Arch_EnableEgressTimeStamp( &HwUnit, Hth );
    }
}

/**
 * @brief    **Can Get Egress TimeStamp**
 *
 * Reads back the egress time stamp on a dedicated message object. It needs to be
 * called within the TxConfirmation() function.
 *
 * @param    TxPduId Tx-PDU handle of CAN L-PDU that has been transmitted.
 * @param    Hth information which HW-transmit handle shall be used for reading the time stamp.
 * @param    timeStampPtr Pointer to a memory location where the time stamp value shall be stored.
 *
 * @retval  E_OK: success
 *          E_NOT_OK: failed to read time stamp.
 *
 * @reqs    SWS_CAN_91027, SWS_CAN_00529, SWS_CAN_00530, SWS_CAN_00531, SWS_CAN_00532
 *
 * @todo    need to define what is a invalid TxPduId
 */
Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection is enabled:
        the function shall check that the service Can_Init was previously called. If the check fails,
        the function shall raise the development error CAN_E_UNINIT. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_EGRESS_TS, CAN_E_UNINIT );
    }
    else if( TxPduId == 0 )
    {
        /* If development error detection is enabled:
        the function shall check the parameter TxPduId for being valid. If the check fails, the
        function shall raise the development error CAN_E_PARAM_LPDU */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_EGRESS_TS, CAN_E_PARAM_LPDU );
    }
    else if( HwUnit.Config->Hohs[ Hth ].ObjectType != CAN_HOH_TYPE_TRANSMIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_GetEgressTimeStamp shall raise the error CAN_E_PARAM_HANDLE if the parameter
        Hth is not a configured Hardware Transmit Handle */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_EGRESS_TS, CAN_E_PARAM_HANDLE );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /* If development error detection is enabled:
        the function shall check the parameter timeStampPtr for being valid. If the check fails, the
        function shall raise the development error CAN_E_PARAM_POINTER. */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_EGRESS_TS, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetEgressTimeStamp( &HwUnit, TxPduId, Hth, timeStampPtr );
    }

    return ReturnValue;
}

/**
 * @brief    **Can Get Ingress TimeStamp**
 *
 * Reads back the ingress time stamp on a dedicated message object. It needs to be
 * called within the RxIndication() function.
 *
 * @param    Hrh information which HW-receive handle shall be used for reading the time stamp.
 * @param    timeStampPtr Pointer to a memory location where the time stamp value shall be stored.
 *
 * @retval  E_OK: success
 *          E_NOT_OK: failed to read time stamp
 *
 * @reqs    SWS_CAN_91028, SWS_CAN_00535, SWS_CAN_00536, SWS_CAN_00537
 */
Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection is enabled:
        the function shall check that the service Can_Init was previously called. If the check fails,
        the function shall raise the development error CAN_E_UNINIT.⌋() */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_INGRESS_TS, CAN_E_UNINIT );
    }
    else if( HwUnit.Config->Hohs[ Hrh ].ObjectType != CAN_HOH_TYPE_RECEIVE )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_GetIngressTimeStamp shall raise the error CAN_E_PARAM_HANDLE if the parameter
        Hrh is not a configured Hardware Receive Handle */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_INGRESS_TS, CAN_E_PARAM_HANDLE );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /* If development error detection is enabled:
        the function shall check the parameter timeStampPtr for being valid. If the check fails, the
        function shall raise the development error CAN_E_PARAM_POINTER */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_INGRESS_TS, CAN_E_PARAM_POINTER );
    }
    else
    {
        /* Enable the slected interrupts to their corresponding interrupt lines */
        ReturnValue = Can_Arch_GetIngressTimeStamp( &HwUnit, Hrh, timeStampPtr );
    }

    return ReturnValue;
}
#endif

/**
 * @brief    **Can Write**
 *
 * This function is called by CanIf to pass a CAN message to CanDrv for transmission.
 *
 * @param    Hth information which HW-transmit handle shall be used for transmit. Implicitly this
 *                  is also the information about the controller to use because the Hth numbers
 *                  are unique inside one hardware unit.
 * @param    PduInfo Pointer to SDU user memory, Data Length and Identifier
 *
 * @retval  E_OK: Write command has been accepted
 *          E_NOT_OK: development error occurred
 *          CAN_BUSY: No TX hardware buffer available or pre-emptive call of Can_Write that can't be
 *          implemented re-entrant (see Can_ReturnType)
 *
 * @note    To detect if controller is in FD mode we use a custom field in Config structure instead
 *          of a valid CanControllerFdBaudrateConfig
 *
 * @reqs    SWS_Can_00233, SWS_Can_00216, SWS_Can_00217, SWS_Can_00219, SWS_Can_00218
 */
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    /*Validate DET error according to SWS_Can_00216, SWS_Can_00217, SWS_Can_00219 */
    if( HwUnit.HwUnitState == CAN_CS_UNINIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_Write shall raise the error CAN_E_UNINIT if the driver is not yet
        initialized */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_WRITE, CAN_E_UNINIT );
    }
    else if( HwUnit.Config->Hohs[ Hth ].ObjectType != CAN_HOH_TYPE_TRANSMIT )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_Write shall raise the error CAN_E_PARAM_HANDLE if the parameter Hth is not
        a configured Hardware Transmit Handle */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_WRITE, CAN_E_PARAM_HANDLE );
    }
    else if( PduInfo == NULL_PTR )
    {
        /* If development error detection for CanDrv is enabled:
        Can_Write() shall raise CAN_E_PARAM_POINTER if the parameter PduInfo is a null pointer */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_WRITE, CAN_E_PARAM_POINTER );
    }
    else
    {
        uint8 FdFlag  = Bfx_GetBit_u32u8_u8( PduInfo->id, 30u );
        uint32 FdMode = HwUnit.Config->Hohs[ Hth ].ControllerRef->FrameFormat;

        if( ( PduInfo->length > 64u ) || ( ( PduInfo->length > 8u ) && ( FdMode == CAN_FRAME_CLASSIC ) ) ||
            ( ( PduInfo->length > 8u ) && ( FdMode != CAN_FRAME_CLASSIC ) && ( FdFlag == STD_OFF ) ) )
        {
            /* The function Can_Write if development error detection for the CAN module is enabled shall
            raise the error CAN_E_PARAM_DATA_LENGTH:
             - If the length is more than 64 byte.
             - If the length is more than 8 byte and the CAN controller is not in CAN FD mode (no
               CanControllerFdBaudrateConfig).
             - If the length is more than 8 byte and the CAN controller is in CAN FD mode (valid
               CanControllerFdBaudrateConfig), but the CAN FD flag in Can_PduType->id is not set (refer
               CAN_MODULE_ID Type) */
            Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_WRITE, CAN_E_PARAM_DATA_LENGTH );
        }
        else
        {
            /* Enable the slected interrupts to their corresponding interrupt lines */
            ReturnValue = Can_Arch_Write( &HwUnit, Hth, PduInfo );
        }
    }

    return ReturnValue;
}

#if CAN_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief    **Can Get Version**
 *
 * This function returns the version information of this module.
 *
 * @param    versioninfo: Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Can_00224, SWS_Can_00177
 */
void Can_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    if( versioninfo == NULL_PTR )
    {
        /* If development error detection for the Can module is enabled:
        The function Can_GetVersionInfo shall raise the error CAN_E_PARAM_POINTER if the parameter
        versionInfo is a null pointer */
        Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_GET_VERSION_INFO, CAN_E_PARAM_POINTER );
    }
    else
    {
        versioninfo->moduleID         = CAN_MODULE_ID;
        versioninfo->vendorID         = CAN_VENDOR_ID;
        versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
    }
}
#endif

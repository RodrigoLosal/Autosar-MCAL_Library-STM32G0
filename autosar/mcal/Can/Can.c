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

/**
 * @brief    **Can Initialization**
 *
 * This function initializes the module and the CAN controller. The CAN controller is initialized
 * according to the parameter Config.
 *
 * @param    Config Pointer to driver configuration
 *
 * @reqs    SWS_Can_00223
 */
void Can_Init( const Can_ConfigType *Config )
{
    (void)Config;
}

/**
 * @brief    **Can Deinitialization**
 *
 * This function de-initializes the module.
 *
 * @reqs    SWS_Can_91002
 */
void Can_DeInit( void )
{
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
 * @reqs    SWS_CAN_00491
 */
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
    (void)Controller;
    (void)BaudRateConfigID;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_00230
 */
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition )
{
    (void)Controller;
    (void)Transition;

    return E_NOT_OK;
}

/**
 * @brief    **Can Enable Controller Interrupts**
 *
 * This function enables all interrupts for this CAN controller.
 *
 * @param    Controller CAN controller for which interrupts shall be enabled.
 *
 * @reqs    SWS_Can_00232
 */
void Can_EnableControllerInterrupts( uint8 Controller )
{
    (void)Controller;
}

/**
 * @brief    **Can Disable Controller Interrupts**
 *
 * This function disables all interrupts for this CAN controller.
 *
 * @param    Controller CAN controller for which interrupts shall be disabled.
 *
 * @reqs    SWS_Can_00231
 */
void Can_DisableControllerInterrupts( uint8 Controller )
{
    (void)Controller;
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
 * @reqs    SWS_Can_00360
 */
Std_ReturnType Can_CheckWakeup( uint8 Controller )
{
    (void)Controller;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_91004
 */
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    (void)ControllerId;
    (void)ErrorStatePtr;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_91014
 */
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType *ControllerModePtr )
{
    (void)Controller;
    (void)ControllerModePtr;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_00511
 */
Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    (void)ControllerId;
    (void)RxErrorCounterPtr;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_00516
 */
Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    (void)ControllerId;
    (void)TxErrorCounterPtr;

    return E_NOT_OK;
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
 * @reqs    SWS_CAN_91026
 */
Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType *timeStampPtr )
{
    (void)ControllerId;
    (void)timeStampPtr;

    return E_NOT_OK;
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
 * @reqs    SWS_CAN_91025
 */
void Can_EnableEgressTimeStamp( Can_HwHandleType Hth )
{
    (void)Hth;
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
 * @reqs    SWS_CAN_91027
 */
Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr )
{
    (void)TxPduId;
    (void)Hth;
    (void)timeStampPtr;

    return E_NOT_OK;
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
 * @reqs    SWS_CAN_91028
 */
Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr )
{
    (void)Hrh;
    (void)timeStampPtr;

    return E_NOT_OK;
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
 * @reqs    SWS_Can_00233
 */
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    (void)Hth;
    (void)PduInfo;

    return E_NOT_OK;
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
    (void)versioninfo;
}
#endif

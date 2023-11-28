/**
 * @file CanIf.c
 * @brief Header file for the CAN interface.
 * @author Diego Perez
 *
 * The CAN Interface module provides CAN communication abstracted access to the CAN Driver and CAN
 * Transceiver Driver services for control and supervision of the CAN network. The CAN Interface
 * forwards downwards the status change requests from the CAN State Manager to the lower layer CAN
 * device drivers, and upwards the CAN Driver / CAN Transceiver Driver events are forwarded by the
 * CAN Interface module to e.g. the corresponding NM module.
 */
#include "Std_Types.h"
#include "Can.h"
#include "CanIf.h"
#include "CanIf_Can.h"

/**
 * @brief Initializes the CAN interface.
 *
 * This service Initializes internal and external interfaces of the CAN Interface for the further processing.
 *
 * @param[in] ConfigPtr Pointer to the CAN Interface configuration structure.
 *
 * @reqs    SWS_CANIF_00001
 */
void CanIf_Init( const CanIf_ConfigType *ConfigPtr )
{
    (void)ConfigPtr;
}

/**
 * @brief Deinitializes the CAN interface.
 *
 * De-initializes the CanIf module. Caller of the CanIf_DeInit() function has to be sure there are no on-going
 * transmissions/receptions, nor any pending transmission confirmations.
 *
 * @reqs    SWS_CANIF_91002
 */
void CanIf_DeInit( void )
{
}

/**
 * @brief Sets the CAN controller mode.
 *
 * This service calls the corresponding CAN Driver service for changing of the CAN controller mode.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[in] ControllerMode Requested mode transition.
 *
 * @return  E_OK: Controller mode request has been accepted
 *          E_NOT_OK: Controller mode request has not been accepted
 *
 * @reqs    SWS_CANIF_00003
 */
Std_ReturnType CanIf_SetControllerMode( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    (void)ControllerId;
    (void)ControllerMode;
    return E_NOT_OK;
}

/**
 * @brief Gets the CAN controller mode.
 *
 * This service calls the corresponding CAN Driver service for getting the current CAN controller mode.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[out] ControllerModePtr Pointer to a memory location, where the current mode of the CAN
 *                               controller will be stored.
 *
 * @return  E_OK: Controller mode request has been accepted
 *          E_NOT_OK: Controller mode request has not been accepted
 *
 * @reqs    SWS_CANIF_00004
 */
Std_ReturnType CanIf_GetControllerMode( uint8 ControllerId, Can_ControllerStateType *ControllerModePtr )
{
    (void)ControllerId;
    (void)ControllerModePtr;
    return E_NOT_OK;
}

/**
 * @brief Gets the CAN controller error state.
 *
 * This service calls the corresponding CAN Driver service for getting the current CAN controller
 * error state.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[out] ErrorStatePtr Pointer to a memory location, where the current error state of the
 *                          CAN controller will be stored.
 *
 * @return  E_OK: Controller mode request has been accepted
 *          E_NOT_OK: Controller mode request has not been accepted
 *
 * @reqs    SWS_CANIF_00005
 */
Std_ReturnType CanIf_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    (void)ControllerId;
    (void)ErrorStatePtr;
    return E_NOT_OK;
}

/**
 * @brief Transmits a CAN L-PDU.
 *
 * This service calls the corresponding CAN Driver service for transmission of a CAN L-PDU.
 *
 * @param[in] TxPduId Identifier of the PDU to be transmitted
 * @param[in] PduInfoPtr Length of and pointer to the PDU data and pointer to MetaData.
 *
 * @return  E_OK: Transmit request has been accepted
 *          E_NOT_OK: Transmit request has not been accepted
 *
 * @reqs    SWS_CANIF_00005
 */
Std_ReturnType CanIf_Transmit( PduIdType TxPduId, const PduInfoType *PduInfoPtr )
{
    (void)TxPduId;
    (void)PduInfoPtr;
    return E_NOT_OK;
}

#if CANIF_PUBLIC_READ_RX_PDU_DATA == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Reads the received data of a CAN L-PDU from the receive buffer.
 *
 * This service provides the Data Length and the received data of the requested CanIfRxSduId to the
 * calling upper layer.
 *
 * @param[in] CanIfRxSduId Receive L-SDU handle specifying the corresponding CAN L-SDU ID and implicitly
 *                          the CAN Driver instance as well as the corresponding CAN controller device.
 * @param[out] CanIfRxInfoPtr Contains the length (SduLength) of the received PDU, a pointer to a buffer
 *                              (SduDataPtr) containing the PDU, and the MetaData related to this PDU.
 *
 * @return  E_OK: Request for L-SDU data has been accepted
 *          E_NOT_OK: No valid data has been received
 *
 * @reqs    SWS_CANIF_00194
 */
Std_ReturnType CanIf_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType *CanIfRxInfoPtr )
{
    (void)CanIfRxSduId;
    (void)CanIfRxInfoPtr;
    return E_NOT_OK;
}
#endif

#if CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Read the Tx notification status of a CAN L-PDU.
 *
 * This service returns the confirmation status (confirmation occurred or not) of a specific static or
 * dynamic CAN Tx L-PDU, requested by the CanIfTxSduId.
 *
 * @param[in] CanIfTxSduId L-SDU handle to be transmitted. This handle specifies the corresponding CAN
 *                          L-SDU ID and implicitly the CAN Driver instance as well as the corresponding
 *                          CAN controller device.
 *
 * @return  Current confirmation status of the corresponding CAN Tx L-PDU.
 *
 * @reqs    SWS_CANIF_00202
 */
CanIf_NotifStatusType CanIf_ReadTxNotifStatus( PduIdType CanIfTxSduId )
{
    (void)CanIfTxSduId;
    return CANIF_NO_NOTIFICATION;
}
#endif

#if CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Sets the requested PDU mode.
 *
 * This service returns the indication status (indication occurred or not) of a specific CAN Rx L-PDU,
 * requested by the CanIfRxSduId.
 *
 * @param[in] CanIfRxSduId Receive L-SDU handle specifying the corresponding CAN L-SDU ID and implicitly
 *                          the CAN Driver instance as well as the corresponding CAN controller device.
 *
 * @return  Current indication status of the corresponding CAN Rx L-PDU.
 *
 * @reqs    SWS_CANIF_00230
 */
CanIf_NotifStatusType CanIf_ReadRxNotifStatus( PduIdType CanIfRxSduId )
{
    (void)CanIfRxSduId;
    return CANIF_NO_NOTIFICATION;
}
#endif

/**
 * @brief Sets the requested PDU mode.
 *
 * This service sets the requested mode at the L-PDUs of a predefined logical PDU channel.
 *
 * @param[in] ControllerId All PDUs of the own ECU connected to the corresponding CanIf ControllerId,
 *                          which is assigned to a physical CAN controller are addressed.
 * @param[in] PduModeRequest Requested PDU mode change.
 *
 * @return  E_OK: Request for mode transition has been accepted.
 *          E_NOT_OK: Request for mode transition has not been accepted.
 *
 * @reqs    SWS_CANIF_00008
 */
Std_ReturnType CanIf_SetPduMode( uint8 ControllerId, CanIf_PduModeType PduModeRequest )
{
    (void)ControllerId;
    (void)PduModeRequest;
    return E_NOT_OK;
}

/**
 * @brief Gets the requested PDU mode.
 *
 * This service returns the requested mode of the L-PDUs of a predefined logical PDU channel.
 *
 * @param[in] ControllerId All PDUs of the own ECU connected to the corresponding CanIf ControllerId,
 *                          which is assigned to a physical CAN controller are addressed.
 * @param[out] PduModePtr Pointer to a memory location, where the requested PDU mode is stored.
 *
 * @return  E_OK: PDU mode request has been accepted
 *          E_NOT_OK: PDU mode request has not been accepted
 *
 * @reqs    SWS_CANIF_00009
 */
Std_ReturnType CanIf_GetPduMode( uint8 ControllerId, CanIf_PduModeType *PduModePtr )
{
    (void)ControllerId;
    (void)PduModePtr;
    return E_NOT_OK;
}

#if CANIF_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Gets the version information of the CAN interface.
 *
 * This service returns the version information of this module.
 *
 * @param[out] VersionInfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_CANIF_00158
 */
void CanIf_GetVersionInfo( Std_VersionInfoType *VersionInfo )
{
    (void)VersionInfo;
}
#endif

/**
 * @brief Sets the CAN controller baudrate.
 *
 * This service reconfigures the corresponding CAN identifier of the requested CAN L-PDU.
 *
 * @param[in] CanIfTxSduId L-SDU handle to be transmitted. This handle specifies the corresponding CAN
 *                         L-SDU ID and implicitly the CAN Driver instance as well as the corresponding
 *                        CAN controller device.
 * @param[in] CanId Standard/Extended CAN ID of CAN L-SDU that shall be transmitted as FD or conventional
 *                  CAN frame.
 *
 * @reqs    SWS_CANIF_00189
 */
void CanIf_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId )
{
    (void)CanIfTxSduId;
    (void)CanId;
}

/**
 * @brief Gets the CAN controller Tx confirmation state.
 *
 * This service reports, if any TX confirmation has been done for the whole CAN controller since the
 * last CAN controller start.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 *
 * @return  Combined TX confirmation status for all TX PDUs of the CAN controller
 *
 * @reqs    SWS_CANIF_00734
 */
CanIf_NotifStatusType CanIf_GetTxConfirmationState( uint8 ControllerId )
{
    (void)ControllerId;
    return CANIF_NO_NOTIFICATION;
}

#if CANIF_SET_BAUDRATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Sets the CAN controller baudrate.
 *
 * This service shall set the baud rate configuration of the CAN controller. Depending on necessary
 * baud rate modifications the controller might have to reset.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[in] BaudRateConfigID Baud rate configuration ID
 *
 * @return  E_OK: Controller mode request has been accepted
 *          E_NOT_OK: Controller mode request has not been accepted
 *
 * @reqs    SWS_CANIF_00867
 */
Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID )
{
    (void)ControllerId;
    (void)BaudRateConfigID;
    return E_NOT_OK;
}
#endif

/**
 * @brief Gets the CAN controller Rx error counter.
 *
 * This service calls the corresponding CAN Driver service for obtaining the Rx error counter of
 * the CAN controller.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[out] RxErrorCounterPtr Pointer to a memory location, where the current Rx error counter
 *
 * @return  E_OK: Rx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 *
 * @reqs    SWS_CANIF_91003
 */
Std_ReturnType CanIf_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    (void)ControllerId;
    (void)RxErrorCounterPtr;
    return E_NOT_OK;
}

/**
 * @brief Gets the CAN controller Tx error counter.
 *
 * This service calls the corresponding CAN Driver service for obtaining the Tx error counter of
 * the CAN controller.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[out] TxErrorCounterPtr Pointer to a memory location, where the current Tx error counter
 *
 * @return  E_OK: Rx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 *
 * @reqs    SWS_CANIF_91004
 */
Std_ReturnType CanIf_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    (void)ControllerId;
    (void)TxErrorCounterPtr;
    return E_NOT_OK;
}

#if CANIF_BUS_MIRRORING_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Enables/Disables the bus mirroring feature.
 *
 * Enables or disables mirroring for a CAN controller.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[in] MirroringActive TRUE: Mirror_ReportCanFrame will be called for each
 *                          frame received or transmitted on the given controller.
 *                          FALSE: Mirror_ReportCanFrame will not be called for the
 *                          given controller.
 *
 * @return  E_OK: Mirroring mode was changed.
 *          E_NOT_OK: Wrong ControllerId, or mirroring globally disabled
 *
 * @reqs    SWS_CANIF_91005
 */
Std_ReturnType CanIf_EnableBusMirroring( uint8 ControllerId, boolean MirroringActive )
{
    (void)ControllerId;
    (void)MirroringActive;
    return E_NOT_OK;
}
#endif

#if CANIF_GLOBAL_TIME_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
/**
 * @brief Gets the current time.
 *
 * This service calls the corresponding CAN Driver service to retrieve the current time value out
 * of the HW registers.
 *
 * @param[in] Controller CAN controller for which the status shall be changed.
 * @param[out] timeStampPtr Pointer to a memory location, where the current time value will be stored.
 *
 * @return  E_OK: successful
 *          E_NOT_OK: failed
 *
 * @reqs    SWS_CANIF_91014
 */
Std_ReturnType CanIf_GetCurrentTime( uint8 Controller, Can_TimeStampType *timeStampPtr )
{
    (void)Controller;
    (void)timeStampPtr;
    return E_NOT_OK;
}

/**
 * @brief Enables the egress time stamp feature.
 *
 * This service calls the corresponding CAN Driver service to activate egress time stamping on a
 * dedicated message object.
 *
 * @param[in] TxPduId L-PDU handle of CAN L-PDU for which the time stamping shall be enabled
 *
 * @reqs    SWS_CANIF_91011
 */
void CanIf_EnableEgressTimeStamp( PduIdType TxPduId )
{
    (void)TxPduId;
}

/**
 * @brief Gets the egress time stamp.
 *
 * This service calls the corresponding CAN Driver service to read back the egress time stamp on a
 * dedicated message object. It needs to be called within the TxConfirmation() function.
 *
 * @param[in] TxPduId L-PDU handle of CAN L-PDU for which the time stamp shall be returned.
 * @param[out] timeStampPtr Pointer to a memory location, where the time stamp value will be stored.
 *
 * @return  E_OK: successful
 *         E_NOT_OK: failed
 *
 * @reqs    SWS_CANIF_91012
 */
Std_ReturnType CanIf_GetEgressTimeStamp( PduIdType TxPduId, Can_TimeStampType *timeStampPtr )
{
    (void)TxPduId;
    (void)timeStampPtr;
    return E_NOT_OK;
}

/**
 * @brief Gets the ingress time stamp.
 *
 * This service calls the corresponding CAN Driver service to reads back the ingress time stamp on
 * a dedicated message object. It needs to be called within the RxIndication() function.
 *
 * @param[in] RxPduId ID of the received I-PDU for which the time stamp shall be returned.
 * @param[out] timeStampPtr Pointer to a memory location, where the time stamp value will be stored.
 *
 * @return  E_OK: successful
 *         E_NOT_OK: failed
 *
 * @reqs    SWS_CANIF_91012
 */
Std_ReturnType CanIf_GetIngressTimeStamp( PduIdType RxPduId, Can_TimeStampType *timeStampPtr )
{
    (void)RxPduId;
    (void)timeStampPtr;
    return E_NOT_OK;
}
#endif

/**
 * @brief Handles the transmit confirmation.
 *
 * This service confirms a previously successfully processed transmission of a CAN TxPDU.
 *
 * @param[in] CanTxPduId ID of the successfully transmitted Tx L-PDU
 *
 * @reqs    SWS_CANIF_00007
 */
void CanIf_TxConfirmation( PduIdType CanTxPduId )
{
    (void)CanTxPduId;
}

/**
 * @brief Handles the received CAN frame.
 *
 * This service indicates a successful reception of a received CAN Rx L-PDU to the CanIf after
 * passing all filters and validation checks.
 *
 * @param[in] Mailbox Identifies the HRH and its corresponding CAN Controller
 * @param[in] PduInfoPtr Pointer to the received L-PDU
 *
 * @reqs    SWS_CANIF_00006
 */
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr )
{
    (void)Mailbox;
    (void)PduInfoPtr;
}

/**
 * @brief Handles the bus-off event.
 *
 * This service indicates a Controller BusOff event referring to the corresponding CAN Controller
 * with the abstract CanIf ControllerId.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_CANIF_00218
 */
void CanIf_ControllerBusOff( uint8 ControllerId )
{
    (void)ControllerId;
}

/**
 * @brief Controller mode indication.
 *
 * This service indicates a controller state transition referring to the corresponding CAN controller
 * with the abstract CanIf ControllerId.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[in] ControllerMode New controller mode.
 *
 * @reqs    SWS_CANIF_00699
 */
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    (void)ControllerId;
    (void)ControllerMode;
}

/**
 * @brief Signal the error state of the CAN controller.
 *
 * The function derives the ErrorCounterTreshold from RxErrorCounter/ TxErrorCounter values
 * and reports it to the IdsM as security event CANIF_SEV_ERRORSTATE_PASSIVE to the IdsM.
 * It also prepares the context data for the respective security event.
 *
 * @param[in] ControllerId Abstracted CanIf ControllerId which is assigned to a CAN
 *                          controller.
 * @param[in] RxErrorCounter Value of the Rx error counter
 * @param[in] TxErrorCounter Value of the Tx error counter
 *
 * @reqs    SWS_CANIF_91008
 */
void CanIf_ControllerErrorStatePassive( uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter )
{
    (void)ControllerId;
    (void)RxErrorCounter;
    (void)TxErrorCounter;
}

/**
 * @brief Signal the error notification of the CAN controller.
 *
 * The function shall derive the bus error source rx or tx from the parameter CanError and report
 * the bus error as security event CANIF_SEV_TX_ERROR_DETECTED or CANIF_SEV_RX_
 * ERROR_DETECTED. It also prepares the context data for the respective security event.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 * @param[in] CanError Reported CAN error
 *
 * @reqs    SWS_CANIF_91009
 */
void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType CanError )
{
    (void)ControllerId;
    (void)CanError;
}

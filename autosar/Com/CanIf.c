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
#include "Bfx.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Can_Cfg.h */
#if CAN_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportError( ModuleId, InstanceId, ApiId, ErrorId )        (void)0

/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportRuntimeError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

/**
 * @brief Pointer to the configuration structure.
 */
CAN_STATIC const CanIf_ConfigType *LocalConfigPtr = NULL_PTR;

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
    LocalConfigPtr = ConfigPtr;
}

/**
 * @brief Deinitializes the CAN interface.
 *
 * De-initializes the CanIf module. Caller of the CanIf_DeInit() function has to be sure there are no on-going
 * transmissions/receptions, nor any pending transmission confirmations.
 *
 * @reqs    SWS_CANIF_91002, SWS_CANIF_00661
 */
void CanIf_DeInit( void )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_DE_INIT, CANIF_E_UNINIT );
    }
    else
    {
        /* De init module */
        LocalConfigPtr = NULL_PTR;
    }
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
 * @reqs    SWS_CANIF_00003, SWS_CANIF_00661, SWS_CANIF_00311, SWS_CANIF_00774
 */
Std_ReturnType CanIf_SetControllerMode( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_CTRL_MODE, CANIF_E_UNINIT );
    }
    else if( ControllerId > LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_SetControllerMode() has an invalid value, the CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_SetControllerMode() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_CTRL_MODE, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( ( ControllerMode < CAN_CS_STARTED ) || ( ControllerMode > CAN_CS_SLEEP ) )
    {
        /*If parameter ControllerMode of CanIf_SetControllerMode() has an invalid value (not
        CAN_CS_STARTED, CAN_CS_SLEEP or CAN_CS_STOPPED), the CanIfshall report development error
        code CANIF_E_PARAM_CTRLMODE to the Det_ReportError service of the DET module, when
        CanIf_SetControllerMode() is called */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_CTRL_MODE, CANIF_E_PARAM_CTRLMODE );
    }
    else
    {
        /* Set controller mode */
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00004, SWS_CANIF_00661, SWS_CANIF_00313, SWS_CANIF_00656
 */
Std_ReturnType CanIf_GetControllerMode( uint8 ControllerId, Can_ControllerStateType *ControllerModePtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_MODE, CANIF_E_UNINIT );
    }
    else if( ControllerId > LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_SetControllerMode() has an invalid value, the CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_SetControllerMode() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_MODE, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( ControllerModePtr == NULL_PTR )
    {
        /*If parameter ControllerModePtr of CanIf_GetControllerMode() has an invalid value (NULL_PTR),
        the CanIf shall report development error code CANIF_E_PARAM_POINTER to the Det_ReportError
        service of the DET module, when CanIf_GetControllerMode() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_MODE, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get controller mode */
        (void)ControllerModePtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00005, SWS_CANIF_00661, SWS_CANIF_00898, SWS_CANIF_00899
 */
Std_ReturnType CanIf_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_ERR_STATE, CANIF_E_UNINIT );
    }
    else if( ControllerId > LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_GetControllerErrorState() has an invalid value, the
        CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET, when CanIf_GetControllerErrorState() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_ERR_STATE, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( ErrorStatePtr == NULL_PTR )
    {
        /*If parameter ErrorStatePtr of CanIf_GetControllerErrorState() has an invalid value (NULL_PTR),
        the CanIf shall report development error code CANIF_E_PARAM_POINTER to the Det_ReportError
        service of the DET module, when CanIf_GetControllerErrorState() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_ERR_STATE, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get controller error state */
        (void)ErrorStatePtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00005, SWS_CANIF_00661, SWS_CANIF_00319, SWS_CANIF_00320, SWS_CANIF_00893
 */
Std_ReturnType CanIf_Transmit( PduIdType TxPduId, const PduInfoType *PduInfoPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TRANSMIT, CANIF_E_UNINIT );
    }
    else if( TxPduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If parameter TxPduId of CanIf_Transmit() has an invalid value, CanIf shall report
        development error code CANIF_E_INVALID_TXPDUID to the Det_ReportError service of the DET, when
        CanIf_Transmit() is called */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TRANSMIT, CANIF_E_INVALID_TXPDUID );
    }
    else if( PduInfoPtr == NULL_PTR )
    {
        /*If parameter PduInfoPtr of CanIf_Transmit() has an in valid value, CanIf shall report
        development error code CANIF_E_PARAM_POINTER to*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TRANSMIT, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /*Get the bit indicating if the message is in FD format, this will extracted from
        the configuration TxPduIds array where we gonna extract FdFlag*/
        // if( ( ( PduInfoPtr->SduLength > 8 ) && ( FdFlag == STD_OFF ) ) || ( ( PduInfoPtr->SduLength > 64 ) && ( FdFlag == STD_ON ) ) )

        if( PduInfoPtr->SduLength > 8 ) /*this is momentary while we define the TxPduIds arrays*/
        {
            /*When CanIf_Transmit() is called with PduInfoPtr->SduLength exceeding the maximum length
            of the PDU referenced by TxPduId:
                • SduLength > 8 if the Can_IdType indicates a classic CAN frame
                • SduLength > 64 if the Can_IdType indicates a CAN FD frame
            CanIf shall report runtime error code CANIF_E_DATA_LENGTH_MISMATCH to the
            Det_ReportRuntimeError() service of the DET*/
            Det_ReportRuntimeError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TRANSMIT, CANIF_E_DATA_LENGTH_MISMATCH );
        }
        else
        {
            /* Transmit */
            RetVal = E_OK;
        }
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00194, SWS_CANIF_00661, SWS_CANIF_00324, SWS_CANIF_00325, SWS_CANIF_00326
 */
Std_ReturnType CanIf_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType *CanIfRxInfoPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_RX_PDU_DATA, CANIF_E_UNINIT );
    }
    else if( CanIfRxSduId >= LocalConfigPtr->MaxRxPduCfg )
    {
        /*If parameter CanIfRxSduId of CanIf_ReadRxPduData() has an invalid value, e.g. not configured
        to be stored within CanIf via CanIfRxPduReadData, CanIf shall report development error code
        CANIF_E_INVALID_RXPDUID to the Det_ReportError service of the DET, when CanIf_ReadRxPduData()
        is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_RX_PDU_DATA, CANIF_E_INVALID_RXPDUID );
    }
    else if( CanIfRxInfoPtr == NULL_PTR )
    {
        /*If parameter CanIfRxInfoPtr of CanIf_ReadRxPduData() has an invalid value, CanIf shall
        report development error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the
        DET module, when CanIf_ReadRxPduData() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_RX_PDU_DATA, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Read Rx PDU data */
        (void)CanIfRxInfoPtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00202, SWS_CANIF_00661, SWS_CANIF_00331
 */
CanIf_NotifStatusType CanIf_ReadTxNotifStatus( PduIdType CanIfTxSduId )
{
    CanIf_NotifStatusType RetVal = CANIF_NO_NOTIFICATION;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_TX_NOTIF_STATUS, CANIF_E_UNINIT );
    }
    else if( CanIfTxSduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If parameter CanIfTxSduId of CanIf_ReadTxNotifStatus() is out of range or if no status
        information was configured for this CAN Tx L-SDU, CanIf shall report development error code
        CANIF_E_INVALID_TXPDUID to the Det_ReportError service of the DET when CanIf_ReadTxNotifStatus()
        is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_TX_NOTIF_STATUS, CANIF_E_INVALID_TXPDUID );
    }
    else
    {
        /* Read Tx notification status */
        RetVal = CANIF_TX_RX_NOTIFICATION;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00230, SWS_CANIF_00661, SWS_CANIF_00336
 */
CanIf_NotifStatusType CanIf_ReadRxNotifStatus( PduIdType CanIfRxSduId )
{
    CanIf_NotifStatusType RetVal = CANIF_NO_NOTIFICATION;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_RX_NOTIF_STATUS, CANIF_E_UNINIT );
    }
    else if( CanIfRxSduId >= LocalConfigPtr->MaxRxPduCfg )
    {
        /*If parameter CanIfRxSduId of CanIf_ReadRxNotifStatus() is out of range or if status for
        CanRxPduId was requested whereas CanIfRxPduReadData is disabled or if no status information
        was configured for this CAN Rx L-SDU, CanIf shall report development error code CANIF_E_INVALID_RXPDUID
        to the Det_ReportError service of the DET, when CanIf_ReadRxNotifStatus() is called */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_READ_RX_NOTIF_STATUS, CANIF_E_INVALID_RXPDUID );
    }
    else
    {
        /* Read Rx notification status */
        RetVal = CANIF_TX_RX_NOTIFICATION;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00008, SWS_CANIF_00661, SWS_CANIF_00341, SWS_CANIF_00860, SWS_CANIF_00874
 */
Std_ReturnType CanIf_SetPduMode( uint8 ControllerId, CanIf_PduModeType PduModeRequest )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_PDU_MODE, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If CanIf_SetPduMode() is called with invalid ControllerId, CanIf shall report development
        error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_PDU_MODE, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( PduModeRequest > CANIF_ONLINE )
    {
        /*If CanIf_SetPduMode() is called with invalid PduModeRequest, CanIf shall report development
        error code CANIF_E_PARAM_PDU_MODE to the Det_ReportError service of the DET module.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_PDU_MODE, CANIF_E_PARAM_PDU_MODE );
    }
    else
    {
        /* Set PDU mode */
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00009, SWS_CANIF_00661, SWS_CANIF_00346, SWS_CANIF_00657
 */
Std_ReturnType CanIf_GetPduMode( uint8 ControllerId, CanIf_PduModeType *PduModePtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_PDU_MODE, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If CanIf_GetPduMode() is called with invalid ControllerId, CanIf shall report development
        error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_PDU_MODE, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( PduModePtr == NULL_PTR )
    {
        /*If CanIf_GetPduMode() is called with invalid PduModePtr, CanIf shall report development
        error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET module.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_PDU_MODE, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get PDU mode */
        (void)PduModePtr;
        RetVal = E_OK;
    }

    return RetVal;
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
    if( VersionInfo == NULL_PTR )
    {
        /*If parameter VersionInfo of CanIf_GetVersionInfo() has an invalid value (NULL_PTR), the
        CanIf shall report development error code CANIF_E_PARAM_POINTER to the Det_ReportError
        service of the DET module, when CanIf_GetVersionInfo() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_VERSION_INFO, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get version info */
        VersionInfo->vendorID         = CANIF_VENDOR_ID;
        VersionInfo->moduleID         = CANIF_MODULE_ID;
        VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION;
    }
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
 * @reqs    SWS_CANIF_00189, SWS_CANIF_00661, SWS_CANIF_00352, SWS_CANIF_00353
 */
void CanIf_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_DYNAMIC_TX_ID, CANIF_E_UNINIT );
    }
    else if( CanIfTxSduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If parameter CanIfTxSduId of CanIf_SetDynamicTxId() has an invalid value, CanIf shall report
        development error code CANIF_E_INVALID_TXPDUID to the Det_ReportError service of the DET module,
        when CanIf_SetDynamicTxId() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_DYNAMIC_TX_ID, CANIF_E_INVALID_TXPDUID );
    }
    else if( CanId == 0u ) /*need to figure it out how to detect an invalid Id*/
    {
        /*If parameter CanId of CanIf_SetDynamicTxId() has an invalid value, CanIf shall report development
        error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET module, when
        CanIf_SetDynamicTxId() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_DYNAMIC_TX_ID, CANIF_E_PARAM_CANID );
    }
    else
    {
        /* Set dynamic Tx ID */
    }
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
 * @reqs    SWS_CANIF_00734, SWS_CANIF_00661, SWS_CANIF_00736
 */
CanIf_NotifStatusType CanIf_GetTxConfirmationState( uint8 ControllerId )
{
    CanIf_NotifStatusType RetVal = CANIF_NO_NOTIFICATION;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_TX_CONFIRM_STATE, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_GetTxConfirmationState() has an invalid value, the CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_GetTxConfirmationState() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_TX_CONFIRM_STATE, CANIF_E_PARAM_CONTROLLERID );
    }
    else
    {
        /* Get Tx confirmation state */
        RetVal = CANIF_TX_RX_NOTIFICATION;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_00867, SWS_CANIF_00661, SWS_CANIF_00869
 */
Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_BAUDRATE, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If CanIf_SetBaudrate() is called with invalid ControllerId, CanIf shall report development
        error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_SET_BAUDRATE, CANIF_E_PARAM_CONTROLLERID );
    }
    else
    {
        /* Set baudrate */
        (void)BaudRateConfigID;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_91003, SWS_CANIF_00661, SWS_CANIF_00907, SWS_CANIF_00908
 */
Std_ReturnType CanIf_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_RX_ERR_CNT, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_GetControllerRxErrorCounter() has an invalid value, the
        CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_GetControllerRxErrorCounter() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_RX_ERR_CNT, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( RxErrorCounterPtr == NULL_PTR )
    {
        /*If parameter RxErrorCounterPtr of CanIf_GetControllerRxErrorCounter() has an invalid value
        (NULL_PTR), the CanIf shall report development error code CANIF_E_PARAM_POINTER to the
        Det_ReportError service of the DET module, when CanIf_GetControllerRxErrorCounter() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_RX_ERR_CNT, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get controller Rx error counter */
        (void)RxErrorCounterPtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_91005, SWS_CANIF_00909, SWS_CANIF_00910
 */
Std_ReturnType CanIf_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_TX_ERR_CNT, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_GetControllerTxErrorCounter() has an invalid value, the
        CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_GetControllerTxErrorCounter() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_TX_ERR_CNT, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( TxErrorCounterPtr == NULL_PTR )
    {
        /*If parameter TxErrorCounterPtr of CanIf_GetControllerTxErrorCounter() has an invalid value
        (NULL_PTR), the CanIf shall report development error code CANIF_E_PARAM_POINTER to the
        Det_ReportError service of the DET module, when CanIf_GetControllerTxErrorCounter() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CTRL_TX_ERR_CNT, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get controller Tx error counter */
        (void)TxErrorCounterPtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_91005, SWS_CANIF_00661, SWS_CANIF_00912
 */
Std_ReturnType CanIf_EnableBusMirroring( uint8 ControllerId, boolean MirroringActive )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ENABLE_BUS_MIRROR, CANIF_E_UNINIT );
    }
    else if( ControllerId > LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_EnableBusMirroring() has an invalid value, the CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET, when CanIf_EnableBusMirroring() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ENABLE_BUS_MIRROR, CANIF_E_PARAM_CONTROLLERID );
    }
    else
    {
        /* Enable bus mirroring */
        (void)MirroringActive;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_91014, SWS_CANIF_00661, SWS_CANIF_00923, SWS_CANIF_00924
 */
Std_ReturnType CanIf_GetCurrentTime( uint8 Controller, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CURRENT_TIME, CANIF_E_UNINIT );
    }
    else if( Controller >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If development error detection is enabled: the function shall check the parameter Controller
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_CONTROLLERID.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CURRENT_TIME, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /*If development error detection is enabled: the function shall check the parameter timeStampPtr
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_POINTER*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_CURRENT_TIME, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get current time */
        (void)timeStampPtr;
        RetVal = E_OK;
    }

    return RetVal;
}

/**
 * @brief Enables the egress time stamp feature.
 *
 * This service calls the corresponding CAN Driver service to activate egress time stamping on a
 * dedicated message object.
 *
 * @param[in] TxPduId L-PDU handle of CAN L-PDU for which the time stamping shall be enabled
 *
 * @reqs    SWS_CANIF_91011, SWS_CANIF_00661, SWS_CANIF_00927
 */
void CanIf_EnableEgressTimeStamp( PduIdType TxPduId )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ENABLE_EGRESS_TS, CANIF_E_UNINIT );
    }
    else if( TxPduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If development error detection is enabled: the function shall check the parameter TxPduId
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_LPDU.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ENABLE_EGRESS_TS, CANIF_E_PARAM_LPDU );
    }
    else
    {
        /* Enable egress time stamp */
    }
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
 * @reqs    SWS_CANIF_91012, SWS_CANIF_00661, SWS_CANIF_00929, SWS_CANIF_00930, SWS_CANIF_00931
 */
Std_ReturnType CanIf_GetEgressTimeStamp( PduIdType TxPduId, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_EGRESS_TS, CANIF_E_UNINIT );
    }
    else if( TxPduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If development error detection is enabled: the function shall check the parameter TxPduId
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_LPDU.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_EGRESS_TS, CANIF_E_PARAM_LPDU );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /*If development error detection is enabled: the function shall check the parameter timeStampPtr
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_POINTER*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_EGRESS_TS, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get egress time stamp */
        (void)timeStampPtr;
        RetVal = E_OK;
    }

    return RetVal;
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
 * @reqs    SWS_CANIF_91012, SWS_CANIF_00661, SWS_CANIF_00933, SWS_CANIF_00934, SWS_CANIF_00935
 */
Std_ReturnType CanIf_GetIngressTimeStamp( PduIdType RxPduId, Can_TimeStampType *timeStampPtr )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_INGRESS_TS, CANIF_E_UNINIT );
    }
    else if( RxPduId >= LocalConfigPtr->MaxRxPduCfg )
    {
        /*If development error detection is enabled: the function shall check the parameter RxPduId
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_LPDU.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_INGRESS_TS, CANIF_E_PARAM_LPDU );
    }
    else if( timeStampPtr == NULL_PTR )
    {
        /*If development error detection is enabled: the function shall check the parameter timeStampPtr
        for being valid. If the check fails, the function shall raise the development error
        CANIF_E_PARAM_POINTER*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_GET_INGRESS_TS, CANIF_E_PARAM_POINTER );
    }
    else
    {
        /* Get ingress time stamp */
        (void)timeStampPtr;
        RetVal = E_OK;
    }

    return RetVal;
}
#endif

/**
 * @brief Handles the transmit confirmation.
 *
 * This service confirms a previously successfully processed transmission of a CAN TxPDU.
 *
 * @param[in] CanTxPduId ID of the successfully transmitted Tx L-PDU
 *
 * @reqs    SWS_CANIF_00007, SWS_CANIF_00661, SWS_CANIF_00410
 */
void CanIf_TxConfirmation( PduIdType CanTxPduId )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TX_CONFIRMATION, CANIF_E_UNINIT );
    }
    else if( CanTxPduId >= LocalConfigPtr->MaxTxPduCfg )
    {
        /*If parameter CanTxPduId of CanIf_TxConfirmation() has an invalid value, the CanIf shall
        report development error code CANIF_E_INVALID_TXPDUID to the Det_ReportError service of the
        DET module, when CanIf_TxConfirmation() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_TX_CONFIRMATION, CANIF_E_INVALID_TXPDUID );
    }
    else
    {
        /* Tx confirmation */
    }
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
 * @reqs    SWS_CANIF_00006, SWS_CANIF_00661, SWS_CANIF_00416, SWS_CANIF_00417, SWS_CANIF_00419
 */
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_RX_INDICATION, CANIF_E_UNINIT );
    }
    else if( ( PduInfoPtr == NULL_PTR ) || ( Mailbox == NULL_PTR ) )
    {
        /*If parameter PduInfoPtr or Mailbox of CanIf_RxIndication() has an invalid value, CanIf shall
        report development error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the
        DET module, when CanIf_RxIndication() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_RX_INDICATION, CANIF_E_PARAM_POINTER );
    }
    else if( Mailbox->Hoh == 0xFFu ) /*need to figure it out how to detect an invalid Hoh*/
    {
        /*If parameter Mailbox->Hoh of CanIf_RxIndication() has an invalid value, CanIf shall report
        development error code CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
        when CanIf_RxIndication() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_RX_INDICATION, CANIF_E_PARAM_HOH );
    }
    else if( Mailbox->CanId == 0u ) /*need to figure it out how to detect an invalid Id*/
    {
        /*If parameter Mailbox->CanId of CanIf_RxIndication() has an invalid value, CanIf shall report
        development error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET module,
        when CanIf_RxIndication() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_RX_INDICATION, CANIF_E_PARAM_CANID );
    }
    else
    {
        /* Rx indication */
    }
}

/**
 * @brief Handles the bus-off event.
 *
 * This service indicates a Controller BusOff event referring to the corresponding CAN Controller
 * with the abstract CanIf ControllerId.
 *
 * @param[in] ControllerId CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_CANIF_00218, SWS_CANIF_00661, SWS_CANIF_00429
 */
void CanIf_ControllerBusOff( uint8 ControllerId )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_BUS_OFF, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_ControllerBusOff() has an invalid value, CanIf shall
        report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
        of the DET module, when CanIf_ControllerBusOff() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_BUS_OFF, CANIF_E_PARAM_CONTROLLERID );
    }
    else
    {
        /* Controller bus-off */
    }
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
 * @reqs    SWS_CANIF_00699, SWS_CANIF_00661, SWS_CANIF_00700
 */
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_MODE_INDICATION, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_ControllerErrorStatePassive() has an invalid value, the
        CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_ControllerErrorStatePassive() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_MODE_INDICATION, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( ( ControllerMode < CAN_CS_STARTED ) || ( ControllerMode > CAN_CS_SLEEP ) )
    {
        /*If parameter ControllerMode of CanIf_ControllerModeIndication() has an invalid value, CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERMODE to the Det_ReportError service
        of the DET module, when CanIf_ControllerModeIndication() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_MODE_INDICATION, CANIF_E_PARAM_CTRLMODE );
    }
    else
    {
        /* Controller mode indication */
    }
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
 * @reqs    SWS_CANIF_91008, SWS_CANIF_00661
 */
void CanIf_ControllerErrorStatePassive( uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_ERR_ST_PASIVE, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_ControllerErrorStatePassive() has an invalid value, the
        CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_ControllerErrorStatePassive() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_CTRL_ERR_ST_PASIVE, CANIF_E_PARAM_CONTROLLERID );
    }
    else
    {
        (void)RxErrorCounter;
        (void)TxErrorCounter;
        /* Controller error state passive */
    }
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
 * @reqs    SWS_CANIF_91009, SWS_CANIF_00661, SWS_CANIF_00920, SWS_CANIF_00921
 */
void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType CanError )
{
    if( LocalConfigPtr == NULL_PTR )
    {
        /*All CanIf API services other than CanIf_Init() and CanIf_GetVersionInfo() shall not execute
        their normal operation and return E_NOT_OK unless the CanIf has been initialized with a
        preceding call of CanIf_Init */
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ERR_NOTIF, CANIF_E_UNINIT );
    }
    else if( ControllerId >= LocalConfigPtr->NumberOfCanControllers )
    {
        /*If parameter ControllerId of CanIf_ErrorNotification() has an invalid value, the CanIf
        shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError
        service of the DET module, when CanIf_ErrorNotification() is called.*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ERR_NOTIF, CANIF_E_PARAM_CONTROLLERID );
    }
    else if( CanError > CAN_ERROR_BUS_LOCK )
    {
        /*If parameter CanError of CanIf_ErrorNotification() has an invalid value, the CanIf shall
        report development error code CANIF_E_PARAM_CAN_ERROR to the Det_ReportError service of the
        DET module, when CanIf_ErrorNotification() is called*/
        Det_ReportError( CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_ID_ERR_NOTIF, CANIF_E_PARAM_CAN_ERROR );
    }
    else
    {
        /* Error notification */
    }
}

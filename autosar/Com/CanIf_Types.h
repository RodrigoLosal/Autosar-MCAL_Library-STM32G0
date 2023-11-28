/**
 * @file    CanIf_Types.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The header contains the type definitions that are used by the Can module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef CANIF_TYPES_H__
#define CANIF_TYPES_H__

#include "Can_Types.h"

/**
 * @defgroup CANIF_Ids Can Id number for module and each API
 *
 * @{ */
#define CANIF_ID_INIT                 0x01 /*!< CanIf_Init() */
#define CANIF_ID_DE_INIT              0x02 /*!< CanIf_DeInit() */
#define CANIF_ID_SET_CTRL_MODE        0x03 /*!< CanIf_SetControllerMode() */
#define CANIF_ID_GET_CTRL_MODE        0x04 /*!< CanIf_GetControllerMode() */
#define CANIF_ID_GET_CTRL_ERR_STATE   0x4b /*!< CanIf_GetControllerErrorState() */
#define CANIF_ID_TRANSMIT             0x49 /*!< CanIf_Transmit() */
#define CANIF_ID_READ_RX_PDU_DATA     0x06 /*!< CanIf_ReadRxPduData() */
#define CANIF_ID_READ_TX_NOTIF_STATUS 0x07 /*!< CanIf_ReadTxNotifStatus() */
#define CANIF_ID_READ_RX_NOTIF_STATUS 0x08 /*!< CanIf_ReadRxNotifStatus() */
#define CANIF_ID_SET_PDU_MODE         0x09 /*!< CanIf_SetPduMode() */
#define CANIF_ID_GET_PDU_MODE         0x0a /*!< CanIf_GetPduMode() */
#define CANIF_ID_GET_VERSION_INFO     0x0b /*!< CanIf_GetVersionInfo() */
#define CANIF_ID_SET_DYNAMIC_TX_ID    0x0c /*!< CanIf_SetDynamicTxId() */
#define CANIF_ID_GET_TX_CONFIRM_STATE 0x19 /*!< CanIf_GetTxConfirmationState() */
#define CANIF_ID_SET_BAUDRATE         0x27 /*!< CanIf_SetBaudrate() */
#define CANIF_ID_GET_CTRL_RX_ERR_CNT  0x4d /*!< CanIf_GetControllerRxErrorCounter() */
#define CANIF_ID_GET_CTRL_TX_ERR_CNT  0x4e /*!< CanIf_GetControllerTxErrorCounter() */
#define CANIF_ID_ENABLE_BUS_MIRROR    0x4c /*!< CanIf_EnableBusMirroring() */
#define CANIF_ID_GET_CURRENT_TIME     0x51 /*!< CanIf_GetCurrentTime() */
#define CANIF_ID_ENABLE_EGRESS_TS     0x52 /*!< CanIf_EnableEgressTimeStamp() */
#define CANIF_ID_GET_EGRESS_TS        0x53 /*!< CanIf_GetEgressTimeStamp() */
#define CANIF_ID_GET_INGRESS_TS       0x54 /*!< CanIf_GetIngressTimeStamp() */
#define CANIF_ID_TX_CONFIRMATION      0x13 /*!< CanIf_TxConfirmation() */
#define CANIF_ID_RX_INDICATION        0x14 /*!< CanIf_RxIndication() */
#define CANIF_ID_CTRL_BUS_OFF         0x16 /*!< CanIf_ControllerBusOff() */
#define CANIF_ID_CTRL_MODE_INDICATION 0x17 /*!< CanIf_ControllerModeIndication() */
#define CANIF_ID_CTRL_ERR_ST_PASIVE   0x4f /*!< CanIf_ControllerErrorStatePassive() */
#define CANIF_ID_ERR_NOTIF            0x50 /*!< CanIf_ErrorNotification() */
/**
 * @} */

/**
 * @defgroup CanIf_Error_Typse CanIf Developtmnet Error Types
 *
 * @reqs  SWS_CANIF_91006
 *
 * @{ */
#define CANIF_E_PARAM_CANID           0x10 /*!< API service called with invalid CAN ID */
#define CANIF_E_PARAM_HOH             0x12 /*!< API service called with invalid hardware object*/
#define CANIF_E_PARAM_LPDU            0x13 /*!< API service called with invalid PDU ID*/
#define CANIF_E_PARAM_CONTROLLERID    0x15 /*!< API service called with invalid controller ID*/
#define CANIF_E_PARAM_WAKEUPSOURCE    0x16 /*!< API service called with invalid wakeup source*/
#define CANIF_E_PARAM_TRCV            0x17 /*!< API service called with invalid transceiver ID*/
#define CANIF_E_PARAM_TRCVMODE        0x18 /*!< API service called with invalid transceiver mode*/
#define CANIF_E_PARAM_TRCVWAKEUPMODE  0x19 /*!< API service called with invalid transceiver wakeup mode*/
#define CANIF_E_PARAM_POINTER         0x20 /*!< API service called with invalid pointer*/
#define CANIF_E_PARAM_CTRLMODE        0x21 /*!< API service called with invalid controller mode*/
#define CANIF_E_PARAM_PDU_MODE        0x22 /*!< API service called with invalid PDU mode*/
#define CANIF_E_PARAM_CAN_ERROR       0x23 /*!< API services called with invalid parameter*/
#define CANIF_E_UNINIT                0x30 /*!< API service used without module initialization*/
#define CANIF_E_INVALID_TXPDUID       0x50 /*!< Transmit PDU ID invalid*/
#define CANIF_E_INVALID_RXPDUID       0x60 /*!< Receive PDU ID invalid*/
#define CANIF_E_INIT_FAILED           0x80 /*!< CAN Interface initialisation failedCANIF_E_PARAM_CANID*/
/**
 * @} */

/**
 * @defgroup CanIf_Runtime_Error_Types CanIf Runtime Error Types
 *
 * @reqs  SWS_CANIF_91007
 *
 * @{ */
#define CANIF_E_INVALID_DATA_LENGTH   0x61 /*!< Failed Data Length CheckN ID*/
#define CANIF_E_DATA_LENGTH_MISMATCH  0x62 /*!< Data Length*/
#define CANIF_E_STOPPED               0x70 /*!< Transmit requested on offline PDU channel*/
#define CANIF_E_TXPDU_LENGTH_EXCEEDED 0x90 /*!< Message length was exceeding the maximum length*/
/**
 * @} */

/**
 * @brief Configuration structure for the CAN interface.
 *
 * This type defines a data structure for the post build parameters of the CAN interface for all
 * underlying CAN drivers. At initialization the CanIf gets a pointer to a structure of this type
 * to get access to its configuration data, which is necessary for initialization.
 *
 * @reqs    SWS_CANIF_00144
 */
typedef struct _CanIf_ConfigType
{
    uint32 dummy; /*!< dummy element*/
} CanIf_ConfigType;

/**
 * @brief Pdu mode type.
 *
 * The PduMode of a channel defines its transmit or receive activity. Communication direction
 * (transmission and/or reception) of the channel can be controlled separately or together by
 * upper layers.
 *
 * @reqs    SWS_CANIF_00137
 */
typedef enum _CanIf_PduModeType
{
    CANIF_OFFLINE = 0x00,           /*!< = 0 Transmit and receive path of the corresponding channel
                                        are disabled => no communication mode */
    CANIF_TX_OFFLINE = 0x01,        /*!< Transmit path of the corresponding channel is disabled.
                                        The receive path is enabled */
    CANIF_TX_OFFLINE_ACTIVE = 0x02, /*!< Transmit path of the corresponding channel is in offline
                                        active mode (see SWS_CANIF_00072). The receive path is enabled.
                                        This mode requires CanIfTxOfflineActive Support = TRUE */
    CANIF_ONLINE = 0x03             /*!< Transmit and receive path of the corresponding channel are
                                        enabled => full operation mode */
} CanIf_PduModeType;

/**
 * @brief Notification status type.
 *
 * Return value of CAN L-PDU notification status.
 *
 * @reqs    SWS_CANIF_00201
 */
typedef enum _CanIf_NotifStatusType
{
    CANIF_NO_NOTIFICATION = 0x00,   /*!< No transmit or receive event occurred for the requested
                                        L-PDU */
    CANIF_TX_RX_NOTIFICATION = 0x01 /*!< The requested Rx/Tx CAN L-PDU was successfully transmitted
                                        or received. */
} CanIf_NotifStatusType;

#endif /* CANIF_TYPES_H__ */

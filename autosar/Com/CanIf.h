/**
 * @file CanIf.h
 * @brief Header file for the CAN interface.
 * @author Diego Perez
 *
 * The CAN Interface module provides CAN communication abstracted access to the CAN Driver and CAN
 * Transceiver Driver services for control and supervision of the CAN network. The CAN Interface
 * forwards downwards the status change requests from the CAN State Manager to the lower layer CAN
 * device drivers, and upwards the CAN Driver / CAN Transceiver Driver events are forwarded by the
 * CAN Interface module to e.g. the corresponding NM module.
 */
#ifndef CANIF_H__
#define CANIF_H__

#include "CanIf_Cfg.h"

/**
 * @defgroup CANIF_Ids Can Id number for module and each API
 *
 * @{ */
#define CANIF_ID_INIT                  0x01 /*!< CanIf_Init() */
#define CANIF_ID_DE_INIT               0x02 /*!< CanIf_DeInit() */
#define CANIF_ID_SET_CTRL_MODE         0x03 /*!< CanIf_SetControllerMode() */
#define CANIF_ID_GET_CTRL_MODE         0x04 /*!< CanIf_GetControllerMode() */
#define CANIF_ID_GET_CTRL_ERR_STATE    0x4b /*!< CanIf_GetControllerErrorState() */
#define CANIF_ID_TRANSMIT              0x49 /*!< CanIf_Transmit() */
#define CANIF_ID_READ_RX_PDU_DATA      0x06 /*!< CanIf_ReadRxPduData() */
#define CANIF_ID_READ_TX_NOTIF_STATUS  0x07 /*!< CanIf_ReadTxNotifStatus() */
#define CANIF_ID_READ_RX_NOTIF_STATUS  0x08 /*!< CanIf_ReadRxNotifStatus() */
#define CANIF_ID_SET_PDU_MODE          0x09 /*!< CanIf_SetPduMode() */
#define CANIF_ID_GET_PDU_MODE          0x0a /*!< CanIf_GetPduMode() */
#define CANIF_ID_GET_VERSION_INFO      0x0b /*!< CanIf_GetVersionInfo() */
#define CANIF_ID_SET_DYNAMIC_TX_ID     0x0c /*!< CanIf_SetDynamicTxId() */
#define CANIF_ID_GET_TX_CONFIRM_STATE  0x19 /*!< CanIf_GetTxConfirmationState() */
#define CANIF_ID_SET_BAUDRATE          0x27 /*!< CanIf_SetBaudrate() */
#define CANIF_ID_GET_CTRL_RX_ERR_CNT   0x4d /*!< CanIf_GetControllerRxErrorCounter() */
#define CANIF_ID_GET_ENABLE_BUS_MIRROR 0x4c /*!< CanIf_EnableBusMirroring() */
#define CANIF_ID_GET_CURRENT_TIME      0x51 /*!< CanIf_GetCurrentTime() */
#define CANIF_ID_ENABLE_EGRESS_TS      0x52 /*!< CanIf_EnableEgressTimeStamp() */
#define CANIF_ID_GET_EGRESS_TS         0x53 /*!< CanIf_GetEgressTimeStamp() */
#define CANIF_ID_GET_INGRESS_TS        0x54 /*!< CanIf_GetIngressTimeStamp() */
#define CANIF_ID_TX_CONFIRMATION       0x13 /*!< CanIf_TxConfirmation() */
#define CANIF_ID_RX_INDICATION         0x14 /*!< CanIf_RxIndication() */
#define CANIF_ID_CTRL_BUS_OFF          0x16 /*!< CanIf_ControllerBusOff() */
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

void CanIf_Init( const CanIf_ConfigType *ConfigPtr );
void CanIf_DeInit( void );
Std_ReturnType CanIf_SetControllerMode( uint8 ControllerId, Can_ControllerStateType ControllerMode );
Std_ReturnType CanIf_GetControllerMode( uint8 ControllerId, Can_ControllerStateType *ControllerModePtr );
Std_ReturnType CanIf_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr );
Std_ReturnType CanIf_Transmit( PduIdType TxPduId, const PduInfoType *PduInfoPtr );
Std_ReturnType CanIf_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType *CanIfRxInfoPtr );
CanIf_NotifStatusType CanIf_ReadTxNotifStatus( PduIdType CanIfTxSduId );
CanIf_NotifStatusType CanIf_ReadRxNotifStatus( PduIdType CanIfRxSduId );
Std_ReturnType CanIf_SetPduMode( uint8 ControllerId, CanIf_PduModeType PduModeRequest );
Std_ReturnType CanIf_GetPduMode( uint8 ControllerId, CanIf_PduModeType *PduModePtr );
void CanIf_GetVersionInfo( Std_VersionInfoType *VersionInfo );
void CanIf_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId );
CanIf_NotifStatusType CanIf_GetTxConfirmationState( uint8 ControllerId );
Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID );
Std_ReturnType CanIf_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr );
Std_ReturnType CanIf_EnableBusMirroring( uint8 ControllerId, boolean MirroringActive );
Std_ReturnType CanIf_GetCurrentTime( uint8 Controller, Can_TimeStampType *timeStampPtr );
void CanIf_EnableEgressTimeStamp( PduIdType TxPduId );
Std_ReturnType CanIf_GetEgressTimeStamp( PduIdType TxPduId, Can_TimeStampType *timeStampPtr );
Std_ReturnType CanIf_GetIngressTimeStamp( PduIdType RxPduId, Can_TimeStampType *timeStampPtr );

#endif // CANIF_H__
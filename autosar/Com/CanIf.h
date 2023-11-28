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


void CanIf_Init( const CanIf_ConfigType *ConfigPtr );
void CanIf_DeInit( void );
Std_ReturnType CanIf_SetControllerMode( uint8 ControllerId, Can_ControllerStateType ControllerMode );
Std_ReturnType CanIf_GetControllerMode( uint8 ControllerId, Can_ControllerStateType *ControllerModePtr );
Std_ReturnType CanIf_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr );
Std_ReturnType CanIf_Transmit( PduIdType TxPduId, const PduInfoType *PduInfoPtr );
#if CANIF_PUBLIC_READ_RX_PDU_DATA == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType CanIf_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType *CanIfRxInfoPtr );
#endif
#if CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
CanIf_NotifStatusType CanIf_ReadTxNotifStatus( PduIdType CanIfTxSduId );
#endif
#if CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
CanIf_NotifStatusType CanIf_ReadRxNotifStatus( PduIdType CanIfRxSduId );
#endif
Std_ReturnType CanIf_SetPduMode( uint8 ControllerId, CanIf_PduModeType PduModeRequest );
Std_ReturnType CanIf_GetPduMode( uint8 ControllerId, CanIf_PduModeType *PduModePtr );
#if CANIF_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void CanIf_GetVersionInfo( Std_VersionInfoType *VersionInfo );
#endif
void CanIf_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId );
CanIf_NotifStatusType CanIf_GetTxConfirmationState( uint8 ControllerId );
#if CANIF_SET_BAUDRATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID );
#endif
Std_ReturnType CanIf_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr );
Std_ReturnType CanIf_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr );
#if CANIF_BUS_MIRRORING_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType CanIf_EnableBusMirroring( uint8 ControllerId, boolean MirroringActive );
#endif
#if CANIF_GLOBAL_TIME_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType CanIf_GetCurrentTime( uint8 Controller, Can_TimeStampType *timeStampPtr );
void CanIf_EnableEgressTimeStamp( PduIdType TxPduId );
Std_ReturnType CanIf_GetEgressTimeStamp( PduIdType TxPduId, Can_TimeStampType *timeStampPtr );
Std_ReturnType CanIf_GetIngressTimeStamp( PduIdType RxPduId, Can_TimeStampType *timeStampPtr );
#endif

#endif // CANIF_H__
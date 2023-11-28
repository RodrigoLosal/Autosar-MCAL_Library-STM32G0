/**
 * @file CanIf_Can.h
 * @brief Header file for the CAN interface callbacks.
 * @author Diego Perez
 *
 * This file contains the prototypes for the CAN interface callbacks. As per AUTOSAR, these functions
 * are called by the CAN driver to notify the CAN interface of certain events. like a message reception,
 * a trnasmition complete or a bus-off condition.
 */
#ifndef CANIF_CAN_H__
#define CANIF_CAN_H__

void CanIf_TxConfirmation( PduIdType CanTxPduId );
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr );
void CanIf_ControllerBusOff( uint8 ControllerId );
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode );
void CanIf_ControllerErrorStatePassive( uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter );
void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType CanError );

#endif /* CANIF_CAN_H__ */

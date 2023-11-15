/**
 * @file CanIf_Can.h
 * @brief Header file for the CAN interface callbacks.
 * @author Diego Perez
 * 
 * ...
*/
#ifndef CANIF_CAN_H__
#define CANIF_CAN_H__

void CanIf_TxConfirmation( PduIdType CanTxPduId );
void CanIf_RxIndication( const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr );
void CanIf_ControllerBusOff( uint8 ControllerId );
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode );
void CanIf_ControllerErrorStatePassive(  uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter );
void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType Can_ErrorType );

#endif /* CANIF_CAN_H__ */

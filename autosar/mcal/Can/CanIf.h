#ifndef CANIF_H__
#define CANIF_H__

void CanIf_TxConfirmation( PduIdType CanTxPduId );
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr );
void CanIf_ControllerBusOff( uint8 ControllerId );
void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType Can_ErrorType );
void CanIf_ControllerErrorStatePassive( uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter );

#endif // CANIF_H__

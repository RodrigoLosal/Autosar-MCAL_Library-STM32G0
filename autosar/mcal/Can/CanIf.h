#ifndef CANIF_H__
#define CANIF_H__

void CanIf_TxConfirmation( PduIdType CanTxPduId );
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr );
void CanIf_ControllerBusOff( uint8 ControllerId );

#endif // CANIF_H__

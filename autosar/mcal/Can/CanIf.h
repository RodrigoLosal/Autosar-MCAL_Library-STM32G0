#ifndef CANIF_H__
#define CANIF_H__

void CanIf_TxConfirmation( PduIdType CanTxPduId );
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr );

#endif // CANIF_H__

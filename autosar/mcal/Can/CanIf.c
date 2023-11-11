#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "CanIf.h"

void CanIf_TxConfirmation( PduIdType CanTxPduId )
{
    (void)CanTxPduId;
}

void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr )
{
    (void)Mailbox;
    (void)PduInfoPtr;
}

void CanIf_ControllerBusOff( uint8 ControllerId )
{
    (void)ControllerId;
}

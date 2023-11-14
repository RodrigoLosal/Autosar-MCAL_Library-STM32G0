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

void CanIf_ErrorNotification( uint8 ControllerId, Can_ErrorType Can_ErrorType )
{
    (void)ControllerId;
    (void)Can_ErrorType;
}

void CanIf_ControllerErrorStatePassive( uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter )
{
    (void)ControllerId;
    (void)RxErrorCounter;
    (void)TxErrorCounter;
}

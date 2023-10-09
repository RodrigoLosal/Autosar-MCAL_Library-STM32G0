#include "Std_Types.h"

typedef uint8 PduIdType;            /*Might be uint16*/

typedef uint8 PduLengthType;        /*Might be uint16 or uint32*/

typedef struct
{
    uint8* SduDataPtr; 
    uint8* MetaDataPtr;           
    PduLengthType SduLength;                        
} PduInfoType;

typedef uint8 PNCHandleType;

typedef enum
{
    TP_STMIN    = 0x00,
    TP_BS       = 0x01,
    TP_BC       = 0x02
} TPParameterType;

typedef enum
{
    BUFREQ_OK       = 0x00,
    BUFREQ_E_NOT_OK = 0x01,
    BUFREQ_E_BUSY   = 0x02,
    BUFREQ_E_OVFL   = 0x03
} BufReq_ReturnType;

typedef enum
{
    TP_DATACONF     = 0x00,
    TP_DATARETRY    = 0x01,
    TP_CONFPENDING  = 0x02
} TpDataStateType;

typedef struct
{
    TpDataStateType TpDataState; 
    PduLengthType TxTpDataCnt;                                  
} RetryInfoType;

typedef uint8 NetworkHandleType;

typedef uint16 CbkHandleIdType;     /*Draft*/
/**
 * @file    Std_Types.h
 * @brief   **Specification of Standard Types**
 *
 * This document specifies the AUTOSAR standard types header file. It contains all types that are used
 * across several modules of the basic software and that are platform and compiler independent
 * It is strongly recommended that those standard types files are unique within the AUTOSAR community
 * to guarantee unique types and to avoid types changes when changing from supplier A to B.
 */
#ifndef STD_TYPES_H /* @reqs SWS_Std_00014*/
#define STD_TYPES_H

/* @reqs SWS_Std_00004*/
#include "Platform_Types.h"

/**
 * @brief  This type can be used as standard API return type which is shared between the RTE
 *         and the BSW modules. range: E_OK and E_NOT_OK
 *
 * @reqs   SWS_Std_00005, SWS_Std_00011
 */
typedef uint8 Std_ReturnType;


/**
 * @brief  The type Std_TransformerClass shall be an enumeration with the following elements
 *         where each element represents a transformer class: range STD_TRANSFORMER_UNSPECIFIED,
 *         STD_TRANSFORMER_SERIALIZER, STD_TRANSFORMER_SAFETY STD_TRANSFORMER_SECURITY and
 *         STD_TRANSFORMER_CUSTOM
 *         @todo clarify if Std_TransformerClass should be an enumeration
 *
 * @reqs   SWS_Std_00023, SWS_Std_00024, SWS_Std_00025, SWS_Std_00026
 */
typedef uint8 Std_TransformerClass;


/**
 * @brief  The type of the Std_TransformerError
 *
 * @reqs   SWS_Std_00022
 */
typedef uint8 Std_TransformerErrorCode;


/**
 * @brief  This type is used to encode the different type of messages. -Currently this encoding
 *         is limited to the distinction between requests and responses in C/S communication.
 *         range: STD_MESSAGETYPE_REQUEST and STD_MESSAGETYPE_RESPONSE
 *         @todo clarify if Std_MessageTypeType should be an enumeration
 *
 * @reqs   SWS_Std_91001, SWS_Std_00017
 */
typedef uint8 Std_MessageTypeType;


/**
 * @brief  This type is used to encode different types of results for response messages. Currently
 *         this encoding is limited to the distinction between OK and ERROR responses.
 *         range: STD_MESSAGERESULT_OK and STD_MESSAGERESULT_ERROR
 *         @todo clarify if Std_MessageResultType should be an enumeration
 *
 * @reqs   SWS_Std_91002, SWS_Std_00019
 */
typedef uint8 Std_MessageResultType;


/**
 * @brief Type for the function pointer to extract the relevant protocol header fields of the
 *        message and the type of the message result of a transformer. At the time being, this
 *        is limited to the types used for C/S communication (i.e., REQUEST and RESPONSE and
 *        OK and ERROR). range: STD_MESSAGERESULT_OK and STD_MESSAGERESULT_ERROR
 *
 * @reqs  SWS_Std_91003
 */
typedef Std_ReturnType ( *Std_ExtractProtocolHeaderFieldsType )( const uint8 *buffer, uint32 bufferLength, Std_MessageTypeType *messageType, Std_MessageResultType *messageResult );


/**
 * @brief   This structure is used to request the version of a BSW module using the
 *          **[Module name]_GetVersionInfo()** function available on each module
 *
 * @reqs    SWS_Std_00015
 */
typedef struct Std_VersionInfoType_Tag
{
    uint16 vendorID;        /**< Assigned vendor ID (Modular)*/
    uint16 moduleID;        /**< BSW software module ID */
    uint8 sw_major_version; /**< BSW software major version */
    uint8 sw_minor_version; /**< BSW software minor version */
    uint8 sw_patch_version; /**< BSW software patch version */
} Std_VersionInfoType;


/**
 * @brief  The Std_TransformerErrorCode represents a transformer error in the context of a
 *         certain transformer chain.
 *
 * @reqs   SWS_Std_00021
 */
typedef struct Std_TransformerError_Tag
{
    Std_TransformerErrorCode errorCode;    /*!< error code ASWS Transformer General*/
    Std_TransformerClass transformerClass; /*!< Transformer class*/
} Std_TransformerError;


/**
 * @name    status_msgs
 * Return status, the values are used to be stored in the variable type #Std_ReturnType
 *
 * @reqs    SWS_Std_00006
 */
/**@{*/
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED         /*!< guard definition */
#define E_OK              0u      /*!< OK return value */
typedef unsigned char StatusType; /*!< OSEK compliance */
#endif
#define E_NOT_OK   1u /*!< Error return value */
/**@}*/


/**
 * @name    physical_states
 * Definitions to identify signal or devices physical states
 *
 * @reqs    SWS_Std_00007
 */
/**@{*/
#define STD_HIGH   1u /*!< Physical state 5V or 3.3V */
#define STD_LOW    0u /*!< Physical state 0V */
/**@}*/


/**
 * @name    logical_states
 * Definitions to identify signal or devices logical states
 *
 * @reqs    SWS_Std_00013
 */
/**@{*/
#define STD_ACTIVE 1u /*!< Logical state active */
#define STD_IDLE   0u /*!< Logical state idle */
/**@}*/


/**
 * @name    binary_states
 * Definitions to identify is a signal or device is ON or OFF
 *
 * @reqs    SWS_Std_00010
 */
/**@{*/
#define STD_ON     1u /*!< Binary state ON */
#define STD_OFF    0u /*!< Binary state OFF */
/**@}*/


/**
 * @brief   null pointer definition
 *
 * @reqs    SWS_Std_00031
 */
#define NULL_PTR   ( (void *)0 )


#endif /* STD_TYPES_H */

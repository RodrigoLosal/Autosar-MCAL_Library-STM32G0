/**
 * @file    Can_GeneralTypes.h
 * @brief   **Can Stack types**
 * @author  Diego Perez
 *
 * This is the implementation of the Can Stack types
 */
#ifndef CAN_GENERAL_TYPES_H__
#define CAN_GENERAL_TYPES_H__

/**
 * @brief   Represents the Identifier of an L-PDU. The two most significant bits specify the frame
 *          type: 00 CAN message with Standard CAN ID 01 CAN FD frame with Standard CAN ID 10 CAN
 *          message with  Extended CAN ID 11 CAN FD frame with Extended CAN ID
 */
typedef uint32 Can_IdType;

/**
 * @brief   Represents the hardware object handles of a CAN hardware unit. For CAN hardware units
 *          with more than 255 HW objects use extended range.
 */
typedef uint16 Can_HwHandleType;

/**
 * @brief   This type defines a data structure which clearly provides an Hardware Object Handle
 *          including its corresponding CAN Controller and therefore CanDrv as well as the
 *          specific CanId.
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef struct _Can_HwType
{                         /* cppcheck-suppress misra-c2012-2.4 ; the enum name it is neccesary */
    Can_IdType CanId;     /*!< Standard/Extended CAN ID of CAN L-PDU*/
    Can_HwHandleType Hoh; /*!< ID of the corresponding Hardware Object Range*/
    uint8 ControllerId;   /*!< ControllerId provided by CanIf clearly identify the corresponding
                              controller*/
} Can_HwType;

/**
 * @brief   This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and Can Id (id)
 *          for any CAN L-SDU
 */
typedef struct _Can_PduType
{
    PduIdType swPduHandle; /*!< ID of CAN L-SDU in CanIf*/
    uint8 length;          /*!< DLC of CAN L-SDU*/
    Can_IdType id;         /*!< CAN identifier of CAN L-SDU*/
    uint8 *sdu;            /*!< Pointer to CAN L-SDU buffer*/
} Can_PduType;

/**
 * @brief   Error states of a CAN controller.
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef enum _Can_ErrorStateType
{
    CAN_ERRORSTATE_ACTIVE = 0x01, /*!< CAN controller takes fully part in communication.*/
    CAN_ERRORSTATE_PASSIVE,       /*!< CAN controller takes part in communication, but does not
                                      send active error frames.*/
    CAN_ERRORSTATE_BUSOFF         /*!< CAN controller doesn't take part in communication.*/
} Can_ErrorStateType;

/**
 * @brief   States that are used by the several ControllerMode functions.
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef enum _Can_ControllerStateType
{
    CAN_CS_UNINIT = 0x01, /*!< CAN controller state UNINIT.*/
    CAN_CS_STARTED,       /*!< CAN controller state STARTED.*/
    CAN_CS_STOPPED,       /*!< CAN controller state STOPPED.*/
    CAN_CS_SLEEP,         /*!< CAN controller state SLEEP.*/
    CAN_CS_WAKEUP,        /*!< CAN controller state WAKEUP.*/
    CAN_CS_READY          /*!< CAN controller state READY.*/
} Can_ControllerStateType;

/**
 * @brief   The enumeration represents a superset of CAN Error Types which typical CAN HW is able
 *          to report. That means not all CAN HW will be able to support the complete set
 */
/* cppcheck-suppress misra-c2012-2.3 ; the enum name it is neccesary */
typedef enum _Can_ErrorType
{                                     /* cppcheck-suppress misra-c2012-2.4 ; the enum name it is neccesary */
    CAN_ERROR_BIT_MONITORING1 = 0x01, /*!< A 0 was transmitted and a 1 was read back*/
    CAN_ERROR_BIT_MONITORING2,        /*!< A 1 was transmitted and a 0 was read back*/
    CAN_ERROR_BIT,                    /*!< The HW reports a CAN bit error but cannot report distinguish
                                          between CAN_ERROR_BIT_MONITORING1 and CAN_ERROR_BIT_MONITORING0*/
    CAN_ERROR_CHECK_ACK_FAILED,       /*!< Acknowledgement check failed*/
    CAN_ERROR_ACK_DELIMITER,          /*!< Acknowledgement delimiter check failed*/
    CAN_ERROR_ARBITRATION_LOST,       /*!< The sender lost in arbitration*/
    CAN_ERROR_OVERLOAD,               /*!< CAN overload detected via an overload frame. Indicates that
                                          the receive buffers of a receiver are full.*/
    CAN_ERROR_CHECK_FORM_FAILED,      /*!< Violations of the fixed frame format*/
    CAN_ERROR_CHECK_STUFFING_FAILED,  /*!< Stuffing bits not as expected*/
    CAN_ERROR_CHECK_CRC_FAILED,       /*!< CRC check failed*/
    CAN_ERROR_BUS_LOCK                /*!< Bus lock (Bus is stuck to dominant level)*/
} Can_ErrorType;

#endif /* CAN_GENERAL_TYPES_H__ */

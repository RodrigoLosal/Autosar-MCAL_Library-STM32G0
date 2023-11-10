/**
 * @file    Can_Arch.h
 * @brief   **Can Specific Arquitecture Driver**
 * @author  Diego Perez
 *
 * Can driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Can driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef CAN_ARCH_H__
#define CAN_ARCH_H__

#include "Can_Types.h"

/**
 * @defgroup CAN_clock_divider CAN Clock Divider
 *
 * @{ */
#define CAN_CLOCK_DIV1                 0x00u /*!< Divide kernel clock by 1  */
#define CAN_CLOCK_DIV2                 0x01u /*!< Divide kernel clock by 2  */
#define CAN_CLOCK_DIV4                 0x02u /*!< Divide kernel clock by 4  */
#define CAN_CLOCK_DIV6                 0x03u /*!< Divide kernel clock by 6  */
#define CAN_CLOCK_DIV8                 0x04u /*!< Divide kernel clock by 8  */
#define CAN_CLOCK_DIV10                0x05u /*!< Divide kernel clock by 10 */
#define CAN_CLOCK_DIV12                0x06u /*!< Divide kernel clock by 12 */
#define CAN_CLOCK_DIV14                0x07u /*!< Divide kernel clock by 14 */
#define CAN_CLOCK_DIV16                0x08u /*!< Divide kernel clock by 16 */
#define CAN_CLOCK_DIV18                0x09u /*!< Divide kernel clock by 18 */
#define CAN_CLOCK_DIV20                0x0Au /*!< Divide kernel clock by 20 */
#define CAN_CLOCK_DIV22                0x0Bu /*!< Divide kernel clock by 22 */
#define CAN_CLOCK_DIV24                0x0Cu /*!< Divide kernel clock by 24 */
#define CAN_CLOCK_DIV26                0x0Du /*!< Divide kernel clock by 26 */
#define CAN_CLOCK_DIV28                0x0Eu /*!< Divide kernel clock by 28 */
#define CAN_CLOCK_DIV30                0x0Fu /*!< Divide kernel clock by 30 */
/**
 * @} */

/**
 * @defgroup CAN_frame_format CAN Frame Format
 *
 * @{ */
#define CAN_FRAME_CLASSIC              0x00000000u                                     /*!< Classic mode                      */
#define CAN_FRAME_FD_NO_BRS            ( (uint32)1u << 8u )                            /*!< FD mode without BitRate Switching */
#define CAN_FRAME_FD_BRS               ( ( (uint32)1u << 8u ) | ( (uint32)1u << 9u ) ) /*!< FD mode with BitRate Switching    */
/**
 * @} */

/**
 * @defgroup CAN_txFifoQueue_Mode CAN Tx FIFO/Queue Mode
 *
 * @{ */
#define CAN_TX_FIFO_OPERATION          0x00000000u           /*!< FIFO mode  */
#define CAN_TX_QUEUE_OPERATION         ( (uint32)1u << 24u ) /*!< Queue mode */
/**
 * @} */

/**
 * @defgroup CAN_mode CAN Operating Mode
 *
 * @{ */
#define CAN_MODE_NORMAL                0x00u /*!< Normal mode               */
#define CAN_MODE_RESTRICTED_OPERATION  0x01u /*!< Restricted Operation mode */
#define CAN_MODE_BUS_MONITORING        0x02u /*!< Bus Monitoring mode       */
#define CAN_MODE_INTERNAL_LOOPBACK     0x03u /*!< Internal LoopBack mode    */
#define CAN_MODE_EXTERNAL_LOOPBACK     0x04u /*!< External LoopBack mode    */
/**
 * @} */

/**
 * @defgroup CAN_Hardware_Object_Type CAN Hardware Object Type
 *
 * @{ */
#define CAN_HOH_TYPE_RECEIVE           0x00u /*!< Receive object */
#define CAN_HOH_TYPE_TRANSMIT          0x01u /*!< Transmit object */
/**
 * @} */

/**
 * @defgroup CAN_TxBuffer CAN Trnasmit Buffers
 *
 * @{ */
#define CAN_TX_BUFFER0                 0x00000001u /*!< Add message to Tx Buffer 0  */
#define CAN_TX_BUFFER1                 0x00000002u /*!< Add message to Tx Buffer 1  */
#define CAN_TX_BUFFER2                 0x00000004u /*!< Add message to Tx Buffer 2  */
/**
 * @} */

/**
 * @defgroup CAN_IntLines CAN Interrupt Lines
 *
 * @{ */
#define CAN_INTERRUPT_LINE0            0u /*!< Interrupt Line 0 */
#define CAN_INTERRUPT_LINE1            1u /*!< Interrupt Line 1 */
/**
 * @} */

/**
 * @defgroup FDCAN_Interrupts_Group FDCAN Interrupts Group
 *
 *  @{ */
#define CAN_IT_GROUP_RX_FIFO0          0u /*!< RX FIFO 0 Interrupts Group: RF0LL: Rx FIFO 0 Message Lost, \
                                              RF0FL: Rx FIFO 0 is Full and RF0NL: Rx FIFO 0 Has New Message */
#define CAN_IT_GROUP_RX_FIFO1          1u /*!< RX FIFO 1 Interrupts Group: RF0LL: Rx FIFO 1 Message Lost, \
                                              RF0FL: Rx FIFO 1 is Full and RF0NL: Rx FIFO 1 Has New Message */
#define CAN_IT_GROUP_SMSG              2u /*!< Status Message Interrupts Group: TCFL: Transmission Cancellation Finished, \
                                              TCL: Transmission Completed and HPML: High Priority Message */
#define CAN_IT_GROUP_TX_FIFO_ERROR     3u /*!< TX FIFO Error Interrupts Group: TEFLL: Tx Event FIFO Element Lost, \
                                              TEFFL: Tx Event FIFO Full, TEFNL: Tx Event FIFO New Entry and       \
                                              TFEL: Tx FIFO Empty Interrupt Line */
#define CAN_IT_GROUP_MISC              4u /*!< Misc. Interrupts Group: TOOL: Timeout Occurred, \
                                              MRAFL: Message RAM Access Failure and TSWL: Timestamp Wraparound */
#define CAN_IT_GROUP_BIT_LINE_ERROR    5u /*!< Bit and Line Error Interrupts Group: EPL: Error Passive and \
                                              ELOL: Error Logging Overflow */
#define CAN_IT_GROUP_PROTOCOL_ERROR    6u /*!< Protocol Error Group: ARAL: Access to Reserved Address Line,                           \
                                              PEDL: Protocol Error in Data Phase Line, PEAL: Protocol Error in Arbitration Phase Line \
                                              WDIL: Watchdog Interrupt Line, BOL: Bus_Off Status and                                  \
                                              EWL: Warning Status */
/**
 * @} */

/**
 * @defgroup FDCAN_Interrupts_List FDCAN Interrupts List
 *
 * @{ */
#define CAN_IT_LIST_RX_FIFO0           0x00000007 /*!< RX FIFO 0 Interrupts List          */
#define CAN_IT_LIST_RX_FIFO1           0x00000038 /*!< RX FIFO 1 Interrupts List          */
#define CAN_IT_LIST_SMSG               0x000001C0 /*!< Status Message Interrupts List     */
#define CAN_IT_LIST_TX_FIFO_ERROR      0x00001E00 /*!< TX FIFO Error Interrupts List      */
#define CAN_IT_LIST_MISC               0x0000E000 /*!< Misc. Interrupts List              */
#define CAN_IT_LIST_BIT_LINE_ERROR     0x00030000 /*!< Bit and Line Error Interrupts List */
#define CAN_IT_LIST_PROTOCOL_ERROR     0x00FC0000 /*!< Protocol Error Interrupts List     */
/**
 * @} */

/**
 * @defgroup CAN_Rx_Fifo0_Interrupts FDCAN Rx FIFO 0 Interrupts
 *
 * @{ */
#define CAN_IT_RX_FIFO0_MESSAGE_LOST   ( (uint32)1u << 0u ) /*!< Rx FIFO 0 message lost            */
#define CAN_IT_RX_FIFO0_FULL           ( (uint32)1u << 1u ) /*!< Rx FIFO 0 full                    */
#define CAN_IT_RX_FIFO0_NEW_MESSAGE    ( (uint32)1u << 2u ) /*!< New message written to Rx FIFO 0  */
/**
 * @} */

/**
 * @defgroup CAN_Rx_Fifo1_Interrupts FDCAN Rx FIFO 1 Interrupts
 *
 * @{ */
#define CAN_IT_RX_FIFO1_MESSAGE_LOST   ( (uint32)1u << 3u ) /*!< Rx FIFO 1 message lost           */
#define CAN_IT_RX_FIFO1_FULL           ( (uint32)1u << 4u ) /*!< Rx FIFO 1 full                   */
#define CAN_IT_RX_FIFO1_NEW_MESSAGE    ( (uint32)1u << 5u ) /*!< New message written to Rx FIFO 1 */
/**
 * @} */

/**
 * @defgroup FDCAN_Rx_Interrupts FDCAN Rx Interrupts
 *
 * @{ */
#define CAN_IT_RX_HIGH_PRIORITY_MSG    ( (uint32)1u << 6u ) /*!< High priority message received */
/**
 * @} */

/**
 * @defgroup CAN_Tx_Interrupts FDCAN Tx Interrupts
 *
 * @{ */
#define CAN_IT_TX_COMPLETE             ( (uint32)1u << 7u ) /*!< Transmission Completed             */
#define CAN_IT_TX_ABORT_COMPLETE       ( (uint32)1u << 8u ) /*!< Transmission Cancellation Finished */
#define CAN_IT_TX_FIFO_EMPTY           ( (uint32)1u << 9u ) /*!< Tx FIFO Empty                      */
/**
 * @} */

/**
 * @defgroup FDCAN_Tx_Event_Fifo_Interrupts FDCAN Tx Event FIFO Interrupts
 *
 * @{ */
#define CAN_IT_TX_EVT_FIFO_NEW_DATA    ( (uint32)1u << 10 ) /*!< Tx Handler wrote Tx Event FIFO element */
#define CAN_IT_TX_EVT_FIFO_FULL        ( (uint32)1u << 11 ) /*!< Tx Event FIFO full                     */
#define CAN_IT_TX_EVT_FIFO_ELT_LOST    ( (uint32)1u << 12 ) /*!< Tx Event FIFO element lost             */
/**
 * @} */

/**
 * @defgroup CAN_Counter_Interrupts CAN Counter Interrupts
 *
 * @{ */
#define CAN_IT_TIMESTAMP_WRAPAROUND    ( (uint32)1u << 13u ) /*!< Timestamp counter wrapped around */
#define CAN_IT_TIMEOUT_OCCURRED        ( (uint32)1u << 15u ) /*!< Timeout reached                  */
/**
 * @} */

/**
 * @defgroup CAN_Error_Interrupts CAN Error Interrupts
 *
 * @{ */
#define CAN_IT_RAM_ACCESS_FAILURE      ( (uint32)1u << 14u ) /*!< Message RAM access failure occurred              */
#define CAN_IT_ERROR_LOGGING_OVERFLOW  ( (uint32)1u << 16u ) /*!< Overflow of FDCAN Error Logging Counter occurred */
#define CAN_IT_RAM_WATCHDOG            ( (uint32)1u << 20u ) /*!< Message RAM Watchdog event due to missing READY  */
#define CAN_IT_ARB_PROTOCOL_ERROR      ( (uint32)1u << 21u ) /*!< Protocol error in arbitration phase detected     */
#define CAN_IT_DATA_PROTOCOL_ERROR     ( (uint32)1u << 22u ) /*!< Protocol error in data phase detected            */
#define CAN_IT_RESERVED_ADDRESS_ACCESS ( (uint32)1u << 23u ) /*!< Access to reserved address occurred              */
/**
 * @} */

/**
 * @defgroup CAN_Error_Status_Interrupts CAN Error Status Interrupts
 *
 * @{ */
#define CAN_IT_ERROR_PASSIVE           ( (uint32)1u << 17u ) /*!< Error_Passive status changed      */
#define CAN_IT_ERROR_WARNING           ( (uint32)1u << 18u ) /*!< Error_Warning status changed      */
#define CAN_IT_BUS_OFF                 ( (uint32)1u << 19u ) /*!< Bus_Off status changed            */
/**
 * @} */

/**
 * @defgroup CAN_Filter_Type CAN Filter Type
 *
 * @{ */
#define CAN_FILTER_TYPE_RANGE          0x00u /*!< Range filter type */
#define CAN_FILTER_TYPE_DUAL           0x01u /*!< Dual filter type  */
#define CAN_FILTER_TYPE_CLASSIC        0x02u /*!< Classic filter type */
/**
 * @} */

/**
 * @defgroup CAN_Hardware_Object_Type CAN Hardware Object Type
 *
 * @{ */
#define CAN_HOH_TYPE_RECEIVE           0x00u /*!< Receive object */
#define CAN_HOH_TYPE_TRANSMIT          0x01u /*!< Transmit object */
/**
 * @} */

/**
 * @defgroup CAN_Object_Payload_Length CAN Object Payload Length
 *
 * @{ */
#define CAN_OBJECT_PL_8                0x08u /*!< 8 bytes payload length  */
#define CAN_OBJECT_PL_12               0x09u /*!< 12 bytes payload length */
#define CAN_OBJECT_PL_16               0x0Au /*!< 16 bytes payload length */
#define CAN_OBJECT_PL_20               0x0Bu /*!< 20 bytes payload length */
#define CAN_OBJECT_PL_24               0x0Cu /*!< 24 bytes payload length */
#define CAN_OBJECT_PL_32               0x0Du /*!< 32 bytes payload length */
#define CAN_OBJECT_PL_48               0x0Eu /*!< 48 bytes payload length */
#define CAN_OBJECT_PL_64               0x0Fu /*!< 64 bytes payload length */
/**
 * @} */

/**
 * @defgroup CAN_Id_Type CAN ID Type to be handle by the HOHs
 *
 * @{ */
#define CAN_ID_STANDARD                0x00u /*!< Standard ID */
#define CAN_ID_EXTENDED                0x01u /*!< Extended ID */
#define CAN_ID_MIXED                   0x02u /*!< Mixed ID    */
/**
 * @} */

/**
 * @defgroup CAN_Hardware_Handler_Type CAN Hardware Handler Type
 *
 * @{ */
#define CAN_FULL                       0x00u /*!< Full CAN */
#define CAN_BASIC                      0x01u /*!< Basic CAN */
/**
 * @} */

/**
 * @defgroup CAN_Processing CAN Controller Rx, Tx type of processing
 *
 * @{ */
#define CAN_PROCESSING_INTERRUPT       0x00u /*!< Interrupt processing */
#define CAN_PROCESSING_POLLING         0x01u /*!< Polling processing   */
#define CAN_PROCESSING_MIXED           0x02u /*!< Mixed processing     */
/**
 * @} */

/**
 * @defgroup CAN_Hohs CAN Hardware Object Handlers
 *
 * @{ */
#define CAN_OBJ_HTH_TX00               0u /*!< HTH zero to controller zero */
#define CAN_OBJ_HRH_RX00               1u /*!< HRH zero to controller zero */
#define CAN_OBJ_HRH_RX01               2u /*!< HRH one to controller zero */
#define CAN_OBJ_HTH_TX10               3u /*!< HTH zero to controller one  */
#define CAN_OBJ_HRH_RX10               4u /*!< HRH zero to controller one  */
#define CAN_OBJ_HRH_RX11               5u /*!< HRH one to controller one   */
/**
 * @} */


void Can_Arch_Init( Can_HwUnit *HwUnit, const Can_ConfigType *Config, uint8 Controller );
void Can_Arch_DeInit( Can_HwUnit *HwUnit, uint8 Controller );
Std_ReturnType Can_Arch_SetBaudrate( Can_HwUnit *HwUnit, uint8 Controller, uint16 BaudRateConfigID );
Std_ReturnType Can_Arch_SetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType Transition );
void Can_Arch_DisableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller );
void Can_Arch_EnableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller );
Std_ReturnType Can_Arch_CheckWakeup( Can_HwUnit *HwUnit, uint8 Controller );
Std_ReturnType Can_Arch_GetControllerErrorState( Can_HwUnit *HwUnit, uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr );
Std_ReturnType Can_Arch_GetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType *ControllerModePtr );
Std_ReturnType Can_Arch_GetControllerRxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *RxErrorCounterPtr );
Std_ReturnType Can_Arch_GetControllerTxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *TxErrorCounterPtr );
Std_ReturnType Can_Arch_Write( Can_HwUnit *HwUnit, Can_HwHandleType Hth, const Can_PduType *PduInfo );
Std_ReturnType Can_Arch_GetCurrentTime( Can_HwUnit *HwUnit, uint8 ControllerId, Can_TimeStampType *timeStampPtr );
void Can_Arch_EnableEgressTimeStamp( Can_HwUnit *HwUnit, Can_HwHandleType Hth );
Std_ReturnType Can_Arch_GetEgressTimeStamp( Can_HwUnit *HwUnit, PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr );
Std_ReturnType Can_Arch_GetIngressTimeStamp( Can_HwUnit *HwUnit, Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr );
void Can_Arch_IsrMainHandler( Can_HwUnit *HwUnit, uint8 Controller );

#endif /* CAN_ARCH_H__ */

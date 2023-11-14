/**
 * @file    Can_Types.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The header contains the type definitions that are used by the Can module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef CAN_TYPES_H__
#define CAN_TYPES_H__

#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/**
 * @defgroup CAN_STATIC CAN static define for testing purposes
 *
 * @{ */
#ifndef UTEST
#define CAN_STATIC static /*!< Add static when no testing */
#else
#define CAN_STATIC /*!< remove static for testing purposes */
#endif
/**
 * @} */

/**
 * @defgroup CAN_Ids Can Id number for module and each API
 *
 * @{ */
#define CAN_ID_INIT                0x00u /*!< Can_Init() api service id */
#define CAN_ID_DE_INIT             0x10u /*!< Can_DeInit() api service id */
#define CAN_ID_SET_BAUDRATE        0x0fu /*!< Can_ChangeBaudrate() api service id */
#define CAN_ID_SET_CTRL_MODE       0x03u /*!< Can_SetControllerMode() api service id */
#define CAN_ID_DISABLE_CTRL_INT    0x04u /*!< Can_DisableControllerInterrupts() api service id */
#define CAN_ID_ENABLE_CTRL_INT     0x05u /*!< Can_EnableControllerInterrupts() api service id */
#define CAN_ID_CHECK_WAKEUP        0x0bu /*!< Can_CheckWakeup() api service id */
#define CAN_ID_GET_CTRL_MODE       0x12u /*!< Can_GetControllerState() api service id */
#define CAN_ID_GET_CTRL_ERR_STATE  0x11u /*!< Can_GetControllerErrorState() api service id */
#define CAN_ID_GET_CTRL_RX_ERR_CNT 0x30u /*!< Can_GetControllerRxErrorCounter() api service id */
#define CAN_ID_GET_CTRL_TX_ERR_CNT 0x31u /*!< Can_GetControllerTxErrorCounter() api service id */
#define CAN_ID_WRITE               0x06u /*!< Can_Write() api service id */
#define CAN_ID_MF_WRITE            0x01u /*!< Can_MainFunction_Write() api service id */
#define CAN_ID_MF_READ             0x08u /*!< Can_MainFunction_Read() api service id */
#define CAN_ID_MF_BUSOFF           0x09u /*!< Can_MainFunction_BusOff() api service id */
#define CAN_ID_MF_WAKEUP           0x0au /*!< Can_MainFunction_Wakeup() api service id */
#define CAN_ID_MF_MODE             0x0cu /*!< Can_MainFunction_MODE() api service id */
#define CAN_ID_GET_VERSION_INFO    0x07u /*!< Can_GetVersionInfo() api service id */
#define CAN_ID_GET_CURRENT_TIME    0x32u /*!< Can_GetCurrentTime() api service id */
#define CAN_ID_ENABLE_EGRESS_TS    0x33u /*!< Can_EnableEgressTimeStamp() api service id */
#define CAN_ID_GET_EGRESS_TS       0x34u /*!< Can_GetEgressTimeStamp() api service id */
#define CAN_ID_GET_INGRESS_TS      0x35u /*!< Can_GetIngressTimeStamp() api service id */
#define CAN_ID_ISR_TRANSMITION     0x02u /*!< Can_IsrTransmition() api service id */
#define CAN_ID_ISR_RECEPTION       0x0du /*!< Can_IsrReception() api service id */
/**
 * @} */

/**
 * @defgroup CAN_Error_Typse Can Developtmnet Error Types
 *
 * @{ */
#define CAN_E_PARAM_POINTER        0x01u /*!< API Service called with wrong parameter */
#define CAN_E_PARAM_HANDLE         0x02u /*!< API Service called with wrong handle */
#define CAN_E_PARAM_DATA_LENGTH    0x03u /*!< API Service called with wrong data length */
#define CAN_E_PARAM_CONTROLLER     0x04u /*!< API Service called with wrong controller */
#define CAN_E_UNINIT               0x05u /*!< API Service used without module initialization */
#define CAN_E_TRANSITION           0x06u /*!< API Service called with wrong controller mode */
#define CAN_E_PARAM_BAUDRATE       0x07u /*!< API Service called with wrong baudrate */
#define CAN_E_INIT_FAILED          0x09u /*!< API Service called with wrong baudrate */
#define CAN_E_PARAM_LPDU           0x0Au /*!< API Service called with wrong L-PDU */
#define CAN_E_DATALOST             0x01u /*!< Received CAN message is lost */
/**
 * @} */


/**
 * @brief **CAN Controller Baudrate Configuration**
 *
 * This container contains bit timing related configuration parameters of the CAN controller(s).
 *
 * @note the element ID defined by autosar is suppressed due to the fact that the index array it
 *      is used as an ID
 */
typedef struct _Can_ControllerBaudrateConfig
{
    uint8 BaudRateConfigID /*!< Unique identifier for a baudrate configuration
                                This parameter value is defined in Can_Cfg.h */
    ;

    uint32 BaudRate; /*!< Baudrate in Kbps
                         The field is only for indication purposes */

    uint8 PropSeg; /*!< Propagation segment in time quanta
                       The field is only for indication purposes */

    uint32 Seg1; /*!< Segment 1 in time quanta
                     This parameter must be a number between 2 and 256 */

    uint32 Seg2; /*!< Segment 2 in time quanta
                     This parameter must be a number between 2 and 128 */

    uint32 SyncJumpWidth; /*!< Synchronization jump width in time quanta
                              This parameter must be a number between 1 and 128 */

    uint32 Prescaler; /*!< Baudrate prescaler
                          This parameter must be a number between 1 and 512 */

    uint8 FdPropSeg; /*!< Propagation segment in time quantas 1 + Seg1 + Seg2
                       The field is only for indication purposes */

    uint32 FdSeg1; /*!< Segment 1 in time quanta for data payload
                     this parameter must be a number between 1 and 32 */

    uint32 FdSeg2; /*!< Segment 2 in time quanta for data payload
                     this parameter must be a number between 1 and 16 */

    uint32 FdPrescaler; /*!< Baudrate prescaler
                          this parameter must be a number between 1 and 32 */

    uint32 FdSspOffset; /*!< Sample point offset in time quanta
                          Field not in use for stm32g0 Mcu */

    uint32 FdSyncJumpWidth; /*!< Synchronization jump width in time quanta
                              this parameter must be a number between 1 and 16 */

    uint8 FdTxBitRateSwitch; /*!< Bit rate switching for transmission
                               this paramter can be STD_OFF or STD_ON */
} Can_ControllerBaudrateConfig;


/**
 * @brief **CAN Controller**
 *
 * This container contains the configuration parameters of the CAN controller(s).
 *
 * @note the element ID defined by autosar is suppressed due to the fact that the index array it
 *       is used as an ID. the default baud rate element is not a pointer but rather an index to the
 *      baud rate array
 */
typedef struct _Can_Controller
{
    uint8 ControllerId; /*!< Specifies the ID of a CAN controller.
                            This parameter value is defined in Can_Cfg.h */

    uint32 Mode; /*!< Specifies the CAN peripheral operation mode.
                     This parameter can be a value of @ref CAN_mode   */

    uint32 ClockDivider; /*!< Specifies the clock divider for the CAN controller
                           This parameter can be a value of @ref CAN_clock_divider */

    uint8 FrameFormat; /*!< Specifies the CAN frame format FD or Classic.
                            This parameter can be a value of @ref CAN_frame_format     */

    uint8 TransmitPause; /*!< Enable or disable the Transmit Pause feature.
                              This parameter can be set to STD_ON or STD_OFF  */

    uint8 ProtocolException; /*!< Enable or disable the Protocol Exception Handling.
                                  This parameter can be set to STD_ON or STD_OFF  */

    uint8 AutoRetransmission; /*!< Enable or disable the automatic retransmission mode.
                                   This parameter can be set to STD_ON or STD_OFF  */

    uint8 TxFifoQueueMode; /*!< Tx FIFO/Queue Mode selection. Queue mode is basically multiplexed tx
                                This parameter can be a value of @ref CAN_txFifoQueue_Mode */

    uint32 Line0ActiveITs; /*!< Specifies the interrupts to be enabled on Line0.
                               This parameter can be a value of CAN_IT_<interrupt> */

    uint32 Line1ActiveITs; /*!< Specifies the interrupts to be enabled on Line1.
                               This parameter can be a value of CAN_IT_<interrupt> */

    Can_RegisterType *BaseAddress; /*!< Base address of the Mcu CAN controller
                                       this paramter must be CAN1 or CAN2 */

    SramCan_RegisterType *SramBA; /*!< Reference to the SRAM location where the HOH is mapped to
                                       this paramter must be SRAMCAN1 or SRAMCAN2 */

    const Can_ControllerBaudrateConfig *DefaultBaudrate; /*!< Reference to baudrate configuration container configured for the
                                                        Can Controller*/

    const Can_ControllerBaudrateConfig *BaudrateConfigs; /*!< This container contains bit timing related configuration
                                                         parameters */

    uint8 BaudrateConfigsCount; /*!< Number of baudrate configurations for the controller */
} Can_Controller;

/**
 * @brief **CAN Hardware Filter**
 *
 * This container contains the configuration parameters of the CAN hardware filter.
 */
typedef struct _Can_HwFilter
{
    uint32 HwFilterCode; /*!< Specifies (together with the filter mask) the identifiers range that
                             passes the hardware filter */

    uint32 HwFilterMask; /*!< Describes a mask for hardware-based filtering of CAN identifiers */

    uint32 HwFilterType; /*!< Specifies the type of the hardware filter.
                             This parameter can be a value of @ref CAN_Id_Type */

    Can_IdType HwFilterIdType; /*!< Specifies whether the HOH handles standard identifiers or
                                extended, @ref CAN_Id_Type */
} Can_HwFilter;

/**
 * @brief **CAN Hardware Object**
 *
 * This container contains the configuration parameters of the CAN hardware objects.
 */
typedef struct _Can_HardwareObject
{
    uint8 CanObjectId; /*!< Specifies the ID of a hardware object.
                           This paramter can be a set of @ref CAN_Hohs */

    uint8 HandleType; /*!< Specifies the type (Full-CAN or Basic-CAN) of a hardware object.
                          This paramter can be a set of @ref CAN_Hardware_Handler_Type */

    uint16 HwObjectCount; /*!< Number of hardware objects used to implement one HOH.
                              On stm32g0 microcontroller this numnber is fixed to 3 for HTH and HRH */

    Can_IdType IdType; /*!< Specifies whether the HOH handles standard identifiers, extended
                           or mixed, @ref CAN_Id_Type */

    uint8 ObjectPayloadLength; /*!< Specifies the maximum L-PDU payload length in bytes the hardware object can
                                   store. 8 byes for classic or 64 for extended */

    uint8 ObjectType; /*!< Select the type of HOH object, for Tx or Rx
                          This paramter can be a set of  @ref CAN_Hardware_Object_Type */

    uint8 FdPaddingValue; /*!< Specifies the value which is used to pad unspecified data in CAN FD frames > 8
                              bytes for transmission. Any number form 0x00 to 0xff. */

    const Can_HwFilter *HwFilter; /*!< Reference to array of hardware filters structures*/

    uint8 HwFilterCount; /*!< Number of hardware filters used to implement */

    const Can_Controller *ControllerRef; /*!< Reference to CAN Controller to which the HOH is associated to
                                         this paramter must be a address of a valid controller structure  */
} Can_HardwareObject;


/**
 * @brief **Hardware unit configuration structure**
 *
 * This structure contains the paramters to configure the hardware unit incuding the controllers and the
 * hardware objects
 *
 * @reqs    SWS_Can_00413
 */
typedef struct _Can_ConfigType
{
    const Can_Controller *Controllers; /*!< Pointer to the controller structure */
    const Can_HardwareObject *Hohs;    /*!< Pointer to the hardware object structure */
} Can_ConfigType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware unit
 * pointers to controller extructure s
 */
typedef struct _Can_HwUnit
{
    uint8 HwUnitState;                        /*!< CAN hardware unit state */
    const Can_ConfigType *Config;             /*!< Pointer to the configuration structure */
    Can_ControllerStateType *ControllerState; /*!< CAN controller states */
} Can_HwUnit;

#endif /* CAN_TYPES_H__ */

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
 * @brief **CAN Controller Baudrate Configuration**
 *
 * This container contains bit timing related configuration parameters of the CAN controller(s).
 *
 * @note the element ID defined by autosar is suppressed due to the fact that the index array it
 *      is used as an ID
 */
typedef struct _Can_ControllerBaudrateConfig
{
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
    uint32 Mode; /*!< Specifies the CAN peripheral operation mode.
                     This parameter can be a value of @ref CAN_mode   */

    uint32 ClockDivider;  /*!< Specifies the clock divider for the CAN controller
                            This parameter can be a value of @ref CAN_clock_divider */

    uint32 FrameFormat; /*!< Specifies the CAN frame format FD or Classic.
                            This parameter can be a value of @ref CAN_frame_format     */

    uint32 TransmitPause; /*!< Enable or disable the Transmit Pause feature.
                              This parameter can be set to STD_ON or STD_OFF  */

    uint32 ProtocolException; /*!< Enable or disable the Protocol Exception Handling.
                                  This parameter can be set to STD_ON or STD_OFF  */

    uint32 AutoRetransmission; /*!< Enable or disable the automatic retransmission mode.
                                   This parameter can be set to STD_ON or STD_OFF  */

    uint32 TxFifoQueueMode; /*!< Tx FIFO/Queue Mode selection. Queue mode is basically multiplexed tx
                                This parameter can be a value of @ref CAN_txFifoQueue_Mode */

    uint32 StdFiltersNbr; /*!< Specifies the number of standard Message ID filters.
                              This parameter must be a number between 0 and 28 */

    uint32 ExtFiltersNbr; /*!< Specifies the number of extended Message ID filters.
                              This parameter must be a number between 0 and 8 */

    uint32 Line0ActiveITs; /*!< Specifies the interrupts to be enabled on Line0.
                               This parameter can be a value of CAN_IT_<interrupt> */

    uint32 Line1ActiveITs; /*!< Specifies the interrupts to be enabled on Line1.
                               This parameter can be a value of CAN_IT_<interrupt> */

    uint32 TxBufferITs; /*!< Specifies the buffers to be interrupt enable on Tx.
                            This parameter can be a value of @ref CAN_TxBuffer */

    uint32 TxBufferAbortITs; /*!< Specifies the buffers to be interrupt enable on Tx Abort.
                                 This parameter can be a value of @ref CAN_TxBuffer */

    Can_RegisterType *BaseAddress; /*!< Base address of the Mcu CAN controller
                                       this paramter must be CAN1 or CAN2 */

    SramCan_RegisterType *SramBA; /*!< Reference to the SRAM location where the HOH is mapped to
                                       this paramter must be SRAMCAN1 or SRAMCAN2 */

    Can_ControllerBaudrateConfig *DefaultBaudrate; /*!< Reference to baudrate configuration container configured for the
                               Can Controller*/

    const Can_ControllerBaudrateConfig *BaudrateConfigs; /*!< This container contains bit timing related configuration
                                                         parameters */
} Can_Controller;


/**
 * @brief **CAN Hardware Object**
 *
 * This container contains the configuration parameters of the CAN hardware objects.
 */
typedef struct _Can_HardwareObject
{
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

    uint32 HwFilter; /*!< This container is only valid for HRHs and contains the configuration */

    uint32 HwFilterCode; /*!< Specifies (together with the filter mask) the identifiers range that
                             passes the hardware filter */

    uint32 HwFilterMask; /*!< Describes a mask for hardware-based filtering of CAN identifiers */

    const Can_Controller *ControllerRef; /*!< Reference to CAN Controller to which the HOH is associated to
                                         this paramter must be a address of a valid controller structure  */

    SramCan_RegisterType *SramRef; /*!< Reference to the SRAM location where the HOH is mapped to
                                       this paramter must be SRAMCAN1 or SRAMCAN2 */
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
    const Can_ConfigType *Config;             /*!< Pointer to the configuration structure */
    uint8 HwUnitState;                        /*!< CAN hardware unit state */
    Can_ControllerStateType *ControllerState; /*!< CAN controller states */
} Can_HwUnit;

#endif /* CAN_TYPES_H__ */

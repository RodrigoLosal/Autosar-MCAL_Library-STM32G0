/**
 * @file    Can.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The Can module provides services for initiating transmissions and calls the callback functions of
 * the CanIf module for notifying events, independently from the hardware. Furthermore, it provides
 * services to control the behavior and state of the CAN controllers that are belonging to the same
 * CAN Hardware Unit. Several CAN controllers can be controlled by a single Can module as long as
 * they belong to the same CAN Hardware Unit.
 */
#ifndef CAN_H__
#define CAN_H__

#include "Can_Cfg.h"

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
/**
 * @} */


void Can_Init( const Can_ConfigType *Config );
void Can_DeInit( void );
#if CAN_SET_BAUDRATE_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
#endif
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition );
void Can_DisableControllerInterrupts( uint8 Controller );
void Can_EnableControllerInterrupts( uint8 Controller );
Std_ReturnType Can_CheckWakeup( uint8 Controller );
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr );
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType *ControllerModePtr );
Std_ReturnType Can_GetControllerRxErrorCounter( uint8 ControllerId, uint8 *RxErrorCounterPtr );
Std_ReturnType Can_GetControllerTxErrorCounter( uint8 ControllerId, uint8 *TxErrorCounterPtr );
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType *PduInfo );
#if CAN_VERSION_INFO_API == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
void Can_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif
#if CAN_GLOBAL_TIME_SUPPORT == STD_ON /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
Std_ReturnType Can_GetCurrentTime( uint8 ControllerId, Can_TimeStampType *timeStampPtr );
void Can_EnableEgressTimeStamp( Can_HwHandleType Hth );
Std_ReturnType Can_GetEgressTimeStamp( PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr );
Std_ReturnType Can_GetIngressTimeStamp( Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr );
#endif

#endif

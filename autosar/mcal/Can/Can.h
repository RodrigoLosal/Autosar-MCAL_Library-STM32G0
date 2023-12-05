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

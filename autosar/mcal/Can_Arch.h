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

#endif /* CAN_ARCH_H__ */

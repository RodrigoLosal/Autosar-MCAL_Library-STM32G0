/**
 * @file    Can_Arch.c
 * @brief   **Can Specific Arquitecture Driver**
 * @author  Diego Perez
 *
 * Can driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Can driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Can_Cfg.h"
#include "Can_Arch.h"


/**
 * @brief    **Can low level Initialization**
 *
 * Set up the internal register for the CAN controller inside the microcontroller. This function
 * shall take out the controller from the reset mode, set operation mode and initialize the baudrate
 * according to the parameters in config structure, enable the interrupts for the controller and
 * initialize all message objects as free.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Config Pointer to driver configuration
 * @param    Controller Index of the controller to be initialized
 */
void Can_Arch_Init( Can_HwUnit *HwUnit, const Can_ConfigType *Config, uint8 Controller )
{
        (void)HwUnit;
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = Config->Controllers[ Controller ].BaseAddress;

    /* Configure Clock divider */
    CAN_CONFIG->CKDIV = Config->ClockDivider;

    /* Request initialisation */
    Bfx_SetBit_u32u8( (uint32 *)Can->CCCR, CCCR_INIT_BIT );

    /* Wait until the INIT bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( (uint32 *)Can->CCCR, CCCR_INIT_BIT ) == FALSE )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Enable configuration change */
    Bfx_SetBit_u32u8( (uint32 *)Can->CCCR, CCCR_CCE_BIT );

    /* Set the no automatic retransmission */
    Bfx_PutBit_u32u8u8( (uint32 *)Can->CCCR, CCCR_DAR_BIT, Config->Controllers[ Controller ].AutoRetransmission );

    /* Set the transmit pause feature */
    Bfx_PutBit_u32u8u8( (uint32 *)Can->CCCR, CCCR_TXP_BIT, Config->Controllers[ Controller ].TransmitPause );

    /* Set the Protocol Exception Handling */
    Bfx_PutBit_u32u8u8( (uint32 *)Can->CCCR, CCCR_PXHD_BIT, Config->Controllers[ Controller ].ProtocolException );

    /* Set FDCAN Frame Format */
    Bfx_ClrBitMask_u32u32( (uint32 *)Can->CCCR, CAN_FRAME_FD_BRS );
    Bfx_SetBitMask_u32u32( (uint32 *)Can->CCCR, Config->Controllers[ Controller ].FrameFormat );

    /* Reset FDCAN Operation Mode */
    Bfx_ClrBitMask_u32u32( (uint32 *)Can->CCCR, ( ( 1u << CCCR_TEST_BIT ) | ( 1u << CCCR_MON_BIT ) | ( 1u << CCCR_ASM_BIT ) ) );
    Bfx_ClrBit_u32u8( (uint32 *)Can->TEST, TEST_LBCK_BIT );

    /* Set FDCAN Operating Mode:
                 | Normal | Restricted |    Bus     | Internal | External
                 |        | Operation  | Monitoring | LoopBack | LoopBack
       CCCR.TEST |   0    |     0      |     0      |    1     |    1
       CCCR.MON  |   0    |     0      |     1      |    1     |    0
       TEST.LBCK |   0    |     0      |     0      |    1     |    1
       CCCR.ASM  |   0    |     1      |     0      |    0     |    0
    */
    if( Config->Controllers[ Controller ].Mode == CAN_MODE_RESTRICTED_OPERATION )
    {
        /* Enable Restricted Operation mode */
        Bfx_ClrBit_u32u8( (uint32 *)Can->CCCR, CCCR_ASM_BIT );
    }
    else if( Config->Controllers[ Controller ].Mode != CAN_MODE_NORMAL )
    {
        if( Config->Controllers[ Controller ].Mode != CAN_MODE_BUS_MONITORING )
        {
            /* Enable write access to TEST register */
            Bfx_SetBit_u32u8( (uint32 *)Can->CCCR, CCCR_TEST_BIT );
            /* Enable LoopBack mode */
            Bfx_SetBit_u32u8( (uint32 *)Can->TEST, TEST_LBCK_BIT );

            if( Config->Controllers[ Controller ].Mode == CAN_MODE_INTERNAL_LOOPBACK )
            {
                /* Enable Internal LoopBack mode */
                Bfx_SetBit_u32u8( (uint32 *)Can->CCCR, CCCR_MON_BIT );
            }
        }
        else
        {
            /* Enable bus monitoring mode */
            Bfx_SetBit_u32u8( (uint32 *)Can->CCCR, CCCR_MON_BIT );
        }
    }
    else
    {
        /* Nothing to do: normal mode */
    }

    /* Select between Tx FIFO and Tx Queue operation modes */
    Bfx_ClrBitMask_u32u32( (uint32 *)Can->TXBC, CAN_TX_QUEUE_OPERATION );
    Bfx_SetBitMask_u32u32( (uint32 *)Can->TXBC, Config->Controllers[ Controller ].TxFifoQueueMode );

    /* Standard filter elements number */
    Bfx_PutBits_u32u8u8u32( (uint32 *)Can->RXGFC, RXGFC_LSS_BIT, 5u, Config->Controllers[ Controller ].StdFiltersNbr );

    /* Extended filter elements number */
    Bfx_PutBits_u32u8u8u32( (uint32 *)Can->RXGFC, RXGFC_LSE_BIT, 4u, Config->Controllers[ Controller ].ExtFiltersNbr );

    /* Flush the allocated Message RAM area */
    //(void)memset( (void *)Config->Hohs->SramRef, 0x00, sizeof( SRAMCAN1 ) );

    /* Initialize the Latest Tx request buffer index */
    // HwUnit.Config->Controllers[ Controller ].LatestTxFifoQRequest = 0U;

    /* Setup the interrupt to line 0 or 1*/
    Can_SetupConfiguredInterrupts( &Config->Controllers[ Controller ], Can );
}

/**
 * @brief    **Can low level Deinitialization**
 *
 * This function deinitializes the CAN controller. It sets the complete CAN controller into a state
 * comparable to power on reset. All CAN controller registers will be reset to their reset values.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller to be de-initialized
 */
void Can_Arch_DeInit( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can low level Set Baudrate**
 *
 * This function sets the baudrate configuration of the CAN controller. The fucntion will determine
 * if FD baud rate configuration is required and will set the baud rate accordingly.
 * Function does not check if the baud rate configuration is valid.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the baud rate shall be set.
 * @param    BaudRateConfigID references a baud rate configuration by ID
 *
 * @retval  E_OK: Service request accepted, setting of (new) baud rate started
 *          E_NOT_OK: Service request not accepted
 */
Std_ReturnType Can_Arch_SetBaudrate( Can_HwUnit *HwUnit, uint8 Controller, uint16 BaudRateConfigID )
{
    (void)HwUnit;
    (void)Controller;
    (void)BaudRateConfigID;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Set Controller Mode**
 *
 * This function performs software triggered state transitions of the CAN controller State machine.
 * Trnasitions are: Start, Stop, Wakeup, Reset. It is required a previous state in order to proceed
 * with the requested transition, otherwise the function will return E_NOT_OK.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the status shall be changed.
 * @param    Transition Transition value to request new state.
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 */
Std_ReturnType Can_Arch_SetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType Transition )
{
    (void)HwUnit;
    (void)Controller;
    (void)Transition;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Enable Controller Interrupts**
 *
 * This function enables all interrupts for this CAN controller. The function will only enable the
 * internals interrupt lines zero and one, the external interrupt line must be enabled by the
 * application using the Nvic Driver.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which interrupts shall be enabled.
 */
void Can_Arch_EnableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can low level Disable Controller Interrupts**
 *
 * This function disables all interrupts for this CAN controller. The function will only disable the
 * internals interrupt lines zero and one, the external interrupt line must be disabled by the
 * application using the Nvic Driver.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which interrupts shall be disabled.
 */
void Can_Arch_DisableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can low level wakeup check**
 *
 * This function checks if a wakeup has occurred for the given controller.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the wakeup shall be checked.
 *
 * @retval  E_OK: wakeup detected
 *          E_NOT_OK: no wakeup detected
 */
Std_ReturnType Can_Arch_CheckWakeup( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Controller Error State**
 *
 * This function returns the error state of the CAN controller reading the internal registers.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ControllerId CanIf ControllerId which is assigned to a CAN controller, which is
 *                          requested for ErrorState.
 * @param    ErrorStatePtr Pointer to a memory location, where the error state of the CAN
 *                          controller will be stored.
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 */
Std_ReturnType Can_Arch_GetControllerErrorState( Can_HwUnit *HwUnit, uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    (void)HwUnit;
    (void)ControllerId;
    (void)ErrorStatePtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Controller Mode**
 *
 * The fucntion only returns the current software flag which stores the mode of the CAN controller
 * set by the Can_Arch_SetControllerMode() function. It does not read any hardware registers
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the status shall be read.
 * @param    ControllerModePtr Pointer to a memory location, where the current mode of the CAN
 *
 * @retval  E_OK: request accepted
 *          E_NOT_OK: request not accepted
 */
Std_ReturnType Can_Arch_GetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType *ControllerModePtr )
{
    (void)HwUnit;
    (void)Controller;
    (void)ControllerModePtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Controller Rx Error Counter**
 *
 * Reads and return the Rx internal error counter of the can peripheral
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ControllerId CAN controller, whose current Rx error counter shall be acquired.
 * @param    RxErrorCounterPtr Pointer to a memory location, where the current Rx error counter
 *                              of the CAN controller will be stored.
 *
 * @retval  E_OK: Rx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
 */
Std_ReturnType Can_Arch_GetControllerRxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    (void)HwUnit;
    (void)ControllerId;
    (void)RxErrorCounterPtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Controller Tx Error Counter**
 *
 * Reads and return the Tx internal error counter of the can peripheral
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ControllerId: CAN controller, whose current Tx error counter shall be acquired.
 * @param    TxErrorCounterPtr: Pointer to a memory location, where the current Tx error counter
 *
 * @retval  E_OK: Tx error counter available.
 *          E_NOT_OK: Wrong ControllerId, or Tx error counter not
 */
Std_ReturnType Can_Arch_GetControllerTxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    (void)HwUnit;
    (void)ControllerId;
    (void)TxErrorCounterPtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Current Time**
 *
 * Returns a time value out of the HW registers.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    ControllerId: CAN controller, whose current time shall be acquired.
 * @param    timeStampPtr: Pointer to a memory location, where the current time of the CAN
 *
 * @retval  E_OK: successful
 *          E_NOT_OK: failed
 */
Std_ReturnType Can_Arch_GetCurrentTime( Can_HwUnit *HwUnit, uint8 ControllerId, Can_TimeStampType *timeStampPtr )
{
    (void)HwUnit;
    (void)ControllerId;
    (void)timeStampPtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Enable Egress TimeStamp**
 *
 * Activates egress time stamping on the messages to be transmitted.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Hth: information which HW-transmit handle shall be used for enabling the time stamp.
 *
 * @note    This is the smallest granularity which can be added for enabling the
 *          timestamp, at HTH level, without affecting the performance.
 */
void Can_Arch_EnableEgressTimeStamp( Can_HwUnit *HwUnit, Can_HwHandleType Hth )
{
    (void)HwUnit;
    (void)Hth;
}

/**
 * @brief    **Can low level Get Egress TimeStamp**
 *
 * Reads back the egress time stamp on a dedicated message object. It needs to be
 * called within the TxConfirmation() function.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    TxPduId: Tx-PDU handle of CAN L-PDU that has been transmitted.
 * @param    Hth: information which HW-transmit handle shall be used for reading the time stamp.
 * @param    timeStampPtr: Pointer to a memory location where the time stamp value shall be stored.
 *
 * @retval  E_OK: success
 *          E_NOT_OK: failed to read time stamp.
 */
Std_ReturnType Can_Arch_GetEgressTimeStamp( Can_HwUnit *HwUnit, PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr )
{
    (void)HwUnit;
    (void)TxPduId;
    (void)Hth;
    (void)timeStampPtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Get Ingress TimeStamp**
 *
 * Reads back the ingress time stamp on a dedicated message object. It needs to be
 * called within the RxIndication() function.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Hrh: information which HW-receive handle shall be used for reading the time stamp.
 * @param    timeStampPtr: Pointer to a memory location where the time stamp value shall be stored.
 *
 * @retval  E_OK: success
 *          E_NOT_OK: failed to read time stamp.
 */
Std_ReturnType Can_Arch_GetIngressTimeStamp( Can_HwUnit *HwUnit, Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr )
{
    (void)HwUnit;
    (void)Hrh;
    (void)timeStampPtr;

    return E_NOT_OK;
}

/**
 * @brief    **Can low level Write**
 *
 * The function stores the message pointed to by PduInfo into the internal Tx message buffer of the CAN
 * Sram area and activates the corresponding hardware transmit bits. It reades the hardware fifo index
 * to know which of the three buffers is available for transmission. The function will return CAN_BUSY
 * if no buffer is available.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Hth: information which HW-transmit handle shall be used for transmit. Implicitly this
 *                  is also the information about the controller to use because the Hth numbers
 *                  are unique inside one hardware unit.
 * @param    PduInfo: Pointer to SDU user memory, Data Length and Identifier
 *
 * @retval  E_OK: Write command has been accepted
 *          E_NOT_OK: development error occurred
 *          CAN_BUSY: No TX hardware buffer available or pre-emptive call of Can_Write that can't be
 *          implemented re-entrant (see Can_ReturnType)
 */
Std_ReturnType Can_Arch_Write( Can_HwUnit *HwUnit, Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    (void)HwUnit;
    (void)Hth;
    (void)PduInfo;

    return E_NOT_OK;
}

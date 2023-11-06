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
#include "Bfx.h"

/**
 * @defgroup CCR_bits CCCR register bits
 *
 * @{ */
#define CCCR_INIT_BIT        0u  /*!< Initialization bit */
#define CCCR_CCE_BIT         1u  /*!< Configuration change enable bit */
#define CCCR_ASM_BIT         2u  /*!< Restricted operation mode bit */
#define CCCR_CSA_BIT         3u  /*!< Clock stop acknowledge bit */
#define CCCR_CSR_BIT         4u  /*!< Clock stop request bit */
#define CCCR_MON_BIT         5u  /*!< Bus monitoring mode bit */
#define CCCR_DAR_BIT         6u  /*!< Disable automatic retransmission bit */
#define CCCR_TEST_BIT        7u  /*!< Test mode enable bit */
#define CCCR_PXHD_BIT        12u /*!< Protocol exception handling disable bit */
#define CCCR_TXP_BIT         14u /*!< Transmit pause bit */
/**
 * @} */

/**
 * @defgroup TEST_bits TEST register bits
 *
 * @{ */
#define TEST_LBCK_BIT        4u /*!< Loop back mode bit */
/**
 * @} */

/**
 * @defgroup NBTP_bits NBTP register bits
 *
 * @{ */
#define NBTP_NTSEG2_BIT      0u  /*!< Nominal Time Segment 2 */
#define NBTP_NTSEG1_BIT      8u  /*!< Nominal Time Segment 1 */
#define NBTP_NBRP_BIT        16u /*!< Nominal Baud Rate Prescaler */
#define NBTP_NSJW_BIT        25u /*!< Nominal (Re)Synchronization Jump Width */
/**
 * @} */

/**
 * @defgroup NBTP_bits NBTP register bit sizes
 *
 * @{ */
#define NBTP_NSJW_SIZE       7u /*!< Nominal Jump Width bitfiled size*/
#define NBTP_NTSEG1_SIZE     8u /*!< Nominal Time Segment 1 bitfiled size*/
#define NBTP_NTSEG2_SIZE     7u /*!< Nominal Time Segment 2 bitfiled size*/
#define NBTP_NBRP_SIZE       9u /*!< Nominal Baud Rate Prescaler bitfiled size*/
/**
 * @} */

/**
 * @defgroup DBTP_bits DBTP register bits
 *
 * @{ */
#define DBTP_DSJW_BIT        0u  /*!< Data (Re)Synchronization Jump Width */
#define DBTP_DTSEG1_BIT      8u  /*!< Data Time Segment 1 */
#define DBTP_DTSEG2_BIT      4u  /*!< Data Time Segment 2 */
#define DBTP_DBRP_BIT        16u /*!< Data Baud Rate Prescaler */
/**
 * @} */

/**
 * @defgroup DBTP_bits DBTP register bit sizes
 *
 * @{ */
#define DBTP_DSJW_SIZE       0u  /*!< Data Jump Width bitfiled size*/
#define DBTP_DTSEG1_SIZE     8u  /*!< Data Time Segment 1 bitfiled size*/
#define DBTP_DTSEG2_SIZE     4u  /*!< Data Time Segment 2 bitfiled size*/
#define DBTP_DBRP_SIZE       16u /*!< Nominal Baud Rate Preescaler bitfiled size*/
/**
 * @} */

/**
 * @defgroup RXGFC_bits RXGFC register bits
 */
#define RXGFC_LSS_BIT        16u /*!< List Size Standard */
#define RXGFC_LSE_BIT        24u /*!< List Size Extended */
/**
 * @} */

/**
 * @defgroup ECR_bits ECR register bits
 *
 * @{ */
#define ECR_TEC_BIT          0u /*!< Transmit Error Counter */
#define ECR_REC_BIT          8u /*!< Receive Error Counter */
/**
 * @} */

/**
 * @defgroup ECR_bits ECR register bit sizes
 *
 * @{ */
#define ECR_TEC_SIZE         8u /*!< Transmit Error Counter bitfiled size*/
#define ECR_REC_SIZE         7u /*!< Receive Error Counter bitfiled size*/
/**
 * @} */

/**
 * @defgroup TXFQS_bits TXFQS register bits
 *
 * @{ */
#define TXFQS_TFQF_BIT       20u /*!< Tx FIFO/Queue Full */
#define TXFQS_TFQPI_BIT      16u /*!< Tx FIFO/Queue Put Index */
#define TXFQS_TFQPI_SIZE     2u  /*!< Tx FIFO/Queue Put Index bitfiled size*/
/**
 * @} */

/**
 * @defgroup TX_Buffer_bits TX Buffer header register bits
 *
 * @{ */
#define TX_BUFFER_ID_11_BITS 18u /*!< Tx standard ID bit */
#define TX_BUFFER_ID_29_BITS 0u  /*!< Tx extended ID bit */
#define TX_BUFFER_XTD_BIT    30u /*!< Extended identifier bit */
#define TX_BUFFER_DLC_BIT    16u /*!< Data length code bit */
#define TX_BUFFER_BRS_BIT    20u /*!< Bit rate switch bit */
#define TX_BUFFER_FDF_BIT    21u /*!< FD format bit */
#define TX_BUFFER_EFC_BIT    23u /*!< Event FIFO Control bit */
/**
 * @} */

/**
 * @defgroup TX_Buffer_bits TX Buffer header register bit sizes
 *
 * @{ */
#define TX_BUFFER_ID_11_SIZE 11u /*!< Tx standard ID bitfield size */
#define TX_BUFFER_ID_29_SIZE 29u /*!< Tx extended ID bitfield size */
#define TX_BUFFER_DLC_SIZE   4u  /*!< Data length code bitfield size */
/**
 * @} */

/**
 * @defgroup ID_Msg_bits ID message bits
 *
 * @{ */
#define MSG_ID_BIT           31u /*!< ID bit */
#define MSG_FROMAT_BIT       30u /*!< Fromat ID bit */
/**
 * @} */

/**
 * @defgroup ID_Type_msg    ID Type message (bit 31) from id message
 *
 * @{ */
#define MSG_STANDARD_ID      0u
#define MSG_EXTENDED_ID      1u
/**
 * @} */

/**
 * @defgroup Frame_Type_msg    Frame Type message (bit 30) from id message
 *
 * @{ */
#define MSG_CLASSIC_FORMAT   0u
#define MSG_FD_FORMAT        1u
/**
 * @} */


/**
 * @brief  Tx Hardware objecj descriptor.
 */
typedef struct _HwHthObject
{
    uint32 TBSAHeader1;       /*!< Tx Buffer Standard Address Header 1 */
    uint32 TBSAHeader2;       /*!< Tx Buffer Standard Address Header 2 */
    uint32 TBSAPayload[ 16 ]; /*!< Tx Buffer Standard Address Payload */
} HwHthObject;


static void Can_SetupConfiguredInterrupts( const Can_Controller *Controller, Can_RegisterType *Can );
static uint8 Can_GetClosestDlcWithPadding( uint8 Dlc, uint32 *RamBuffer, uint8 PaddingValue );
static void Can_Isr_RxFifo0NewMessage( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_RxFifo0Full( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_RxFifo0MessageLost( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_RxFifo1NewMessage( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_RxFifo1Full( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_RxFifo1MessageLost( Can_HwUnit *HwUnit, uint8 Controller );
static void Can_Isr_HighPriorityMessageRx( Can_HwUnit *HwUnit, uint8 Controller );

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
 *
 * @reqs    SWS_Can_00237, SWS_Can_00236, SWS_Can_00238, SWS_Can_00239, SWS_Can_00419, SWS_Can_00250,
 *          SWS_Can_00053, SWS_Can_00407, SWS_Can_00021, SWS_Can_00291, SWS_Can_00413, SWS_Can_00223
 */
void Can_Arch_Init( Can_HwUnit *HwUnit, const Can_ConfigType *Config, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;
    /* get default baudrate values */
    uint8 DefaultBaudrate = ControllerConfig->DefaultBaudrate;

    /* Configure Clock divider */
    Can->CKDIV = Config->ClockDivider;

    /* Flush the allocated Message RAM area */
    for( uint8 i = 0u; i < ( sizeof( SramCan_RegisterType ) / sizeof( uint32 ) ); i++ )
    {
        /* Flush the allocated Message RAM area */
        ( (uint32 *)ControllerConfig->SramBA )[ i ] = 0x00000000u;
    }

    /* Request initialisation */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

    /* Wait until the INIT bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT ) == FALSE )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Enable configuration change */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CCE_BIT );

    /* Set the no automatic retransmission */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_DAR_BIT, ControllerConfig->AutoRetransmission );

    /* Set the transmit pause feature */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_TXP_BIT, ControllerConfig->TransmitPause );

    /* Set the Protocol Exception Handling */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_PXHD_BIT, ControllerConfig->ProtocolException );

    /* Set FDCAN Frame Format */
    Bfx_ClrBitMask_u32u32( (uint32 *)&Can->CCCR, CAN_FRAME_FD_BRS );
    Bfx_SetBitMask_u32u32( (uint32 *)&Can->CCCR, ControllerConfig->FrameFormat );

    /* Reset FDCAN Operation Mode */
    Bfx_ClrBitMask_u32u32( (uint32 *)&Can->CCCR, ( ( 1u << CCCR_TEST_BIT ) | ( 1u << CCCR_MON_BIT ) | ( 1u << CCCR_ASM_BIT ) ) );
    Bfx_ClrBit_u32u8( (uint32 *)&Can->TEST, TEST_LBCK_BIT );

    /* Set FDCAN Operating Mode:
                 | Normal | Restricted |    Bus     | Internal | External
                 |        | Operation  | Monitoring | LoopBack | LoopBack
       CCCR.TEST |   0    |     0      |     0      |    1     |    1
       CCCR.MON  |   0    |     0      |     1      |    1     |    0
       TEST.LBCK |   0    |     0      |     0      |    1     |    1
       CCCR.ASM  |   0    |     1      |     0      |    0     |    0
    */
    if( ControllerConfig->Mode == CAN_MODE_RESTRICTED_OPERATION )
    {
        /* Enable Restricted Operation mode */
        Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_ASM_BIT );
    }
    else if( ControllerConfig->Mode != CAN_MODE_NORMAL )
    {
        if( ControllerConfig->Mode != CAN_MODE_BUS_MONITORING )
        {
            /* Enable write access to TEST register */
            Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_TEST_BIT );
            /* Enable LoopBack mode */
            Bfx_SetBit_u32u8( (uint32 *)&Can->TEST, TEST_LBCK_BIT );

            if( ControllerConfig->Mode == CAN_MODE_INTERNAL_LOOPBACK )
            {
                /* Enable Internal LoopBack mode */
                Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_MON_BIT );
            }
        }
        else
        {
            /* Enable bus monitoring mode */
            Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_MON_BIT );
        }
    }
    else
    {
        /* Nothing to do: normal mode */
    }

    /* Set the default nominal bit timing register */
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NSJW_BIT, NBTP_NSJW_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].SyncJumpWidth - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG1_BIT, NBTP_NTSEG1_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].Seg1 - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG2_BIT, NBTP_NTSEG2_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].Seg2 - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NBRP_BIT, NBTP_NBRP_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].Prescaler - 1u ) );

    /*set default data bit timing register id FD is active*/
    if( ( ControllerConfig->FrameFormat == CAN_FRAME_FD_BRS ) )
    {
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DSJW_BIT, DBTP_DSJW_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].FdSyncJumpWidth - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG1_BIT, DBTP_DTSEG1_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].FdSeg1 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG2_BIT, DBTP_DTSEG2_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].FdSeg2 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DBRP_BIT, DBTP_DBRP_SIZE, ( ControllerConfig->BaudrateConfigs[ DefaultBaudrate ].FdPrescaler - 1u ) );
    }

    /* Select between Tx FIFO and Tx Queue operation modes */
    Bfx_ClrBitMask_u32u32( (uint32 *)&Can->TXBC, CAN_TX_QUEUE_OPERATION );
    Bfx_SetBitMask_u32u32( (uint32 *)&Can->TXBC, ControllerConfig->TxFifoQueueMode );

    /* Standard filter elements number */
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_LSS_BIT, 5u, ControllerConfig->StdFiltersNbr );

    /* Extended filter elements number */
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_LSE_BIT, 4u, ControllerConfig->ExtFiltersNbr );

    /* Setup the interrupt to line 0 or 1*/
    Can_SetupConfiguredInterrupts( &Config->Controllers[ Controller ], Can );

    /*paramter not in use, placed to keep standard and for potential future use*/
    (void)HwUnit;
}

/**
 * @brief    **Can low level Deinitialization**
 *
 * This function deinitializes the CAN controller. It sets the complete CAN controller into a state
 * comparable to power on reset. All CAN controller registers will be reset to their reset values.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller to be de-initialized
 *
 * @reqs    SWS_Can_00223
 */
void Can_Arch_DeInit( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;

    /* Request initialisation */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

    /* Wait until the INIT bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT ) == FALSE )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Exit from Sleep mode */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

    /* Wait until FDCAN exits sleep mode */
    while( Bfx_GetBit_u32u8_u8( (uint32 *)&Can->CCCR, CCCR_CSA_BIT ) == FALSE )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Enable configuration change */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CCE_BIT );

    /* Disable interrupt lines */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE0 );
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE1 );
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
 *
 * @reqs    SWS_Can_00255, SWS_Can_00256, SWS_Can_00260, SWS_Can_00422, SWS_Can_00500
 *          SWS_Can_00062
 */
Std_ReturnType Can_Arch_SetBaudrate( Can_HwUnit *HwUnit, uint8 Controller, uint16 BaudRateConfigID )
{
    Std_ReturnType RetVal = E_NOT_OK;

    if( HwUnit->ControllerState[ Controller ] == CAN_CS_STOPPED )
    {
        /* get controller configuration */
        const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
        /*Get the Can controller register structure*/
        Can_RegisterType *Can = ControllerConfig->BaseAddress;
        /* get baudrate configuration */
        const Can_ControllerBaudrateConfig *Baudrate = &ControllerConfig->BaudrateConfigs[ BaudRateConfigID ];

        /* Set the nominal bit timing register */
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NSJW_BIT, NBTP_NSJW_SIZE, ( Baudrate->SyncJumpWidth - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG1_BIT, NBTP_NTSEG1_SIZE, ( Baudrate->Seg1 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG2_BIT, NBTP_NTSEG2_SIZE, ( Baudrate->Seg2 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NBRP_BIT, NBTP_NBRP_SIZE, ( Baudrate->Prescaler - 1u ) );

        /* If FD operation with BRS is selected, set the data bit timing register */
        if( ( HwUnit->Config->Controllers[ Controller ].FrameFormat == CAN_FRAME_FD_BRS ) )
        {
            Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DSJW_BIT, DBTP_DSJW_SIZE, ( Baudrate->FdSyncJumpWidth - 1u ) );
            Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG1_BIT, DBTP_DTSEG1_SIZE, ( Baudrate->FdSeg1 - 1u ) );
            Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG2_BIT, DBTP_DTSEG2_SIZE, ( Baudrate->FdSeg2 - 1u ) );
            Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DBRP_BIT, DBTP_DBRP_SIZE, ( Baudrate->FdPrescaler - 1u ) );
        }

        RetVal = E_OK;
    }

    return RetVal;
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
 *
 * @reqs    SWS_Can_00261, SWS_Can_00409, SWS_Can_00265, SWS_Can_00266, SWS_Can_00411, SWS_Can_00017
 *          SWS_Can_00384
 */
Std_ReturnType Can_Arch_SetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType Transition )
{
    Std_ReturnType RetVal = E_NOT_OK;
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;

    switch( Transition )
    {
        case CAN_CS_STARTED:
            /*Transition shall be carried out from STOPPED to STARTED*/
            if( HwUnit->ControllerState[ Controller ] == CAN_CS_STOPPED )
            {
                /* Request leave initialisation */
                Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

                /* Change CAN peripheral state */
                HwUnit->ControllerState[ Controller ] = CAN_CS_STARTED;

                RetVal = E_OK;
            }
            break;

        case CAN_CS_STOPPED:
            /*Transition shall be carried out from STARTED to STOPPED*/
            if( HwUnit->ControllerState[ Controller ] == CAN_CS_STARTED )
            {
                /* Request initialisation */
                Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

                /* Wait until the INIT bit into CCCR register is set */
                while( Bfx_GetBit_u32u8_u8( (uint32 *)Can->CCCR, CCCR_INIT_BIT ) == FALSE )
                {
                    /*Wee need to stablish a timeout counter to avois a potential endless loop,
                    according to AUTOSAR a Os tick shall be used, but for the moment it will
                    remain empty*/
                }

                /* Exit from Sleep mode */
                Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

                /* Wait until FDCAN exits sleep mode */
                while( Bfx_GetBit_u32u8_u8( (uint32 *)Can->CCCR, CCCR_CSA_BIT ) == FALSE )
                {
                    /*Wee need to stablish a timeout counter to avois a potential endless loop,
                    according to AUTOSAR a Os tick shall be used, but for the moment it will
                    remain empty*/
                }

                /* Enable configuration change */
                Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CCE_BIT );

                /* Change CAN peripheral state */
                HwUnit->ControllerState[ Controller ] = CAN_CS_STOPPED;

                RetVal = E_OK;
            }
            break;

        case CAN_CS_SLEEP:
            /*Transition shall be carried out from STOPPED to SLEEP*/
            if( HwUnit->ControllerState[ Controller ] == CAN_CS_STOPPED )
            {
                /* Request clock stop */
                Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

                /* Wait until CAN is ready for power down */
                while( Bfx_GetBit_u32u8_u8( (uint32 *)&Can->CCCR, CCCR_CSA_BIT ) == FALSE )
                {
                    /*Wee need to stablish a timeout counter to avois a potential endless loop,
                    according to AUTOSAR a Os tick shall be used, but for the moment it will
                    remain empty*/
                }

                /* Change CAN peripheral state */
                HwUnit->ControllerState[ Controller ] = CAN_CS_SLEEP;
            }
            break;

        default:
            RetVal = E_NOT_OK;
            break;
    }

    return RetVal;
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
 *
 * @reqs    SWS_Can_00208
 */
void Can_Arch_EnableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;

    /* Enable Interrupt line 0 */
    Bfx_SetBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE0 );

    /* Enable Interrupt line 1 */
    Bfx_SetBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE1 );
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
 *
 * @reqs    SWS_Can_00049
 */
void Can_Arch_DisableControllerInterrupts( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;

    /* Disable interrupt line 0 */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE0 );

    /* Disable interrupt line 1 */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE1 );
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
 *
 * @reqs    SWS_Can_91014, SWS_Can_91015
 */
Std_ReturnType Can_Arch_GetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType *ControllerModePtr )
{
    *ControllerModePtr = HwUnit->ControllerState[ Controller ];

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
 *
 * @reqs    SWS_Can_00511, SWS_Can_00515
 */
Std_ReturnType Can_Arch_GetControllerRxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *RxErrorCounterPtr )
{
    const Can_RegisterType *Can = HwUnit->Config->Controllers[ ControllerId ].BaseAddress;

    /* Read the error counters register */
    *RxErrorCounterPtr = Bfx_GetBits_u32u8u8_u32( Can->ECR, ECR_REC_BIT, ECR_REC_SIZE );

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
 *
 * @reqs    SWS_Can_00516, SWS_Can_00520
 */
Std_ReturnType Can_Arch_GetControllerTxErrorCounter( Can_HwUnit *HwUnit, uint8 ControllerId, uint8 *TxErrorCounterPtr )
{
    const Can_RegisterType *Can = HwUnit->Config->Controllers[ ControllerId ].BaseAddress;

    /* Read the error counters register */
    *TxErrorCounterPtr = Bfx_GetBits_u32u8u8_u32( Can->ECR, ECR_TEC_BIT, ECR_TEC_SIZE );

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
 *
 * @reqs    SWS_Can_00213, SWS_Can_00214, SWS_Can_00275, SWS_Can_00277, SWS_Can_00401, SWS_Can_00402
 *          SWS_Can_00403, SWS_Can_00011, SWS_Can_00486, SWS_Can_00502
 */
Std_ReturnType Can_Arch_Write( Can_HwUnit *HwUnit, Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    Std_ReturnType RetVal = E_NOT_OK;
    uint8 DataLenght;
    uint32 RamBuffer[ 16u ];

    /* get controller configuration */
    const Can_RegisterType *Can = HwUnit->Config->Hohs[ Hth ].ControllerRef;

    /* Check that the Tx FIFO/Queue is not full*/
    if( ( Bfx_GetBit_u32u8_u8( (uint32 *)Can->TXFQS, TXFQS_TFQF_BIT ) == FALSE ) )
    {
        /* Retrieve the Tx FIFO PutIndex */
        uint32 PutIndex = Bfx_GetBits_u32u8u8_u32( Can->TXFQS, TXFQS_TFQPI_BIT, TXFQS_TFQPI_SIZE );

        /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
        HwHthObject *HthObject = (HwHthObject *)&HwUnit->Config->Hohs[ Hth ].SramRef->TBSA;

        /*get the message ID type*/
        uint8 IdType = Bfx_GetBit_u32u8_u8( (uint32 *)&PduInfo->id, MSG_ID_BIT );

        /* Set the message ID, standard (11 bits) or extended (29 bits) */
        if( IdType == MSG_STANDARD_ID )
        {
            Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].TBSAHeader1, TX_BUFFER_ID_11_BITS, TX_BUFFER_ID_11_SIZE, PduInfo->id );
            /* Write the ID type bit */
            Bfx_ClrBit_u32u8( &HthObject[ PutIndex ].TBSAHeader1, TX_BUFFER_XTD_BIT );
        }
        else
        {
            Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].TBSAHeader1, TX_BUFFER_ID_29_BITS, TX_BUFFER_ID_29_SIZE, PduInfo->id );
            /* Write the ID type bit */
            Bfx_SetBit_u32u8( &HthObject[ PutIndex ].TBSAHeader1, TX_BUFFER_XTD_BIT );
        }

        /* Get the type of frame to send */
        uint8 FrameType = Bfx_GetBit_u32u8_u8( (uint32 *)&PduInfo->id, MSG_FROMAT_BIT );

        /* Set the frame */
        if( FrameType == MSG_CLASSIC_FORMAT )
        {
            /*Frame format*/
            Bfx_ClrBit_u32u8( &HthObject[ PutIndex ].TBSAHeader2, TX_BUFFER_FDF_BIT );
            /* Set the actual data lenght (DLC) */
            DataLenght = PduInfo->length;
        }
        else
        {
            /*Frame format*/
            Bfx_SetBit_u32u8( &HthObject[ PutIndex ].TBSAHeader2, TX_BUFFER_FDF_BIT );
            /* Get the actual data lenght (DLC) */
            DataLenght = Can_GetClosestDlcWithPadding( PduInfo->length, RamBuffer, HwUnit->Config->Hohs[ Hth ].FdPaddingValue );
        }

        /*Store Tx Events*/
        Bfx_SetBit_u32u8( &HthObject[ PutIndex ].TBSAHeader2, TX_BUFFER_EFC_BIT );

        /* copy message into a 32bit wide buffer*/
        for( uint8 Byte = 0; Byte < DataLenght; Byte++ )
        {
            ( (uint8 *)RamBuffer )[ Byte ] = PduInfo->sdu[ Byte ];
        }
        /* Write message data lenght */
        Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].TBSAHeader2, TX_BUFFER_DLC_BIT, TX_BUFFER_DLC_SIZE, DataLenght );

        /* Write Tx payload to the message RAM */
        for( uint8 Word = 0; Word < DataLenght; Word++ )
        {
            HthObject[ PutIndex ].TBSAPayload[ Word ] = RamBuffer[ Word ];
        }

        /* Activate the corresponding transmission request */
        Bfx_SetBit_u32u8( (uint32 *)Can->TXBAR, PutIndex );

        RetVal = E_OK;
    }
    else
    {
        RetVal = CAN_BUSY;
    }

    return RetVal;
}

/**
 * @brief    **Can Interrupt Handler**
 *
 * This function is the interrupt handler for the Can controller, it will check the interrupt flags
 * and call the corresponding callback functions.
 */
void Can_Arch_IsrMainHandler( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = ControllerConfig->BaseAddress;

    /* clang-format off */
    void (*IsrPointer[])(Can_HwUnit*, uint8) = 
    {
        Can_Isr_RxFifo0NewMessage,
        Can_Isr_RxFifo0Full,
        Can_Isr_RxFifo0MessageLost,
        Can_Isr_RxFifo1NewMessage,
        Can_Isr_RxFifo1Full,
        Can_Isr_RxFifo1MessageLost,
        Can_Isr_HighPriorityMessageRx
    };
    /* clang-format on */

    for( uint8 Interrupt = 0u; Interrupt < sizeof( IsrPointer ); Interrupt++ )
    {
        /* High Priority Message interrupt management */
        if( Bfx_GetBit_u32u8_u8( (uint32 *)Can->IR, Interrupt ) == STD_ON )
        {
            if( Bfx_GetBit_u32u8_u8( (uint32 *)Can->IE, Interrupt ) == STD_ON )
            {
                /* Clear the High Priority Message flag */
                Bfx_SetBit_u32u8( (uint32 *)&Can->IR, Interrupt );

                /* High Priority Message Callback */
                IsrPointer[ Interrupt ]( HwUnit, Controller );
            }
        }
    }
}


/**
 * @brief    **setup Can controller interrupts**
 *
 * This function setup the interrupts for the Can controller, tkaes the values in Line0ActiveITs and
 * Line1ActiveITs and assign to interrupt lines plus enable the Tx complete and abort interrupts
 *
 * @param    Controller: CAN controller for which the status shall be changed.
 * @param    Can: Pointer to the Can controller register structure
 */
static void Can_SetupConfiguredInterrupts( const Can_Controller *Controller, Can_RegisterType *Can )
{
    /* Enable the slected interrupts to their corresponding interrupt lines */
    Bfx_SetBitMask_u32u32( (uint32 *)&Can->IE, Controller->Line0ActiveITs | Controller->Line1ActiveITs );

    /* Assign group of interrupts Rx Fifo 0 to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_RX_FIFO0, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_RX_FIFO0 ) != 0 ) );

    /* Assign group of interrupts Rx Fifo 1 to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_RX_FIFO1, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_RX_FIFO1 ) != 0 ) );

    /* Assign group of interrupts SMSG to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_SMSG, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_SMSG ) != 0 ) );

    /* Assign group of interrupts Tx Fifo/Queue Error to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_TX_FIFO_ERROR, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_TX_FIFO_ERROR ) != 0 ) );

    /* Assign group of interrupts Tx Event Fifo to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_MISC, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_MISC ) != 0 ) );

    /* Assign group of interrupts Bit line errors to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_BIT_LINE_ERROR, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_BIT_LINE_ERROR ) != 0 ) );

    /* Assign group of interrupts Protocol errors to line 0 or line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_PROTOCOL_ERROR, (uint8)( ( Controller->Line1ActiveITs & CAN_IT_LIST_PROTOCOL_ERROR ) != 0 ) );


    /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
         but interrupt will only occur if TC is enabled in IE register */
    if( ( ( Controller->Line1ActiveITs & CAN_IT_TX_COMPLETE ) != 0u ) || ( ( Controller->Line0ActiveITs & CAN_IT_TX_COMPLETE ) != 0u ) )
    {
        Bfx_SetBitMask_u32u32( (uint32 *)&Can->TXBTIE, Controller->TxBufferITs );
    }

    /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
         but interrupt will only occur if TCF is enabled in IE register */
    if( ( ( Controller->Line1ActiveITs & CAN_IT_TX_ABORT_COMPLETE ) != 0u ) || ( ( Controller->Line0ActiveITs & CAN_IT_TX_ABORT_COMPLETE ) != 0u ) )
    {
        Bfx_SetBitMask_u32u32( (uint32 *)&Can->TXBCIE, Controller->TxBufferAbortITs );
    }
}

/**
 * @brief    **Determine data lenth to send**
 *
 * This function determines the data lenght to send according to the CAN FD specification, in case
 * the actual data lenght do not match with any of the available data lenghts, the function will
 * return the closest data lenght with padding.
 *
 * @param    Dlc: Data lenght to send
 * @param    RamBuffer: Pointer to the buffer where the data will be stored
 * @param    PaddingValue: Value to use for padding
 *
 * @retval  DataLenght: Define with for data lenght to send
 */
static uint8 Can_GetClosestDlcWithPadding( uint8 Dlc, uint32 *RamBuffer, uint8 PaddingValue )
{
    uint8 DataLenght = 0u;

    /*set padding value*/
    for( uint8 Byte = 0u; Byte < Dlc; Byte++ )
    {
        ( (uint8 *)RamBuffer )[ Byte ] = PaddingValue;
    }

    if( ( Dlc > 8u ) && ( Dlc <= 12u ) )
    {
        DataLenght = CAN_OBJECT_PL_12;
    }
    else if( ( Dlc > 12u ) && ( Dlc <= 16u ) )
    {
        DataLenght = CAN_OBJECT_PL_16;
    }
    else if( ( Dlc > 16u ) && ( Dlc <= 20u ) )
    {
        DataLenght = CAN_OBJECT_PL_20;
    }
    else if( ( Dlc > 20u ) && ( Dlc <= 24u ) )
    {
        DataLenght = CAN_OBJECT_PL_24;
    }
    else if( ( Dlc > 24u ) && ( Dlc <= 32u ) )
    {
        DataLenght = CAN_OBJECT_PL_32;
    }
    else if( ( Dlc > 32u ) && ( Dlc <= 48u ) )
    {
        DataLenght = CAN_OBJECT_PL_48;
    }
    else if( ( Dlc > 48u ) && ( Dlc <= 64u ) )
    {
        DataLenght = CAN_OBJECT_PL_64;
    }
    else
    {
        DataLenght = CAN_OBJECT_PL_8;
    }

    return DataLenght;
}

/**
 * @brief    **Can Rx Fifo 0 New Message Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo0NewMessage( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Rx Fifo 0 Full Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo0Full( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Rx Fifo 0 Message Lost Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo0MessageLost( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Rx Fifo 1 New Message Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo1NewMessage( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Rx Fifo 1 Full Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo1Full( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Rx Fifo 1 Message Lost Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_RxFifo1MessageLost( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Tx Fifo/Queue Error Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
static void Can_Isr_HighPriorityMessageRx( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}
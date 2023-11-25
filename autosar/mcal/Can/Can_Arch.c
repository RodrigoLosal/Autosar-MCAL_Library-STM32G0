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
#include "Registers.h"
#include "Can_Cfg.h"
#include "Can_Arch.h"
#include "Bfx.h"
#include "CanIf_Can.h"

/* cppcheck-suppress misra-c2012-20.9 ; this is declared at Can_Cfg.h */
#if CAN_DEV_ERROR_DETECT == STD_OFF
/**
 * @param   ModuleId    module id number
 * @param   InstanceId  Instance Id
 * @param   ApiId       Pai id
 * @param   ErrorId     Error code
 */
#define Det_ReportRuntimeError( ModuleId, InstanceId, ApiId, ErrorId ) (void)0
#else
#include "Det.h"
#endif

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
#define CCCR_FDOE_BIT        8u  /*!< FD operation enable bit */
#define CCCR_BRSE_BIT        9u  /*!< Bit rate switch enable bit */
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
 * @defgroup NBTP_sizes NBTP register bit sizes
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
 * @defgroup DBTP_sizes DBTP register bit sizes
 *
 * @{ */
#define DBTP_DSJW_SIZE       4u /*!< Data Jump Width bitfiled size*/
#define DBTP_DTSEG1_SIZE     5u /*!< Data Time Segment 1 bitfiled size*/
#define DBTP_DTSEG2_SIZE     4u /*!< Data Time Segment 2 bitfiled size*/
#define DBTP_DBRP_SIZE       5u /*!< Nominal Baud Rate Preescaler bitfiled size*/
/**
 * @} */

#define TXBC_TFQM_BIT        24u /*!< Tx FIFO/Queue Mode bit */

/**
 * @defgroup RXGFC_bits RXGFC register bits
 *
 * @{ */
#define RXGFC_LSS_BIT        16u /*!< List Size Standard */
#define RXGFC_LSE_BIT        24u /*!< List Size Extended */
#define RXGFC_ANFS_BIT       4u  /*!< Accept Non-matching Frames Standard */
#define RXGFC_ANFE_BIT       2u  /*!< Accept Non-matching Frames Extended */
/**
 * @} */

/**
 * @defgroup RXGFC_size RXGFC register bit sizes
 *
 * @{ */
#define RXGFC_RRFE_BIT       0u /*!< Reject Remote Frames Extended */
#define RXGFC_RRFS_BIT       1u /*!< Reject Remote Frames Standard */
#define RXGFC_LSS_SIZE       5u /*!< List Size Standard */
#define RXGFC_LSE_SIZE       4u /*!< List Size Extended */
#define RXGFC_ANFS_SIZE      2u /*!< Accept Non-matching Frames Standard */
#define RXGFC_ANFE_SIZE      2u /*!< Accept Non-matching Frames Extended */
/**
 * @} */

/**
 * @defgroup ECR_bits ECR register bits
 *
 * @{ */
#define ECR_TEC_BIT          0u  /*!< Transmit Error Counter */
#define ECR_REC_BIT          8u  /*!< Receive Error Counter */
#define ECR_RP_BIT           15u /*!< Receive Error Passive */
/**
 * @} */

/**
 * @defgroup ECR_sizes ECR register bit sizes
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
/**
 * @} */

/**
 * @defgroup TXFQS_sizes TXFQS register bit sizes
 *
 * @{ */
#define TXFQS_TFQPI_SIZE     2u /*!< Tx FIFO/Queue Put Index bitfiled size*/
/**
 * @} */

/**
 * @defgroup TXEFS_bits TXEFS register bits
 *
 * @{ */
#define TXEFS_EFGI_BIT       8u /*!< Tx FIFO/Queue Get Index */
#define TXEFS_EFFL_BIT       0u /*!< Tx FIFO/Queue Fill Level */
/**
 * @} */

/**
 * @defgroup TXEFS_sizes TXEFS register bit sizes
 *
 * @{ */
#define TXEFS_EFGI_SIZE      2u /*!< Tx FIFO/Queue Get Index bitfiled size*/
#define TXEFS_EFFL_SIZE      3u /*!< Tx FIFO/Queue Fill Level bitfiled size*/
/**
 * @} */

/**
 * @defgroup RXF0s_bits RXF0S register bits
 *
 * @{ */
#define RXF0S_F0GI_BIT       8 /*!< Rx FIFO 0 Get Index */
#define RXF0S_F0FL_BIT       0 /*!< Rx FIFO 0 Fill Level */
/**
 * @} */

/**
 * @defgroup RXF0s_sizes RXF0S register bit sizes
 *
 * @{ */
#define RXF0S_F0GI_SIZE      3 /*!< Rx FIFO 0 Get Index bitfiled size*/
#define RXF0S_F0FL_SIZE      4 /*!< Rx FIFO 0 Fill Level */
/**
 * @} */

/**
 * @defgroup PSRs_bits PSR register bits
 *
 * @{ */
#define PSR_BO_BIT           7u /*!< Bus_Off bit */
#define PSR_EP_BIT           5u /*!< Protocol_Error bit */
/* cppcheck-suppress misra-c2012-2.5 ; the use of this define is precompile conditioned */
#define PSR_LEC_BIT          0u /*!< Last_Error_Code bit */
/* cppcheck-suppress misra-c2012-2.5 ; the use of this define is precompile conditioned */
#define PSR_DLEC_BIT         8u /*!< Data_Last_Error_Code bit */
/**
 * @} */

/**
 * @defgroup PSRs_sizes PSR register bits
 *
 * @{ */
/* cppcheck-suppress misra-c2012-2.5 ; the use of this define is precompile conditioned */
#define PSR_LEC_SIZE         3u /*!< Last_Error_Code bitfield size */
/* cppcheck-suppress misra-c2012-2.5 ; the use of this define is precompile conditioned */
#define PSR_DLEC_SIZE        3u /*!< Data_Last_Error_Code bitfield size */
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
#define TX_BUFFER_MM_BIT     24u /*!< Message Marker bit */
/**
 * @} */

/**
 * @defgroup TX_Buffer_bit_sizes TX Buffer header register bit sizes
 *
 * @{ */
#define TX_BUFFER_ID_11_SIZE 11u /*!< Tx standard ID bitfield size */
#define TX_BUFFER_ID_29_SIZE 29u /*!< Tx extended ID bitfield size */
#define TX_BUFFER_DLC_SIZE   4u  /*!< Data length code bitfield size */
#define TX_BUFFER_MM_SIZE    8u  /*!< Message Marker bitfield size */
/**
 * @} */

/**
 * @defgroup RX_Buffer_bits RX Buffer header register bits
 *
 * @{ */
#define RX_BUFFER_ID_11_BITS 18u /*!< Rx standard ID bit */
#define RX_BUFFER_ID_29_BITS 0u  /*!< Rx extended ID bit */
#define RX_BUFFER_DLC_BIT    16u /*!< Data length code bit */
#define RX_BUFFER_XTD_BIT    30u /*!< Extended identifier bit */
#define RX_BUFFER_FDF_BIT    21u /*!< FD format bit */
/**
 * @} */

/**
 * @defgroup RX_Buffer_bit_sizes rX Buffer header register bit sizes
 *
 * @{ */
#define RX_BUFFER_ID_11_SIZE 11u /*!< Rx standard ID bitfield size */
#define RX_BUFFER_ID_29_SIZE 29u /*!< Rx extended ID bitfield size */
#define RX_BUFFER_DLC_SIZE   4u  /*!< Data length code bitfield size */
/**
 * @} */

/**
 * @defgroup ID_Msg_bits ID message bits
 *
 * @{ */
#define MSG_ID_BIT           31u /*!< ID bit */
#define MSG_FORMAT_BIT       30u /*!< Fromat ID bit */
/**
 * @} */

/**
 * @defgroup STD_Filter_bits    Standard ID Filter bits
 *
 * @{ */
#define FLSSA_SFID2_BIT      0u  /*!< Standard ID Filter 2 */
#define FLSSA_SFID1_BIT      16u /*!< Standard ID Filter 1 */
#define FLSSA_SFEC_BIT       27u /*!< Standard ID Filter Element Configuration */
#define FLSSA_SFT_BIT        30u /*!< Standard ID Filter Type */
/**
 * @} */

/**
 * @defgroup STD_Filter_sizes    Standard ID Filter bit sizes
 *
 * @{ */
#define FLSSA_SFT_SIZE       2u /*!< Standard ID Filter Type bitfield size */
#define FLSSA_SFEC_SIZE      3u /*!< Standard ID Filter 1 bitfield size */
/**
 * @} */

/**
 * @defgroup EXT_Filter_bits    Extended ID Filter bits
 *
 * @{ */
#define FLESA_EFID_BIT       0u  /*!< Extended ID Filter 1 */
#define FLESA_EFEC_BIT       29u /*!< Extended ID Filter Element Configuration */
#define FLESA_EFT_BIT        30u /*!< Extended ID Filter Type */
/**
 * @} */

/**
 * @defgroup EXT_Filter_sizes    Extended ID Filter bit sizes
 *
 * @{ */
#define FLESA_EFT_SIZE       2u /*!< Extended ID Filter Type bitfield size */
#define FLESA_EFEC_SIZE      3u /*!< Extended ID Filter 1 bitfield size */
/**
 * @} */

/**
 * @brief  Tx Hardware objecj descriptor.
 */
typedef struct _HwObjectHandler
{
    uint32 ObjHeader1;       /*!< Tx Buffer Standard Address Header 1 */
    uint32 ObjHeader2;       /*!< Tx Buffer Standard Address Header 2 */
    uint32 ObjPayload[ 16 ]; /*!< Tx Buffer Standard Address Payload */
} HwObjectHandler;

/**
 * @brief  Extended Filter descriptor.
 */
typedef struct _HwExtFilter
{
    uint32 ExtFilterHeader1; /*!< Extended Filter Standard Address Header 1 */
    uint32 ExtFilterHeader2; /*!< Extended Filter Standard Address Header 2 */
} HwExtFilter;

/**
 * @brief  Autosar errors to report
 */
/* clang-format off */
static const Can_ErrorType AutosarError[] = { 
    0,
    CAN_ERROR_CHECK_STUFFING_FAILED,
    CAN_ERROR_CHECK_FORM_FAILED,
    CAN_ERROR_CHECK_ACK_FAILED,
    CAN_ERROR_BIT_MONITORING1,
    CAN_ERROR_BIT_MONITORING0,
    CAN_ERROR_CHECK_CRC_FAILED,
};
/* clang-format on */

/**
 * @brief  Can controller register structure.
 */
static Can_RegisterType *CanPeripherals[] = { CAN1, CAN2 };

/**
 * @brief  Can controller SRAM register structure.
 */
static SramCan_RegisterType *SramCanPeripherals[] = { SRAMCAN1, SRAMCAN2 };

/**
 * @brief  Dlc defines to actual bytes.
 */
static const uint8 DlcToBytes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64 };

/**
 * @brief  Fifo 0 to controller id decoder.
 */
static const uint8 Fifo0ToCtrlIds[] = { CAN_OBJ_HRH_RX00, CAN_OBJ_HRH_RX10 };

/**
 * @brief  Fifo 1 to controller id decoder.
 */
static const uint8 Fifo1ToCtrlIds[] = { CAN_OBJ_HRH_RX01, CAN_OBJ_HRH_RX11 };

CAN_STATIC void Can_SetupConfiguredInterrupts( const Can_Controller *Controller, Can_RegisterType *Can );
CAN_STATIC void Can_SetupConfiguredFilters( const Can_ConfigType *Config, uint8 Controller );
CAN_STATIC void Can_SetupBaudrateConfig( const Can_ControllerBaudrateConfig *Baudrate, Can_RegisterType *Can );
CAN_STATIC uint8 Can_GetClosestDlcWithPadding( uint8 Dlc, uint32 *RamBuffer, uint8 PaddingValue );
CAN_STATIC uint8 Can_GetTxPduId( const Can_Controller *Controller, PduIdType *CanPduId );
CAN_STATIC void Can_GetMessage( volatile uint32 *Fifo, PduInfoType *PduInfo, uint32 *CanId );

CAN_STATIC void Can_Isr_RxFifo0NewMessage( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_RxFifo0Full( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_RxFifo0MessageLost( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_RxFifo1NewMessage( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_RxFifo1Full( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_RxFifo1MessageLost( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_HighPriorityMessageRx( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TransmissionCompleted( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TransmissionCancellationFinished( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TxEventFifoElementLost( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TxEventFifoFull( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TxEventFifoNewEntry( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TxFifoEmpty( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TimestampWraparound( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_MessageRamAccessFailure( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_TimeoutOccurred( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_ErrorLoggingOverflow( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_ErrorPassive( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_WarningStatus( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_BusOffStatus( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_WatchdogInterrupt( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_ProtocolErrorInArbitrationPhase( Can_HwUnit *HwUnit, uint8 Controller );
CAN_STATIC void Can_Isr_ProtocolErrorInDataPhase( Can_HwUnit *HwUnit, uint8 Controller );

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
 *          SWS_Can_00245
 */
void Can_Arch_Init( Can_HwUnit *HwUnit, const Can_ConfigType *Config, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* Configure Clock divider */
    Can->CKDIV = ControllerConfig->ClockDivider;

    /* Flush the allocated Message RAM area */
    for( uint8 i = 0u; i < ( sizeof( SramCan_RegisterType ) / sizeof( uint32 ) ); i++ )
    {
        /* Flush the allocated Message RAM area */
        ( (uint32 *)SramCanPeripherals[ ControllerConfig->CanReference ] )[ i ] = 0x00000000u;
    }

    /* Exit from Sleep mode */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

    /* Wait until the CSA bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_CSA_BIT ) == STD_ON )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Request initialisation */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

    /* Wait until the INIT bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_INIT_BIT ) == STD_OFF )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Enable configuration change */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CCE_BIT );

    /* Set the automatic retransmission */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_DAR_BIT, !ControllerConfig->AutoRetransmission );

    /* Set the transmit pause feature */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_TXP_BIT, ControllerConfig->TransmitPause );

    /* Set the Protocol Exception Handling */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_PXHD_BIT, !ControllerConfig->ProtocolException );

    /* Set CAN Frame Format */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_FDOE_BIT, ControllerConfig->FrameFormat );

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
        Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_ASM_BIT );
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
    Can_SetupBaudrateConfig( ControllerConfig->DefaultBaudrate, Can );

    /* Select between Tx FIFO and Tx Queue operation modes */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->TXBC, TXBC_TFQM_BIT, ControllerConfig->TxFifoQueueMode );

    /* Setup filter for Fifo 0 and Fifo 1*/
    Can_SetupConfiguredFilters( Config, Controller );

    /* As per autosar reject all Std remote frames*/
    Bfx_SetBit_u32u8( (uint32 *)&Can->RXGFC, RXGFC_RRFS_BIT );
    /* As per autosar reject all Ext remote frames*/
    Bfx_SetBit_u32u8( (uint32 *)&Can->RXGFC, RXGFC_RRFE_BIT );

    /* As per autosar reject all Std remote frames*/
    Bfx_SetBit_u32u8( (uint32 *)&Can->RXGFC, RXGFC_RRFS_BIT );
    /* As per autosar reject all Ext remote frames*/
    Bfx_SetBit_u32u8( (uint32 *)&Can->RXGFC, RXGFC_RRFE_BIT );

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
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* Request initialisation */
    Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

    /* Wait until the INIT bit into CCCR register is set */
    while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_INIT_BIT ) == FALSE )
    {
        /*Wee need to stablish a timeout counter to avois a potential endless loop,
        according to AUTOSAR a Os tick shall be used, but for the moment it will
        remain empty*/
    }

    /* Exit from Sleep mode */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

    /* Wait until FDCAN exits sleep mode */
    while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_CSA_BIT ) == FALSE )
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
        Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
        /* get baudrate configuration */
        const Can_ControllerBaudrateConfig *Baudrate = &ControllerConfig->BaudrateConfigs[ BaudRateConfigID ];

        /* Set the new baud rate */
        Can_SetupBaudrateConfig( Baudrate, Can );

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
 *          SWS_Can_00384, SWS_Can_00257, SWS_Can_00282, SWS_Can_00426, SWS_Can_00425
 */
Std_ReturnType Can_Arch_SetControllerMode( Can_HwUnit *HwUnit, uint8 Controller, Can_ControllerStateType Transition )
{
    Std_ReturnType RetVal = E_NOT_OK;
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

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
                /* Add cancellation request for all buffers */
                Can->TXBCR = 0x03u;

                /* Request initialisation */
                Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_INIT_BIT );

                /* Wait until the INIT bit into CCCR register is set */
                while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_INIT_BIT ) == FALSE )
                {
                    /*Wee need to stablish a timeout counter to avois a potential endless loop,
                    according to AUTOSAR a Os tick shall be used, but for the moment it will
                    remain empty*/
                }

                /* Exit from Sleep mode */
                Bfx_ClrBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CSR_BIT );

                /* Wait until FDCAN exits sleep mode */
                while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_CSA_BIT ) == TRUE )
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
                while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_CSA_BIT ) == FALSE )
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
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /*enable interrupts only if this function is called the same number of times than
    disable interrupts*/
    if( HwUnit->DisableIntsLvl[ Controller ] == 0u )
    {
        /* Enable Interrupt line 0 */
        Bfx_SetBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE0 );
        /* Enable Interrupt line 1 */
        Bfx_SetBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE1 );
    }
    else
    {
        HwUnit->DisableIntsLvl[ Controller ]--;
    }
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
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* Disable interrupt line 0 */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE0 );
    /* Disable interrupt line 1 */
    Bfx_ClrBit_u32u8( (uint32 *)&Can->ILE, CAN_INTERRUPT_LINE1 );

    /*increase the number of disable int but keeping at maximum of 255*/
    if( HwUnit->DisableIntsLvl[ Controller ] < 255u )
    {
        HwUnit->DisableIntsLvl[ Controller ]++;
    }
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
 *
 * @reqs    SWS_Can_91008
 */
Std_ReturnType Can_Arch_GetControllerErrorState( Can_HwUnit *HwUnit, uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ ControllerId ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /*Inquire is bus off status*/
    if( Bfx_GetBit_u32u8_u8( Can->PSR, PSR_BO_BIT ) == STD_ON )
    {
        *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
    }
    else
    {
        /*Eror passive or active state*/
        if( Bfx_GetBit_u32u8_u8( Can->PSR, PSR_EP_BIT ) == STD_ON )
        {
            *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
        }
        else
        {
            *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
        }
    }

    return E_OK;
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
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ ControllerId ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* Read the error counters register */
    *RxErrorCounterPtr = Bfx_GetBits_u32u8u8_u32( Can->ECR, ECR_REC_BIT, ECR_REC_SIZE );
    Bfx_PutBit_u32u8u8( (uint32 *)RxErrorCounterPtr, 7u, Bfx_GetBit_u32u8_u8( Can->ECR, ECR_RP_BIT ) );

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
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ ControllerId ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

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
 *          SWS_Can_00403, SWS_Can_00011, SWS_Can_00486, SWS_Can_00502, SWS_Can_00276
 */
Std_ReturnType Can_Arch_Write( Can_HwUnit *HwUnit, Can_HwHandleType Hth, const Can_PduType *PduInfo )
{
    Std_ReturnType RetVal = E_NOT_OK;
    uint8 DataLenght;
    uint32 RamBuffer[ 16u ];

    /* get controller configuration */
    const Can_Controller *ControllerConfig = HwUnit->Config->Hohs[ Hth ].ControllerRef;
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* Check that the Tx FIFO/Queue is not full*/
    if( ( Bfx_GetBit_u32u8_u8( Can->TXFQS, TXFQS_TFQF_BIT ) == FALSE ) )
    {
        /* Retrieve the Tx FIFO PutIndex */
        uint32 PutIndex = Bfx_GetBits_u32u8u8_u32( Can->TXFQS, TXFQS_TFQPI_BIT, TXFQS_TFQPI_SIZE );

        /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
        HwObjectHandler *HthObject = (HwObjectHandler *)SramCanPeripherals[ ControllerConfig->CanReference ]->TBSA;

        /*get the message ID type*/
        uint8 IdType = Bfx_GetBit_u32u8_u8( PduInfo->id, MSG_ID_BIT );

        /* Set the message ID, standard (11 bits) or extended (29 bits) */
        if( IdType == CAN_ID_STANDARD )
        {
            Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].ObjHeader1, TX_BUFFER_ID_11_BITS, TX_BUFFER_ID_11_SIZE, PduInfo->id );
            /* Write the ID type bit */
            Bfx_ClrBit_u32u8( &HthObject[ PutIndex ].ObjHeader1, TX_BUFFER_XTD_BIT );
        }
        else
        {
            Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].ObjHeader1, TX_BUFFER_ID_29_BITS, TX_BUFFER_ID_29_SIZE, PduInfo->id );
            /* Write the ID type bit */
            Bfx_SetBit_u32u8( &HthObject[ PutIndex ].ObjHeader1, TX_BUFFER_XTD_BIT );
        }

        /* Store the PduId into FIFO events  */
        Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_MM_BIT, TX_BUFFER_MM_SIZE, PduInfo->swPduHandle );

        /* Get the type of frame to send */
        uint8 FrameType = Bfx_GetBit_u32u8_u8( PduInfo->id, MSG_FORMAT_BIT );

        /* Set the frame */
        if( FrameType == CAN_FRAME_CLASSIC )
        {
            /*Frame format*/
            Bfx_ClrBit_u32u8( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_FDF_BIT );
            /* Set the actual data lenght (DLC) */
            DataLenght = PduInfo->length;
        }
        else
        {
            /*Frame format*/
            Bfx_SetBit_u32u8( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_FDF_BIT );
            /* Get the actual data lenght (DLC) */
            DataLenght = Can_GetClosestDlcWithPadding( PduInfo->length, RamBuffer, HwUnit->Config->Hohs[ Hth ].FdPaddingValue );
            /* Bit rate switch */
            if( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_BRSE_BIT ) == STD_ON )
            {
                Bfx_SetBit_u32u8( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_BRS_BIT );
            }
        }

        /*Store Tx Events*/
        Bfx_SetBit_u32u8( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_EFC_BIT );

        /* copy message into a 32bit wide buffer*/
        for( uint8 Byte = 0; Byte < PduInfo->length; Byte++ )
        {
            ( (uint8 *)RamBuffer )[ Byte ] = PduInfo->sdu[ Byte ];
        }

        /* Write message data lenght */
        Bfx_PutBits_u32u8u8u32( &HthObject[ PutIndex ].ObjHeader2, TX_BUFFER_DLC_BIT, TX_BUFFER_DLC_SIZE, DataLenght );

        /* Write Tx payload with padding value to the message RAM */
        for( uint8 Word = 0; Word < ( DlcToBytes[ DataLenght ] / sizeof( uint32 ) ); Word++ )
        {
            HthObject[ PutIndex ].ObjPayload[ Word ] = RamBuffer[ Word ];
        }

        /* Activate the corresponding transmission request */
        Bfx_SetBit_u32u8( (uint32 *)&Can->TXBAR, PutIndex );

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
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00420, SWS_Can_00033
 */
void Can_Arch_IsrMainHandler( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* clang-format off */
    void (*IsrPointer[])(Can_HwUnit*, uint8) = 
    {
        Can_Isr_RxFifo0NewMessage,
        Can_Isr_RxFifo0Full,
        Can_Isr_RxFifo0MessageLost,
        Can_Isr_RxFifo1NewMessage,
        Can_Isr_RxFifo1Full,
        Can_Isr_RxFifo1MessageLost,
        Can_Isr_HighPriorityMessageRx,
        Can_Isr_TransmissionCompleted,
        Can_Isr_TransmissionCancellationFinished,
        Can_Isr_TxEventFifoElementLost,
        Can_Isr_TxEventFifoFull,
        Can_Isr_TxEventFifoNewEntry,
        Can_Isr_TxFifoEmpty,
        Can_Isr_TimestampWraparound,
        Can_Isr_MessageRamAccessFailure,
        Can_Isr_TimeoutOccurred,
        Can_Isr_ErrorLoggingOverflow,
        Can_Isr_ErrorPassive,
        Can_Isr_WarningStatus,
        Can_Isr_BusOffStatus,
        Can_Isr_WatchdogInterrupt,
        Can_Isr_ProtocolErrorInArbitrationPhase,
        Can_Isr_ProtocolErrorInDataPhase
    };
    /* clang-format on */

    /*Go throu all interrupts potentianly enable*/
    for( uint8 Interrupt = 0u; Interrupt < sizeof( IsrPointer ) / sizeof( IsrPointer[ 0 ] ); Interrupt++ )
    {
        /* If interrupt in turn is active */
        if( Bfx_GetBit_u32u8_u8( Can->IR, Interrupt ) == STD_ON )
        {
            /*Double check if the interrupt is enable*/
            if( Bfx_GetBit_u32u8_u8( Can->IE, Interrupt ) == STD_ON )
            {
                /* Call its interrupt service rutine */
                IsrPointer[ Interrupt ]( HwUnit, Controller );
            }
            /* Clear the interrupt flag */
            Bfx_SetBit_u32u8( (uint32 *)&Can->IR, Interrupt );
        }
    }
}

/**
 * @brief    **Setup reception Filters**
 *
 * This function sets up the reception filters for the given controller. It will set the filters
 * for the standard and extended ID's. The function will only set the filters if the HwFilter
 * pointer is not NULL.
 *
 * @param    Config Pointer to the hardware unit configuration
 * @param    Controller CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_SetupConfiguredFilters( const Can_ConfigType *Config, uint8 Controller )
{
    uint8 StdFilterIndex = 0u;
    uint8 ExtFilterIndex = 0u;

    const Can_Controller *ControllerConfig = &Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    for( uint8 Hoh = 0; Hoh < Config->HohsCount; Hoh++ )
    {
        /*explore only those Hardware Objects for the Controller assigned*/
        if( Config->Hohs[ Hoh ].ControllerRef->ControllerId == ControllerConfig->ControllerId )
        {
            /*look only for Receive objects*/
            if( Config->Hohs[ Hoh ].ObjectType == CAN_HOH_TYPE_RECEIVE )
            {
                /* set the filter only if filters are availables*/
                if( Config->Hohs[ Hoh ].HwFilter != NULL_PTR )
                {
                    /* Loop for all filters set */
                    for( uint8 Filter = 0; Filter < Config->Hohs[ Hoh ].HwFilterCount; Filter++ )
                    {
                        /* Set the filter ID, standard (11 bits) or extended (29 bits) */
                        if( ( Config->Hohs[ Hoh ].IdType == CAN_ID_STANDARD ) || ( ( Config->Hohs[ Hoh ].IdType == CAN_ID_MIXED ) && ( Config->Hohs[ Hoh ].HwFilter->HwFilterIdType == CAN_ID_STANDARD ) ) )
                        {
                            uint32 *StdFilter            = (uint32 *)&SramCanPeripherals[ ControllerConfig->CanReference ]->FLSSA[ StdFilterIndex ];
                            const Can_HwFilter *HwFilter = &Config->Hohs[ Hoh ].HwFilter[ Filter ];

                            Bfx_PutBits_u32u8u8u32( StdFilter, FLSSA_SFID1_BIT, RX_BUFFER_ID_11_SIZE, HwFilter->HwFilterCode );
                            Bfx_PutBits_u32u8u8u32( StdFilter, FLSSA_SFID2_BIT, RX_BUFFER_ID_11_SIZE, HwFilter->HwFilterMask );
                            Bfx_PutBits_u32u8u8u32( StdFilter, FLSSA_SFEC_BIT, FLSSA_SFEC_SIZE, Config->Hohs[ Hoh ].RxFifo );
                            Bfx_PutBits_u32u8u8u32( StdFilter, FLSSA_SFT_BIT, FLSSA_SFT_SIZE, HwFilter->HwFilterType );
                            StdFilterIndex++;
                        }
                        else if( ( Config->Hohs[ Hoh ].IdType == CAN_ID_EXTENDED ) || ( ( Config->Hohs[ Hoh ].IdType == CAN_ID_MIXED ) && ( Config->Hohs[ Hoh ].HwFilter->HwFilterIdType == CAN_ID_EXTENDED ) ) )
                        {
                            HwExtFilter *ExtFilter       = (HwExtFilter *)&SramCanPeripherals[ ControllerConfig->CanReference ]->FLESA[ ExtFilterIndex ];
                            const Can_HwFilter *HwFilter = &Config->Hohs[ Hoh ].HwFilter[ Filter ];

                            Bfx_PutBits_u32u8u8u32( &ExtFilter->ExtFilterHeader1, FLESA_EFID_BIT, RX_BUFFER_ID_29_SIZE, HwFilter->HwFilterCode );
                            Bfx_PutBits_u32u8u8u32( &ExtFilter->ExtFilterHeader2, FLESA_EFID_BIT, RX_BUFFER_ID_29_SIZE, HwFilter->HwFilterMask );
                            Bfx_PutBits_u32u8u8u32( &ExtFilter->ExtFilterHeader2, FLESA_EFT_BIT, FLESA_EFT_SIZE, HwFilter->HwFilterType );
                            Bfx_PutBits_u32u8u8u32( &ExtFilter->ExtFilterHeader1, FLESA_EFEC_BIT, FLESA_EFEC_SIZE, Config->Hohs[ Hoh ].RxFifo );
                            ExtFilterIndex++;
                        }
                        else
                        {
                            /*Do nothing*/
                        }
                    }
                }
            }
        }
    }

    if( StdFilterIndex != 0u )
    {
        /* Standard filter elements number */
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_LSS_BIT, RXGFC_LSS_SIZE, StdFilterIndex );
        /*Reject all messages that do not match with filters*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_ANFS_BIT, RXGFC_ANFS_SIZE, 3u );
    }

    if( ExtFilterIndex != 0u )
    {
        /* Extended filter elements number */
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_LSE_BIT, RXGFC_LSE_SIZE, ExtFilterIndex );
        /*Reject all messages that do not match with filters*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->RXGFC, RXGFC_ANFE_BIT, RXGFC_ANFE_SIZE, 3u );
    }
}

/**
 * @brief    **setup Can controller baudrate**
 *
 * This function sets up the baudrate for the given controller. It will set the baudrate for the
 * nominal and data bit timing registers. The function will only set the baudrate if the Baudrate
 * pointer is not NULL.
 *
 * @param    Baudrate: Baudrate configuration
 * @param    Can: Register structure of the CAN controller
 */
CAN_STATIC void Can_SetupBaudrateConfig( const Can_ControllerBaudrateConfig *Baudrate, Can_RegisterType *Can )
{
    /* Set the default nominal bit timing register */
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NSJW_BIT, NBTP_NSJW_SIZE, ( Baudrate->SyncJumpWidth - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG1_BIT, NBTP_NTSEG1_SIZE, ( Baudrate->Seg1 - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NTSEG2_BIT, NBTP_NTSEG2_SIZE, ( Baudrate->Seg2 - 1u ) );
    Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->NBTP, NBTP_NBRP_BIT, NBTP_NBRP_SIZE, ( Baudrate->Prescaler - 1u ) );

    /*set default data bit timing register if FD is active*/
    if( Baudrate->FdTxBitRateSwitch == STD_ON )
    {
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DSJW_BIT, DBTP_DSJW_SIZE, ( Baudrate->FdSyncJumpWidth - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG1_BIT, DBTP_DTSEG1_SIZE, ( Baudrate->FdSeg1 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DTSEG2_BIT, DBTP_DTSEG2_SIZE, ( Baudrate->FdSeg2 - 1u ) );
        Bfx_PutBits_u32u8u8u32( (uint32 *)&Can->DBTP, DBTP_DBRP_BIT, DBTP_DBRP_SIZE, ( Baudrate->FdPrescaler - 1u ) );
    }

    /* set data bit rate switch */
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->CCCR, CCCR_BRSE_BIT, Baudrate->FdTxBitRateSwitch );
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
CAN_STATIC void Can_SetupConfiguredInterrupts( const Can_Controller *Controller, Can_RegisterType *Can )
{
    uint32 Line1ITs = 0u;
    uint32 Line0ITs = 0u;

    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_ON
    Line0ITs = CAN_IT_RX_FIFO1_MESSAGE_LOST | CAN_IT_RX_FIFO1_MESSAGE_LOST | CAN_IT_TX_EVT_FIFO_ELT_LOST;
    Line1ITs = CAN_IT_ERROR_PASSIVE | CAN_IT_ARB_PROTOCOL_ERROR | CAN_IT_DATA_PROTOCOL_ERROR;
#endif

    /* Disable all interrupts interrupts a set all of them to Line0 by default*/
    Can->IE  = 0x0000u;
    Can->ILS = 0x00u;

    /*Enable interrupts*/
    Bfx_SetBitMask_u32u32( (uint32 *)&Can->IE, Controller->ActiveITs | Line0ITs | Line1ITs );

    /* Assign group of interrupts Tx Event Fifo to line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_MISC, (uint8)( ( Line1ITs & CAN_IT_LIST_MISC ) != 0 ) );
    /* Assign group of interrupts Bit line errors to line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_BIT_LINE_ERROR, (uint8)( ( Line1ITs & CAN_IT_LIST_BIT_LINE_ERROR ) != 0 ) );

    /* Assign group of interrupts Protocol errors to line 1*/
    Bfx_PutBit_u32u8u8( (uint32 *)&Can->ILS, CAN_IT_GROUP_PROTOCOL_ERROR, (uint8)( ( Line1ITs & CAN_IT_LIST_PROTOCOL_ERROR ) != 0 ) );


    /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
         but interrupt will only occur if TC is enabled in IE register */
    if( ( Controller->ActiveITs & CAN_IT_TX_COMPLETE ) != 0u )
    {
        Can->TXBTIE = CAN_TX_BUFFER0 | CAN_TX_BUFFER1 | CAN_TX_BUFFER2;
    }

    /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
         but interrupt will only occur if TCF is enabled in IE register */
    if( ( Controller->ActiveITs & CAN_IT_TX_ABORT_COMPLETE ) != 0u )
    {
        Can->TXBCIE = CAN_TX_BUFFER0 | CAN_TX_BUFFER1 | CAN_TX_BUFFER2;
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
CAN_STATIC uint8 Can_GetClosestDlcWithPadding( uint8 Dlc, uint32 *RamBuffer, uint8 PaddingValue )
{
    uint8 DataLenght = 0u;
    uint8 Counter;

    if( ( Dlc > 8u ) && ( Dlc <= 12u ) )
    {
        DataLenght = CAN_OBJECT_PL_12;
        Counter    = 12;
    }
    else if( ( Dlc > 12u ) && ( Dlc <= 16u ) )
    {
        DataLenght = CAN_OBJECT_PL_16;
        Counter    = 16;
    }
    else if( ( Dlc > 16u ) && ( Dlc <= 20u ) )
    {
        DataLenght = CAN_OBJECT_PL_20;
        Counter    = 20;
    }
    else if( ( Dlc > 20u ) && ( Dlc <= 24u ) )
    {
        DataLenght = CAN_OBJECT_PL_24;
        Counter    = 24;
    }
    else if( ( Dlc > 24u ) && ( Dlc <= 32u ) )
    {
        DataLenght = CAN_OBJECT_PL_32;
        Counter    = 32;
    }
    else if( ( Dlc > 32u ) && ( Dlc <= 48u ) )
    {
        DataLenght = CAN_OBJECT_PL_48;
        Counter    = 48;
    }
    else if( ( Dlc > 48u ) && ( Dlc <= 64u ) )
    {
        DataLenght = CAN_OBJECT_PL_64;
        Counter    = 64;
    }
    else
    {
        DataLenght = CAN_OBJECT_PL_8;
        Counter    = 8;
    }

    /*set padding value*/
    for( uint8 Byte = 0u; Byte < Counter; Byte++ )
    {
        ( (uint8 *)RamBuffer )[ Byte ] = PaddingValue;
    }

    return DataLenght;
}

/**
 * @brief    **Get an CAN PduId from the Tx Event FIFO zone**
 *
 * This function gets the oldest CAN PduId from the Tx Event FIFO zone, it also returns the number
 * of elements in the Tx Event FIFO zone., the CAN Pdu id is actually store into the MM field of the
 * Tx Event FIFO element.
 *
 * @param    Controller CAN controller for which the status shall be changed.
 * @param    CanPduId Pointer to the variable where the CAN PduId will be stored.
 *
 * @retval  Number of elements left in the Tx Event FIFO zone.
 */
CAN_STATIC uint8 Can_GetTxPduId( const Can_Controller *Controller, PduIdType *CanPduId )
{
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ Controller->CanReference ];
    /*Get the Sram Can controller register structure*/
    SramCan_RegisterType *SramCan = SramCanPeripherals[ Controller->CanReference ];

    /* Calculate Tx event FIFO element address */
    uint8 GetIndex = Bfx_GetBits_u32u8u8_u32( Can->TXEFS, TXEFS_EFGI_BIT, TXEFS_EFGI_SIZE );

    /* Get the CAN Pdu store in the message marker field */
    *CanPduId = Bfx_GetBits_u32u8u8_u32( SramCan->EFSA[ GetIndex ], TX_BUFFER_MM_BIT, TX_BUFFER_MM_SIZE );

    /* Acknowledge the Tx Event FIFO that the oldest element is read so that it increments the GetIndex */
    Can->TXEFA = GetIndex;

    return Bfx_GetBits_u32u8u8_u32( Can->TXEFS, TXEFS_EFFL_BIT, TXEFS_EFFL_SIZE );
}

/**
 * @brief    **Get a Message from one of the the Rx FIFOs**
 *
 * This function gets the oldest message from one of the the Rx FIFOs, it also returns the message
 * ID and the data lenght, the message is actually store into the ObjHeader1, ObjHeader2 and
 * ObjPayload fields of the Rx FIFO element.
 *
 * @param    Fifo Pointer to the Rx FIFO element.
 * @param    PduInfo Pointer to the variable where the message will be stored.
 * @param    CanId Pointer to the variable where the message ID will be stored.
 */
CAN_STATIC void Can_GetMessage( volatile uint32 *Fifo, PduInfoType *PduInfo, uint32 *CanId )
{
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    HwObjectHandler *HrhObject = (HwObjectHandler *)Fifo;

    /* Retrieve DataLength */
    PduInfo->SduLength = Bfx_GetBits_u32u8u8_u32( HrhObject->ObjHeader2, RX_BUFFER_DLC_BIT, RX_BUFFER_DLC_SIZE );
    PduInfo->SduLength = DlcToBytes[ PduInfo->SduLength ];
    /* Retrieve Rx payload */
    PduInfo->SduDataPtr = (uint8 *)&HrhObject->ObjPayload;

    /*Retrieve message ID Type*/
    uint8 IdType = Bfx_GetBit_u32u8_u8( HrhObject->ObjHeader1, RX_BUFFER_XTD_BIT );

    /* Set the message ID, standard (11 bits) or extended (29 bits) */
    if( IdType == CAN_ID_STANDARD )
    {
        *CanId = Bfx_GetBits_u32u8u8_u32( HrhObject->ObjHeader1, RX_BUFFER_ID_11_BITS, RX_BUFFER_ID_11_SIZE );
    }
    else
    {
        *CanId = Bfx_GetBits_u32u8u8_u32( HrhObject->ObjHeader1, RX_BUFFER_ID_29_BITS, RX_BUFFER_ID_29_SIZE );
    }
    /* Bit indication for standart or extended */
    Bfx_PutBit_u32u8u8( CanId, MSG_ID_BIT, IdType );

    /* Set frame type*/
    uint8 Format = Bfx_GetBit_u32u8_u8( HrhObject->ObjHeader2, RX_BUFFER_FDF_BIT );
    /* Bit indication for Classic or FD frame */
    Bfx_PutBit_u32u8u8( CanId, MSG_FORMAT_BIT, Format );
}


/**
 * @brief    **Can Rx Fifo 0 New Message Callback**
 *
 * This function is the callback for the Rx Fifo 0 New Message interrupt, it will read the oldest
 * message arrived and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00489, SWS_Can_00501, SWS_Can_00423, SWS_Can_00279
 */
CAN_STATIC void Can_Isr_RxFifo0NewMessage( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    HwObjectHandler *HrhObject = (HwObjectHandler *)SramCanPeripherals[ ControllerConfig->CanReference ]->F0SA;

    PduInfoType PduInfo;
    Can_HwType Mailbox;

    /* Set Hoh and controller Ids */
    Mailbox.Hoh          = Fifo0ToCtrlIds[ Controller ];
    Mailbox.ControllerId = Controller;

    /* Get Rx FIFO Get index */
    uint8 Index = Bfx_GetBits_u32u8u8_u32( Can->RXF0S, RXF0S_F0GI_BIT, RXF0S_F0GI_SIZE );

    /* Read the oldest message arrived */
    Can_GetMessage( (uint32 *)&HrhObject[ Index ], &PduInfo, &Mailbox.CanId );
    /* Pass the messages to upper layer */
    CanIf_RxIndication( &Mailbox, &PduInfo );

    /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the GetIndex */
    Can->RXF0A = Index;
}

/**
 * @brief    **Can Rx Fifo 0 Full Callback**
 *
 * This function is the callback for the Rx Fifo 0 Full interrupt, it will read all the messages
 * arrived and pass them to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00489, SWS_Can_00501, SWS_Can_00423, SWS_Can_00279
 */
CAN_STATIC void Can_Isr_RxFifo0Full( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    HwObjectHandler *HrhObject = (HwObjectHandler *)SramCanPeripherals[ ControllerConfig->CanReference ]->F0SA;

    PduInfoType PduInfo;
    Can_HwType Mailbox;
    uint8 Index;

    /* Set Hoh and controller Ids, same for all messages */
    Mailbox.Hoh          = Fifo0ToCtrlIds[ Controller ];
    Mailbox.ControllerId = Controller;

    while( Bfx_GetBits_u32u8u8_u32( Can->RXF0S, RXF0S_F0FL_BIT, RXF0S_F0FL_SIZE ) > 0u )
    {
        /* Get Rx FIFO Get index */
        Index = Bfx_GetBits_u32u8u8_u32( Can->RXF0S, RXF0S_F0GI_BIT, RXF0S_F0GI_SIZE );
        /* Read the oldest message arrived */
        Can_GetMessage( (uint32 *)&HrhObject[ Index ], &PduInfo, &Mailbox.CanId );
        /* Pass the messages to upper layer */
        CanIf_RxIndication( &Mailbox, &PduInfo );
        /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the GetIndex */
        Can->RXF0A = Index;
    }
}

/**
 * @brief    **Can Rx Fifo 0 Message Lost Callback**
 *
 * A messages haven't read on time and it was overwritten or not by a new message.
 * if FIfo is in blocking mode the message will never overwrite but this ISR will be called
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00395
 */
CAN_STATIC void Can_Isr_RxFifo0MessageLost( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
#else
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    Can_ErrorType Error = CAN_ERROR_OVERLOAD;
    CanIf_ErrorNotification( ControllerConfig->ControllerId, &Error );
#endif

    Det_ReportRuntimeError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ISR_RECEPTION, CAN_E_DATALOST );
}

/**
 * @brief    **Can Rx Fifo 1 New Message Callback**
 *
 * This function is the callback for the Rx Fifo 1 New Message interrupt, it will read the oldest
 * message arrived and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00489, SWS_Can_00501, SWS_Can_00423, SWS_Can_00279
 */
CAN_STATIC void Can_Isr_RxFifo1NewMessage( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    HwObjectHandler *HrhObject = (HwObjectHandler *)SramCanPeripherals[ ControllerConfig->CanReference ]->F1SA;

    PduInfoType PduInfo;
    Can_HwType Mailbox;

    /* Set Hoh and controller Ids */
    Mailbox.Hoh          = Fifo1ToCtrlIds[ Controller ];
    Mailbox.ControllerId = Controller;

    /* Get Rx FIFO Get index */
    uint8 Index = Bfx_GetBits_u32u8u8_u32( Can->RXF1S, RXF0S_F0GI_BIT, RXF0S_F0GI_SIZE );

    /* Read the oldest message arrived */
    Can_GetMessage( (uint32 *)&HrhObject[ Index ], &PduInfo, &Mailbox.CanId );
    /* Pass the messages to upper layer */
    CanIf_RxIndication( &Mailbox, &PduInfo );

    /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the GetIndex */
    Can->RXF1A = Index;
}

/**
 * @brief    **Can Rx Fifo 1 Full Callback**
 *
 * This function is the callback for the Rx Fifo 1 Full interrupt, it will read all the messages
 * arrived and pass them to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00489, SWS_Can_00501, SWS_Can_00423, SWS_Can_00279
 */
CAN_STATIC void Can_Isr_RxFifo1Full( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    HwObjectHandler *HrhObject = (HwObjectHandler *)SramCanPeripherals[ ControllerConfig->CanReference ]->F1SA;

    PduInfoType PduInfo;
    Can_HwType Mailbox;
    uint8 Index;

    /* Set Hoh and controller Ids, same for all messages */
    Mailbox.Hoh          = Fifo1ToCtrlIds[ Controller ];
    Mailbox.ControllerId = Controller;

    while( Bfx_GetBits_u32u8u8_u32( Can->RXF1S, RXF0S_F0FL_BIT, RXF0S_F0FL_SIZE ) > 0u )
    {
        /* Get Rx FIFO Get index */
        Index = Bfx_GetBits_u32u8u8_u32( Can->RXF1S, RXF0S_F0GI_BIT, RXF0S_F0GI_SIZE );
        /* Read the oldest message arrived */
        Can_GetMessage( (uint32 *)&HrhObject[ Index ], &PduInfo, &Mailbox.CanId );
        /* Pass the messages to upper layer */
        CanIf_RxIndication( &Mailbox, &PduInfo );
        /* Acknowledge the Rx FIFO 1 that the oldest element is read so that it increments the GetIndex */
        Can->RXF1A = Index;
    }
}

/**
 * @brief    **Can Rx Fifo 1 Message Lost Callback**
 *
 * A messages haven't read on time and it was overwritten or not by a new message.
 * if FIfo is in blocking mode the message will never overwrite but this ISR will be called
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00395
 */
CAN_STATIC void Can_Isr_RxFifo1MessageLost( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
#else
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    Can_ErrorType Error = CAN_ERROR_OVERLOAD;
    CanIf_ErrorNotification( ControllerConfig->ControllerId, &Error );
#endif

    Det_ReportRuntimeError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_ID_ISR_RECEPTION, CAN_E_DATALOST );
}

/**
 * @brief    **Can Tx Fifo/Queue Error Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_HighPriorityMessageRx( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Transmission completed Callback**
 *
 * This function is the callback for the Transmission completed interrupt, it will read the
 * PduId of the recent message transmitted and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @note    This interrupt callback shall not be called if Can_Isr_TxEventFifoNewEntry
 *          is been use
 *
 * @reqs    SWS_Can_00016
 */
CAN_STATIC void Can_Isr_TransmissionCompleted( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];

    PduIdType CanPduId;

    /*Get the PduId store in the MMS field*/
    (void)Can_GetTxPduId( ControllerConfig, &CanPduId );

    /*Pass the PduId od the senede message to upper layer*/
    CanIf_TxConfirmation( CanPduId );
}

/**
 * @brief    **Can Transmission cancellation finished Callback**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_TransmissionCancellationFinished( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Tx Event Fifo Element Lost Callback**
 *
 * A messages event haven't read on time and it was overwritten or not by a new message.
 * if FIfo is in blocking mode the message will never overwrite but this ISR will be called
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_91022
 */
CAN_STATIC void Can_Isr_TxEventFifoElementLost( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
#else
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    Can_ErrorType Error = CAN_ERROR_OVERLOAD;
    CanIf_ErrorNotification( ControllerConfig->ControllerId, &Error );
#endif
}

/**
 * @brief    **Can Tx Event Fifo Full Callback**
 *
 * This function is the callback for the Tx Event Fifo Full interrupt, it will read the
 * PduId of the all recent message transmitted and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @note    This interrupt callback shall not be called if Can_Isr_TxFifoEmpty
 *          is been use
 *
 * @reqs    SWS_Can_00016
 */
CAN_STATIC void Can_Isr_TxEventFifoFull( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];

    PduIdType CanPduId;
    uint8 Msgs;

    do
    {
        /*Get the PduId store in the MMS field*/
        Msgs = Can_GetTxPduId( ControllerConfig, &CanPduId );
        /*Pass the PduId od the senede message to upper layer*/
        CanIf_TxConfirmation( CanPduId );
    } while( Msgs > 0u );
}

/**
 * @brief    **Can Tx Event Fifo New Entry Callback**
 *
 * This function is the callback for the Tx Event Fifo New Entry interrupt, it will read the
 * PduId of the recent message transmitted and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @note    This interrupt callback shall not be called if Can_Isr_TransmissionCompleted
 *          is been use
 *
 * @reqs    SWS_Can_00016
 */
CAN_STATIC void Can_Isr_TxEventFifoNewEntry( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];

    PduIdType CanPduId;

    /*Get the PduId store in the MMS field*/
    (void)Can_GetTxPduId( ControllerConfig, &CanPduId );

    /*Pass the PduId od the senede message to upper layer*/
    CanIf_TxConfirmation( CanPduId );
}

/**
 * @brief    **Can Tx Event Fifo Empty Callback**
 *
 * This function is the callback for the Tx Event Fifo Empty interrupt, it will read the
 * PduId of the all recent message transmitted and pass it to the upper layer.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @note    This interrupt callback shall not be called if Can_Isr_TxEventFifoFull
 *          is been use
 *
 * @reqs    SWS_Can_00016
 */
CAN_STATIC void Can_Isr_TxFifoEmpty( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];

    PduIdType CanPduId;
    uint8 Msgs;

    do
    {
        /*Get the PduId store in the MMS field*/
        Msgs = Can_GetTxPduId( ControllerConfig, &CanPduId );
        /*Pass the PduId od the senede message to upper layer*/
        CanIf_TxConfirmation( CanPduId );
    } while( Msgs > 0u );
}

/**
 * @brief    **Timestamp wraparound**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_TimestampWraparound( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Message RAM access failure**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_MessageRamAccessFailure( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Timeout occurred**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_TimeoutOccurred( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Error logging overflow**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_ErrorLoggingOverflow( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Error passive**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_91023
 */
CAN_STATIC void Can_Isr_ErrorPassive( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
#else
    uint8 RxErrorCounter;
    uint8 TxErrorCounter;
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    if( Bfx_GetBit_u32u8_u8( Can->PSR, PSR_EP_BIT ) == STD_ON )
    {
        /* Get the Rx and Tx error counters */
        Can_Arch_GetControllerRxErrorCounter( HwUnit, ControllerConfig->ControllerId, &RxErrorCounter );
        Can_Arch_GetControllerTxErrorCounter( HwUnit, ControllerConfig->ControllerId, &TxErrorCounter );
        /* Notify error passive */
        CanIf_ControllerErrorStatePassive( ControllerConfig->ControllerId, RxErrorCounter, TxErrorCounter );
    }
#endif
}

/**
 * @brief    **Warning status**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_WarningStatus( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Can Bus Off Callback**
 *
 * This function is the callback for the Bus Off interrupt, it will set the controller mode to
 * stopped and notify the upper layer that the controller is in bus off mode.
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_00020, SWS_Can_00272, SWS_Can_00273, SWS_Can_00274
 */
CAN_STATIC void Can_Isr_BusOffStatus( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];

    /* make sure the transition when to Bus_Off and not the other way around */
    if( Bfx_GetBit_u32u8_u8( Can->PSR, PSR_BO_BIT ) == STD_ON )
    {
        /* Add cancellation request for all buffers */
        /*we don't know if this gonna take time */
        Can->TXBCR = 0x03u;

        /* Wait until the INIT bit into CCCR register is set, this bit was set
        automatically by the Bus_Off event */
        while( Bfx_GetBit_u32u8_u8( Can->CCCR, CCCR_INIT_BIT ) == FALSE )
        {
            /*Wee need to stablish a timeout counter to avois a potential endless loop,
            according to AUTOSAR a Os tick shall be used, but for the moment it will
            remain empty*/
        }

        /* Enable configuration change */
        Bfx_SetBit_u32u8( (uint32 *)&Can->CCCR, CCCR_CCE_BIT );

        /* Change CAN peripheral state */
        HwUnit->ControllerState[ Controller ] = CAN_CS_STOPPED;
        /* Notify Bus off */
        CanIf_ControllerBusOff( ControllerConfig->ControllerId );
    }
}

/**
 * @brief    **Watchdog error**
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 */
CAN_STATIC void Can_Isr_WatchdogInterrupt( Can_HwUnit *HwUnit, uint8 Controller )
{
    (void)HwUnit;
    (void)Controller;
}

/**
 * @brief    **Protocol error in arbitration phase (nominal bit time is used)**
 *
 * The function report the Error code to upper layer CanIf in error happens in arbitration phase, errors
 * reported are only tose the Mcu supports, if the Mcu doesn't support the error it will be ignored
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_91021, SWS_Can_91022, SWS_Can_91024
 */
CAN_STATIC void Can_Isr_ProtocolErrorInArbitrationPhase( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
    (void)AutosarError;
#else
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the erro code */
    uint8 ErrorCode = Bfx_GetBits_u32u8u8_u32( Can->PSR, PSR_LEC_BIT, PSR_LEC_SIZE );
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    CanIf_ErrorNotification( ControllerConfig->ControllerId, (Can_ErrorType *)&AutosarError[ ErrorCode ] );
#endif
}

/**
 * @brief    **Protocol error in data phase (data bit time is used)**
 *
 * The function report the Error code to upper layer CanIf in error happens in data phase, errors
 * reported are only tose the Mcu supports, if the Mcu doesn't support the error it will be ignored
 *
 * @param    HwUnit: Pointer to the hardware unit configuration
 * @param    Controller: CAN controller for which the status shall be changed.
 *
 * @reqs    SWS_Can_91021, SWS_Can_91022, SWS_Can_91024
 */
CAN_STATIC void Can_Isr_ProtocolErrorInDataPhase( Can_HwUnit *HwUnit, uint8 Controller )
{
    /* cppcheck-suppress misra-c2012-20.9 ; it is necesary to use a define for this function */
#if CAN_ENABLE_SECURITY_EVENT_REPORTING == STD_OFF
    (void)HwUnit;
    (void)Controller;
    (void)AutosarError;
#else
    /* get controller configuration */
    const Can_Controller *ControllerConfig = &HwUnit->Config->Controllers[ Controller ];
    /*Get the Can controller register structure*/
    Can_RegisterType *Can = CanPeripherals[ ControllerConfig->CanReference ];
    /*Get the erro code */
    uint8 ErrorCode = Bfx_GetBits_u32u8u8_u32( Can->PSR, PSR_DLEC_BIT, PSR_DLEC_SIZE );
    /*Get the buffer to write as per autosar will be the transmit hardware objet from Sram*/
    CanIf_ErrorNotification( ControllerConfig->ControllerId, (Can_ErrorType *)&AutosarError[ ErrorCode ] );
#endif
}

/**
 * @file    test_Can_Arch.c
 * @brief   **Unit testing for Can Architeture Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Can_Arch.h file
 */
#include "unity.h"
#include "Registers.h"
#include "Bfx.h"
#include "Can_Cfg.h"
#include "Can.h"
#include "Can_Arch.h"
#include "mock_Det.h"
#include "mock_CanIf.h"
#include <string.h>

typedef struct _Std_Filter
{
    uint32 Sfid2 : 11;
    uint32 Reserved : 5;
    uint32 Sfid1 : 11;
    uint32 Sfec : 3;
    uint32 Sft : 2;
} Std_Filter;

typedef struct _Ext_Filter
{
    uint64 Efid1 : 29;
    uint64 Efec : 3;
    uint64 Efid2 : 29;
    uint64 Reserved : 1;
    uint64 Efti : 2;
} Ext_Filter;

#define CAN_ID_INVALID 0xFFu

/**
 * @brief   Mock register for CAN1
 */
Can_RegisterType CAN1_BASE;

/**
 * @brief   Mock register for CAN2
 */
Can_RegisterType CAN2_BASE;

/**
 * @brief   Mock register for SRAMCAN1
 */
SramCan_RegisterType SRAMCAN1_BASE;

/**
 * @brief   Mock register for SRAMCAN2
 */
SramCan_RegisterType SRAMCAN2_BASE;

extern Can_HwUnit HwUnit;

void Can_SetupBaudrateConfig( const Can_ControllerBaudrateConfig *Baudrate, Can_RegisterType *Can );
void Can_SetupConfiguredFilters( const Can_ConfigType *Config, uint8 Controller );
void Can_SetupConfiguredInterrupts( const Can_Controller *Controller, Can_RegisterType *Can );
uint8 Can_GetClosestDlcWithPadding( uint8 Dlc, uint32 *RamBuffer, uint8 PaddingValue );
uint8 Can_GetTxPduId( const Can_Controller *Controller, PduIdType *CanPduId );
uint8 Can_GetTxPduId( const Can_Controller *Controller, PduIdType *CanPduId );


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    /*Set the register to their reset values for each test*/
    CAN1->CCCR   = 0x00000001,
    CAN1->TEST   = 0x00000000,
    CAN1->CKDIV  = 0x00000000,
    CAN1->DBTP   = 0x00000A33,
    CAN1->NBTP   = 0x06000A03,
    CAN1->RXGFC  = 0x00000000,
    CAN1->IE     = 0x00000000,
    CAN1->ILS    = 0x00000000,
    CAN1->TXBTIE = 0x00000000,
    CAN1->TXBCIE = 0x00000000,
    CAN1->TXEFS  = 0x00000000,

    /*se inti values for control structure*/
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanConfig;

    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_CONTROLLER_0 );

    HwUnit.HwUnitState                         = CAN_CS_READY;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_STOPPED;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_STOPPED;
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   Test case for CKDIV reg in Can_Init function.
 *
 * This test case will check that the CKDIV register is set to the correct value of 5 when config
 * structure is set with .ClockDivider = CAN_CLOCK_DIV10, and the Can_Init function is called.
 */
void test__Can_Arch_Init__clock_div_value( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00000005, CAN1->CKDIV, "Wrong clock divider value" );
}

/**
 * @brief   Test case for init CANARCH_CONTROLLER_0 in Can_Init function.
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 * setting for this controller are:
 * .Mode = CAN_MODE_NORMAL,
 * .FrameFormat = CAN_FRAME_CLASSIC,
 * .ClockDivider = CAN_CLOCK_DIV10,
 * .AutoRetransmission = STD_OFF,
 * .TransmitPause = STD_ON,
 * .ProtocolException = STD_OFF,
 */
void test__Can_Arch_Init__set_to_normal_mode( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00005043, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( 0x00000000, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   Test case for init CANARCH_RESTRICTED_OPERATION in Can_Init function.
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_1, and the Can_Init function is called.
 * setting for this controller are:
 * .Mode = CAN_MODE_RESTRICTED_OPERATION,
 * .FrameFormat = CAN_FRAME_CLASSIC,
 * .ClockDivider = CAN_CLOCK_DIV10,
 * .AutoRetransmission = STD_OFF,
 * .TransmitPause = STD_ON,
 * .ProtocolException = STD_OFF,
 */
void test__Can_Arch_Init__set_to_restricted_operation_mode( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_RESTRICTED_OPERATION );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005047, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   Test case for init CANARCH_BUS_MONITORING in Can_Init function.
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_1, and the Can_Init function is called.
 * setting for this controller are:
 * .Mode = CAN_MODE_BUS_MONITORING,
 * .FrameFormat = CAN_FRAME_CLASSIC,
 * .ClockDivider = CAN_CLOCK_DIV10,
 * .AutoRetransmission = STD_OFF,
 * .TransmitPause = STD_ON,
 * .ProtocolException = STD_OFF,
 */
void test__Can_Arch_Init__set_to_bus_monitoring( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_BUS_MONITORING );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005063, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   Test case for init CANARCH_INTERNAL_LOOPBACK in Can_Init function.
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_1, and the Can_Init function is called.
 * setting for this controller are:
 * .Mode = CAN_MODE_INTERNAL_LOOPBACK,
 * .FrameFormat = CAN_FRAME_CLASSIC,
 * .ClockDivider = CAN_CLOCK_DIV10,
 * .AutoRetransmission = STD_OFF,
 * .TransmitPause = STD_ON,
 * .ProtocolException = STD_OFF,
 */
void test__Can_Arch_Init__internal_loopback( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_INTERNAL_LOOPBACK );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x000050E3, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000010, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   Test case for init CANARCH_EXTERNAL_LOOPBACK in Can_Init function.
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_1, and the Can_Init function is called.
 * setting for this controller are:
 * .Mode = CAN_MODE_EXTERNAL_LOOPBACK,
 * .FrameFormat = CAN_FRAME_CLASSIC,
 * .ClockDivider = CAN_CLOCK_DIV10,
 * .AutoRetransmission = STD_OFF,
 * .TransmitPause = STD_ON,
 * .ProtocolException = STD_OFF,
 */
void test__Can_Arch_Init__external_loopback( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanInitConfig;
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_EXTERNAL_LOOPBACK );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x000050C3, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000010, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   Test case for de init CANARCH_CONTROLLER_0
 *
 * This test case will check that the CCCR register is set to the correct values of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_DeInit function is called.
 */
void test__Can_Arch_DeInit__set_to_uninit( void )
{
    CAN1->CCCR = 0x0000504A;
    Can_Arch_DeInit( &HwUnit, CAN_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0000504B, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1->ILE, "Wrong clock stop value" );
}

/**
 * @brief   Set baudrate to 500k i classic mode
 *
 * This test case will check that the NBTP and DBTP registers are set to the correct values when
 * config structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 */
void test__Can_Arch_SetBaudrate__set_baudrate_classic( void )
{
    Can_Arch_SetBaudrate( &HwUnit, CANARCH_CONTROLLER_0, CANARCH_BAUDRATE_500k_CLASSIC );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005043, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x02090E03, CAN1->NBTP, "Wrong NBTP value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000A33, CAN1->DBTP, "Wrong DBTP value" );
}

/**
 * @brief   Try to set baud rate when controller is not stopped
 *
 * This test case will check that the NBTP and DBTP registers are not modified with the mew values
 * because the controller is not stopped.
 */
void test__Arch_SetBaudrate__controller_no_stopped( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_STARTED;

    Can_Arch_SetBaudrate( &HwUnit, CANARCH_CONTROLLER_0, CANARCH_BAUDRATE_500k_CLASSIC );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005043, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C01, CAN1->NBTP, "Wrong NBTP value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000A33, CAN1->DBTP, "Wrong DBTP value" );
}

/**
 * @brief   Set moide to started
 *
 * This test case will check that the CCCR register is set to the correct values when state
 * trsition to started
 */
void test__Can_Arch_SetControllerMode__set_to_started( void )
{
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005042, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STARTED, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Try to set mode to started when controller is not stopped
 *
 * This test case will check that the CCCR register is not modified when the controller is not
 * stopped.
 */
void test__Can_Arch_SetControllerMode__set_to_start_when_no_stopped( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_STARTED;

    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005043, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STARTED, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Set mode to stopped
 *
 * This test case will check that the CCCR register is set to the correct values when state
 * trsition to stopped
 */
void test__Can_Arch_SetControllerMode__set_to_stopped( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_STARTED;

    /*set CCR register to previous values to stop*/
    CAN1->CCCR = 0x00005042;
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_STOPPED );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005043, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Try to set mode to stopped when controller is not started
 *
 * This test case will check that the CCCR register is not modified when the controller is not
 * started.
 */
void test__Can_Arch_SetControllerMode__set_to_stopped_when_no_started( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_STOPPED;

    /*set CCR register to previous values to stop*/
    CAN1->CCCR = 0x00005042;
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_STOPPED );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005042, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Set mode to sleep
 *
 * This test case will check that the CCCR register is set to the correct values when state
 * trsition to sleep
 */
void test__Can_Arch_SetControllerMode__set_to_sleep( void )
{
    /*set CCR register to previous values to stop*/
    CAN1->CCCR = 0x0000504C;
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_SLEEP );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0000505C, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_SLEEP, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Try to set mode to sleep when controller is not stopped
 *
 * This test case will check that the CCCR register is not modified when the controller is not
 * stopped.
 */
void test__Can_Arch_SetControllerMode__set_mode_when_no_stopped( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_SLEEP;

    /*set CCR register to previous values to stop*/
    CAN1->CCCR = 0x00005042;
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, CAN_CS_SLEEP );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00005042, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_SLEEP, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Wrong controller state" );
}

/**
 * @brief   Set mode to invalid mode
 *
 * This test case will check that the CCCR register is not modified when the controller is not
 * stopped.
 */
void test__Can_Arch_SetControllerMode__invalid_state( void )
{
    Can_Arch_SetControllerMode( &HwUnit, CAN_CONTROLLER_0, 0xFFu );
}

/**
 * @brief   Test case for getting error active
 *
 * This test case will check that the function return the correct value when the controller is in
 * error active state.
 */
void test__Can_Arch_GetControllerErrorState__controller_error_active( void )
{
    Can_ErrorStateType ErrorState;

    CAN1->PSR = 0x00000000;

    Can_Arch_GetControllerErrorState( &HwUnit, CAN_CONTROLLER_0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_ERRORSTATE_ACTIVE, ErrorState, "Wrong controller error state" );
}

/**
 * @brief   Test case for getting error passive
 *
 * This test case will check that the function return the correct value when the controller is in
 * error passive state.
 */
void test__Can_Arch_GetControllerErrorState__controller_error_passive( void )
{
    Can_ErrorStateType ErrorState;

    CAN1->PSR = 0x00000020;

    Can_Arch_GetControllerErrorState( &HwUnit, CAN_CONTROLLER_0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_ERRORSTATE_PASSIVE, ErrorState, "Wrong controller error state" );
}

/**
 * @brief   Test case for getting bus off
 *
 * This test case will check that the function return the correct value when the controller is in
 * bus off state.
 */
void test__Can_Arch_GetControllerErrorState__controller_bus_off( void )
{
    Can_ErrorStateType ErrorState;

    CAN1->PSR = 0x00000080;

    Can_Arch_GetControllerErrorState( &HwUnit, CAN_CONTROLLER_0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_ERRORSTATE_BUSOFF, ErrorState, "Wrong controller error state" );
}

/**
 * @brief   Void Test case for getting current time
 *
 * This is just to make 100 codde coverage, but the fucntion is still not implemented.
 */
void test__Can_Arch_GetCurrentTime__void_test( void )
{
    Can_TimeStampType TimeStamp;
    Can_Arch_GetCurrentTime( &HwUnit, CAN_CONTROLLER_0, &TimeStamp );
}

/**
 * @brief   Void Test case for setting current time
 *
 * This is just to make 100 codde coverage, but the fucntion is still not implemented.
 */
void test__Can_Arch_EnableEgressTimeStamp__void_test( void )
{
    Can_HwHandleType Hth = 0;
    Can_Arch_EnableEgressTimeStamp( &HwUnit, Hth );
}

/**
 * @brief   Void Test case for setting current time
 *
 * This is just to make 100 codde coverage, but the fucntion is still not implemented.
 */
void test__Can_Arch_GetEgressTimeStamp__void_test( void )
{
    Can_TimeStampType TimeStamp;
    PduIdType CanPduId   = 0;
    Can_HwHandleType Hth = 0;
    Can_Arch_GetEgressTimeStamp( &HwUnit, CanPduId, Hth, &TimeStamp );
}

/**
 * @brief   Void Test case for setting current time
 *
 * This is just to make 100 codde coverage, but the fucntion is still not implemented.
 */
void test__Can_Arch_GetIngressTimeStamp__void_test( void )
{
    Can_TimeStampType TimeStamp;
    Can_HwHandleType Hth = 0;
    Can_Arch_GetIngressTimeStamp( &HwUnit, Hth, &TimeStamp );
}

/**
 * @brief   Test filter with wrong controller id
 *
 * This test case will avoid to setup any filter from the Hoh if is does not belong to the right
 * controller.
 */
void test__Can_SetupConfiguredFilters__wrong_controller_id( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ 2u ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        },
        {
            .ControllerId = 1u,
            .CanReference = CAN_FDCAN2,
        } 
    };
    
    const Can_HardwareObject Hohs[ 1u ] = {
        { 
            .ControllerRef = &Controllers[ 0u ] 
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 2u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 1u );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0, SRAMCAN1->FLSSA[ 0u ], "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with wrong hoh type
 *
 * This test case will avoid to setup any filter from the Hoh if is does not belong to the right
 * type.
 */
void test__Can_SetupConfiguredFilters__wrong_hoh_type( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ 1u ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };
    
    const Can_HardwareObject Hohs[ 1u ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_TRANSMIT
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0, SRAMCAN1->FLSSA[ 0u ], "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with wrong hoh type
 *
 * This test case will avoid to setup any filter from the Hoh if not filter is assigned
 */
void test__Can_SetupConfiguredFilters__no_filters( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ 1u ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };
    
    const Can_HardwareObject Hohs[ 1u ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .HwFilter = NULL_PTR
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0, SRAMCAN1->FLSSA[ 0u ], "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with one single valid std filter
 *
 * This test case will setup one single filter with the following values:
 * .HwFilterCode   = 0x127,
 * .HwFilterMask   = 0x7FF,
 * .HwFilterType   = CAN_FILTER_TYPE_DUAL,
 * .HwFilterIdType = CAN_ID_STANDARD
 */
void test__Can_SetupConfiguredFilters__setup_std_filter_hoh_id_standard( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x127,
            .HwFilterMask   = 0x7FF,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_STANDARD 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .IdType        = CAN_ID_STANDARD,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );
    Std_Filter *Filter = (Std_Filter *)&SRAMCAN1->FLSSA[ 0u ];

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterCode, Filter->Sfid1, "Wrong Sfid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterMask, Filter->Sfid2, "Wrong Sfid2 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Hohs[ 0 ].RxFifo, Filter->Sfec, "Wrong FIFO value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterType, Filter->Sft, "Wrong FILTER Type value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00010030, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with one single valid std filter
 *
 * This test case will setup one single filter with the following values:
 * .HwFilterCode   = 0x127,
 * .HwFilterMask   = 0x7FF,
 * .HwFilterType   = CAN_FILTER_TYPE_DUAL,
 * .HwFilterIdType = CAN_ID_STANDARD
 */
void test__Can_SetupConfiguredFilters__setup_std_filter_hoh_id_mixed( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x127,
            .HwFilterMask   = 0x7FF,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_STANDARD 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .IdType        = CAN_ID_MIXED,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );
    Std_Filter *Filter = (Std_Filter *)&SRAMCAN1->FLSSA[ 0u ];

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterCode, Filter->Sfid1, "Wrong Sfid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterMask, Filter->Sfid2, "Wrong Sfid2 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Hohs[ 0 ].RxFifo, Filter->Sfec, "Wrong FIFO value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterType, Filter->Sft, "Wrong FILTER Type value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00010030, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with one single valid ext filter
 *
 * This test case will setup one single filter with the following values:
 * .HwFilterCode   = 0x1277,
 * .HwFilterMask   = 0x7FF7,
 * .HwFilterType   = CAN_FILTER_TYPE_DUAL,
 * .HwFilterIdType = CAN_ID_EXTENDED
 */
void test__Can_SetupConfiguredFilters__setup_std_filter_hoh_id_extended( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x1277,
            .HwFilterMask   = 0x7FF7,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_EXTENDED 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .IdType        = CAN_ID_EXTENDED,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );
    Ext_Filter *Filter = (Ext_Filter *)&SRAMCAN1->FLESA[ 0u ];

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterCode, Filter->Efid1, "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterMask, Filter->Efid2, "Wrong Efid2 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Hohs[ 0 ].RxFifo, Filter->Efec, "Wrong FIFO value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterType, Filter->Efti, "Wrong FILTER Type value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0100000C, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with one single valid ext filter
 *
 * This test case will setup one single filter with the following values:
 * .HwFilterCode   = 0x1277,
 * .HwFilterMask   = 0x7FF7,
 * .HwFilterType   = CAN_FILTER_TYPE_DUAL,
 * .HwFilterIdType = CAN_ID_EXTENDED
 */
void test__Can_SetupConfiguredFilters__setup_std_filter_hoh_id_extended_2( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x1277,
            .HwFilterMask   = 0x7FF7,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_EXTENDED 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .IdType        = CAN_ID_MIXED,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );
    Ext_Filter *Filter = (Ext_Filter *)&SRAMCAN1->FLESA[ 0u ];

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterCode, Filter->Efid1, "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterMask, Filter->Efid2, "Wrong Efid2 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Hohs[ 0 ].RxFifo, Filter->Efec, "Wrong FIFO value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( HwFilter[ 0 ].HwFilterType, Filter->Efti, "Wrong FILTER Type value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0100000C, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   Test filter with one single valid ext filter
 *
 * This test case will check that the filter is not setup if the filter type is invalid
 */
void test__Can_SetupConfiguredFilters__setup_with_wrong_hoh_id_type( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x1277,
            .HwFilterMask   = 0x7FF7,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_EXTENDED 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_RECEIVE,
            .IdType        = CAN_ID_INVALID,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );
}

/**
 * @brief   Test filter with invalid filter type
 *
 * This test case will check that the filter is not setup if the filter type is invalid
 */
void test__Can_SetupConfiguredFilters__setup_with_wrong_filter_id( void )
{
    /* clang-format off */
    const Can_Controller Controllers[ ] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        }
    };

    const Can_HwFilter HwFilter[] = {
        {
            .HwFilterCode   = 0x1277,
            .HwFilterMask   = 0x7FF7,
            .HwFilterType   = CAN_FILTER_TYPE_DUAL,
            .HwFilterIdType = CAN_ID_INVALID 
        } 
    };
    
    const Can_HardwareObject Hohs[ ] = {
        { 
            .ControllerRef = &Controllers[ 0u ],
            .ObjectType    = CAN_HOH_TYPE_TRANSMIT,
            .IdType        = CAN_ID_INVALID,
            .RxFifo        = CAN_RX_FIFO0,
            .HwFilter = HwFilter,
            .HwFilterCount = 1u
        } 
    };

    const Can_ConfigType Config = {
        .Controllers      = Controllers,
        .ControllersCount = 1u,
        .Hohs             = Hohs,
        .HohsCount        = 1u 
    };
    /* clang-format on */

    /**init register for the test*/
    memset( &SRAMCAN1_BASE, 0x00, sizeof( SramCan_RegisterType ) );
    CAN1_BASE.RXGFC = 0x00000000;

    Can_SetupConfiguredFilters( &Config, 0u );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0, SRAMCAN1->FLSSA[ 0u ], "Wrong Efid1 value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1_BASE.RXGFC, "Wrong RXGFC value" );
}

/**
 * @brief   set baud rate in classic mode
 *
 * This test case will check that the NBTP and DBTP registers are set to the correct values when
 * config structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 */
void test__Can_SetupBaudrateConfig__classic_mode( void )
{
    /* clang-format off */
    const Can_ControllerBaudrateConfig BaudrateConfig[] =
    {
        {
            .BaudRateConfigID  = 0,
            .Seg1              = 13,
            .Seg2              = 2,
            .SyncJumpWidth     = 1,
            .Prescaler         = 4,
            .FdTxBitRateSwitch = STD_OFF,
        },
    };
    /* clang-format on */

    /**init register for the test*/
    CAN1_BASE.CCCR = 0x00000001;
    CAN1_BASE.DBTP = 0x00000A33;
    CAN1_BASE.NBTP = 0x06000A03;

    Can_SetupBaudrateConfig( &BaudrateConfig[ 0 ], CAN1 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00000001, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C01, CAN1->NBTP, "Wrong NBTP value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000A33, CAN1->DBTP, "Wrong DBTP value" );
}

/**
 * @brief   set baud rate in FD mode
 *
 * This test case will check that the NBTP and DBTP registers are set to the correct values when
 * config structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 */
void test__Can_SetupBaudrateConfig__fd_mode( void )
{
    /* clang-format off */
    const Can_ControllerBaudrateConfig BaudrateConfig[] =
    {
        {
            .BaudRateConfigID  = 0,
            .Seg1              = 13,
            .Seg2              = 2,
            .SyncJumpWidth     = 1,
            .Prescaler         = 4,
            .FdSeg1            = 13,
            .FdSeg2            = 2,
            .FdSyncJumpWidth   = 1,
            .FdPrescaler       = 4,
            .FdTxBitRateSwitch = STD_ON,
        }
    };
    /* clang-format on */

    /**init register for the test*/
    CAN1_BASE.CCCR = 0x00000001;
    CAN1_BASE.DBTP = 0x00000A33;
    CAN1_BASE.NBTP = 0x06000A03;

    Can_SetupBaudrateConfig( &BaudrateConfig[ 0 ], CAN1 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00000201, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C01, CAN1->NBTP, "Wrong NBTP value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C10, CAN1->DBTP, "Wrong DBTP value" );
}

/**
 * @brief   Configure interrupts for one controller
 *
 * This test case will check that the IE, ILS, TXBTIE and TXBCIE registers are set to the correct
 * values when config structure is set with .ControllerId = CAN_CONTROLLER_0
 */
void test__Can_SetupConfiguredInterrupts__setup_interrupts( void )
{
    /* clang-format off */
    const Can_Controller Controllers[] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
            .ActiveITs    = CAN_IT_TX_COMPLETE | CAN_IT_TX_ABORT_COMPLETE,
        } 
    };
    /* clang-format on */

    /**init register for the test*/
    CAN1_BASE.IE     = 0x00000000;
    CAN1_BASE.ILS    = 0x00000000;
    CAN1_BASE.TXBTIE = 0x00000000;
    CAN1_BASE.TXBCIE = 0x00000000;

    Can_SetupConfiguredInterrupts( &Controllers[ 0 ], CAN1 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00621188, CAN1->IE, "Wrong ILE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000060, CAN1->ILS, "Wrong IE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000007, CAN1->TXBTIE, "Wrong IE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000007, CAN1->TXBCIE, "Wrong IE value" );
}

/**
 * @brief   Configure interrupts for one controller
 *
 * This test case will check that the IE, ILS, but not the TXBTIE and TXBCIE registers are
 * set to the correct
 */
void test__Can_SetupConfiguredInterrupts__setup_interrupts_with_no_tx( void )
{
    /* clang-format off */
    const Can_Controller Controllers[] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
            .ActiveITs    = CAN_IT_RX_FIFO1_FULL | CAN_IT_RX_FIFO0_NEW_MESSAGE,
        } 
    };
    /* clang-format on */

    /**init register for the test*/
    CAN1_BASE.IE     = 0x00000000;
    CAN1_BASE.ILS    = 0x00000000;
    CAN1_BASE.TXBTIE = 0x00000000;
    CAN1_BASE.TXBCIE = 0x00000000;

    Can_SetupConfiguredInterrupts( &Controllers[ 0 ], CAN1 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0062101C, CAN1->IE, "Wrong ILE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000060, CAN1->ILS, "Wrong IE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1->TXBTIE, "Wrong IE value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000, CAN1->TXBCIE, "Wrong IE value" );
}

/**
 * @brief   get close DLC with padding fo 8 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_4_bytes( void )
{
    uint32 Buffer[ 2 ] = { 0 };
    uint8 Reference[ 8 ];

    memset( Reference, 0xAA, 8 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 4, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_8, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 8, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 12 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_12_bytes( void )
{
    uint32 Buffer[ 3 ] = { 0 };
    uint8 Reference[ 12 ];

    memset( Reference, 0xAA, 12 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 10, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_12, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 12, "Wrong padding value" );
}
/**
 * @brief   get close DLC with padding fo 16 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_16_bytes( void )
{
    uint32 Buffer[ 4 ] = { 0 };
    uint8 Reference[ 16 ];

    memset( Reference, 0xAA, 16 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 14, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_16, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 16, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 20 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_20_bytes( void )
{
    uint32 Buffer[ 5 ] = { 0 };
    uint8 Reference[ 20 ];

    memset( Reference, 0xAA, 20 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 18, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_20, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 20, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 24 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_24_bytes( void )
{
    uint32 Buffer[ 6 ] = { 0 };
    uint8 Reference[ 24 ];

    memset( Reference, 0xAA, 24 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 22, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_24, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 24, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 32 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_32_bytes( void )
{
    uint32 Buffer[ 8 ] = { 0 };
    uint8 Reference[ 32 ];

    memset( Reference, 0xAA, 32 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 30, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_32, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 32, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 48 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_48_bytes( void )
{
    uint32 Buffer[ 12 ] = { 0 };
    uint8 Reference[ 48 ];

    memset( Reference, 0xAA, 48 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 46, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_48, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 48, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding fo 64 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__padding_64_bytes( void )
{
    uint32 Buffer[ 16 ] = { 0 };
    uint8 Reference[ 64 ];

    memset( Reference, 0xAA, 64 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 51, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_64, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 64, "Wrong padding value" );
}

/**
 * @brief   get close DLC with padding for more then 64 bytes
 *
 * This test case will check that the function returns the correct DLC value and the padding
 * value is set to 0xAA
 */
void test__Can_GetClosestDlcWithPadding__more_than_64( void )
{
    uint32 Buffer[ 2 ] = { 0 };
    uint8 Reference[ 8 ];

    memset( Reference, 0xAA, 8 );

    uint8 Dlc = Can_GetClosestDlcWithPadding( 70, Buffer, 0xAA );

    TEST_ASSERT_EQUAL_HEX8_MESSAGE( CAN_OBJECT_PL_8, Dlc, "Wrong DLC value" );
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( Reference, Buffer, 8, "Wrong padding value" );
}

/**
 * @brief   get the most oldest Pdu If from TX FIFO
 *
 * This test case will check that the function returns the correct PduId and the number of elements
 * left in the FIFO
 */
void test__Can_GetTxPduId__get_the_oldes_pdu_id( void )
{
    /* clang-format off */
    const Can_Controller Controller[] = {
        {
            .ControllerId = 0u,
            .CanReference = CAN_FDCAN1,
        } 
    };
    /* clang-format on */

    PduIdType CanPduId;

    /*simulate data in TXEFS register with 2 elements in FIFO buffer*/
    CAN1->TXEFS         = 0x00000202;
    SRAMCAN1->EFSA[ 0 ] = 0xAA000000;
    SRAMCAN1->EFSA[ 1 ] = 0xBB000000;
    SRAMCAN1->EFSA[ 2 ] = 0xCC000000;

    uint8 Left = Can_GetTxPduId( Controller, &CanPduId );

    TEST_ASSERT_EQUAL_MESSAGE( 2, Left, "Wrong number of elements left in FIFO" );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xCC, CanPduId, "Wrong PduId" );
}

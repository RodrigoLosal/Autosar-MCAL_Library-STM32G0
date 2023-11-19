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

/**
 * @brief   Mock register for CAN1
 */
/* clang-format off */
Can_RegisterType CAN1_BASE =
{
    .TEST = 0x00000000,
    .CCCR = 0x00000001,
    .DBTP = 0x00000A33,
    .NBTP = 0x06000A03,
    .CKDIV = 0x00000000
};

/**
 * @brief   Mock register for CAN2
*/
Can_RegisterType CAN2_BASE =
{
    .TEST = 0x00000000,
    .CCCR = 0x00000001,
    .CKDIV = 0x00000000
};
/* clang-format on */

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


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    /*se inti values for control structure*/
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = &ArchCanConfig;

    CAN1_BASE.CCCR = 0x00000001;
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
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00000005, CAN1->CKDIV, "Wrong clock divider value" );
}

/**
 * @brief   Test case for SRAMCAN1 reg in Can_Init function.
 *
 * This test case will check that the SRAMCAN1 register is set to the correct value of 0 when config
 * structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 */
void test__Can_Arch_Init__flush_sram( void )
{
    SramCan_RegisterType SRAMCAN_TEST = { 0 };

    /*pre set the RAM area with values different from zero*/
    memset( &SRAMCAN1_BASE, 0xAA, sizeof( SramCan_RegisterType ) );

    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MEMORY_MESSAGE( &SRAMCAN_TEST, &SRAMCAN1_BASE, sizeof( SramCan_RegisterType ), "Wrong flush sram value" );
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
    Can_Arch_Init( &HwUnit, HwUnit.Config, CANARCH_EXTERNAL_LOOPBACK );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x000050C3, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000010, CAN1->TEST, "Wrong reset operational mode bit value" );
}

/**
 * @brief   set baud rate in classic mode
 *
 * This test case will check that the NBTP and DBTP registers are set to the correct values when
 * config structure is set with .ControllerId = CAN_CONTROLLER_0, and the Can_Init function is called.
 */
void test__Can_SetupBaudrateConfig__classic_mode( void )
{
    const Can_Controller *Controller                   = &HwUnit.Config->Controllers[ CANARCH_CONTROLLER_0 ];
    const Can_ControllerBaudrateConfig *BaudrateConfig = &Controller->BaudrateConfigs[ CANARCH_BAUDRATE_100k_CLASSIC ];

    Can_SetupBaudrateConfig( BaudrateConfig, CAN1 );

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
    const Can_Controller *Controller                   = &HwUnit.Config->Controllers[ CANARCH_CONTROLLER_0 ];
    const Can_ControllerBaudrateConfig *BaudrateConfig = &Controller->BaudrateConfigs[ CANARCH_BAUDRATE_100k_FD ];

    Can_SetupBaudrateConfig( BaudrateConfig, CAN1 );

    TEST_ASSERT_EQUAL_MESSAGE( 0x00000201, CAN1->CCCR, "Wrong clock stop value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C01, CAN1->NBTP, "Wrong NBTP value" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00030C10, CAN1->DBTP, "Wrong DBTP value" );
}

void test__Can_SetupConfiguredFilters__set_all_filters( void )
{
    Can_SetupConfiguredFilters( HwUnit.Config, CANARCH_CONTROLLER_0 );
}

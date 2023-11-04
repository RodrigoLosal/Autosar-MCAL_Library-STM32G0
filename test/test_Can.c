/**
 * @file    test_Can.c
 * @brief   **Unit testing for Can Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Can.h file
 */
#include "unity.h"
#include "Can.h"
#include "mock_Can_Arch.h"
#include "mock_Det.h"

extern Can_HwUnit HwUnit;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    Can_Init( Config );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{

}

/**
 * @brief   **Test Init when not CAN_CS_UNINIT**
 * 
 * The test checks that the function does not call the Can_Arch_Init function and HwUnit structure
 * does not set to CAN_CS_READY, plus Config pointer is not set.
*/
void test__Can_Init__when_not_uninit_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_READY;

    Det_ReportError_ExpectedAndReturn( E_OK );

    Can_Init( NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
}

/**
 * @brief   **Test Init when Controlller 0 is not CAN_CS_UNINIT**
 * 
 * The test checks that the function does not call the Can_Arch_Init function and HwUnit structure
 * does not set to CAN_CS_READY, Config pointer is not set and Controller states are not CAN_CS_STOPPED.
*/
void test__Can_Init__when_not_uninit_value_in_ControllerState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;
    HwUnit.Controller[0].ControllerState = CAN_CS_STOPPED;

    Det_ReportError_ExpectedAndReturn( E_OK );

    Can_Init( NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.Controller[0].ControllerState, "Controller state should not change" );
}

/**
 * @brief   **Test Init when Controlller 1 is not CAN_CS_UNINIT**
 * 
 * The test checks that the function does not call the Can_Arch_Init function and HwUnit structure
 * does not set to CAN_CS_READY, Config pointer is not set and Controller states are not CAN_CS_STOPPED.
*/
void test__Can_Init__when_not_uninit_value_in_ControllerState_1( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;
    HwUnit.Controller[1].ControllerState = CAN_CS_STOPPED;

    Det_ReportError_ExpectedAndReturn( E_OK );

    Can_Init( NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.Controller[1].ControllerState, "Controller state should not change" );
}

/**
 * @brief   **Test Init when HwUnit has all the right values**
 * 
 * The test checks that the function calls the Can_Arch_Init function and HwUnit structure
 * sets to CAN_CS_READY, Config pointer is set and Controller states are CAN_CS_STOPPED.
*/
void test__Can_Init__when_all_values_are_correct( void )
{
    Can_Arch_Init_ExpectedAndIgnore();

    Can_Init( &Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( &Config, HwUnit.Config, "Config pointer should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.Controller[0].ControllerState, "Controller state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.Controller[1].ControllerState, "Controller state should change" );
}

/**
 * @brief   **Test DeInit when not CAN_CS_UNINIT**
 * 
 * The test checks that the function does not call the Can_Arch_DeInit function and HwUnit structure
 * does not set to CAN_CS_UNINIT, plus Config pointer is not set.
*/
void test__Can_DeInit__when_not_uninit_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_READY;

    Det_ReportError_ExpectedAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
}

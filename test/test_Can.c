/**
 * @file    test_Can.c
 * @brief   **Unit testing for Can Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Can.h file
 */
#include "unity.h"
#include "Can_Cfg.h"
#include "Can.h"
#include "mock_Can_Arch.h"
#include "mock_Det.h"

#define CAN_CS_INVALID 0xFFu

extern Can_HwUnit HwUnit;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    HwUnit.HwUnitState          = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 1 ] = CAN_CS_UNINIT;
    HwUnit.Config               = NULL_PTR;

    Can_Arch_Init_Ignore( );

    Can_Init( &CanConfig );
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
    HwUnit.HwUnitState          = CAN_CS_INVALID;
    HwUnit.ControllerState[ 0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 1 ] = CAN_CS_UNINIT;
    HwUnit.Config               = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_Init( HwUnit.Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.HwUnitState, "Unit state should not change" );
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
    HwUnit.HwUnitState          = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 0 ] = CAN_CS_INVALID;
    HwUnit.ControllerState[ 1 ] = CAN_CS_UNINIT;
    HwUnit.Config               = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_Init( HwUnit.Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ 0 ], "Controller state should not change" );
}

/**
 * @brief   **Test Init when Controlller 1 is not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_Init function and HwUnit structure
 * does not set to CAN_CS_READY, Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_Init__when_not_uninit_value_in_ControllerState_1( void )
{
    HwUnit.HwUnitState          = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 1 ] = CAN_CS_INVALID;
    HwUnit.Config               = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_Init( HwUnit.Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ 1 ], "Controller state should not change" );
}

/**
 * @brief   **Test Init when HwUnit has all the right values**
 *
 * The test checks that the function calls the Can_Arch_Init function and HwUnit structure
 * sets to CAN_CS_READY, Config pointer is set and Controller states are CAN_CS_STOPPED.
 */
void test__Can_Init__when_all_values_are_correct( void )
{
    HwUnit.HwUnitState          = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ 1 ] = CAN_CS_UNINIT;
    HwUnit.Config               = NULL_PTR;

    Can_Arch_Init_Ignore( );

    Can_Init( &CanConfig );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( &CanConfig, HwUnit.Config, "Config pointer should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ 0 ], "Controller state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ 1 ], "Controller state should change" );
}

/**
 * @brief   **Test DeInit when not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_DeInit function and HwUnit structure
 * does not set to CAN_CS_UNINIT, plus Config pointer is not set.
 */
void test__Can_DeInit__when_not_uninit_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.HwUnitState, "Unit state should not change" );
}

/**
 * @brief   **Test DeInit when Controlller 0 is not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_DeInit function and HwUnit structure
 * does not set to CAN_CS_UNINIT, plus Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_DeInit__when_not_uninit_value_in_ControllerState( void )
{
    HwUnit.ControllerState[ 0 ] = CAN_CS_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ 0 ], "Controller state should not change" );
}

/**
 * @brief   **Test DeInit when Controlller 1 is not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_DeInit function and HwUnit structure
 * does not set to CAN_CS_UNINIT, plus Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_DeInit__when_not_uninit_value_in_ControllerState_1( void )
{
    HwUnit.ControllerState[ 1 ] = CAN_CS_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ 1 ], "Controller state should not change" );
}

/**
 * @brief   **Test DeInit when HwUnit has all the right values**
 *
 * The test checks that the function calls the Can_Arch_DeInit function and HwUnit structure
 * sets to CAN_CS_UNINIT, plus Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_DeInit__when_all_values_are_correct( void )
{
    Can_Arch_DeInit_Ignore( );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.ControllerState[ 0 ], "Controller state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.ControllerState[ 1 ], "Controller state should change" );
}

/**
 * @brief   **Test SetBaudrate when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_SetBaudrate function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_SetBaudrate__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetBaudrate( 0, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetBaudrate when BaudrateConfigID is unkown**
 *
 * The test checks that the function does not call the Can_Arch_SetBaudrate function when the BaudrateConfigID
 * is out of range.
 */
void test__Can_SetBaudrate__when_BaudrateConfigID_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetBaudrate( 0, 1 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetBaudrate when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_SetBaudrate function when the Controller
 * is out of range.
 */
void test__Can_SetBaudrate__when_Controller_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetBaudrate( 2, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetBaudrate when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_SetBaudrate function when all values are correct.
 */
void test__Can_SetBaudrate__when_all_values_are_correct( void )
{
    Can_Arch_SetBaudrate_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetBaudrate( 0, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, Return, "Return value should be E_OK" );
}

/**
 * @brief   **Test SetControllerMode when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_SetControllerMode function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_SetControllerMode__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( 0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetControllerMode when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_SetControllerMode function when the Controller
 * is out of range.
 */
void test__Can_SetControllerMode__when_Controller_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( 2, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetControllerMode when Transition is unkown**
 *
 * The test checks that the function does not call the Can_Arch_SetControllerMode function when the Transition
 * is out of range.
 */
void test__Can_SetControllerMode__when_Transition_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( 0, 0xFF );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetControllerMode when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_SetControllerMode function when all values are correct.
 */
void test__Can_SetControllerMode__when_all_values_are_correct( void )
{
    Can_Arch_SetControllerMode_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( 0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, Return, "Return value should be E_OK" );
}

/**
 * @brief   **Test DisableControllerInterrupts when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_DisableControllerInterrupts function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_DisableControllerInterrupts__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DisableControllerInterrupts( 0 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test DisableControllerInterrupts when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_DisableControllerInterrupts function when the Controller
 * is out of range.
 */
void test__Can_DisableControllerInterrupts__when_Controller_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DisableControllerInterrupts( 2 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test DisableControllerInterrupts when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_DisableControllerInterrupts function when all values are correct.
 */
void test__Can_DisableControllerInterrupts__when_all_values_are_correct( void )
{
    Can_Arch_DisableControllerInterrupts_Ignore( );

    Can_DisableControllerInterrupts( 0 );

    /* test is testing if Can_Arch_DisableControllerInterrupts was called */
}

/**
 * @brief   **Test EnableControllerInterrupts when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_EnableControllerInterrupts function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_EnableControllerInterrupts__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_EnableControllerInterrupts( 0 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test EnableControllerInterrupts when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_EnableControllerInterrupts function when the Controller
 * is out of range.
 */
void test__Can_EnableControllerInterrupts__when_Controller_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_EnableControllerInterrupts( 2 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test EnableControllerInterrupts when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_EnableControllerInterrupts function when all values are correct.
 */
void test__Can_EnableControllerInterrupts__when_all_values_are_correct( void )
{
    Can_Arch_EnableControllerInterrupts_Ignore( );

    Can_EnableControllerInterrupts( 0 );

    /* test is testing if Can_Arch_EnableControllerInterrupt was called */
}

/**
 * @brief   **Test CheckWakeup when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_CheckWakeup function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_CheckWakeup__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_CheckWakeup( 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test CheckWakeup when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_CheckWakeup function when the Controller
 * is out of range.
 */
void test__Can_CheckWakeup__when_Controller_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_CheckWakeup( 2 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test CheckWakeup when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_CheckWakeup function when all values are correct.
 */
void test__Can_CheckWakeup__when_all_values_are_correct( void )
{
    Can_Arch_CheckWakeup_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_CheckWakeup( 0 );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerMode when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerMode function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetControllerMode__when_not_ready_value_in_HwUnitState( void )
{
    Can_ControllerStateType ControllerMode;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerMode( 0, &ControllerMode );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerMode when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerMode function when the Controller
 * is out of range.
 */
void test__Can_GetControllerMode__when_Controller_is_unkown( void )
{
    Can_ControllerStateType ControllerMode;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerMode( 2, &ControllerMode );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerMode when ControllerMode is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerMode function when the ControllerMode
 * is NULL.
 */
void test__Can_GetControllerMode__when_ControllerMode_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerMode( 0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerMode when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetControllerMode function when all values are correct.
 */
void test__Can_GetControllerMode__when_all_values_are_correct( void )
{
    Can_ControllerStateType ControllerMode;

    Can_Arch_GetControllerMode_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerMode( 0, &ControllerMode );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerErrorState when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerErrorState function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetControllerErrorState__when_not_ready_value_in_HwUnitState( void )
{
    Can_ErrorStateType ErrorState;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerErrorState( 0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerErrorState when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerErrorState function when the Controller
 * is out of range.
 */
void test__Can_GetControllerErrorState__when_Controller_is_unkown( void )
{
    Can_ErrorStateType ErrorState;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerErrorState( 2, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerErrorState when ErrorState is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerErrorState function when the ErrorState
 * is NULL.
 */
void test__Can_GetControllerErrorState__when_ErrorState_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerErrorState( 0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerErrorState when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetControllerErrorState function when all values are correct.
 */
void test__Can_GetControllerErrorState__when_all_values_are_correct( void )
{
    Can_ErrorStateType ErrorState;

    Can_Arch_GetControllerErrorState_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerErrorState( 0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerRxErrorCounter when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerRxErrorCounter function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetControllerRxErrorCounter__when_not_ready_value_in_HwUnitState( void )
{
    uint8 RxErrorCounter;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( 0, &RxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerRxErrorCounter when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerRxErrorCounter function when the Controller
 * is out of range.
 */
void test__Can_GetControllerRxErrorCounter__when_Controller_is_unkown( void )
{
    uint8 RxErrorCounter;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( 2, &RxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerRxErrorCounter when RxErrorCounter is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerRxErrorCounter function when the RxErrorCounter
 * is NULL.
 */
void test__Can_GetControllerRxErrorCounter__when_RxErrorCounter_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( 0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerRxErrorCounter when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetControllerRxErrorCounter function when all values are correct.
 */
void test__Can_GetControllerRxErrorCounter__when_all_values_are_correct( void )
{
    uint8 RxErrorCounter;

    Can_Arch_GetControllerRxErrorCounter_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( 0, &RxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerTxErrorCounter when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerTxErrorCounter function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetControllerTxErrorCounter__when_not_ready_value_in_HwUnitState( void )
{
    uint8 TxErrorCounter;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( 0, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerTxErrorCounter when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerTxErrorCounter function when the Controller
 * is out of range.
 */
void test__Can_GetControllerTxErrorCounter__when_Controller_is_unkown( void )
{
    uint8 TxErrorCounter;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( 2, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerTxErrorCounter when TxErrorCounter is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetControllerTxErrorCounter function when the TxErrorCounter
 * is NULL.
 */
void test__Can_GetControllerTxErrorCounter__when_TxErrorCounter_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( 0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetControllerTxErrorCounter when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetControllerTxErrorCounter function when all values are correct.
 */
void test__Can_GetControllerTxErrorCounter__when_all_values_are_correct( void )
{
    uint8 TxErrorCounter;

    Can_Arch_GetControllerTxErrorCounter_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( 0, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

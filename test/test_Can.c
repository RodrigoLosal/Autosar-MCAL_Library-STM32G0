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

/**
 * @defgroup    support_defines defines for internal use
 *
 * @{ */
#define CAN_CS_INVALID        0xFFu /*!< Invalid driver/controller state */
#define CAN_CONTROLLER_2      2u    /*!< Invalid controller */
#define CAN_INVALID_BAUDRATE  0xFFu /*!< Invalid baudrate */
#define CAN_VALID_TX_PDU_ID   0xAAu /*!< Valid Tx Pdu ID */
#define CAN_INVALID_TX_PDU_ID 0x00u /*!< Invalid Tx Pdu ID */
/**
 * @} */

extern Can_HwUnit HwUnit;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = NULL_PTR;

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
    HwUnit.HwUnitState                         = CAN_CS_INVALID;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = NULL_PTR;

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
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_INVALID;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_Init( HwUnit.Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Controller state should not change" );
}

/**
 * @brief   **Test Init when Controlller 1 is not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_Init function and HwUnit structure
 * does not set to CAN_CS_READY, Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_Init__when_not_uninit_value_in_ControllerState_1( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_INVALID;
    HwUnit.Config                              = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_Init( HwUnit.Config );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit.Config, "Config pointer should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ CAN_CONTROLLER_1 ], "Controller state should not change" );
}

/**
 * @brief   **Test Init when HwUnit has all the right values**
 *
 * The test checks that the function calls the Can_Arch_Init function and HwUnit structure
 * sets to CAN_CS_READY, Config pointer is set and Controller states are CAN_CS_STOPPED.
 */
void test__Can_Init__when_all_values_are_correct( void )
{
    HwUnit.HwUnitState                         = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_UNINIT;
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_UNINIT;
    HwUnit.Config                              = NULL_PTR;

    Can_Arch_Init_Ignore( );

    Can_Init( &CanConfig );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( &CanConfig, HwUnit.Config, "Config pointer should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Controller state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_STOPPED, HwUnit.ControllerState[ CAN_CONTROLLER_1 ], "Controller state should change" );
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
    HwUnit.ControllerState[ CAN_CONTROLLER_0 ] = CAN_CS_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Controller state should not change" );
}

/**
 * @brief   **Test DeInit when Controlller 1 is not CAN_CS_UNINIT**
 *
 * The test checks that the function does not call the Can_Arch_DeInit function and HwUnit structure
 * does not set to CAN_CS_UNINIT, plus Config pointer is not set and Controller states are not CAN_CS_STOPPED.
 */
void test__Can_DeInit__when_not_uninit_value_in_ControllerState_1( void )
{
    HwUnit.ControllerState[ CAN_CONTROLLER_1 ] = CAN_CS_INVALID;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_READY, HwUnit.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_INVALID, HwUnit.ControllerState[ CAN_CONTROLLER_1 ], "Controller state should not change" );
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
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.ControllerState[ CAN_CONTROLLER_0 ], "Controller state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( CAN_CS_UNINIT, HwUnit.ControllerState[ CAN_CONTROLLER_1 ], "Controller state should change" );
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

    Std_ReturnType Return = Can_SetBaudrate( CAN_CONTROLLER_0, CAN_BAUDRATE_100k );

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

    Std_ReturnType Return = Can_SetBaudrate( CAN_CONTROLLER_0, CAN_INVALID_BAUDRATE );

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

    Std_ReturnType Return = Can_SetBaudrate( CAN_CONTROLLER_2, 0 );

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

    Std_ReturnType Return = Can_SetBaudrate( CAN_CONTROLLER_0, 0 );

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

    Std_ReturnType Return = Can_SetControllerMode( CAN_CONTROLLER_0, CAN_CS_STARTED );

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

    Std_ReturnType Return = Can_SetControllerMode( CAN_CONTROLLER_2, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetControllerMode when Transition is invalid**
 *
 * The test checks that the function does not call the Can_Arch_SetControllerMode function when the Transition
 * is out of range.
 */
void test__Can_SetControllerMode__when_Transition_is_invalid( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( CAN_CONTROLLER_0, CAN_CS_UNINIT );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, Return, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetControllerMode when Transition is invalid**
 *
 * The test checks that the function does not call the Can_Arch_SetControllerMode function when the Transition
 * is out of range.
 */
void test__Can_SetControllerMode__when_Transition_is_invalid2( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_SetControllerMode( CAN_CONTROLLER_0, CAN_CS_WAKEUP );

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

    Std_ReturnType Return = Can_SetControllerMode( CAN_CONTROLLER_0, CAN_CS_STARTED );

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

    Can_DisableControllerInterrupts( CAN_CONTROLLER_0 );

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

    Can_DisableControllerInterrupts( CAN_CONTROLLER_2 );

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

    Can_DisableControllerInterrupts( CAN_CONTROLLER_0 );

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

    Can_EnableControllerInterrupts( CAN_CONTROLLER_0 );

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

    Can_EnableControllerInterrupts( CAN_CONTROLLER_2 );

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

    Can_EnableControllerInterrupts( CAN_CONTROLLER_0 );

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

    Std_ReturnType Return = Can_CheckWakeup( CAN_CONTROLLER_0 );

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

    Std_ReturnType Return = Can_CheckWakeup( CAN_CONTROLLER_2 );

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

    Std_ReturnType Return = Can_CheckWakeup( CAN_CONTROLLER_0 );

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

    Std_ReturnType Return = Can_GetControllerMode( CAN_CONTROLLER_0, &ControllerMode );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerMode( CAN_CONTROLLER_2, &ControllerMode );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerMode( CAN_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerMode( CAN_CONTROLLER_0, &ControllerMode );

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

    Std_ReturnType Return = Can_GetControllerErrorState( CAN_CONTROLLER_0, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerErrorState( CAN_CONTROLLER_2, &ErrorState );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerErrorState( CAN_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerErrorState( CAN_CONTROLLER_0, &ErrorState );

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

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( CAN_CONTROLLER_0, &RxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( CAN_CONTROLLER_2, &RxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( CAN_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerRxErrorCounter( CAN_CONTROLLER_0, &RxErrorCounter );

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

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( CAN_CONTROLLER_0, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( CAN_CONTROLLER_2, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( CAN_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
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

    Std_ReturnType Return = Can_GetControllerTxErrorCounter( CAN_CONTROLLER_0, &TxErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_GetCurrentTime when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetCurrentTime function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetCurrentTime__when_not_ready_value_in_HwUnitState( void )
{
    Can_TimeStampType CurrentTime;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetCurrentTime( CAN_CONTROLLER_0, &CurrentTime );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetCurrentTime when Controller is unkown**
 *
 * The test checks that the function does not call the Can_Arch_GetCurrentTime function when the Controller
 * is out of range.
 */
void test__Can_GetCurrentTime__when_Controller_is_unkown( void )
{
    Can_TimeStampType CurrentTime;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetCurrentTime( CAN_CONTROLLER_2, &CurrentTime );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetCurrentTime when CurrentTime is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetCurrentTime function when the CurrentTime
 * is NULL.
 */
void test__Can_GetCurrentTime__when_CurrentTime_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetCurrentTime( CAN_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetCurrentTime when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetCurrentTime function when all values are correct.
 */
void test__Can_GetCurrentTime__when_all_values_are_correct( void )
{
    Can_TimeStampType CurrentTime;

    Can_Arch_GetCurrentTime_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetCurrentTime( CAN_CONTROLLER_0, &CurrentTime );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_EnableEgressTimeStamp when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_EnableEgressTimeStamp function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_EnableEgressTimeStamp__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_EnableEgressTimeStamp( CAN_HTH_0_CTRL_0 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test Can_EnableEgressTimeStamp when Hth is not for transmit**
 *
 * The test checks that the function does not call the Can_Arch_EnableEgressTimeStamp function when the Hth
 * is not for transmit.
 */
void test__Can_EnableEgressTimeStamp__when_Hth_is_unkown( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_EnableEgressTimeStamp( CAN_HRH_0_CTRL_0 );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test Can_EnableEgressTimeStamp when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_EnableEgressTimeStamp function when all values are correct.
 */
void test__Can_EnableEgressTimeStamp__when_all_values_are_correct( void )
{
    Can_Arch_EnableEgressTimeStamp_Ignore( );

    Can_EnableEgressTimeStamp( CAN_HTH_0_CTRL_0 );

    /* test is testing if Can_Arch_EnableEgressTimeStamp was called */
}

/**
 * @brief   **Test Can_GetEgressTimeStamp when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetEgressTimeStamp function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetEgressTimeStamp__when_not_ready_value_in_HwUnitState( void )
{
    Can_TimeStampType EgressTimeStamp;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetEgressTimeStamp( CAN_VALID_TX_PDU_ID, CAN_HTH_0_CTRL_0, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetEgressTimeStamp when Hth is not for transmit**
 *
 * The test checks that the function does not call the Can_Arch_GetEgressTimeStamp function when the Hth
 * is not for transmit.
 */
void test__Can_GetEgressTimeStamp__when_Hth_is_unkown( void )
{
    Can_TimeStampType EgressTimeStamp;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetEgressTimeStamp( CAN_VALID_TX_PDU_ID, CAN_HRH_0_CTRL_0, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetEgressTimeStamp when EgressTimeStamp is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetEgressTimeStamp function when the EgressTimeStamp
 * is NULL.
 */
void test__Can_GetEgressTimeStamp__when_EgressTimeStamp_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetEgressTimeStamp( CAN_VALID_TX_PDU_ID, CAN_HTH_0_CTRL_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetEgressTimeStamp when TxPduId is invalid**
 *
 * The test checks that the function does not call the Can_Arch_GetEgressTimeStamp function when the TxPduId
 * is invalid.
 *
 * @todo need to define what is a invalid TxPduId
 */
void test__Can_GetEgressTimeStamp__when_TxPduId_is_invalid( void )
{
    Can_TimeStampType EgressTimeStamp;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetEgressTimeStamp( CAN_INVALID_TX_PDU_ID, CAN_HTH_0_CTRL_0, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetEgressTimeStamp when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetEgressTimeStamp function when all values are correct.
 */
void test__Can_GetEgressTimeStamp__when_all_values_are_correct( void )
{
    Can_TimeStampType EgressTimeStamp;

    Can_Arch_GetEgressTimeStamp_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetEgressTimeStamp( CAN_VALID_TX_PDU_ID, CAN_HTH_0_CTRL_0, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_GetIngressTimeStamp when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_GetIngressTimeStamp function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_GetIngressTimeStamp__when_not_ready_value_in_HwUnitState( void )
{
    Can_TimeStampType IngressTimeStamp;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetIngressTimeStamp( CAN_HRH_0_CTRL_0, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetIngressTimeStamp when Hrh is not for receive**
 *
 * The test checks that the function does not call the Can_Arch_GetIngressTimeStamp function when the Hrh
 * is not for receive.
 */
void test__Can_GetIngressTimeStamp__when_Hrh_is_unkown( void )
{
    Can_TimeStampType IngressTimeStamp;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetIngressTimeStamp( CAN_HTH_0_CTRL_0, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetIngressTimeStamp when IngressTimeStamp is NULL**
 *
 * The test checks that the function does not call the Can_Arch_GetIngressTimeStamp function when the IngressTimeStamp
 * is NULL.
 */
void test__Can_GetIngressTimeStamp__when_IngressTimeStamp_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetIngressTimeStamp( CAN_HRH_0_CTRL_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_GetIngressTimeStamp when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetIngressTimeStamp function when all values are correct.
 */
void test__Can_GetIngressTimeStamp__when_all_values_are_correct( void )
{
    Can_TimeStampType IngressTimeStamp;

    Can_Arch_GetIngressTimeStamp_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_GetIngressTimeStamp( CAN_HRH_0_CTRL_0, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_Write when not CAN_CS_READY**
 *
 * The test checks that the function does not call the Can_Arch_Write function when CAN module
 * is not intialized (when HwUnitState is not CAN_CS_READY).
 */
void test__Can_Write__when_not_ready_value_in_HwUnitState( void )
{
    Can_PduType PduInfo;
    HwUnit.HwUnitState = CAN_CS_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_0, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}
/**
 * @brief   **Test Can_Write when Hth is not for transmit**
 *
 * The test checks that the function does not call the Can_Arch_Write function when the Hth
 * is not for transmit.
 */
void test__Can_Write__when_Hth_is_unkown( void )
{
    Can_PduType PduInfo;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HRH_0_CTRL_0, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_Write when PduInfo is NULL**
 *
 * The test checks that the function does not call the Can_Arch_Write function when the PduInfo
 * is NULL.
 */
void test__Can_Write__when_PduInfo_is_NULL( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_Write when lenght is bigger than 64**
 *
 * The test checks that the function does not call the Can_Arch_Write function when the lenght
 * is bigger than 64.
 */
void test__Can_Write__when_lenght_is_bigger_than_64( void )
{
    uint8 message[ 8 ];
    Can_PduType PduInfo;

    PduInfo.length = 65;
    PduInfo.id     = 0x000007ff;
    PduInfo.sdu    = message;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_0, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_Write when lenght is bigger than 8 in frame classic**
 *
 * The test checks that the function does not call the Can_Arch_Write function when the lenght
 * is bigger than 8 in frame classic.
 */
void test__Can_Write__when_lenght_is_bigger_than_8_in_frame_classic( void )
{
    uint8 message[ 8 ];
    Can_PduType PduInfo;

    PduInfo.length = 9;
    PduInfo.id     = 0x000007ff;
    PduInfo.sdu    = message;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_0, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_Write when frame is bigger than 8 but CAN mode is not FD**
 *
 * The test checks that the function does not call the Can_Arch_Write function when the frame
 * is bigger than 8 but CAN mode is not FD.
 */
void test__Can_Write__when_frame_is_bigger_than_8_but_CAN_mode_is_not_FD( void )
{
    uint8 message[ 8 ];
    Can_PduType PduInfo;

    PduInfo.length = 9;
    PduInfo.id     = 0x000007ff;
    PduInfo.sdu    = message;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_1, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Can_Write when all paramters are right**
 *
 * The test checks that the function calls the Can_Arch_Write function when all paramters are right.
 */
void test__Can_Write__when_all_paramters_are_right( void )
{
    uint8 message[ 8 ];
    Can_PduType PduInfo;

    PduInfo.length = 8;
    PduInfo.id     = 0x000007ff;
    PduInfo.sdu    = message;

    Can_Arch_Write_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_0, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_Write when all paramters are right and CAN mode is FD**
 *
 * The test checks that the function calls the Can_Arch_Write function when all paramters are right and CAN mode is FD.
 */
void test__Can_Write__when_all_paramters_are_right_and_CAN_mode_is_FD( void )
{
    uint8 message[ 64 ];
    Can_PduType PduInfo;

    PduInfo.length = 64;
    PduInfo.id     = 0x400007ff;
    PduInfo.sdu    = message;

    Can_Arch_Write_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Can_Write( CAN_HTH_0_CTRL_1, &PduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Can_GetVersionInfo when null**
 *
 * The test checks that the function does not call the Can_Arch_GetVersionInfo function when the versioninfo
 * is NULL.
 */
void test__Can_GetVersionInfo__when_null( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Can_GetVersionInfo( NULL_PTR );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test Can_GetVersionInfo when all values are correct**
 *
 * The test checks that the function calls the Can_Arch_GetVersionInfo function when all values are correct.
 */
void test__Can_GetVersionInfo__when_all_values_are_correct( void )
{
    Std_VersionInfoType versioninfo;

    Can_GetVersionInfo( &versioninfo );

    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.vendorID, CAN_MODULE_ID, "vendorID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.moduleID, CAN_VENDOR_ID, "moduleID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_major_version, CAN_SW_MAJOR_VERSION, "sw_major_version should be 1" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_minor_version, CAN_SW_MINOR_VERSION, "sw_minor_version should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_patch_version, CAN_SW_PATCH_VERSION, "sw_patch_version should be 0" );
}

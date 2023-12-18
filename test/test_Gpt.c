/**
 * @file    test_Gpt.c
 * @brief   **Unit testing for the GPT (General Purpose Timer) module in AUTOSAR.**
 *
 * This file contains unit tests for the GPT module functionality. It includes test cases for various
 * features such as initialization, deinitialization, start, stop, get timer values, etc. The tests
 * are designed to ensure the correct behavior and reliability of the GPT module in compliance with
 * AUTOSAR standards.
 */
#include "unity.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"
#include "mock_Gpt_Arch.h"
#include "mock_Det.h"

#define GPT_INVALID_CHANNEL       3
#define GPT_INVALID_ARR_VALUE_MIN 0x0
#define GPT_INVALID_ARR_VALUE_MAX 0x00010000u

extern Gpt_HwUnit HwUnit_Gpt;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    Gpt_Arch_Init_Ignore( );

    Gpt_Init( &GptConfig );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

void test__Gpt_Init__valid_pointer( void )
{
    Gpt_Arch_Init_Ignore( );

    Gpt_Init( &GptConfig );

    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Gpt.HwUnitState, GPT_STATE_INIT, "Expected HwUnitState changed to GPT_STATE_INIT" );
}

/**
 * @brief   **Test Gpt_DeInit when module is uninitialized**
 *
 * The test runs Gpt_DeInit function before the Gpt module is uninitialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_DeInit__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState = GPT_STATE_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_DeInit( );
}

/**
 * @brief   **Test Gpt_DeInit with module initialized**
 *
 * The test runs Gpt_DeInit function after the Gpt module is initialized, just to check
 * the change of the variable HwUnitState to GPT_STATE_UNINIT. The arch function is ignored
 * with a mock.
 */
void test__Gpt_DeInit__run_after_Gpt_Init( void )
{
    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_DeInit_Ignore( );
    Gpt_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Gpt.HwUnitState, GPT_STATE_UNINIT, "Expected HwUnitState changed to GPT_STATE_UNINIT" );
}

/**
 * @brief   **Test Gpt_GetTimeElapsed with module uninitialized**
 *
 * The test runs Gpt_GetTimeElapsed function before the Gpt module is initialized, to check is the
 * Return value changes to '0' due to the GPT_E_UNINIT error.
 */
void test__Gpt_GetTimeElapsed__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState    = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel   = GPT_CHANNEL_0;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_GetTimeElapsed_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeElapsed( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 0, "Expected ReturnValue to change to '0' due to GPT_E_UNINIT error." );
}

/**
 * @brief   **Test Gpt_GetTimeElapsed with module initialized and invalid Channel input**
 *
 * The test runs Gpt_GetTimeElapsed function after the Gpt module is initialized, to check is the
 * Return value changes to '0' due to the GPT_E_PARAM_CHANNEL error.
 */
void test__Gpt_GetTimeElapsed__run_after_Gpt_Init_invalid_Channel( void )
{
    Gpt_ChannelType Channel   = GPT_INVALID_CHANNEL;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_GetTimeElapsed_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeElapsed( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 0, "Expected ReturnValue to change to '0' due to GPT_E_PARAM_CHANNEL error." );
}

/**
 * @brief   **Test Gpt_GetTimeElapsed with module initialized and valid Channel input**
 *
 * The test runs Gpt_GetTimeElapsed function after the Gpt module is initialized, to check is the
 * Return value changes to E_OK.
 */
void test__Gpt_GetTimeElapsed__run_after_Gpt_Init_valid_Channel( void )
{
    Gpt_ChannelType Channel   = GPT_CHANNEL_1;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_GetTimeElapsed_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeElapsed( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected ReturnValue to change to E_OK." );
}

/**
 * @brief   **Test Gpt_GetTimeRemaining with module uninitialized**
 *
 * The test runs Gpt_GetTimeRemaining function before the Gpt module is initialized, to check is the
 * Return value changes to '0' due to the GPT_E_UNINIT error.
 */
void test__Gpt_GetTimeRemaining__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState    = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel   = GPT_CHANNEL_0;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_GetTimeRemaining_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeRemaining( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 0, "Expected ReturnValue to change to '0' due to GPT_E_UNINIT error." );
}

/**
 * @brief   **Test Gpt_GetTimeRemaining with module initialized and invalid Channel input**
 *
 * The test runs Gpt_GetTimeRemaining function after the Gpt module is initialized, to check is the
 * Return value changes to '0' due to the GPT_E_PARAM_CHANNEL error.
 */
void test__Gpt_GetTimeRemaining__run_after_Gpt_Init_invalid_Channel( void )
{
    Gpt_ChannelType Channel   = GPT_INVALID_CHANNEL;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_GetTimeRemaining_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeRemaining( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, 0, "Expected ReturnValue to change to '0' due to GPT_E_PARAM_CHANNEL error." );
}

/**
 * @brief   **Test Gpt_GetTimeRemaining with module initialized and valid Channel input**
 *
 * The test runs Gpt_GetTimeRemaining function after the Gpt module is initialized, to check is the
 * Return value changes to E_OK.
 */
void test__Gpt_GetTimeRemaining__run_after_Gpt_Init_valid_Channel( void )
{
    Gpt_ChannelType Channel   = GPT_CHANNEL_1;
    Gpt_ValueType ReturnValue = E_NOT_OK;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_GetTimeRemaining_IgnoreAndReturn( E_OK );
    ReturnValue = Gpt_GetTimeRemaining( Channel );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected ReturnValue to change to E_OK." );
}

/**
 * @brief   **Test Gpt_StartTimer with module uninitialized**
 *
 * The test runs Gpt_StartTimer function before the Gpt module is uninitialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_StartTimer__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState  = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel = GPT_CHANNEL_0;
    Gpt_ValueType Value     = GPT_ARR_MAX;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StartTimer( Channel, Value );
}

/**
 * @brief   **Test Gpt_StartTimer with module initialized, invalid Channel and valid ARR Value**
 *
 * The test runs Gpt_StartTimer function after the Gpt module is initialized, with an invalid Channel
 * and an valid ARR Value, just to check the Det for this case. This is a
 * non-return function, so no check value-change validation is performed.
 */
void test__Gpt_StartTimer__run_after_Gpt_Init_invalid_Channel_valid_Value( void )
{
    Gpt_ChannelType Channel = GPT_INVALID_CHANNEL;
    Gpt_ValueType Value     = GPT_ARR_MAX;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StartTimer( Channel, Value );
}

/**
 * @brief   **Test Gpt_StartTimer with module initialized, valid Channel and invalid ARR Value ( ARR = 0 )**
 *
 * The test runs Gpt_StartTimer function after the Gpt module is initialized, with a valid Channel
 * and an invalid ARR Value ( ARR = 0 ), just to check the branch which executes the Det for this case.
 * This is a non-return function, so no check value-change validation is performed.
 */
void test__Gpt_StartTimer__run_after_Gpt_Init_valid_Channel_invalid_Value_Min( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_0;
    Gpt_ValueType Value     = GPT_INVALID_ARR_VALUE_MIN;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StartTimer( Channel, Value );
}

/**
 * @brief   **Test Gpt_StartTimer with module initialized, valid Channel and invalid ARR Value ( ARR > ARR_MAX )**
 *
 * The test runs Gpt_StartTimer function after the Gpt module is initialized, with a valid Channel
 * and an invalid ARR Value ( ARR > ARR_MAX ), just to check the branch which executes the Det for this case.
 * This is a non-return function, so no check value-change validation is performed.
 */
void test__Gpt_StartTimer__run_after_Gpt_Init_valid_Channel_invalid_Value_Max( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_0;
    Gpt_ValueType Value     = GPT_INVALID_ARR_VALUE_MAX;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StartTimer( Channel, Value );
}

/**
 * @brief   **Test Gpt_StartTimer with module initialized, valid Channel and valid ARR Value**
 *
 * The test runs Gpt_StartTimer function after the Gpt module is initialized, with an valid Channel
 * and a valid ARR Value, just to check the branch which executes the the Arch function. This is a
 * non-return function, so no check value-change validation is performed.
 */
void test__Gpt_StartTimer__run_after_Gpt_Init_valid_Channel_valid_Value( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_0;
    Gpt_ValueType Value     = GPT_ARR_MAX;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_StartTimer_Ignore( );
    Gpt_StartTimer( Channel, Value );
}

/**
 * @brief   **Test Gpt_StopTimer with module uninitialized**
 *
 * The test runs Gpt_StopTimer function before the Gpt module is uninitialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_StopTimer__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState  = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel = GPT_CHANNEL_0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StopTimer( Channel );
}

/**
 * @brief   **Test Gpt_StopTimer with module initialized and invalid Channel**
 *
 * The test runs Gpt_StopTimer function after the Gpt module is initialized, with an invalid Channel,
 * just to check the Det for this case. This is a non-return function, so no check value-change
 * validation is performed.
 */
void test__Gpt_StopTimer__run_after_Gpt_Init_invalid_Channel( void )
{
    Gpt_ChannelType Channel = GPT_INVALID_CHANNEL;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_StopTimer( Channel );
}

/**
 * @brief   **Test Gpt_StopTimer with module initialized and valid Channel**
 *
 * The test runs Gpt_StopTimer function after the Gpt module is initialized, with an valid Channel,
 * just to check the branch which executes the Arch function. This is a non-return function, so
 * no check value-change validation is performed.
 */
void test__Gpt_StopTimer__run_after_Gpt_Init_valid_Channel( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_1;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_StopTimer_Ignore( );
    Gpt_StopTimer( Channel );
}

/**
 * @brief   **Test GetVersionInfo with module Uninitialized**
 *
 * The test runs GetVersionInfo function before the Gpt module is initialized, just to check
 * the branch which executes the Det for this case. Noo check value-change validation is performed
 * due to no passing a VersionInfoType pointer.
 */
void test__Gpt_GetVersionInfo__run_without_rigth_parameter( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   **Test GetVersionInfo with module Initialized**
 *
 * The test runs GetVersionInfo function after the Gpt module is initialized.
 * Value-change validation is performed on the VersionInfo struct.
 */
void test__Gpt_GetVersionInfo__run_with_right_parameter( void )
{
    Std_VersionInfoType versionInfo_test = { 0 };

    Gpt_GetVersionInfo( &versionInfo_test );

    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.moduleID, GPT_MODULE_ID, "Expected GPT_MODULE_ID" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.vendorID, GPT_VENDOR_ID, "Expected GPT_VENDOR_ID" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_major_version, GPT_SW_MAJOR_VERSION, "Expected GPT_SW_MAJOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_minor_version, GPT_SW_MINOR_VERSION, "Expected GPT_SW_MINOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfo_test.sw_patch_version, GPT_SW_PATCH_VERSION, "Expected GPT_SW_MINOR_VERSION" );
}

/**
 * @brief   **Test Gpt_EnableNotification with module uninitialized**
 *
 * The test runs Gpt_EnableNotification function before the Gpt module is uninitialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_EnableNotification__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState  = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel = GPT_CHANNEL_0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_EnableNotification( Channel );
}

/**
 * @brief   **Test Gpt_EnableNotification with module initialized and invalid Channel**
 *
 * The test runs Gpt_EnableNotification function after the Gpt module is initialized, with an invalid
 * Channel, just to check the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_EnableNotification__run_after_Gpt_Init_invalid_Channel( void )
{
    Gpt_ChannelType Channel = GPT_INVALID_CHANNEL;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_EnableNotification( Channel );
}

/**
 * @brief   **Test Gpt_EnableNotification with module initialized, valid Channel and invalid function pointer**
 *
 * The test runs Gpt_EnableNotification function after the Gpt module is initialized, with a valid
 * Channel and an invalid function pointer in the config variable GptNotification, just to check the
 * branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_EnableNotification__run_after_Gpt_Init_valid_Channel_invalid_Pointer( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_1;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_EnableNotification_Ignore( );
    Gpt_EnableNotification( Channel );
}

/**
 * @brief   **Test Gpt_DisableNotification with module uninitialized**
 *
 * The test runs Gpt_DisableNotification function before the Gpt module is uninitialized, just to check
 * the branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_DisableNotification__run_before_Gpt_Init( void )
{
    HwUnit_Gpt.HwUnitState  = GPT_STATE_UNINIT;
    Gpt_ChannelType Channel = GPT_CHANNEL_0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_DisableNotification( Channel );
}

/**
 * @brief   **Test Gpt_DisableNotification with module initialized and invalid Channel**
 *
 * The test runs Gpt_DisableNotification function after the Gpt module is initialized, with an invalid
 * Channel, just to check the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_DisableNotification__run_after_Gpt_Init_invalid_Channel( void )
{
    Gpt_ChannelType Channel = GPT_INVALID_CHANNEL;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Det_ReportError_IgnoreAndReturn( E_OK );
    Gpt_DisableNotification( Channel );
}

/**
 * @brief   **Test Gpt_DisableNotification with module initialized, valid Channel and invalid function pointer**
 *
 * The test runs Gpt_DisableNotification function after the Gpt module is initialized, with a valid
 * Channel and an invalid function pointer in the config variable GptNotification, just to check the
 * branch which executes the Det for this case. This is a non-return function, so no check
 * value-change validation is performed.
 */
void test__Gpt_DisableNotification__run_after_Gpt_Init_valid_Channel_invalid_Pointer( void )
{
    Gpt_ChannelType Channel = GPT_CHANNEL_1;

    Gpt_Arch_Init_Ignore( );
    Gpt_Init( &GptConfig );

    Gpt_Arch_DisableNotification_Ignore( );
    Gpt_DisableNotification( Channel );
}

/**
 * @brief   **Test Gpt_Notification_Channel0**
 *
 * The test runs Gpt_Notification_Channel0. This is a non-return function, so no check value-change
 * validation is performed.
 */
void test__Gpt_Notification_Channel0( void )
{
    Gpt_Arch_Notification_Channel0_Ignore( );
    Gpt_Notification_Channel0( );
}

/**
 * @brief   **Test Gpt_Notification_Channel1**
 *
 * The test runs Gpt_Notification_Channel1. This is a non-return function, so no check value-change
 * validation is performed.
 */
void test__Gpt_Notification_Channel1( void )
{
    Gpt_Arch_Notification_Channel1_Ignore( );
    Gpt_Notification_Channel1( );
}
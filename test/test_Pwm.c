/**
 * @file    test_Pwm.c
 * @brief   **Unit testing for Pwm Driver**
 * @author  Jazmin Melendrez
 *
 * This file contains unit tests for the PWM (Pulse Width Modulation) driver module including 41
 * test cases covering 13 functions and their 54 branches.
 */
#include "unity.h"
#include "Pwm_Cfg.h"
#include "Pwm.h"
#include "mock_Pwm_Arch.h"
#include "mock_Det.h"

/**
 * @defgroup These definitions set the valid and invalid channel numbers
 *
 * @{ */
#define VALID_CHANNEL_NUMBER       2 /*!< Valid Channels Numbers */
#define INVALID_CHANNEL_NUMBER_UP  3 /*!< Invalid channel number, too high */
#define INVALID_CHANNEL_NUMBER_LOW 0 /*!< Invalid channel number, too low */
/**
 * @} */

/**
 * @defgroup These definitions set the current and the new Period and duty Cycle
 *
 * @{ */
#define PERIOD                     10 /*!< Current Period */
#define PERIOD_NEW                 20 /*!< New Period */
#define DUTY_CYCLE                 50 /*!< Current Duty Cycle */
#define DUTY_CYCLE_NEW             20 /*!< New Duty Cycle */
/**
 * @} */

/**
 * @defgroup This definition set the Power State Type
 *
 * @{ */
#define POWER_STATE                0 /*!< Full Power State Type */
/**
 * @} */

/**
 * @defgroup These definitions set the minimum and maximum channel numbers for PWM operations.
 *
 * @{ */
#define PWM_CHANNEL_MIN            1 /*!< Minimum valid PWM channel number.  */
#define PWM_CHANNEL_MAX            2 /*!< Maximum valid PWM channel number.  */
/**
 * @} */

extern Pwm_HwUnit HwUnit_Pwm;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    HwUnit_Pwm.HwUnitState       = PWM_STATE_UNINIT,
    HwUnit_Pwm.Config            = NULL_PTR,
    HwUnit_Pwm.Pwm_ChannelClass  = PWM_VARIABLE_PERIOD,
    HwUnit_Pwm.Pwm_channelNumber = PWM_CHANNEL_MAX;
    HwUnit_Pwm.Duty_Cycle        = DUTY_CYCLE;
    HwUnit_Pwm.Period            = PERIOD;
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test Initialization when module is uninitialized**
 *
 * The test checks that the function set to Init the Pwm hardware unit state and that the Pwm hardware
 * configuration pointer points to the test configuration.
 */
void test__Pwm_Init__run_for_first_time( void )
{
    Pwm_ConfigType PwmConfig = { 0 };

    Pwm_Arch_Init_Ignore( );

    Pwm_Init( &PwmConfig );

    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Pwm.HwUnitState, PWM_STATE_INIT, "Expected HwUnitState to be changed to PWM_STATE_INIT after initialization" );
    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Pwm.Config, &PwmConfig, "Expected Config to point to the provided PwmConfig structure" );
}

/**
 * @brief   **Test Initialization When PWM Module is already initialized**
 *
 * This test checks that the function does not change the hardware unit state and the configuration
 * pointer remains unchanged as the Pwm Module is already initialized.
 */
void test__Pwm_Init__is_already_initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;
    HwUnit_Pwm.Config      = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_Init( HwUnit_Pwm.Config );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_STATE_INIT, HwUnit_Pwm.HwUnitState, "Unit state should not change as it is already initialized" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit_Pwm.Config, "Config pointer should not change as the module is already initialized" );
}

/**
 * @brief   **Test DeInitialization When PWM Module is Uninitialized**
 *
 * This test checks that calling Pwm_DeInit does not alter the state or the configuration pointer
 * of the module when it is uninitialized.
 */
void test__Pwm_DeInit__When_Pwm_is_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_STATE_UNINIT, HwUnit_Pwm.HwUnitState, "Unit state should not change as it is not initialized yet" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit_Pwm.Config, "Config pointer should not change as the module is Uninitialized" );
}

/**
 * @brief   **Test DeInitialization When PWM Module is Initialized**
 *
 * This test ensures that calling Pwm_DeInit alter to the Uninit state of the module when the module is
 * initialized.
 */
void test__Pwm_DeInit__When_Pwm_is_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Pwm_Arch_DeInit_Ignore( );

    Pwm_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_STATE_UNINIT, HwUnit_Pwm.HwUnitState, "Expected HwUnitState to be changed to PWM_STATE_UNINIT after Deinitialization" );
}

/**
 * @brief   **Test SetDutyCycle When PWM Module is Uninitialized**
 *
 * This test checks that the function does not change the new duty cycle as the Pwm module
 * is uninitialized.
 */
void test__Pwm_SetDutyCycle__When_Pwm_is_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetDutyCycle( VALID_CHANNEL_NUMBER, DUTY_CYCLE_NEW );
    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should not change as the module is Uninitialized" );
}

/**
 * @brief   **Test SetDutyCycle When the Channel Number is an invalid value**
 *
 * This test checks that the function maintains the existing duty cycle when the module is initialized
 * and the provided Channel Number is above Valid Range.
 */
void test__Pwm_SetDutyCycle__When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetDutyCycle( INVALID_CHANNEL_NUMBER_UP, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should not change as the Channel Number is invalid" );
}

/**
 * @brief   **Test SetDutyCycle When the Channel Number Is Below Valid Rangee**
 *
 * This test checks that the function retains the current duty cycle when the provided Channel Number
 * is below Valid Range.
 */
void test__Pwm_SetDutyCycle__When_ChannelNumber_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_Arch_SetDutyCycle_Ignore( );

    Pwm_SetDutyCycle( INVALID_CHANNEL_NUMBER_LOW, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should not change as the Channel Number is invalid" );
}

/**
 * @brief   **Test SetDutyCycle When the Pwm is Initialized**
 *
 * This test checks that the function update the duty cycle when the Pwm Module is already initilized.
 */
void test__Pwm_SetDutyCycle__When_Pwm_is_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Pwm_Arch_SetDutyCycle_Ignore( );

    Pwm_SetDutyCycle( VALID_CHANNEL_NUMBER, DUTY_CYCLE_NEW );
    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should change as the Pwm module is initialized" );
}

/**
 * @brief   **Test SetPeriodAndDuty When the PWM Module Is Uninitialized**
 *
 * This test checks that the Pwm_SetPeriodAndDuty function does not change the current duty cycle
 * and period when the module is uninitialized.
 */
void test__Pwm_SetPeriodAndDuty__When_Pwm_is_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetPeriodAndDuty( PWM_CHANNEL_MAX, PERIOD_NEW, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should not change as the module is Uninitialized" );
    TEST_ASSERT_EQUAL_MESSAGE( PERIOD, HwUnit_Pwm.Period, "Period should not change as the module is Uninitialized" );
}

/**
 * @brief   **Test SetPeriodAndDuty When the Channel Is Not Variable Period Class**
 *
 * This test checks that the Pwm_SetPeriodAndDuty function does not change the current duty cycle and
 * period when the Unit is initialized and the channel class is fixed period, which does not allow
 * period changes.
 */
void test__Pwm_SetPeriodAndDuty__When_ChannelNotVariablePeriod( void )
{
    HwUnit_Pwm.HwUnitState      = PWM_STATE_INIT;
    HwUnit_Pwm.Pwm_ChannelClass = PWM_FIXED_PERIOD;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetPeriodAndDuty( VALID_CHANNEL_NUMBER, PERIOD_NEW, DUTY_CYCLE );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should remain unchanged as the channel is of fixed period class" );
    TEST_ASSERT_EQUAL_MESSAGE( PERIOD, HwUnit_Pwm.Period, "Period should remain unchanged as the channel is of fixed period class" );
}

/**
 * @brief   **Test SetPeriodAndDuty When the Channel is an invalid value**
 *
 * This test checks that the Pwm_SetPeriodAndDuty function does not change the current duty cycle and
 * period when the Unit is initialized and the provided Channel Number is above Valid Range.
 */
void test__Pwm_SetPeriodAndDuty__When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState      = PWM_STATE_INIT;
    HwUnit_Pwm.Pwm_ChannelClass = PWM_VARIABLE_PERIOD;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetPeriodAndDuty( INVALID_CHANNEL_NUMBER_UP, PERIOD_NEW, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should remain unchanged as the channel exceeds the maximum allowable value" );
    TEST_ASSERT_EQUAL_MESSAGE( PERIOD, HwUnit_Pwm.Period, "Period should remain unchanged as the channel exceeds the maximum allowable value" );
}

/**
 * @brief   **Test SetPeriodAndDuty When the Channel Number Is Below Valid Range**
 *
 * This test checks that the Pwm_SetPeriodAndDuty function does not change the current duty cycle and
 * period when the Unit is initialized and the provided Channel Number is below Valid Range.
 */
void test__Pwm_SetPeriodAndDuty__When_ChannelNumber_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState      = PWM_STATE_INIT;
    HwUnit_Pwm.Pwm_ChannelClass = PWM_VARIABLE_PERIOD;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetPeriodAndDuty( INVALID_CHANNEL_NUMBER_LOW, PERIOD_NEW, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should remain unchanged since the channel number is below the valid range" );
    TEST_ASSERT_EQUAL_MESSAGE( PERIOD, HwUnit_Pwm.Period, "Period should remain unchanged since the channel number is below the valid range" );
}

/**
 * @brief   **Test SetPeriodAndDuty When all conditions are valid**
 *
 * This test checks that the Pwm_SetPeriodAndDuty function change duty cycle and period when the Unit is
 * initialized, the channel class is variable and the Channel number is within the range.
 */
void test__Pwm_SetPeriodAndDuty__When_ConditionsAreValid( void )
{
    HwUnit_Pwm.HwUnitState      = PWM_STATE_INIT;
    HwUnit_Pwm.Pwm_ChannelClass = PWM_VARIABLE_PERIOD;

    Pwm_Arch_SetPeriodAndDuty_Ignore( );

    Pwm_SetPeriodAndDuty( VALID_CHANNEL_NUMBER, PERIOD_NEW, DUTY_CYCLE_NEW );

    TEST_ASSERT_EQUAL_MESSAGE( DUTY_CYCLE, HwUnit_Pwm.Duty_Cycle, "Duty cycle should Change" );
    TEST_ASSERT_EQUAL_MESSAGE( PERIOD, HwUnit_Pwm.Period, "Period should Change " );
}

/**
 * @brief   **Test SetOutputToIdle When PWM Module is Uninitialized**
 *
 * The test checks that the function does not call the Pwm_Arch_SetOutputToIdle function when
 * the module is uninitialized.
 */
void test__Pwm_SetOutputToIdle__When_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetOutputToIdle( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test SetOutputToIdle Reports Error When Channel Number Is Invalid**
 *
 * This test verifies that the Pwm_SetOutputToIdle function reports an error when the module
 * is initialized and the Channel Number is above Valid Range.
 */
void test__Pwm_SetOutputToIdle__When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetOutputToIdle( INVALID_CHANNEL_NUMBER_UP );
}

/**
 * @brief   **Test SetOutputToIdle When the Channel Number Is Below Valid Range**
 *
 * This test verifies that the Pwm_SetOutputToIdle function reports an error when the module is
 * initialized and the Channel Number is below Valid Range.
 */
void test__Pwm_SetOutputToIdle__When_ChannelNumber_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_SetOutputToIdle( INVALID_CHANNEL_NUMBER_LOW );
}

/**
 * @brief   **Test SetOutputToIdle When Initialized and Channel Is Valid**
 *
 * This test the Pwm_SetOutputToIdle function after the Pwm module has been initialized and
 * with a valid channel number.
 */
void test__Pwm_SetOutputToIdle__When_InitializedAndChannelIsValid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Pwm_Arch_SetOutputToIdle_Ignore( );

    Pwm_SetOutputToIdle( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test GetOutputState When PWM Module is Uninitialized**
 *
 * The test checks that the function does not call the Pwm_Arch_GetOutputState function when
 * the module is uninitialized.
 */
void test__Pwm_GetOutputState__When_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_OutputStateType state = Pwm_GetOutputState( VALID_CHANNEL_NUMBER );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_HIGH, state, "The state should not change as the module is uninitialized" );
}

/**
 * @brief   **Test GetOutputState When the Channel Number is Above Valid Range**
 *
 * This test checks that the Pwm_GetOutputState function reports an error when the module
 * is initialized and the Channel Number is above Valid Range.
 */
void test__Pwm_GetOutputState__When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_OutputStateType state = Pwm_GetOutputState( INVALID_CHANNEL_NUMBER_UP );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_HIGH, state, "The state should not change as the Channel Number is invalid" );
}

/**
 * @brief   **Test GetOutputState When the Channel Number Is Below Valid Range**
 *
 * This test checks that the Pwm_GetOutputState function reports an error when the module is
 * initialized and the Channel Number is below Valid Range.
 */
void test__Pwm_GetOutputState__When_ChannelNumber_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_OutputStateType state = Pwm_GetOutputState( INVALID_CHANNEL_NUMBER_LOW );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_HIGH, state, "The state should not change as the Channel Number is invalid" );
}

/**
 * @brief   **Test GetOutputState When the Pwm module is Initilized and the Channel Number is valid**
 *
 * This test checks that the Pwm_GetOutputState function call the Pwm_Arch_GetOutputState function
 * when the module is initialized and the provided Channel Number is valid
 */
void test__Pwm_GetOutputState__When_InitializedAndChannelIsValid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Pwm_Arch_GetOutputState_IgnoreAndReturn( E_OK );

    Pwm_OutputStateType state = Pwm_GetOutputState( VALID_CHANNEL_NUMBER );

    TEST_ASSERT_EQUAL_MESSAGE( PWM_HIGH, state, "The state should change as the module is initialized" );
}

/**
 * @brief   **Test Pwm_DisableNotification when the module is uninitialized**
 *
 * The test checks that the function does not call the Pwm_Arch_DisableNotification function when
 * the module is uninitialized.
 */
void test__Pwm_DisableNotification__When_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_DisableNotification( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test Pwm_DisableNotification when the Channel Number is above Valid Range**
 *
 * The test checks that the function does not call the Pwm_Arch_DisableNotification function when
 * the module is initialized and the Channel Number is above Valid Range.
 */
void test__Pwm_DisableNotification__When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_DisableNotification_Ignore( );

    Pwm_DisableNotification( INVALID_CHANNEL_NUMBER_UP );
}

/**
 * @brief   **Test Pwm_DisableNotification When the Channel Number Is Below Valid Range**
 *
 * The test checks that the function does not call the Pwm_Arch_DisableNotification function when
 * the module is initialized and the provided Channel Number Channel Number is below Valid Range.
 */
void test__Pwm_DisableNotification__When_ChannelNumber_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_DisableNotification_Ignore( );

    Pwm_DisableNotification( INVALID_CHANNEL_NUMBER_LOW );
}

/**
 * @brief   **Test Pwm_DisableNotification When Channel Number Equals Total Channels**
 *
 * This test checks that the Pwm_DisableNotification function calls Pwm_Arch_DisableNotification when
 * the module is initialized and the provided Channel Number equals the total number of channels,
 * which is considered a valid value.
 */
void test__Pwm_DisableNotification__When_ChannelNumber_Is_Equal_To_Pwm_ChannelNumber( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_DisableNotification_Ignore( );

    Pwm_DisableNotification( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test Pwm_DisableNotification when the Channel Number is valid**
 *
 * The test checks that the function call the Pwm_Arch_DisableNotification function when the module
 * is uninitialized and the provided Channel Number is valid.
 */
void test__Pwm_DisableNotification__When_ChannelNumber_Isvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_DisableNotification_Ignore( );

    Pwm_DisableNotification( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test Pwm_DisableNotification when the module is initialized and the Channel Number is valid**
 *
 * The test checks that the function calls the Pwm_Arch_DisableNotification function when the module
 * is initialized and the Channel Number is valid.
 */
void test__Pwm_DisableNotification__When_InitializedAndChannelIsValid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_DisableNotification_Ignore( );

    Pwm_DisableNotification( VALID_CHANNEL_NUMBER );
}

/**
 * @brief   **Test Pwm_EnableNotification when the module is uninitialized**
 *
 * The test checks that the function does not call the Pwm_Arch_EnableNotification function when
 * the module is uninitialized.
 */
void test__Pwm_EnableNotification_Should_ReportError_When_Uninitialized( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_EnableNotification( VALID_CHANNEL_NUMBER, PWM_RISING_EDGE );
}

/**
 * @brief   **Test Pwm_EnableNotification when the Channel Number is invalid**
 *
 * The test checks that the function does not call the Pwm_Arch_EnableNotification function when
 * the module
 * is initialized and the Channel Number is above Valid Range.
 */
void test__Pwm_EnableNotification_Should_ReportError_When_ChannelNumber_IsInvalid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_EnableNotification( INVALID_CHANNEL_NUMBER_UP, PWM_RISING_EDGE );
}

/**
 * @brief   **Test Pwm_EnableNotification when the module is initialized and the Channel Number is valid**
 *
 * The test checks that the function calls the Pwm_Arch_EnableNotification function when the module
 * is initialized and the Channel Number is valid.
 */
void test__Pwm_EnableNotification__When_InitializedAndChannelIsValid( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Pwm_Arch_EnableNotification_Ignore( );

    Pwm_EnableNotification( VALID_CHANNEL_NUMBER, PWM_RISING_EDGE );
}

/**
 * @brief   **Test Pwm_EnableNotification When the Channel Number Is Below Valid Range**
 *
 * The test checks that the function does not call the Pwm_Arch_EnableNotification function when
 * the Module is Initialized and the Channel Number is below Valid Range.
 */
void test__Pwm_EnableNotification__When_Channel_IsInvalid_0( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_EnableNotification( INVALID_CHANNEL_NUMBER_LOW, PWM_RISING_EDGE );
}

/**
 * @brief   **Test Pwm_SetPowerState when the module is uninitialized**
 *
 * The test checks that does not call the Pwm_Arch_SetPowerState function and return a E_NOT_OK
 * when the module is uninitialized,
 */
void test__Pwm_SetPowerState__When_Uninitialized( void )
{
    Pwm_PowerStateRequestResultType result;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType returnValue = Pwm_SetPowerState( &result );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, returnValue, "The return value should be E_NOT_OK as the module is uninitialized" );
}

/**
 * @brief   **Test Pwm_SetPowerState when the module is initialized**
 *
 * The test checks that call the Pwm_Arch_SetPowerState function and return the expected E_OK value
 * when the module is initialized,
 */
void test__Pwm_SetPowerState__When_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Std_ReturnType expectedReturnValue = E_OK;

    Pwm_Arch_SetPowerState_IgnoreAndReturn( E_OK );

    Pwm_PowerStateRequestResultType result;
    Std_ReturnType returnValue = Pwm_SetPowerState( &result );

    TEST_ASSERT_EQUAL_MESSAGE( expectedReturnValue, returnValue, "The return value should be E_OK as the module is initialized" );
}

/**
 * @brief   **Test GetCurrentPowerState when the module is uninitialized**
 *
 * The test checks that does not call the Pwm_Arch_GetCurrentPowerState function and return a E_NOT_OK
 * when the module is uninitialized,
 */
void test__Pwm_GetCurrentPowerState__When_Uninitialized( void )
{
    Pwm_PowerStateType currentPowerState;
    Pwm_PowerStateRequestResultType result;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType returnValue = Pwm_GetCurrentPowerState( &currentPowerState, &result );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, returnValue, "The return value should be E_NOT_OK as the module is uninitialized" );
}

/**
 * @brief   **Test GetCurrentPowerState when the module is initialized**
 *
 * The test checks that call the Pwm_Arch_GetCurrentPowerState function and return the Current Power State
 * when the module is initialized.
 */
void test__Pwm_GetCurrentPowerState__When_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_Arch_GetCurrentPowerState_IgnoreAndReturn( E_OK );

    Pwm_PowerStateType currentPowerState = PWM_FULL_POWER;
    Pwm_PowerStateRequestResultType result;

    Std_ReturnType returnValue = Pwm_GetCurrentPowerState( &currentPowerState, &result );

    TEST_ASSERT_EQUAL_MESSAGE( currentPowerState, returnValue, "The return value should be the current Power State as the module is initialized" );
}

/**
 * @brief   **Test GetTargetPowerState when the module is uninitialized**
 *
 * The test checks that does not call the Pwm_Arch_GetTargetPowerState function and return a E_NOT_OK
 * when the module is uninitialized,
 */
void test__Pwm_GetTargetPowerState__When_Uninitialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_PowerStateType targetPowerState;
    Pwm_PowerStateRequestResultType result;

    Std_ReturnType returnValue = Pwm_GetTargetPowerState( &targetPowerState, &result );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, returnValue, "The return value should be E_NOT_OK as the module is uninitialized" );
}

/**
 * @brief   **Test Pwm_GetTargetPowerState when the module is initialized**
 *
 * The test checks that call the Pwm_Arch_GetTargetPowerStatefunction and return the expected E_OK value
 * when the module is initialized,
 */
void test__Pwm_GetTargetPowerState__When_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_Arch_GetTargetPowerState_IgnoreAndReturn( E_OK );

    Pwm_PowerStateType targetPowerState;
    Pwm_PowerStateRequestResultType result;

    Std_ReturnType returnValue = Pwm_GetTargetPowerState( &targetPowerState, &result );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, returnValue, "The return value should be E_OK as the module is initialized" );
}

/**
 * @brief   **Test PreparePowerState when the module is uninitialized**
 *
 * The test checks that does not call the Pwm_Arch_PreparePowerState function and return a E_NOT_OK
 * when the module is uninitialized,
 */
void test__Pwm_PreparePowerState__When_Uninitialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_PowerStateRequestResultType result;
    Std_ReturnType returnValue = Pwm_PreparePowerState( POWER_STATE, &result );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, returnValue, "The return value should be E_NOT_OK as the module is uninitialized" );
}

/**
 * @brief   **Test Pwm_PreparePowerState when the module is initialized**
 *
 * The test checks that call the Pwm_Arch_PreparePowerState function and return the expected E_OK value
 * when the module is initialized,
 */
void test__Pwm_PreparePowerState__When_Initialized( void )
{
    HwUnit_Pwm.HwUnitState = PWM_STATE_INIT;

    Std_ReturnType expectedReturnValue = E_OK;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Pwm_Arch_PreparePowerState_IgnoreAndReturn( E_OK );

    Pwm_PowerStateRequestResultType result;
    Pwm_PowerStateType PowerState = PWM_FULL_POWER;

    Std_ReturnType returnValue = Pwm_PreparePowerState( PowerState, &result );

    TEST_ASSERT_EQUAL_MESSAGE( expectedReturnValue, returnValue, "The return value should be E_OK as the module is initialized" );
}

/**
 * @brief   **Test Pwm_GetVersionInfo when null**
 *
 * The test checks that the function does not call the Pwm_Arch_GetVersionInfo function when the versioninfo
 * is NULL.
 */
void test__Pwm_GetVersionInfo__When_Null( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Pwm_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   **Test Pwm_GetVersionInfo when all values are correct**
 *
 * The test checks that the function calls the Pwm_Arch_GetVersionInfo function when all values are correct.
 */
void test__Pwm_GetVersionInfo__run_with_rigth_parameter( void )
{
    Std_VersionInfoType versioninfo;

    Pwm_GetVersionInfo( &versioninfo );

    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.vendorID, PWM_MODULE_ID, "vendorID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.moduleID, PWM_VENDOR_ID, "moduleID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_major_version, PWM_SW_MAJOR_VERSION, "sw_major_version should be 1" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_minor_version, PWM_SW_MINOR_VERSION, "sw_minor_version should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_patch_version, PWM_SW_PATCH_VERSION, "sw_patch_version should be 0" );
}
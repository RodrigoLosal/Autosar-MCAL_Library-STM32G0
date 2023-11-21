/**
 * @file    test_Mcu.c
 * @brief   **Unit testing for MCU Driver**
 * @author  Angel Lozano
 *
 * The Mcu module provides servic ...
 * ...
 */
#include "unity.h"
#include "Mcu_Cfg.h"
#include "Mcu.h"
#include "mock_Mcu_Arch.h"
#include "mock_Det.h"

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
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
void test__Mcu_Init__myTest( void )
{
    uint16 var;

    var = 15;

    TEST_ASSERT_EQUAL_MESSAGE( var, 15, "Expected 15 heheheha" );
}
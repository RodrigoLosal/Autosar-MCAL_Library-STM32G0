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

extern Mcu_HwUnit HwUnit_Mcu;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    HwUnit_Mcu.HwUnitState = MCU_STATE_UNINIT;
    HwUnit_Mcu.Config      = NULL_PTR;
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test Init**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_Init__run_for_first_time( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Mcu.HwUnitState, MCU_STATE_INIT, "Expected HwUnitState changed to MCU_STATE_INIT(1)" );
    TEST_ASSERT_EQUAL_MESSAGE( HwUnit_Mcu.Config, &McuConfigTest, "Expected Config points to McuConfigTest" );
}

/**
 * @brief   **Test InitRamSection**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_InitRamSection__run_before_Mcu_init( void )
{
    Mcu_RamSectionType RamSectionTest = 0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_InitRamSection( RamSectionTest );
}

/**
 * @brief   **Test InitRamSection**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_InitRamSection__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest      = { 0 };
    Mcu_RamSectionType RamSectionTest = 0;
    Std_ReturnType ReturnValue        = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_InitRamSection_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_InitRamSection( RamSectionTest );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}
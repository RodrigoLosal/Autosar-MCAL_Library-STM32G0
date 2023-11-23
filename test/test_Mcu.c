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

/**
 * @brief   **Test Init Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_InitClock__run_before_Mcu_init( void )
{
    Mcu_ClockType ClockSettingTest = 0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_InitClock( ClockSettingTest );
}

/**
 * @brief   **Test Init Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_InitClock__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest   = { 0 };
    Mcu_ClockType ClockSettingTest = 0;
    Std_ReturnType ReturnValue     = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_InitClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_InitClock( ClockSettingTest );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}

/**
 * @brief   **Test Distribute Pll Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_DistributePllClock__run_before_Mcu_init( void )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

    Det_ReportError_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_NOT_OK (1)" );
}

/**
 * @brief   **Test Distribute Pll Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init_with_pll_unlocked( void )
{
    Mcu_ConfigType McuConfigTest = { .PllStatus = MCU_PLL_UNLOCKED };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Det_ReportError_IgnoreAndReturn( E_OK );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_OK (1)" );
}

/**
 * @brief   **Test Distribute Pll Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init_with_pll_undefined( void )
{
    Mcu_ConfigType McuConfigTest = { .PllStatus = MCU_PLL_STATUS_UNDEFINED };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Det_ReportError_IgnoreAndReturn( E_OK );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_NOT_OK, "Expected E_OK (1)" );
}

/**
 * @brief   **Test Distribute Pll Clock**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_DistributePllClock__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_DistributePllClock_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_DistributePllClock( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}

/**
 * @brief   **Test Get Pll Status**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetPllStatus__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetPllStatus( );
}

/**
 * @brief   **Test Get Pll Status**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetPllStatus__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_GetPllStatus_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetPllStatus( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}

/**
 * @brief   **Test Get Reset Reason**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetResetReason__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetResetReason( );
}

/**
 * @brief   **Test Get Reset Reason**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetResetReason__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_GetResetReason_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetResetReason( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}

/**
 * @brief   **Test Get Reset Raw Value**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetResetRawValue__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetResetRawValue( );
}

/**
 * @brief   **Test Get Reset Raw Value**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetResetRawValue__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_GetResetRawValue_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetResetRawValue( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}

/**
 * @brief   **Test Perform Reset**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_PerformReset__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_PerformReset( );
}

/**
 * @brief   **Test Perform Reset**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_PerformReset__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_PerformReset_Ignore( );
    Mcu_PerformReset( );
}

/**
 * @brief   **Test Set Mode**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_SetMode__run_before_Mcu_init( void )
{
    Mcu_ModeType McuModeTest = 0;

    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_SetMode( McuModeTest );
}

/**
 * @brief   **Test Set Mode**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_SetMode__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Mcu_ModeType McuModeTest     = 0;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_SetMode_Ignore( );
    Mcu_SetMode( McuModeTest );
}

/**
 * @brief   **Test Get Version Info**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetVersionInfo__run_without_rigth_parameter( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   **Test Get Version Info**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetVersionInfo__run_with_rigth_parameter( void )
{
    Std_VersionInfoType versionInfoTest = { 0 };

    Mcu_GetVersionInfo( &versionInfoTest );

    TEST_ASSERT_EQUAL_MESSAGE( versionInfoTest.moduleID, MCU_MODULE_ID, "Expected MCU_MODULE_ID (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfoTest.vendorID, MCU_VENDOR_ID, "Expected MCU_VENDOR_ID (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfoTest.sw_major_version, MCU_SW_MAJOR_VERSION, "Expected MCU_SW_MAJOR_VERSION (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfoTest.sw_minor_version, MCU_SW_MINOR_VERSION, "Expected MCU_SW_MINOR_VERSION (0)" );
    TEST_ASSERT_EQUAL_MESSAGE( versionInfoTest.sw_patch_version, MCU_SW_PATCH_VERSION, "Expected MCU_SW_MINOR_VERSION (0)" );
}

/**
 * @brief   **Test Get Ram State**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetRamState__run_before_Mcu_init( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );
    Mcu_GetRamState( );
}

/**
 * @brief   **Test Get Ram State**
 *
 * The test runs Init function, calling Arch_Init and checking that HwUnitState of the HwUnit
 * struct changes by MCU_STATE_INIT (value 1) and Config of HwUnit points to the passed parameter
 */
void test__Mcu_GetRamState__run_after_Mcu_init( void )
{
    Mcu_ConfigType McuConfigTest = { 0 };
    Std_ReturnType ReturnValue   = E_NOT_OK;

    Mcu_Arch_Init_Ignore( );
    Mcu_Init( &McuConfigTest );

    Mcu_Arch_GetRamState_IgnoreAndReturn( E_OK );
    ReturnValue = Mcu_GetRamState( );

    TEST_ASSERT_EQUAL_MESSAGE( ReturnValue, E_OK, "Expected E_OK (0)" );
}
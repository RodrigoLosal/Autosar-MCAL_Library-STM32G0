#include "unity.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "mock_Port_Arch.h"
#include "mock_Det.h"

#define PORT_PIN_INVALID     0xFFu
#define PORT_PINMODE_INVALID 0xF0u
#define PORT_ALTMODE_INVALID 0x0Fu

extern const Port_ConfigType *Port_ConfigPtr;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    Port_Arch_Init_Ignore( );

    Port_Init( &PortConfig );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   Test the Port_Init function with an invalid pointer.
 *
 * The function Port_Init shall raise the error PORT_E_INIT_FAILED if the parameter ConfigPtr is a
 * null value.
 */
void test__Port_Init__null_pointer( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_Init( NULL_PTR );
}

/**
 * @brief   Test the Port_Init function with a valid pointer.
 *
 * The function Port_Init shall raise the error PORT_E_INIT_FAILED if the parameter ConfigPtr is a
 * null value.
 */
void test__Port_Init__valid_pointer( void )
{
    Port_Arch_Init_Ignore( );

    Port_Init( &PortConfig );
}

/**
 * @brief   Test the Port_SetPinDirection function with an invalid pointer.
 *
 * The function Port_SetPinDirection shall raise the error PORT_E_UNINIT if the parameter
 * Port_ConfigPtr is a null value.
 */
void test__Port_SetPinDirection__null_pointer( void )
{
    Port_ConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinDirection( PORT_PIN_LCD_CS, PORT_PIN_OUT );
}

/**
 * @brief   Test the Port_SetPinDirection function with an invalid pin.
 *
 * The function Port_SetPinDirection shall raise the error PORT_E_PARAM_PIN if an incorrect port pin
 * ID has been passed.
 */
void test__Port_SetPinDirection__invalid_pin( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinDirection( PORT_PIN_INVALID, PORT_PIN_OUT );
}

/**
 * @brief   Test the Port_SetPinDirection function with an unchangeable pin.
 *
 * The function Port_SetPinDirection shall raise the error PORT_E_DIRECTION_UNCHANGEABLE if the pin
 * is not configured as changeable.
 */
void test__Port_SetPinDirection__unchangeable_pin( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinDirection( PORT_PIN_LCD_RS, PORT_PIN_OUT );
}

/**
 * @brief   Test the Port_SetPinDirection function with a valid pin.
 *
 * The function Port_SetPinDirection shall raise the error PORT_E_PARAM_PIN if an incorrect port pin
 * ID has been passed.
 */
void test__Port_SetPinDirection__valid_pin( void )
{
    Port_Arch_SetPinDirection_Ignore( );

    Port_SetPinDirection( PORT_PIN_LCD_CS, PORT_PIN_OUT );
}

/**
 * @brief   Test the Port_SetPinMode function with an invalid pointer.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_UNINIT if the parameter Port_ConfigPtr
 * is a null value.
 */
void test__Port_SetPinMode__null_pointer( void )
{
    Port_ConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinMode( PORT_PIN_LCD_CS, PORT_MODE_OUTPUT );
}

/**
 * @brief   Test the Port_SetPinMode function with an invalid pin.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_PARAM_PIN if an incorrect port pin ID
 * has been passed.
 */
void test__Port_SetPinMode__invalid_pin( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinMode( PORT_PIN_INVALID, PORT_MODE_OUTPUT );
}

/**
 * @brief   Test the Port_SetPinMode function with an unchangeable pin.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_MODE_UNCHANGEABLE if the mode is
 * unchangeable.
 */
void test__Port_SetPinMode__unchangeable_pin( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinMode( PORT_PIN_LCD_RS, PORT_MODE_OUTPUT );
}

/**
 * @brief   Test the Port_SetPinMode function with an invalid mode.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_PARAM_INVALID_MODE if an incorrect port
 * pin ID has been passed.
 */
void test__Port_SetPinMode__invalid_pin_mode( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinMode( PORT_PIN_LCD_CS, PORT_PINMODE_INVALID );
}

/**
 * @brief   Test the Port_SetPinMode function with an invalid alt mode.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_PARAM_INVALID_MODE if an incorrect port
 * pin ID has been passed.
 */
void test__Port_SetPinMode__invalid_alt_mode( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_SetPinMode( PORT_PIN_LCD_CS, PORT_ALTMODE_INVALID );
}

/**
 * @brief   Test the Port_SetPinMode function with a valid pin and mode.
 *
 * The function Port_SetPinMode shall raise the error PORT_E_PARAM_PIN if an incorrect port pin ID
 * has been passed.
 */
void test__Port_SetPinMode__valid_pin_and_mode( void )
{
    Port_Arch_SetPinMode_Ignore( );

    Port_SetPinMode( PORT_PIN_LCD_CS, PORT_MODE_OUTPUT );
}

/**
 * @brief   Test the Port_GetVersionInfo function with an invalid pointer.
 *
 * The function Port_GetVersionInfo shall raise the error PORT_E_PARAM_POINTER if the parameter
 * versioninfo is a null pointer.
 */
void test__Port_GetVersionInfo__null_pointer( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   Test the Port_GetVersionInfo function with a valid pointer.
 *
 * The function Port_GetVersionInfo shall raise the error PORT_E_PARAM_POINTER if the parameter
 * versioninfo is a null pointer.
 */
void test__Port_GetVersionInfo__valid_pointer( void )
{
    Std_VersionInfoType versioninfo;

    Port_GetVersionInfo( &versioninfo );

    TEST_ASSERT_EQUAL( PORT_MODULE_ID, versioninfo.moduleID );
    TEST_ASSERT_EQUAL( PORT_VENDOR_ID, versioninfo.vendorID );
    TEST_ASSERT_EQUAL( PORT_SW_MAJOR_VERSION, versioninfo.sw_major_version );
    TEST_ASSERT_EQUAL( PORT_SW_MINOR_VERSION, versioninfo.sw_minor_version );
    TEST_ASSERT_EQUAL( PORT_SW_PATCH_VERSION, versioninfo.sw_patch_version );
}

/**
 * @brief   Test the Port_RefreshPortDirection function with an invalid pointer.
 *
 * The function Port_RefreshPortDirection shall raise the error PORT_E_UNINIT if the parameter
 * Port_ConfigPtr is a null value.
 */
void test__Port_RefreshPortDirection__null_pointer( void )
{
    Port_ConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Port_RefreshPortDirection( );
}

/**
 * @brief   Test the Port_RefreshPortDirection function with a valid pointer.
 *
 * The function Port_RefreshPortDirection shall raise the error PORT_E_UNINIT if the parameter
 * Port_ConfigPtr is a null value.
 */
void test__Port_RefreshPortDirection__valid_pointer( void )
{
    Port_Arch_RefreshPortDirection_Ignore( );

    Port_RefreshPortDirection( );
}

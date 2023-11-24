/**
 * @file    test_Dio.c
 * @brief   **Unit testing for Dio Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Dio.h file
 */
#include "unity.h"
#include "Dio_Cfg.h"
#include "Dio.h"
#include "mock_Dio_Arch.h"
#include "mock_Det.h"

#define DIO_CHANNEL_INVALID 100u /*!< invalid channel */
#define DIO_PORT_INVALID    100u /*!< invalid port */


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test for Dio_ReadChannel**
 *
 * This test case verifies that Dio_ReadChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_ReadChannel__invalid_channel( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_LevelType Level = Dio_ReadChannel( DIO_CHANNEL_INVALID );
    TEST_ASSERT_EQUAL_MESSAGE( STD_OFF, Level, "Dio_ReadChannel() should return STD_OFF" );
}

/**
 * @brief   **Test for Dio_ReadChannel**
 *
 * This test case verifies that Dio_ReadChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_ReadChannel__valid_channel( void )
{
    Dio_Arch_ReadChannel_IgnoreAndReturn( STD_ON );

    Dio_LevelType Level = Dio_ReadChannel( DIO_CHANNEL_RED_LED );
    TEST_ASSERT_EQUAL_MESSAGE( STD_ON, Level, "Dio_ReadChannel() should return STD_ON" );
}

/**
 * @brief   **Test for Dio_WriteChannel**
 *
 * This test case verifies that Dio_WriteChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_WriteChannel__invalid_channel( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_WriteChannel( DIO_CHANNEL_INVALID, STD_ON );
}

/**
 * @brief   **Test for Dio_WriteChannel**
 *
 * This test case verifies that Dio_WriteChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_WriteChannel__valid_channel( void )
{
    Dio_Arch_WriteChannel_Ignore( );

    Dio_WriteChannel( DIO_CHANNEL_RED_LED, STD_ON );
}

/**
 * @brief   **Test for Dio_ReadPort**
 *
 * This test case verifies that Dio_ReadPort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_ReadPort__invalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_PortLevelType Level = Dio_ReadPort( DIO_PORT_INVALID );
    TEST_ASSERT_EQUAL_MESSAGE( STD_OFF, Level, "Dio_ReadPort() should return 0x00" );
}

/**
 * @brief   **Test for Dio_ReadPort**
 *
 * This test case verifies that Dio_ReadPort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_ReadPort__valid_port( void )
{
    Dio_Arch_ReadPort_IgnoreAndReturn( 0xAA );

    Dio_PortLevelType Level = Dio_ReadPort( DIO_PORT_A );
    TEST_ASSERT_EQUAL_MESSAGE( 0xAA, Level, "Dio_ReadPort() should return 0x00" );
}

/**
 * @brief   **Test for Dio_WritePort**
 *
 * This test case verifies that Dio_WritePort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_WritePort__invalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_WritePort( DIO_PORT_INVALID, 0x00 );
}

/**
 * @brief   **Test for Dio_WritePort**
 *
 * This test case verifies that Dio_WritePort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_WritePort__valid_port( void )
{
    Dio_Arch_WritePort_Ignore( );

    Dio_WritePort( DIO_PORT_A, 0x00 );
}

/**
 * @brief   **Test for Dio_ReadChannelGroup**
 *
 * This test case verifies that Dio_ReadChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_ReadChannelGroup__invalid_group( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_PortLevelType Level = Dio_ReadChannelGroup( NULL_PTR );
    TEST_ASSERT_EQUAL_MESSAGE( 0, Level, "Dio_ReadChannelGroup() should return 0x00" );
}

/**
 * @brief   **Test for Dio_ReadChannelGroup**
 *
 * This test case verifies that Dio_ReadChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_ReadChannelGroup__invalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_PortLevelType Level = Dio_ReadChannelGroup( DIO_GROUP_INVALID );
    TEST_ASSERT_EQUAL_MESSAGE( 0, Level, "Dio_ReadChannelGroup() should return 0x00" );
}

/**
 * @brief   **Test for Dio_ReadChannelGroup**
 *
 * This test case verifies that Dio_ReadChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_ReadChannelGroup__valid_group( void )
{
    Dio_Arch_ReadChannelGroup_IgnoreAndReturn( 0x01 );

    Dio_PortLevelType Level = Dio_ReadChannelGroup( DIO_GROUP_LCD_DATA );
    TEST_ASSERT_EQUAL_MESSAGE( 0x01, Level, "Dio_ReadChannelGroup() should return 0x00" );
}

/**
 * @brief   **Test for Dio_WriteChannelGroup**
 *
 * This test case verifies that Dio_WriteChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_WriteChannelGroup__invalid_group( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_WriteChannelGroup( NULL_PTR, 0x00 );
}

/**
 * @brief   **Test for Dio_WriteChannelGroup**
 *
 * This test case verifies that Dio_WriteChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_WriteChannelGroup__invalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_WriteChannelGroup( DIO_GROUP_INVALID, 0x00 );
}

/**
 * @brief   **Test for Dio_WriteChannelGroup**
 *
 * This test case verifies that Dio_WriteChannelGroup() returns the correct value
 * when a valid group is passed as parameter.
 */
void test__Dio_WriteChannelGroup__valid_group( void )
{
    Dio_Arch_WriteChannelGroup_Ignore( );

    Dio_WriteChannelGroup( DIO_GROUP_LCD_DATA, 0x00 );
}

/**
 * @brief   **Test for Dio_FlipChannel**
 *
 * This test case verifies that Dio_FlipChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_FlipChannel__invalid_channel( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_LevelType Level = Dio_FlipChannel( DIO_CHANNEL_INVALID );
    TEST_ASSERT_EQUAL_MESSAGE( STD_OFF, Level, "Dio_FlipChannel() should return STD_OFF" );
}

/**
 * @brief   **Test for Dio_FlipChannel**
 *
 * This test case verifies that Dio_FlipChannel() returns the correct value
 * when a valid channel is passed as parameter.
 */
void test__Dio_FlipChannel__valid_channel( void )
{
    Dio_Arch_FlipChannel_IgnoreAndReturn( STD_ON );

    Dio_LevelType Level = Dio_FlipChannel( DIO_CHANNEL_RED_LED );
    TEST_ASSERT_EQUAL_MESSAGE( STD_ON, Level, "Dio_FlipChannel() should return STD_OFF" );
}

/**
 * @brief   **Test for Dio_MaskedWritePort**
 *
 * This test case verifies that Dio_MaskedWritePort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_MaskedWritePort__invalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_MaskedWritePort( DIO_PORT_INVALID, 0x00, 0x00 );
}

/**
 * @brief   **Test for Dio_MaskedWritePort**
 *
 * This test case verifies that Dio_MaskedWritePort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_MaskedWritePort__valid_port( void )
{
    Dio_Arch_MaskedWritePort_Ignore( );

    Dio_MaskedWritePort( DIO_PORT_A, 0xAA, 0x00 );
}

/**
 * @brief   **Test for Dio_MaskedWritePort**
 *
 * This test case verifies that Dio_MaskedWritePort() returns the correct value
 * when a valid port is passed as parameter.
 */
void test__Dio_MaskedWritePort__ivalid_port( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_MaskedWritePort( DIO_PORT_INVALID, 0x00, 0x00 );
}

/**
 * @brief   **Test for Dio_GetVersionInfo**
 *
 * This test case verifies that Dio_GetVersionInfo() returns the correct value
 */
void test__Dio_GetVersionInfo__valid_pointer( void )
{
    Std_VersionInfoType VersionInfo;
    Dio_GetVersionInfo( &VersionInfo );

    TEST_ASSERT_EQUAL_MESSAGE( DIO_SW_MAJOR_VERSION, VersionInfo.sw_major_version, "Dio_GetVersionInfo() should return DIO_SW_MAJOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( DIO_SW_MINOR_VERSION, VersionInfo.sw_minor_version, "Dio_GetVersionInfo() should return DIO_SW_MINOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( DIO_SW_PATCH_VERSION, VersionInfo.sw_patch_version, "Dio_GetVersionInfo() should return DIO_SW_PATCH_VERSION" );
}

/**
 * @brief   **Test for Dio_GetVersionInfo**
 *
 * This test case verifies that Dio_GetVersionInfo() returns the correct value
 */
void test__Dio_GetVersionInfo__invalid_pointer( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Dio_GetVersionInfo( NULL_PTR );
}

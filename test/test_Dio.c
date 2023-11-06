/**
 * @file    test_Dio.c
 * @brief   **This file contains the unit testing of DIO driver.**
 *
 * The file is designed to test the functions of DIO as entablished at the official
 * documentation of AUTOSAR.
 */
#include "unity.h"
#include "Registers.h"
#include "Bfx_32bits.h"
#include "Dio.h"

/*mock microcontroller registers with its initial values*/
/*                               Reserverd1            IDR   ODR   BSRR    Reserved2       BRR*/
Dio_RegisterType DIOA_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOB_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOC_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOD_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOE_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOF_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };


/**
  * @defgroup Bit-operations support macros to read and write bits.
  @{ */
#define GET_1_BIT( reg, bit )              ( ( ( reg ) >> ( bit ) ) & 0x01u )               /*!< This macro will return the logical state of \
                                                                                            the input data for the requested bit position. */
#define GET_BITS( reg, BitStartPn, BitLn ) ( reg >> BitStartPn ) & ( ( 1u << BitLn ) - 1u ) /*!< This macro will return the logical state of the \
                                                                                            input data for the requested bits positions. */
/**
  @} */

/**
 * @brief   **setUp**
 *
 * This function is required by Ceedling to run any code before the test cases.
 */
void setUp( void )
{
}

/**
 * @brief   **tearDown**
 *
 * This function is required by Ceedling to run any code before the test cases.
 */
void tearDown( void )
{
}


/**
 * @brief   **Test of Dio_WriteChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the specified Level will be written to the specified port.
 */
void test__Dio_WriteChannel__pin_A07( void )
{
    Dio_LevelType PinLevel;
    Dio_WriteChannel( DIO_PIN_PA_07, STD_HIGH );
    PinLevel = GET_1_BIT( DIOA->ODR, 1u );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_WriteChannel function for DIO_PIN_PB_02**
 *
 * This test will check that the specified Level will be written to the specified port.
 */
void test__Dio_WriteChannel__pin_B02( void )
{
    Dio_LevelType PinLevel;
    Dio_WriteChannel( DIO_PIN_PB_02, STD_HIGH );
    PinLevel = GET_1_BIT( DIOB->ODR, 1u );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the function returns the value of the specified DIO channel.
 */
void test__Dio_ReadChannel__pin_A07( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_ReadChannel( DIO_PIN_PA_07 );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadChannel function for DIO_PIN_PB_02**
 *
 * This test will check that the function returns the value of the specified DIO channel.
 */
void test__Dio_ReadChannel__pin_B02( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_ReadChannel( DIO_PIN_PB_02 );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_FlipChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the function returns the value of the specified DIO channel inverted.
 */
void test__Dio_FlipChannel__pin_A07( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_FlipChannel( DIO_PIN_PA_07 );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_FlipChannel function for DIO_PIN_PD_03**
 *
 * This test will check that the function returns the value of the specified DIO channel inverted.
 */
void test__Dio_FlipChannel__pin_D03( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_FlipChannel( DIO_PIN_PD_03 );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadPort function for PORT_B**
 *
 * This test will check that the function returns the value for all channels of the specified Port.
 */
void test__Dio_ReadPort_B( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_ReadPort( PORTS_B );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadPort function for PORT_D**
 *
 * This test will check that the function returns the value for all channels of the specified Port.
 */
void test__Dio_ReadPort_D( void )
{
    Dio_LevelType PinLevel;
    PinLevel = Dio_ReadPort( PORTS_D );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_WritePort function for PORT_B**
 *
 * This test will check that the function is setting the value specified by the Level parameter
 * for the specified port.
 */
void test__Dio_WritePort_B( void )
{
    Dio_WritePort( PORTS_B, 0x05 );
    TEST_ASSERT_EQUAL_MESSAGE( 5u, DIOB->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_WritePort function for PORT_C**
 *
 * This test will check that the function is setting the value specified by the Level parameter
 * for the specified port.
 */
void test__Dio_WritePort_C( void )
{
    Dio_WritePort( PORTS_C, 0x04 );
    TEST_ASSERT_EQUAL_MESSAGE( 4u, DIOC->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_WriteChannelGroup function**
 *
 * This test will check that the function has set a subset of the adjacent bits of
 * a port (channel group) to a specified level. Also this function will perform
 * the masking of the channel group and in addition the function will perform the
 * shift so that the values written by the function are aligned with the LSB.
 */
void test__Dio_WriteChannelGroup_PortD( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 17;
    ChannelGroup.offset = 0x03;
    ChannelGroup.port   = PORTS_D;
    Dio_WriteChannelGroup( &ChannelGroup, 0x03 );

    PinLevel = GET_BITS( DIOD->ODR, ChannelGroup.offset, ChannelGroup.mask );
    TEST_ASSERT_EQUAL_MESSAGE( 3u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_WriteChannelGroup function**
 *
 * This test will check that the function has set a subset of the adjacent bits of
 * a port (channel group) to a specified level. Also this function will perform
 * the masking of the channel group and in addition the function will perform the
 * shift so that the values written by the function are aligned with the LSB.
 */
void test__Dio_WriteChannelGroup_PortF( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 12;
    ChannelGroup.offset = 0x05;
    ChannelGroup.port   = PORTS_F;
    Dio_WriteChannelGroup( &ChannelGroup, 0x05 );

    PinLevel = GET_BITS( DIOF->ODR, ChannelGroup.offset, ChannelGroup.mask );
    TEST_ASSERT_EQUAL_MESSAGE( 5u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadChannelGroup function**
 *
 * This test will check that the function has performed the channel group masking and
 * that the offset has been performed so that the values read by the function are
 * aligned with the LSB.
 */
void test__Dio_ReadChannelGroup_PortD( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 17;
    ChannelGroup.offset = 0x03;
    ChannelGroup.port   = PORTS_D;

    PinLevel = Dio_ReadChannelGroup( &ChannelGroup );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_ReadChannelGroup function**
 *
 * This test will check that the function has performed the channel group masking and
 * that the offset has been performed so that the values read by the function are
 * aligned with the LSB.
 */
void test__Dio_ReadChannelGroup_PortF( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 12;
    ChannelGroup.offset = 0x05;
    ChannelGroup.port   = PORTS_F;

    PinLevel = Dio_ReadChannelGroup( &ChannelGroup );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_GetVersionInfo function**
 *
 * This function will check that the specified value is set for the channels on
 * the specified port.
 */
void test__Dio_MaskedWritePort_C( void )
{
    Dio_MaskedWritePort( PORTS_C, 0x05, 0x03 );
    TEST_ASSERT_EQUAL_MESSAGE( 1u, DIOC->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_GetVersionInfo function**
 *
 * This function will check that the specified value is set for the channels on
 * the specified port.
 */
void test__Dio_MaskedWritePort_A( void )
{
    Dio_MaskedWritePort( PORTS_A, 0x06, 0x04 );
    TEST_ASSERT_EQUAL_MESSAGE( 4u, DIOA->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_GetVersionInfo function**
 *
 * This function to check that all members on VersionInfo structure have a value. In
 * this case the function it was modified to return one in case that the members
 * have a value.
 */
void test__Port_GetVersionInfo( void )
{
    Std_VersionInfoType test;
    Dio_GetVersionInfo( &test );
    TEST_ASSERT_EQUAL_HEX32( 0, test.moduleID );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_major_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_minor_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_patch_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.vendorID );
}
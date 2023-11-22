/**
 * @file    test_Dio.c
 * @brief   **Unit testing for Dio Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Dio.h file
 */
#include "unity.h"
#include "Registers.h"
#include "Dio_Arch.h"
#include "Bfx.h"

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
#define SET_1_BIT( reg, bit )              ( ( reg ) |= ( 1u << ( bit ) ) )                 /*!< This macro will set the logical state of the \
                                                                                            input data for the requested bit position. */
#define GET_BITS( reg, BitStartPn, BitLn ) ( reg >> BitStartPn ) & ( ( 1u << BitLn ) - 1u ) /*!< This macro will return the logical state of the \
                                                                                            input data for the requested bits positions. */
/**
  @} */

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test of Dio_Arch_WriteChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the specified Level will be written to the specified port.
 */
void test__Dio_Arch_WriteChannel__pin_A07( void )
{
    Dio_Arch_WriteChannel( DIO_PORT_A, 7u, STD_HIGH );

    Dio_LevelType PinLevel = GET_1_BIT( DIOA->ODR, 7u );
    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_WriteChannel function for DIO_PIN_PB_02**
 *
 * This test will check that the specified Level will be written to the specified port.
 */
void test__Dio_Arch_WriteChannel__pin_B02( void )
{
    Dio_Arch_WriteChannel( DIO_PORT_B, 2u, STD_HIGH );

    Dio_LevelType PinLevel = GET_1_BIT( DIOB->ODR, 2u );
    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the function returns the value of the specified DIO channel.
 */
void test__Dio_Arch_ReadChannel__pin_A07( void )
{
    SET_1_BIT( DIOA->IDR, 7u );
    Dio_LevelType PinLevel = Dio_Arch_ReadChannel( DIO_PORT_A, 7u );

    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadChannel function for DIO_PIN_PB_02**
 *
 * This test will check that the function returns the value of the specified DIO channel.
 */
void test__Dio_Arch_ReadChannel__pin_B02( void )
{
    SET_1_BIT( DIOB->IDR, 2u );
    Dio_LevelType PinLevel = Dio_Arch_ReadChannel( DIO_PORT_B, 2u );

    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_FlipChannel function for DIO_PIN_PA_07**
 *
 * This test will check that the function returns the value of the specified DIO channel inverted.
 */
void test__Dio_Arch_FlipChannel__pin_A07( void )
{
    SET_1_BIT( DIOA->IDR, 7u );
    Dio_LevelType PinLevel = Dio_Arch_FlipChannel( DIO_PORT_A, 7u );

    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_FlipChannel function for DIO_PIN_PD_03**
 *
 * This test will check that the function returns the value of the specified DIO channel inverted.
 */
void test__Dio_Arch_FlipChannel__pin_D03( void )
{
    SET_1_BIT( DIOD->IDR, 3u );
    Dio_LevelType PinLevel = Dio_Arch_FlipChannel( DIO_PORT_D, 3u );

    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadPort function for PORT_B**
 *
 * This test will check that the function returns the value for all channels of the specified Port.
 */
void test__Dio_Arch_ReadPort_B( void )
{
    DIOB->IDR                   = 0x05;
    Dio_PortLevelType PortLevel = Dio_Arch_ReadPort( DIO_PORT_B );

    TEST_ASSERT_EQUAL_MESSAGE( 0x05u, PortLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadPort function for PORT_D**
 *
 * This test will check that the function returns the value for all channels of the specified Port.
 */
void test__Dio_Arch_ReadPort_D( void )
{
    DIOD->IDR                   = 0xAA;
    Dio_PortLevelType PortLevel = Dio_Arch_ReadPort( DIO_PORT_D );

    TEST_ASSERT_EQUAL_MESSAGE( 0xAAu, PortLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_WritePort function for PORT_B**
 *
 * This test will check that the function is setting the value specified by the Level parameter
 * for the specified port.
 */
void test__Dio_Arch_WritePort_B( void )
{
    Dio_Arch_WritePort( DIO_PORT_B, 0x05 );
    TEST_ASSERT_EQUAL_MESSAGE( 5u, DIOB->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_WritePort function for PORT_C**
 *
 * This test will check that the function is setting the value specified by the Level parameter
 * for the specified port.
 */
void test__Dio_Arch_WritePort_C( void )
{
    Dio_Arch_WritePort( DIO_PORT_C, 0x04 );
    TEST_ASSERT_EQUAL_MESSAGE( 4u, DIOC->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_WriteChannelGroup function**
 *
 * This test will check that the function has set a subset of the adjacent bits of
 * a port (channel group) to a specified level. Also this function will perform
 * the masking of the channel group and in addition the function will perform the
 * shift so that the values written by the function are aligned with the LSB.
 */
void test__Dio_Arch_WriteChannelGroup_PortD( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 17;
    ChannelGroup.offset = 0x03;
    ChannelGroup.port   = DIO_PORT_D;
    Dio_Arch_WriteChannelGroup( &ChannelGroup, 0x03 );

    PinLevel = GET_BITS( DIOD->ODR, ChannelGroup.offset, ChannelGroup.mask );
    TEST_ASSERT_EQUAL_MESSAGE( 3u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_WriteChannelGroup function**
 *
 * This test will check that the function has set a subset of the adjacent bits of
 * a port (channel group) to a specified level. Also this function will perform
 * the masking of the channel group and in addition the function will perform the
 * shift so that the values written by the function are aligned with the LSB.
 */
void test__Dio_Arch_WriteChannelGroup_PortF( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 12;
    ChannelGroup.offset = 0x05;
    ChannelGroup.port   = DIO_PORT_F;
    Dio_Arch_WriteChannelGroup( &ChannelGroup, 0x05 );

    PinLevel = GET_BITS( DIOF->ODR, ChannelGroup.offset, ChannelGroup.mask );
    TEST_ASSERT_EQUAL_MESSAGE( 5u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadChannelGroup function**
 *
 * This test will check that the function has performed the channel group masking and
 * that the offset has been performed so that the values read by the function are
 * aligned with the LSB.
 */
void test__Dio_Arch_ReadChannelGroup_PortD( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 17;
    ChannelGroup.offset = 0x03;
    ChannelGroup.port   = DIO_PORT_D;

    PinLevel = Dio_Arch_ReadChannelGroup( &ChannelGroup );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_ReadChannelGroup function**
 *
 * This test will check that the function has performed the channel group masking and
 * that the offset has been performed so that the values read by the function are
 * aligned with the LSB.
 */
void test__Dio_Arch_ReadChannelGroup_PortF( void )
{
    Dio_ChannelGroupType ChannelGroup;
    Dio_LevelType PinLevel;

    ChannelGroup.mask   = 12;
    ChannelGroup.offset = 0x05;
    ChannelGroup.port   = DIO_PORT_F;

    PinLevel = Dio_Arch_ReadChannelGroup( &ChannelGroup );
    TEST_ASSERT_EQUAL_MESSAGE( 0u, PinLevel, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_MaskedWritePort function**
 *
 * This function will check that writting a value to a port will not affect the
 * values of the masked bits.
 */
void test__Dio_Arch_MaskedWritePort_C( void )
{
    Dio_Arch_MaskedWritePort( DIO_PORT_C, 0x05, 0x03 );
    TEST_ASSERT_EQUAL_MESSAGE( 1u, DIOC->ODR, "Dio result was not the supposed value" );
}

/**
 * @brief   **Test of Dio_Arch_MaskedWritePort function**
 *
 * This function will check that writting a value to a port will not affect the
 * values of the masked bits.
 */
void test__Dio_Arch_MaskedWritePort_E( void )
{
    Dio_Arch_MaskedWritePort( DIO_PORT_E, 0x06, 0x04 );
    TEST_ASSERT_EQUAL_MESSAGE( 4u, DIOE->ODR, "Dio result was not the supposed value" );
}

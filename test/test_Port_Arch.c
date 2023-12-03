/**
 * @file    test_Port_Arch.c
 * @brief   **Unit testing for Port Low level Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Port_Arch.h file
 */
#include "unity.h"
#include "Port_Cfg.h"
#include "Port_Arch.h"
#include "Registers.h"

/*mock microcontroller registers with its initial values*/
/*                               MODER      OTYPER OSPEEDR     PUPDR       IDR   ODR   BSRR  LCKR    AFRL  AFRH    BRR*/
Port_RegisterType PORTA_BASE = { 0xEBFFFFFF, 0x00, 0x0C000000, 0x24000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTB_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTC_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTD_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTE_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTF_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief Test the initialization of a pin as output.
 *
 * This test case verifies that the initialization of a pin as output is done correctly.
 */
void test__Port_Arch_Init__pin_C5_as_ouput( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinC5= 
    {
        .Pin         = 5,
        .Port        = PORT_C,
        .Pull        = PORT_PULLUP,
        .OutputDrive = PORT_PUSH_PULL,
        .Speed       = PORT_HIGH_SPEED,
        .Mode        = PORT_MODE_OUTPUT 
    };
    /* clang-format on */

    Port_Arch_Init( &PortPinC5 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFF7FF, PORTC->MODER, "MODER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000400u, PORTC->PUPDR, "PUPDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->OTYPER, "OTYPER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000800u, PORTC->OSPEEDR, "OSPEEDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->AFRL, "AFRL register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->AFRH, "AFRH register not initialized correctly" );
}

/**
 * @brief Test the initialization of a pin as alter mode 7.
 *
 * This test case verifies that the initialization of a pin as alter mode is done correctly.
 */
void test__Port_Arch_Init__pin_A10_as_alternate_mode_8( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinA10= 
    {
        .Pin         = 10,
        .Port        = PORT_A,
        .Pull        = PORT_NOPULL,
        .OutputDrive = PORT_PUSH_PULL,
        .Speed       = PORT_HIGH_SPEED,
        .Mode        = PORT_MODE_ALT_AF7
    };
    /* clang-format on */

    Port_Arch_Init( &PortPinA10 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xEBEFFFFFu, PORTA->MODER, "MODER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x24000000u, PORTA->PUPDR, "PUPDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTA->OTYPER, "OTYPER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0C200000u, PORTA->OSPEEDR, "OSPEEDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTA->AFRL, "AFRL register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000700u, PORTA->AFRH, "AFRH register not initialized correctly" );
}

/**
 * @brief Test the change direction of a pin as input.
 *
 * This test case verifies that the change of direction of a pin as input is done correctly.
 */
void test__Port_Arch_SetPinDirection__pin_D7_as_input( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinD7= 
    {
        .Pin         = 7,
        .Port        = PORT_D,
    };
    /* clang-format on */

    Port_Arch_SetPinDirection( &PortPinD7, PORT_PIN_IN );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFF3FFF, PORTD->MODER, "MODER register not initialized correctly" );
}

/**
 * @brief Test the change altern mode of a pin B5.
 *
 * This test case verifies that the change of altern mode of a pin B5 is done correctly.
 */
void test__Port_Arch_SetPinMode__pin_B5_as_alternate_mode_5( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinB5= 
    {
        .Pin         = 5,
        .Port        = PORT_B,
        .Mode        = PORT_MODE_ALT_AF5
    };
    /* clang-format on */

    uint8 PinMode = PortPinB5.Mode >> 4u;
    uint8 AltMode = PortPinB5.Mode & 0x0Fu;

    Port_Arch_SetPinMode( &PortPinB5, PinMode, AltMode );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFBFFu, PORTB->MODER, "MODER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00500000u, PORTB->AFRL, "AFRL register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTB->AFRH, "AFRH register not initialized correctly" );
}

/**
 * @brief Test the change altern mode of a pin C10.
 *
 * This test case verifies that the change of altern mode of a pin C10 is done correctly.
 */
void test__Port_Arch_SetPinMode__pin_B10_as_alternate_mode_3( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinB10= 
    {
        .Pin         = 10,
        .Port        = PORT_B,
        .Mode        = PORT_MODE_ALT_AF3
    };
    /* clang-format on */

    uint8 PinMode = PortPinB10.Mode >> 4u;
    uint8 AltMode = PortPinB10.Mode & 0x0Fu;

    Port_Arch_SetPinMode( &PortPinB10, PinMode, AltMode );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFEFFBFFu, PORTB->MODER, "MODER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00500000u, PORTB->AFRL, "AFRH register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000300u, PORTB->AFRH, "AFRL register not initialized correctly" );
}

/**
 * @brief Test the refresh of a pin E5.
 *
 * This test case verifies that the refresh of a pin E5 is done correctly.
 */
void test__Port_Arch_RefreshPortDirection__refresh_pin_E5_as_output( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinE5= 
    {
        .Pin         = 5,
        .Port        = PORT_E,
        .Mode        = PORT_MODE_OUTPUT,
        .DirChange   = FALSE
    };
    /* clang-format on */

    Port_Arch_RefreshPortDirection( &PortPinE5 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFF7FF, PORTE->MODER, "MODER register not initialized correctly" );
}

/**
 * @brief Test the refresh of a pin F5.
 *
 * This test case verifies that the refresh of a pin F5 is done correctly.
 */
void test__Port_Arch_RefreshPortDirection__refresh_pin_F5_as_input( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinF5= 
    {
        .Pin         = 5,
        .Port        = PORT_F,
        .Mode        = PORT_MODE_INPUT,
        .DirChange   = FALSE
    };
    /* clang-format on */

    Port_Arch_RefreshPortDirection( &PortPinF5 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFF3FF, PORTF->MODER, "MODER register not initialized correctly" );
}

/**
 * @brief Test the bot refresh of a pin F6.
 *
 * This test case verifies that the refresh of a pin F6 is not done as expected.
 */
void test__Port_Arch_RefreshPortDirection__no_refresh_pin_F6_as_input( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinF6= 
    {
        .Pin         = 6,
        .Port        = PORT_F,
        .Mode        = PORT_MODE_INPUT,
        .DirChange   = TRUE
    };
    /* clang-format on */

    Port_Arch_RefreshPortDirection( &PortPinF6 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFF3FF, PORTF->MODER, "MODER register not initialized correctly" );
}

/**
 * @brief Test the no refresh of a pin F11.
 *
 * This test case verifies that the refresh of a pin F11 is done correctly.
 */
void test__Port_Arch_RefreshPortDirection__no_refresh_pin_F11_as_input( void )
{
    /* clang-format off */
    const Port_PinConfigType PortPinF11= 
    {
        .Pin         = 11,
        .Port        = PORT_F,
        .Mode        = PORT_MODE_ALT_AF0,
        .DirChange   = FALSE
    };
    /* clang-format on */

    Port_Arch_RefreshPortDirection( &PortPinF11 );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFF3FF, PORTF->MODER, "MODER register not initialized correctly" );
}

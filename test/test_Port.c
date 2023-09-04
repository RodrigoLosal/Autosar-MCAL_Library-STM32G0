#include "unity.h"
#include "Std_Types.h"
#include "Registers.h"

/*mock microcontroller registers with its initial values*/
/*                               MODER      OTYPER OSPEEDR     PUPDR       IDR   ODR   BSRR  LCKR    AFRL  AFRH    BRR*/
Port_RegisterType PORTA_BASE = { 0xEBFFFFFF, 0x00, 0x0C000000, 0x24000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTB_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTC_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTD_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTE_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
Port_RegisterType PORTF_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*redefine the port numbers from Port_Cfg.h*/


#include "Port.h"

/*set the ports and pins and its corresponding values to test*/
const Port_ConfigType PortsConfig[ PORT_PIN_NUMBER_OF_PORTS ] =
{
{ .Port          = PORTS_C,
  .Pins          = PORTS_PIN_0 | PORTS_PIN_1,
  .Pull          = PORTS_NOPULL,
  .OutputDrive   = PORTS_PUSH_PULL,
  .Speed         = PORTS_LOW_SPEED,
  .Mode          = PORTS_MODE_OUTPUT,
  .Altern        = 0,
  .Pin_direction = PORTS_CHANGEABLE },
{ .Port          = PORTS_A,
  .Pins          = PORTS_PIN_4 | PORTS_PIN_5,
  .Pull          = PORTS_PULLDOWN,
  .OutputDrive   = PORTS_OPEN_COLECTOR,
  .Speed         = PORTS_VERY_HIGH_SPEED,
  .Mode          = PORTS_MODE_OUTPUT,
  .Altern        = 0,
  .Pin_direction = PORTS_NON_CHANGEABLE },
{ .Port          = PORTS_B,
  .Pins          = PORTS_PIN_13 | PORTS_PIN_10 | PORTS_PIN_5,
  .Pull          = PORTS_PULLDOWN,
  .OutputDrive   = PORTS_OPEN_COLECTOR,
  .Speed         = PORTS_VERY_HIGH_SPEED,
  .Mode          = PORTS_MODE_ALT,
  .Altern        = PORT_PIN_MODE_AF2,
  .Pin_direction = PORTS_NON_CHANGEABLE } };

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * MODER for pins 0 and 1 from port C.
 */
void test__Port_Init__PortC_pins0and1_MODER( void )
{
    Port_Init( &PortsConfig[ 0 ] );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFFFFF5, PORTC->MODER );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * OSPEEDR for pins 0 and 1 from port C.
 */
void test__Port_Init__PortC_pins0and1_SPEED( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00000005, PORTC->OSPEEDR );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * PUPDR for pins 0 and 1 from port C.
 */
void test__Port_Init__PortC_pins0and1_PUPDR( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00000000, PORTC->PUPDR );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * PUOTYPERPDR for pins 0 and 1 from port C.
 */
void test__Port_Init__PortC_pins0and1_OTYPER( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00000000, PORTC->OTYPER );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * OSPEEDR for pins 4 and 5 from port A.
 */
void test__Port_Init__PortA_pins4and5_SPEED( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x0C000F00, PORTA->OSPEEDR );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * OSPEEDR for pins 5 and 4 from port A.
 */
void test__Port_Init__PortA_pins4and5_MODER( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0xEBFFF5FF, PORTA->MODER );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * PUPDR for pins 5 and 4 from port A.
 */
void test__Port_Init__PortA_pins4and5_PUPDR( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x24000A00, PORTA->PUPDR );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * OTYPER for pins 5 and 4 from port A.
 */
void test__Port_Init__PortA_pins4and5_OTYPER( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00000030, PORTA->OTYPER );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * AFRL for pins 13 and 10 from port B.
 */
void test__Port_Init__PortB_pins13and10_AFRL( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00200000, PORTB->AFRL );
}

/**
 * @brief   Test the Port_Init function
 *
 * This test will check if the Port_Init function is setting the correct values in the register
 * AFRH for pins 13 and 10 from port B.
 */
void test__Port_Init__PortB_pins13and10_AFRH( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00200200, PORTB->AFRH );
}

/**
 * @brief   Test the Port_SetPinDirection port C function
 *
 * This test will check if the Port_SetPinDirection function is setting the correct values in the register
 * MODER for pin 0 port C.
 */
void test__SetPinDirection__PortC_pin0_IN( void )
{
    Port_SetPinDirection( PORT_PIN_PC_00, PORT_PIN_IN );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFFFFF4, PORTC->MODER );
}

/**
 * @brief   Test the Port_SetPinDirection port C function
 *
 * This test will check if the Port_SetPinDirection function is setting the correct values in the register
 * MODER for pin 0 port C.
 */
void test__SetPinDirection__PortC_pin0_OUT( void )
{
    Port_SetPinDirection( PORT_PIN_PC_00, PORT_PIN_OUT );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFFFFF5, PORTC->MODER );
}

/**
 * @brief   Test the Port_SetPinMode port B function
 *
 * This test will check if the Port_SetPinMode function is setting the correct values in the register
 * MODER for pin 0 port C.
 */
void test__Port_SetPinMode__PortB_pin13_AF7( void )
{
    Port_SetPinMode( PORT_PIN_PB_13, PORT_PIN_MODE_AF7 );
    TEST_ASSERT_EQUAL_HEX32( 0x00700200, PORTB->AFRH );
}

/**
 * @brief   Test the Port_SetPinMode port B function
 *
 * This test will check if the Port_SetPinMode function is setting the correct values in the register
 * MODER for pin 0 port C.
 */
void test__Port_SetPinMode__PortB_pin05_AF7( void )
{
    Port_SetPinMode( PORT_PIN_PB_05, PORT_PIN_MODE_AF7 );
    TEST_ASSERT_EQUAL_HEX32( 0x00700000, PORTB->AFRL );
}

/**
 * @brief   Test the Port_GetVersionInfo
 *
 * This test will check if the Port_GetVersionInfo function is giving the correct values
 */
void test__Port_GetVersionInfo( void )
{
    Std_VersionInfoType test;
    Port_GetVersionInfo( &test );
    TEST_ASSERT_EQUAL_HEX32( 0, test.moduleID );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_major_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_minor_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_patch_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.vendorID );
}

/**
 * @brief   Test the Port_RefreshPortDirection
 *
 * This test will check if the Port_RefreshPortDirection function is refreshing the values on
 * a non changeable port
 */
void test__Port_RefreshPortDirection_non_changeable( void )
{
    PORTA->MODER = 0xEBFFFFFF;
    Port_RefreshPortDirection( );
    TEST_ASSERT_EQUAL_HEX32( PORTA->MODER, 0xEBFFF5FF );
}

/**
 * @brief   Test the Port_RefreshPortDirection
 *
 * This test will check if the Port_RefreshPortDirection function is not refreshing the values on
 * a changeable port
 */
void test__Port_RefreshPortDirection_changeable( void )
{
    PORTC->MODER = 0xFFFFFFFF;
    Port_RefreshPortDirection( );
    TEST_ASSERT_EQUAL_HEX32( PORTC->MODER, 0xFFFFFFFF );
}
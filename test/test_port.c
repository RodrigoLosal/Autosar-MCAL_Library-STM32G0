#include "unity.h"
#include "Std_Types.h"
#include "Registers.h"

/*mock microcontroller registers with its initial values*/
/*                               MODER      OTYPER OSPEEDR     PUPDR       IDR   ODR   BSRR  LCKR    AFRL  AFRH    BRR*/
Port_RegisterType PORTA_BASE = { 0xEBFFFFFF, 0x00, 0x0C000000, 0x24000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };
Port_RegisterType PORTB_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };
Port_RegisterType PORTC_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };
Port_RegisterType PORTD_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };
Port_RegisterType PORTE_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };
Port_RegisterType PORTF_BASE = { 0xFFFFFFFF, 0x00, 0x00000000, 0x00000000, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00 , 0x00 };

#include "Port.h"

/*redefine the port numbers from Port_Cfg.h*/
#undef PORT_PIN_NUMBER_OF_PORTS
#define PORT_PIN_NUMBER_OF_PORTS     2

/*set the ports and pins and its corresponding values to test*/
const Port_ConfigType PortsConfig[PORT_PIN_NUMBER_OF_PORTS] = 
{
    {
        .Port = PORTS_C,
        .Pins = PORTS_PIN_0 | PORTS_PIN_1,
        .Pull = PORTS_NOPULL,
        .OutputDrive = PORTS_PUSH_PULL,
        .Speed = PORTS_LOW_SPEED,
        .Mode = PORTS_MODE_OUTPUT,
        .Altern = 0
    },
    {
        .Port = PORTS_A,
        .Pins = PORTS_PIN_4 | PORTS_PIN_5,
        .Pull = PORTS_PULLDOWN,
        .OutputDrive = PORTS_OPEN_COLECTOR,
        .Speed = PORTS_VERY_HIGH_SPEED,
        .Mode = PORTS_MODE_OUTPUT,
        .Altern = 0
    }
};

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
    Port_Init( &PortsConfig[0] );
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
 * @brief   Test the Port_SetPinDirection port B function
 * 
 * This test will check if the Port_SetPinDirection function is setting the correct values in the register
 * MODER for pin 7 port B.
*/
void test__SetPinDirection__PortB_pin7_IN( void )
{
    Port_SetPinDirection( PORT_PIN_PB_07,PORT_PIN_IN );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFF3FFF, PORTB->MODER );
}

/**
 * @brief   Test the Port_SetPinDirection port F function
 * 
 * This test will check if the Port_SetPinDirection function is setting the correct values in the register
 * MODER for pin 15 port F.
*/
void test__SetPinDirection__PortF_pin15_OUT( void )
{
    Port_SetPinDirection( PORT_PIN_PA_15,PORT_PIN_OUT );
    TEST_ASSERT_EQUAL_HEX32( 0x7FFFFFFF, PORTF->MODER );
}

/**
 * @brief   Test the Port_SetPinDirection port F function
 * 
 * This test will check if the Port_SetPinDirection function is setting the correct values in the register
 * MODER for pin 15 port F.
*/
void test__SetPinDirection__PortF_pin15_IN( void )
{
    Port_SetPinDirection( PORT_PIN_PA_15,PORT_PIN_IN );
    TEST_ASSERT_EQUAL_HEX32( 0x3FFFFFFF, PORTF->MODER );
}
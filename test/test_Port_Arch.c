#include "unity.h"
#include "Port_Cfg.h"
#include "Port_Arch.h"

/*mock microcontroller registers with its initial values*/
/*                               Reserverd1            IDR   ODR   BSRR    Reserved2       BRR*/
Port_RegisterType DIOA_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Port_RegisterType DIOB_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Port_RegisterType DIOC_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Port_RegisterType DIOD_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Port_RegisterType DIOE_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Port_RegisterType DIOF_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}


void test__Port_Arch_Init__pin_5_as_ouput(void)
{
    const Port_PinConfigType = {
        .Pin         = 5,
        .Port        = PORT_C,
        .Pull        = PORT_NOPULL,
        .OutputDrive = PORT_PUSH_PULL,
        .Speed       = PORT_LOW_SPEED,
        .Mode        = PORT_MODE_OUTPUT
    };

    Port_Arch_Init( &Port_PinConfigType );

    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->MODER, "MODER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->PUPDR, "PUPDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->OTYPER, "OTYPER register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->OSPEEDR, "OSPEEDR register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->AFRL, "AFRL register not initialized correctly" );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00000000u, PORTC->AFRH, "AFRH register not initialized correctly" );
}

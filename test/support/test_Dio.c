#include "unity.h"
//#include "Registers.h"

/*mock microcontroller registers with its initial values*/
/*                               Reserverd1                IDR   ODR   BSRR    Reserved2           BRR*/
Dio_RegisterType DIOA_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOB_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOC_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOD_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOE_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };
Dio_RegisterType DIOF_BASE = { { 0x00, 0x00, 0x00, 0x00 }, 0x00, 0x00, 0x00, { 0x00, 0x00, 0x00 }, 0x00 };

#include "Dio.h"

/*support macros to read and write bits*/
#define GET_1_BIT( reg, bit )       ( ( ( reg ) >> ( bit ) ) & 0x01u )
#define SET_1_BIT( reg, bit )       ( ( reg ) |= ( 1u << ( bit ) ) )

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

void test__Dio_WriteChannel__pin_A07( void )
{
    Dio_LevelType PinLevel;
    /*simulate a pin input*/
    Dio_WriteChannel( DIO_LED_BLUE, STD_HIGH );
    /*read the pin*/
    PinLevel = GET_1_BIT( DIOA->ODR, 1u );
    TEST_ASSERT_EQUAL_MESSAGE( 1u, PinLevel, "Pin has not been set as supposed to be" );
}
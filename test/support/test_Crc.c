#include "unity.h"
#include "Crc.h"

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

void test_Crc_8bits( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF; // Initial CRC value
    boolean isFirstCall = true; // First call indicator
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xCB, crcResult, "Result was not set as supposed to be" );
}

void test_Crc_8bits2HF( void )
{
    uint8 data[]      = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength = sizeof( data ) / sizeof( data[ 0 ] );
    ;
    uint8 startValue    = 0xFF; // Initial CRC value
    boolean isFirstCall = true; // First call indicator
    uint8 crcResult     = ~Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x6C, crcResult, "Bit 2 was not set as supposed to be" );
}

void test_Crc_16bit( void )
{
    uint8 data[]        = { 0x0F, 0xAA, 0x00, 0x55 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = true;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x2023, crcResult, "Bit 2 was not set as supposed to be" );
}
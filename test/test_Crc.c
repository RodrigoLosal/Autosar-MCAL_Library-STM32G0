/**
 * @file    test_Crc.c
 * @brief   **This file contains the unit testing of CRC driver.**
 *
 * The file is designed to test the functions of CRC as entablished at the official documentation
 * of AUTOSAR CRCLibrary.
 */

#include "unity.h"
#include "Std_Types.h"
#include "Crc.h"

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
 * @brief   **Function to test the Crc_CalculateCRC8 with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC8 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_8bits_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF; // Initial CRC value
    boolean isFirstCall = TRUE; // First call indicator
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x59, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8 with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC8 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_8bits_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x74, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8 with 3 different bytes according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC8 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_8bits_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x37, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8 with nine bytes according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC8 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_8bits_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xCB, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8H2F with full zeros on data**
 *
 * Function to test the test_Crc_8bits2HF with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_8bits2HF_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x12, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8H2F with 3 bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC8H2F with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_8bits2HF_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xC2, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8H2F with nine bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC8H2F with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_8bits2HF_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x11, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC8H2F with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC8H2F with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_8bits2HF_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x6C, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC16 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_16bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x84C0, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with 3 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC16 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_16bit_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xD374, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with 9 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC16 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_16bit_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xF53F, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with 4 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC16 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x0F, 0xAA, 0x00, 0x55}
 */
void test_Crc_16bit_FIRST_4BYTES( void )
{
    uint8 data[]        = { 0x0F, 0xAA, 0x00, 0x55 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x2023, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC16 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_16bit_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x1D0F, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16ARC with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC16ARC with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_16bitARC_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x0000, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16ARC with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC16ARC with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_16bitARC_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x9401, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16ARC with 9 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC16ARC with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_16bitARC_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xAE98, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC16 with 3 bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC16ARC with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_16bitARC_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xC2E1, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32 with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC32 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_32bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x2144DF1C, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32 with FALSE on isFirstCall parameter**
 *
 * Function to test the Crc_CalculateCRC32 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00} and with FALSE on isFirstCall.
 */
void test_Crc_32bit_isFirstCall_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32 with full OXFF on data**
 *
 * Function to test the Crc_CalculateCRC32 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_32bit_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32 with 3 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC32 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_32bit_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x24AB9D77, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32 with 9 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC32 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_32bit_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xB0AE863D, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32P4 with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC32P4 with parameters of the official documentation to Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_32bitP4_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x6FB32240, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32P4 with 3 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC32P4 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_32bitP4_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x4F721A25, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32P4 with 9 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC32P4 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_32bitP4_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xA65A343D, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32P4 with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC32P4 with parameters of the official documentation to Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_32bitP4_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC32P4 with FALSE on isFirstCall paramter**
 *
 * Function to test the Crc_CalculateCRC32P4 with parameters of the official documentation to Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF} and with FALSE on isFirstCall.
 */
void test_Crc_32bitP4_isFirstCall_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC64 with full zeros on data**
 *
 * Function to test the Crc_CalculateCRC64 with parameters of the official documentation to Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00}
 */
void test_Crc_64bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xF4A586351E1B9F4B, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC64 with 3 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC64 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xF2, 0x01, 0x83}
 */
void test_Crc_64bit_FIRST_3BYTES( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0x319C27668164F1C6, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC64 with full 0xFF on data**
 *
 * Function to test the Crc_CalculateCRC64 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0xFF, 0xFF, 0xFF, 0xFF}
 */
void test_Crc_64bit_FULL_BYTES_0xFF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xFFFFFFFF00000000, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC64 with 9 different bytes on data according to AUTOSAR**
 *
 * Function to test the Crc_CalculateCRC64 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}
 */
void test_Crc_64bit_9BYTES_AA_TO_FF( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0x701ECEB219A8E5D5, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test the Crc_CalculateCRC64 with FALSE on isFirstCall parameter**
 *
 * Function to test the Crc_CalculateCRC64 with parameters of the official documentation of Autosar.
 * Parameters for test: data (data to calculate CRC), dataLength to know the size of data,
 * startValue this is the initial value of CRC acording to documentation, isFirstCall indicator to
 * assign a value to CRC frame.
 *
 * In this case the data was assigned of one of the results according to official documentation
 * data {0x00, 0x00, 0x00, 0x00} and with FALSE on isFirstCall.
 */
void test_Crc_64bit_isFirstCall_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xFFFFFFFFFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

/**
 * @brief   **Function to test if members of test_Crc_GetVersionInfo have a value**
 *
 * Function to check that all members on VersionInfo structure have a value.
 * In this case the function it was modified to return one in case that the members have a value.
 */
void test_Crc_GetVersionInfo( void )
{
    Std_VersionInfoType VersionInfo;
    uint8 VersionValue = Crc_GetVersionInfo( &VersionInfo );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x01, VersionValue, "Get version was not the supposed value" );
}
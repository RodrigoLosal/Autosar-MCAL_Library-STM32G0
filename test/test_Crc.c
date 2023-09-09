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

void test_Crc_8bits_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF; // Initial CRC value
    boolean isFirstCall = TRUE; // First call indicator
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x59, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x74, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits_3_BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x37, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xCB, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits2HF_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x12, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits2HF_3_BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xC2, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits2HF_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x11, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_8bits2HF_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint8 startValue    = 0xFF;
    boolean isFirstCall = TRUE;
    uint8 crcResult     = Crc_CalculateCRC8H2F( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x6C, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x84C0, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bit_3_BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xD374, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bit_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xF53F, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bit( void )
{
    uint8 data[]        = { 0x0F, 0xAA, 0x00, 0x55 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x2023, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bit_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint16 startValue   = 0xFFFF;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x1D0F, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bitARC_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x0000, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bitARC_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x9401, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bitARC_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xAE98, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_16bitARC_3BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data );
    uint16 startValue   = 0x0000;
    boolean isFirstCall = TRUE;
    uint16 crcResult    = Crc_CalculateCRC16ARC( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xC2E1, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x2144DF1C, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bit_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bit_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bit_3BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x24AB9D77, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bit_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xB0AE863D, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bitP4_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x6FB32240, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bitP4_3BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x4F721A25, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bitP4_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xA65A343D, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bitP4_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_32bitP4_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint32 dataLength   = sizeof( data ) / sizeof( data[ 0 ] );
    uint32 startValue   = 0xFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint32 crcResult    = Crc_CalculateCRC32P4( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_64bit_ZEROS( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xF4A586351E1B9F4B, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_64bit_3BYTES_1( void )
{
    uint8 data[]        = { 0xF2, 0x01, 0x83 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0x319C27668164F1C6, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_64bit_FF( void )
{
    uint8 data[]        = { 0xFF, 0xFF, 0xFF, 0xFF };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xFFFFFFFF00000000, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_64bit_HEX_NUM( void )
{
    uint8 data[]        = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = TRUE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0x701ECEB219A8E5D5, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_64bit_FALSE( void )
{
    uint8 data[]        = { 0x00, 0x00, 0x00, 0x00 };
    uint64 dataLength   = sizeof( data );
    uint64 startValue   = 0xFFFFFFFFFFFFFFFF;
    boolean isFirstCall = FALSE;
    uint64 crcResult    = Crc_CalculateCRC64( data, dataLength, startValue, isFirstCall );
    TEST_ASSERT_EQUAL_HEX64_MESSAGE( 0xFFFFFFFFFFFFFFFF, crcResult, "Crc result was not the supposed value" );
}

void test_Crc_GetVersionInfo( void )
{
    Std_VersionInfoType VersionInfo;
    uint8 VersionValue = Crc_GetVersionInfo( &VersionInfo );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x01, VersionValue, "Get version was not the supposed value" );
}
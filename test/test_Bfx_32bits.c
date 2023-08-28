/**
 * @file    test_Bfx_32bits.c
 * @brief   **This file contains 2 unit testing functions per each function in the library Bfx_32bits.**
 *
 * The file is designed to test the functions present in the "Bfx_32bits.h" library, which deals with
 * operations on 32-bit values. The unit testing file contains multiple test cases and assertions to
 * verify if the library functions work as expected.
 */

#include "unity.h"
#include "Bfx_32bits.h"

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
 * @brief   **Test set bit 2**
 *
 * The test validates if bit 2 is set over a varible with value 0x00, to pass the test data should have
 * a value of 0x04.
 */
void test__Bfx_SetBit_u32u8__bit2( void )
{
    uint32 Data = 0u;
    Bfx_SetBit_u32u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x04, "Bit 2 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 7**
 *
 * The test validates if bit 7 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x80.
 */
void test__Bfx_SetBit_u32u8__bit7( void )
{
    uint32 Data = 0u;
    Bfx_SetBit_u32u8( &Data, 7u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x80, "Bit 7 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 0**
 *
 * The test validates if the bit 0 of the value 0000 0101 is cleared, resulting in 0000 0100 = 0x04
 */
void test__Bfx_ClrBit_u32u8__bit0( void )
{
    uint32 Data = 0b00000101;
    Bfx_ClrBit_u32u8( &Data, 0u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x04, "Bit 0 was not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit 6**
 *
 * The test validates if the bit 6 of the value 1111 1010 is cleared, resulting in 1011 1010 = 0xBA
 */
void test__Bfx_ClrBit_u32u8__bit6( void )
{
    uint32 Data = 0b11111010;
    Bfx_ClrBit_u32u8( &Data, 6u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xBA, "Bit 6 was not cleared as supposed to be" );
}

/**
 * @brief   **Test get bit 2**
 *
 * The test validates if the bit 2 of the value 1111 1010 is read correctly, resulting in FALSE
 */
void test__Bfx_GetBit_u32u8_u8__bit2( void )
{
    uint32 Data    = 0b11111010;
    boolean Result = Bfx_GetBit_u32u8_u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bit 2 was not read as supposed to be" );
}

/**
 * @brief   **Test get bit 1**
 *
 * The test validates if the bit 1 of the value 1010 1111 is read correctly, resulting in TRUE
 */
void test__Bfx_GetBit_u32u8_u8__bit1( void )
{
    uint32 Data    = 0b10101111;
    boolean Result = Bfx_GetBit_u32u8_u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bit 2 was not read as supposed to be" );
}

/**
 * @brief   **Test set bits 3-6 to 0**
 *
 * The test validates if the bits 3 to 6 of the value 1010 1111 are set to 0 correctly, resulting in
 * 1000 0111 = 0x87
 */
void test__Bfx_SetBits_u32u8u8u8__bits3to6( void )
{
    uint32 Data = 0b10101111;
    Bfx_SetBits_u32u8u8u8( &Data, 3u, 4u, 0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x87, "Bits 3-6 were not set as supposed to be" );
}

/**
 * @brief   **Test set bits 2-5 to 1**
 *
 * The test validates if the bits 2 to 5 of the value 1000 0001 are set to 1 correctly, resulting in
 * 1011 1101 = 0xBD
 */
void test__Bfx_SetBits_u32u8u8u8__bits2to5( void )
{
    uint32 Data = 0b10000001;
    Bfx_SetBits_u32u8u8u8( &Data, 2u, 4u, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xBD, "Bits 2-5 were not set as supposed to be" );
}

/**
 * @brief   **Test get bits 0-3**
 *
 * The test validates if the bits 0 to 3 of the value 1000 1001 are read correctly, resulting in
 * 0000 1001 = 0x09
 */
void test__GetBits_u32u8u8_u32__bits0to3( void )
{
    uint32 Data   = 0b10001001;
    uint32 Result = Bfx_GetBits_u32u8u8_u32( Data, 0, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x09, "Bits 0-3 were not read as supposed to be" );
}

/**
 * @brief   **Test get bits 3-7**
 *
 * The test validates if the bits 3 to 7 of the value 1011 1001 are read correctly, resulting in
 * 0001 0111 = 0x17
 */
void test__GetBits_u32u8u8_u32__bits3to7( void )
{
    uint32 Data   = 0b10111001;
    uint32 Result = Bfx_GetBits_u32u8u8_u32( Data, 3, 5u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x17, "Bits 0-3 were not read as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 2-6**
 *
 * The test validates if the bits 2 to 6 of the value 1000 0001 are getting set correctly with
 * the mask 0111 1100 resulting in 1111 1101 = 0xFD
 */
void test__SetBitMask_u32u32__bits2to6( void )
{
    uint32 Data = 0b10000001;
    Bfx_SetBitMask_u32u32( &Data, 0b01111100 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFD, "Bits 2-6 were not set as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 2-6**
 *
 * The test validates if the bits 0 to 7 of the value 1000 0001 are getting set correctly with
 * the mask 1000 0001 resulting in 1000 0001 = 0x81
 */
void test__SetBitMask_u32u32__bits0to7( void )
{
    uint32 Data = 0b10000001;
    Bfx_SetBitMask_u32u32( &Data, 0b10000001 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x81, "Bits 0-7 were not set as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 0-7**
 *
 * The test validates if the bits 0 to 7 of the value 1000 0001 are getting cleared correctly with
 * the mask 1000 0001 resulting in 0000 0000 = 0x00
 */
void test__ClrBitMask_u32u32__bits0to7( void )
{
    uint32 Data = 0b10000001;
    Bfx_ClrBitMask_u32u32( &Data, 0b10000001 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00, "Bits 0-7 were not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 3-5**
 *
 * The test validates if the bits 3 to 5 of the value 1011 1001 are getting cleared correctly with
 * the mask 0010 1000 resulting in 1001 0001 = 0x91
 */
void test__ClrBitMask_u32u32__bits3to5( void )
{
    uint32 Data = 0b10111001;
    Bfx_ClrBitMask_u32u32( &Data, 0b00101000 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x91, "Bits 3-5 were not cleared as supposed to be" );
}

/**
 * @brief   **Test of test bit mask bits 4-7**
 *
 * The test validates if the bits 4 to 7 of the value 1001 0011 are already set compared to the mask
 * the mask 1001 0000 resulting in TRUE
 */
void test__TstBitMask_u32u32_u8__bits4to7( void )
{
    uint32 Data    = 0b10010011;
    boolean Result = Bfx_TstBitMask_u32u32_u8( Data, 0b10010000 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bits 4-7 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit mask bits 0-3**
 *
 * The test validates if the bits 0 to 3 of the value 1001 0011 are already set compared to the mask
 * the mask 1001 0001 resulting in FALSE
 */
void test__TstBitMask_u32u32_u8__bits0to3( void )
{
    uint32 Data    = 0b10010001;
    boolean Result = Bfx_TstBitMask_u32u32_u8( Data, 0b10010011 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bits 0-3 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit length mask bits 0-7**
 *
 * The test validates if at least one bit of the value 1100 1100 is set as per the mask 0011 0011
 * resulting in a FALSE
 */
void test__TstBitLnMask_u32u32_u8__bits0to7( void )
{
    uint32 Data    = 0b11001100;
    boolean Result = Bfx_TstBitLnMask_u32u32_u8( Data, 0b00110011 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "At least 1 bit of bits 0-7 was not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit length mask bits 1-28**
 *
 * The test validates if at least one bit of the value 0xF000008C is set as per the mask 0x10000042
 * resulting in a TRUE
 */
void test__TstBitLnMask_u32u32_u8__bits1to28( void )
{
    uint32 Data    = 0xF000008C;
    boolean Result = Bfx_TstBitLnMask_u32u32_u8( Data, 0x10000042 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "At least 1 bit of bits 1-28 was not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test parity odd of a number**
 *
 * Test the number of bits set to 1. If this number is even, it shall return TRUE, otherwise
 * it returns FALSE.
 */
void test__Bfx_TstParityEven_u32_u8__Odd( void )
{
    uint32 Data    = 0xFFFFFFFE;
    boolean Result = Bfx_TstParityEven_u32_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "The parity isnt odd" );
}

/**
 * @brief   **Test parity even of a number**
 *
 * Test if the number of bits is set to 1. If this number is even, it shall return TRUE, otherwise
 * it returns FALSE.
 */
void test__Bfx_TstParityEven_u32_u8__Even( void )
{
    uint32 Data    = 0xFFFFFFFF;
    boolean Result = Bfx_TstParityEven_u32_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "The parity isnt even" );
}

/**
 * @brief   **Test 1 of toggle bits**
 *
 * The test validates the toggling of all the bits in the value 0xCCCCCCCC, resulting in
 * 0x33333333
 */
void test__Bfx_ToggleBits_u32__test1( void )
{
    uint32 Data = 0xCCCCCCCC;
    Bfx_ToggleBits_u32( &Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x33333333, "The 32 bits did not toggle as supposed to" );
}

/**
 * @brief   **Test 2 of toggle bits**
 *
 * The test validates the toggling of all the bits in the value 0x5A5A5A5A, resulting in
 * 0xA5A5A5A5
 */
void test__Bfx_ToggleBits_u32__test2( void )
{
    uint32 Data = 0x5A5A5A5A;
    Bfx_ToggleBits_u32( &Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xA5A5A5A5, "The 32 bits did not toggle as supposed to" );
}

/**
 * @brief   **Test 1 of toggle bits mask**
 *
 * The test validates the toggling of all the bits in the value 0x99999999 given the mask
 * 0x66666666 resulting in 0xFFFFFFFF
 */
void test__Bfx_ToggleBitMask_u32u32__test1( void )
{
    uint32 Data = 0x99999999;
    Bfx_ToggleBitMask_u32u32( &Data, 0x66666666 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFFFFFFFF, "The mask did not toggle the bits of the value as supposed to" );
}

/**
 * @brief   **Test 2 of toggle bits mask**
 *
 * The test validates the toggling of all the bits in the value 0x88888888 given the mask
 * 0x58585858 resulting in 0xD0D0D0D0
 */
void test__Bfx_ToggleBitMask_u32u32__test2( void )
{
    uint32 Data = 0x88888888;
    Bfx_ToggleBitMask_u32u32( &Data, 0x58585858 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xD0D0D0D0, "The mask did not toggle the bits of the value as supposed to" );
}

/**
 * @brief   **Test 1 of shift bit right**
 *
 * The test validates the shifting right of all the bits in the value 0xF8F8F8F8 by the amount of 4
 * is 0x0F8F8F8F
 */
void test__Bfx_ShiftBitRt_u32u8__test1( void )
{
    uint32 Data = 0xF8F8F8F8;
    Bfx_ShiftBitRt_u32u8( &Data, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x0F8F8F8F, "The function did not shift right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of shift bit right**
 *
 * The test validates the shifting right of all the bits in the value 0x8F8F8F8F by the amount of 2
 * is 0x23E3E3E3
 */
void test__Bfx_ShiftBitRt_u32u8__test2( void )
{
    uint32 Data = 0x8F8F8F8F;
    Bfx_ShiftBitRt_u32u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x23E3E3E3, "The function did not shift right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of shift bit left**
 *
 * The test validates the shifting left of all the bits in the value 1111 1000 by the amount of 4 is
 * 1000 0000 = 0x80
 */
void test__ShiftBitLt_u32u8__test1( void )
{
    uint32 Data = 0xF8F8F8F8;
    Bfx_ShiftBitLt_u32u8( &Data, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x8F8F8F80, "The function did not shift left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of shift bit left**
 *
 * The test validates the shifting left of all the bits in the value 0x8F8F8F8F by the amount of 2
 * is 0x3E3E3E3C
 */
void test__ShiftBitLt_u32u8__test2( void )
{
    uint32 Data = 0x8F8F8F8F;
    Bfx_ShiftBitLt_u32u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x3E3E3E3C, "The function did not shift left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of rotate bit right**
 *
 * The test validates the rotating right of the bits in the value 0x00000017 by the amount of 1 is
 * 0x8000000B
 */
void test__RotBitRt_u32u8__test1( void )
{
    uint32 Data = 0x00000017;
    Bfx_RotBitRt_u32u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x8000000B, "The function did not rotate right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of rotate bit right**
 *
 * The test validates the rotating right of the bits in the value 0x00000017 by the amount of 3 is
 * 0xE0000002
 */
void test__RotBitRt_u32u8__test2( void )
{
    uint32 Data = 0x00000017;
    Bfx_RotBitRt_u32u8( &Data, 3u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xE0000002, "The function did not rotate right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of rotate bit left**
 *
 * The test validates the rotating left of the bits in the value 0xC00000B7 by the amount of 1 is
 * 0x8000016F
 */
void test__RotBitLt_u32u8__test1( void )
{
    uint32 Data = 0xC00000B7;
    Bfx_RotBitLt_u32u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x8000016F, "The function did not rotate left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of rotate bit left**
 *
 * The test validates the rotating left of the bits in the value 0XF00000B7 by the amount of 3 is
 * 0x800005BF
 */
void test__RotBitLt_u32u8__test2( void )
{
    uint32 Data = 0XF00000B7;
    Bfx_RotBitLt_u32u8( &Data, 3u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x800005BF, "The function did not rotate left the bits of the value as supposed to be" );
}


/**
 * @brief   **Test copying bits from one number to another**
 *
 * Test if function copies a bit 1 from source data from bit position to destination data at bit
 * position
 */
void test__Bfx_CopyBit_u32u8u32u8__0to1( void )
{
    uint32 Data = 0x88888888;
    Bfx_CopyBit_u32u8u32u8( &Data, 28, 0xAAAAAAAA, 31 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x98888888, "The bit isnt copying correctly" );
}

/**
 * @brief   **Test copying bits from one number to another**
 *
 * Test if function copies a bit 0 from source data from bit position to destination data at bit
 * position
 */
void test__Bfx_CopyBit_u32u8u32u8__1to0( void )
{
    uint32 Data = 0x88888888;
    Bfx_CopyBit_u32u8u32u8( &Data, 15, 0xAAAAAAAA, 26 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x88880888, "The bit isnt copying correctly" );
}

/**
 * @brief   **Test putting bits as in Pattern from the bit position**
 *
 * Test if function put bits as mentioned in Pattern to the input Data from the
 * specified bit position
 */
void test__Bfx_PutBits_u32u8u8u32__specs( void )
{
    uint32 Data = 0xF0F0F0F0;
    Bfx_PutBits_u32u8u8u32( &Data, 17, 3, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF0F6F0F0, "The bit or pattern are incorrect" );
}

/**
 * @brief   **Test putting bits as in Pattern from the bit position (changing postion and length)**
 *
 * Test if function put bits as mentioned in Pattern to the input Data from the
 * specified bit swaping the previous starting position and length
 */
void test__Bfx_PutBits_u32u8u8u32__specsinv( void )
{
    uint32 Data = 0xF0F0F0F0;
    Bfx_PutBits_u32u8u8u32( &Data, 19, 1, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF0F8F0F0, "The bit or pattern are incorrect" );
}

/**
 * @brief   **Test changing bits with a pattert and mask**
 *
 * The test validates if function changes bits with a pattert and mask
 */
void test__Bfx_PutBitsMask_u32u32u32__specs( void )
{
    uint32 Data = 0xE0E0E0E0;
    Bfx_PutBitsMask_u32u32u32( &Data, 0xCDCDCDCD, 0x0F0F0F0F );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xEDEDEDED, "The mask or pattern are incorrect" );
}

/**
 * @brief   **Test changing bits with a pattert and mask inverted**
 *
 * The test validates if function changes bits with a pattert and mask inverted
 */
void test__Bfx_PutBitsMask_u32u32u32__specsinv( void )
{
    uint32 Data = 0xE0E0E0E0;
    Bfx_PutBitsMask_u32u32u32( &Data, 0x0F0F0F0F, 0xCDCDCDCD );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x2D2D2D2D, "The mask or pattern are incorrect" );
}

/**
 * @brief   **Test putting a bit to zero on the 17 position**
 *
 * The test validates if function puts a bit to zero on the 17 position
 */
void test__Bfx_PutBit_u32u8u8__0on17( void )
{
    uint32 Data = 0xFFFFFFFF;
    Bfx_PutBit_u32u8u8( &Data, 17, 0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFFFDFFFF, "The bit wasnt put on the 17 position" );
}

/**
 * @brief   **Test putting a bit to one on the 16 position**
 *
 * The test validates if function puts a bit to one on the 16 position
 */
void test__Bfx_PutBit_u32u8u8__1on16( void )
{
    uint32 Data = 0x00000000;
    Bfx_PutBit_u32u8u8( &Data, 16, 1 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00008000, "The bit wasnt put on the 16 position" );
}

/**
 * @brief   **Test Count Leading ones with 32**
 *
 * The test validates if function counts 32 ones from left to right
 */
void test__Bfx_CountLeadingOnes_u32__32ones( void )
{
    uint32 Data  = 0xFFFFFFFF;
    uint8 Result = Bfx_CountLeadingOnes_u32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 32, "There are no 32 ones from left to right" );
}

/**
 * @brief   **Test Count Leading ones with 10**
 *
 * The test validates if function counts 10 ones from left to right
 */
void test__Bfx_CountLeadingOnes_u32__10ones( void )
{
    uint32 Data  = 0xFFC00000;
    uint8 Result = Bfx_CountLeadingOnes_u32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 10, "There are no 10 ones from left to right" );
}

/**
 * @brief   **Test Count Leading Zeros with 30**
 *
 * The test validates if function counts 30 zeros from left to right
 */
void test__Bfx_CountLeadingZeros_u32__30zeros( void )
{
    uint32 Data  = 0x00000003;
    uint8 Result = Bfx_CountLeadingZeros_u32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 30, "There are no 30 zeros from left to right" );
}

/**
 * @brief   **Test Count Leading Zeros with 5**
 *
 * The test validates if function counts 5 zeros from left to right
 */
void test__Bfx_CountLeadingZeros_u32__5zeros( void )
{
    uint32 Data  = 0x04000000;
    uint8 Result = Bfx_CountLeadingZeros_u32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 5, "There are no 5 zeros from left to right" );
}

/**
 * @brief   **Test Count Leading Signs with 4**
 *
 * The test validates if function counts 4 ones after the sign bit (1)
 */
void test__CountLeadingSigns_s32__4ones( void )
{
    sint32 Data  = 0xF8000000u;
    uint8 Result = Bfx_CountLeadingSigns_s32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x04, "There are no 4 ones after de MSB" );
}

/**
 * @brief   **Test Count Leading Signs with 3**
 *
 * The test validates if function counts 3 zeros after the sign bit (0)
 */
void test__CountLeadingSigns_s32__3zeros( void )
{
    sint32 Data  = 0x08000000;
    uint8 Result = Bfx_CountLeadingSigns_s32( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x03, "There are no 3 zeros after de MSB" );
}
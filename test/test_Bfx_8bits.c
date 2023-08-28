/**
 * @file    test_Bfx_8bits.c
 * @brief   **This file contains 2 unit testing functions per each function in the library Bfx_8bits.**
 *
 * The file is designed to test the functions present in the "Bfx_8bits.c" library, which deals with
 * operations on 8-bit values. The unit testing file contains multiple test cases and assertions to
 * verify if the library functions work as expected.
 */

#include "unity.h"
#include "Bfx_8bits.h"

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
void test__Bfx_SetBit_u8u8__bit2( void )
{
    uint8 Data = 0u;
    Bfx_SetBit_u8u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x04, "Bit 2 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 7**
 *
 * The test validates if bit 7 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x80.
 */
void test__Bfx_SetBit_u8u8__bit7( void )
{
    uint8 Data = 0u;
    Bfx_SetBit_u8u8( &Data, 7u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x80, "Bit 7 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 0**
 *
 * The test validates if the bit 0 of the value 0x05 = 0000 0101 is cleared,
 * resulting in 0000 0100 = 0x04
 */
void test__Bfx_ClrBit_u8u8__bit0( void )
{
    uint8 Data = 0x05;
    Bfx_ClrBit_u8u8( &Data, 0u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x04, "Bit 0 was not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit 6**
 *
 * The test validates if the bit 6 of the value 0xFA = 1111 1010 is cleared,
 * resulting in 1011 1010 = 0xBA
 */
void test__Bfx_ClrBit_u8u8__bit6( void )
{
    uint8 Data = 0xFA;
    Bfx_ClrBit_u8u8( &Data, 6u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xBA, "Bit 6 was not cleared as supposed to be" );
}

/**
 * @brief   **Test get bit 2**
 *
 * The test validates if the bit 2 of the value 0xFA = 1111 1010 is read correctly,
 * resulting in FALSE
 */
void test__Bfx_GetBit_u8u8_u8__bit2( void )
{
    uint8 Data     = 0xFA;
    boolean Result = Bfx_GetBit_u8u8_u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bit 2 was not read as supposed to be" );
}

/**
 * @brief   **Test get bit 1**
 *
 * The test validates if the bit 1 of the value 0xAF = 1010 1111 is read correctly,
 * resulting in TRUE
 */
void test__Bfx_GetBit_u8u8_u8__bit1( void )
{
    uint8 Data     = 0xAF;
    boolean Result = Bfx_GetBit_u8u8_u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bit 2 was not read as supposed to be" );
}

/**
 * @brief   **Test set bits 3-6 to 0**
 *
 * The test validates if the bits 3 to 6 of the value 0xAF = 1010 1111 are set to 0 correctly,
 * resulting in 1000 0111 = 0x87
 */
void test__Bfx_SetBits_u8u8u8u8__bits3to6( void )
{
    uint8 Data = 0xAF;
    Bfx_SetBits_u8u8u8u8( &Data, 3u, 4u, 0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x87, "Bits 3-6 were not set as supposed to be" );
}

/**
 * @brief   **Test set bits 2-5 to 1**
 *
 * The test validates if the bits 2 to 5 of the value 0x81 = 1000 0001 are set to 1 correctly,
 * resulting in 1011 1101 = 0xBD
 */
void test__Bfx_SetBits_u8u8u8u8__bits2to5( void )
{
    uint8 Data = 0x81;
    Bfx_SetBits_u8u8u8u8( &Data, 2u, 4u, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xBD, "Bits 2-5 were not set as supposed to be" );
}

/**
 * @brief   **Test get bits 0-3**
 *
 * The test validates if the bits 0 to 3 of the value 0x89 = 1000 1001 are read correctly,
 * resulting in 0000 1001 = 0x09
 */
void test__GetBits_u8u8u8_u8__bits0to3( void )
{
    uint8 Data   = 0x89;
    uint8 Result = Bfx_GetBits_u8u8u8_u8( Data, 0, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x09, "Bits 0-3 were not read as supposed to be" );
}

/**
 * @brief   **Test get bits 3-7**
 *
 * The test validates if the bits 3 to 7 of the value B9 = 1011 1001 are read correctly,
 * resulting in 0001 0111 = 0x17
 */
void test__GetBits_u8u8u8_u8__bits3to7( void )
{
    uint8 Data   = 0xB9;
    uint8 Result = Bfx_GetBits_u8u8u8_u8( Data, 3, 5u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x17, "Bits 0-3 were not read as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 2-6**
 *
 * The test validates if the bits 2 to 6 of the value 0x81 = 1000 0001 are getting set correctly with
 * the mask 0x7C = 0111 1100 resulting in 1111 1101 = 0xFD
 */
void test__SetBitMask_u8u8__bits2to6( void )
{
    uint8 Data = 0x81;
    Bfx_SetBitMask_u8u8( &Data, 0x7C );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFD, "Bits 2-6 were not set as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 2-6**
 *
 * The test validates if the bits 0 to 7 of the value 0x81 = 1000 0001 are getting set correctly with
 * the mask 0x81 = 1000 0001 resulting in 1000 0001 = 0x81
 */
void test__SetBitMask_u8u8__bits0to7( void )
{
    uint8 Data = 0x81;
    Bfx_SetBitMask_u8u8( &Data, 0x81 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x81, "Bits 0-7 were not set as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 0-7**
 *
 * The test validates if the bits 0 to 7 of the value 0x81 = 1000 0001 are getting cleared correctly with
 * the mask 0x81 = 1000 0001 resulting in 0000 0000 = 0x00
 */
void test__ClrBitMask_u8u8__bits0to7( void )
{
    uint8 Data = 0x81;
    Bfx_ClrBitMask_u8u8( &Data, 0x81 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00, "Bits 0-7 were not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 3-5**
 *
 * The test validates if the bits 3 to 5 of the value 0xB9 = 1011 1001 are getting cleared correctly with
 * the mask 0x28 = 0010 1000 resulting in 1001 0001 = 0x91
 */
void test__ClrBitMask_u8u8__bits3to5( void )
{
    uint8 Data = 0xB9;
    Bfx_ClrBitMask_u8u8( &Data, 0x28 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x91, "Bits 3-5 were not cleared as supposed to be" );
}

/**
 * @brief   **Test of test bit mask bits 4-7**
 *
 * The test validates if the bits 4 to 7 of the value 0x93 = 1001 0011 are already set compared to the mask
 * the mask 0x90 = 1001 0000 resulting in TRUE
 */
void test__TstBitMask_u8u8_u8__bits4to7( void )
{
    uint8 Data     = 0x93;
    boolean Result = Bfx_TstBitMask_u8u8_u8( Data, 0x90 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bits 4-7 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit mask bits 0-3**
 *
 * The test validates if the bits 0 to 3 of the value 0x91 = 1001 0011 are already set compared to the mask
 * the mask 0x93 = 1001 0001 resulting in FALSE
 */
void test__TstBitMask_u8u8_u8__bits0to3( void )
{
    uint8 Data     = 0x91;
    boolean Result = Bfx_TstBitMask_u8u8_u8( Data, 0x93 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bits 0-3 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit length mask bits 0-7**
 *
 * The test validates if at least one bit of the value 0xCC = 1100 1100 is set as per the mask
 * 0x33 = 0011 0011 resulting in a FALSE
 */
void test__TstBitLnMask_u8u8_u8__bits0to7( void )
{
    uint8 Data     = 0xCC;
    boolean Result = Bfx_TstBitLnMask_u8u8_u8( Data, 0x33 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "At least 1 bit of bits 0-7 was not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit length mask bits 1-6**
 *
 * The test validates if at least one bit of the value 0x8C = 1000 1100 is set as per the mask
 * 0x46 = 0100 0110 resulting in a TRUE
 */
void test__TstBitLnMask_u8u8_u8__bits1to6( void )
{
    uint8 Data     = 0x8C;
    boolean Result = Bfx_TstBitLnMask_u8u8_u8( Data, 0x46 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "At least 1 bit of bits 1-6 was not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test parity even 3 bits as set**
 *
 * The test validates the number of bits set to 1 in the value 0xC8 = 1100 1000 is even resulting
 * in a FALSE
 */
void test__TstParityEven_u8_u8__3bits( void )
{
    uint8 Data     = 0xC8;
    boolean Result = Bfx_TstParityEven_u8_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "The parity test did not go supposed to be" );
}

/**
 * @brief   **Test of test parity even 6 bits as set**
 *
 * The test validates the number of bits set to 1 in the value 0xDD = 1101 1101 is even resulting
 * in a TRUE
 */
void test__TstParityEven_u8_u8__6bits( void )
{
    uint8 Data     = 0xDD;
    boolean Result = Bfx_TstParityEven_u8_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "The parity test did not go supposed to be" );
}

/**
 * @brief   **Test 1 of toggle bits**
 *
 * The test validates the toggling of all the bits in the value 0x99 = 1001 1001, resulting in
 * 0110 0110 = 0x66
 */
void test__Bfx_ToggleBits_u8__test1( void )
{
    uint8 Data = 0x99;
    Bfx_ToggleBits_u8( &Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x66, "The 8 bits did not toggle as supposed to be" );
}

/**
 * @brief   **Test 2 of toggle bits**
 *
 * The test validates the toggling of all the bits in the value 0x5A = 0101 1010, resulting in
 * 1010 0101 = 0xA5
 */
void test__Bfx_ToggleBits_u8__test2( void )
{
    uint8 Data = 0x5A;
    Bfx_ToggleBits_u8( &Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xA5, "The 8 bits did not toggle as supposed to be" );
}

/**
 * @brief   **Test 1 of toggle bits mask**
 *
 * The test validates the toggling of all the bits in the value 0x99 = 1001 1001 given the
 * mask 0x66 = 0110 0110 resulting in 1111 1111 = 0xFF
 */
void test__Bfx_ToggleBitMask_u8u8__test1( void )
{
    uint8 Data = 0x99;
    Bfx_ToggleBitMask_u8u8( &Data, 0x66 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFF, "The mask did not toggle the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of toggle bits mask**
 *
 * The test validates the toggling of all the bits in the value 0x88 = 1000 1000 given the
 * mask 0x58 = 0101 1000 resulting in 1101 0000 = 0xD0
 */
void test__Bfx_ToggleBitMask_u8u8__test2( void )
{
    uint8 Data = 0x88;
    Bfx_ToggleBitMask_u8u8( &Data, 0x58 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xD0, "The mask did not toggle the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of shift bit right**
 *
 * The test validates the shifting right of all the bits in the value 0xF8 1111 1000 by the amount of
 * 4 is 0000 1111 = 0x0F
 */
void test__Bfx_ShiftBitRt_u8u8__test1( void )
{
    uint8 Data = 0xF8;
    Bfx_ShiftBitRt_u8u8( &Data, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x0F, "The function did not shift right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of shift bit right**
 *
 * The test validates the shifting right of all the bits in the value 0x8F = 1000 1111 by the
 * amount of 2 is 0010 0011 = 0x23
 */
void test__Bfx_ShiftBitRt_u8u8__test2( void )
{
    uint8 Data = 0x8F;
    Bfx_ShiftBitRt_u8u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x23, "The function did not shift right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of shift bit left**
 *
 * The test validates the shifting left of all the bits in the value 0xF8 = 1111 1000 by the
 * amount of 4 is 1000 0000 = 0x80
 */
void test__ShiftBitLt_u8u8__test1( void )
{
    uint8 Data = 0xF8;
    Bfx_ShiftBitLt_u8u8( &Data, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x80, "The function did not shift left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of shift bit left**
 *
 * The test validates the shifting left of all the bits in the value 0x8F = 1000 1111 by the amount of 2
 * is 0011 1100 = 0x3C
 */
void test__ShiftBitLt_u8u8__test2( void )
{
    uint8 Data = 0x8F;
    Bfx_ShiftBitLt_u8u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x3C, "The function did not shift left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of rotate bit right**
 *
 * The test validates the rotating right of the bits in the value 0x17 = 0001 0111 by the amount of 1 is
 * 1000 1011  = 0x8B
 */
void test__RotBitRt_u8u8__test1( void )
{
    uint8 Data = 0x17;
    Bfx_RotBitRt_u8u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x8B, "The function did not rotate right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of rotate bit right**
 *
 * The test validates the rotating right of the bits in the value 0x17 = 0001 0111 by the amount of 3 is
 * 1110 0010  = 0xE2
 */
void test__RotBitRt_u8u8__test2( void )
{
    uint8 Data = 0x17;
    Bfx_RotBitRt_u8u8( &Data, 3u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xE2, "The function did not rotate right the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 1 of rotate bit left**
 *
 * The test validates the rotating left of the bits in the value 0xB7 = 1011 0111 by the amount of 1 is
 * 0110 1111  = 0x6F
 */
void test__RotBitLt_u8u8__test1( void )
{
    uint8 Data = 0xB7;
    Bfx_RotBitLt_u8u8( &Data, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x6F, "The function did not rotate left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test 2 of rotate bit left**
 *
 * The test validates the rotating left of the bits in the value 0xB7 = 1011 0111 by the amount of 3 is
 * 1011 1101  = 0xBD
 */
void test__RotBitLt_u8u8__test2( void )
{
    uint8 Data = 0xB7;
    Bfx_RotBitLt_u8u8( &Data, 3u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xBD, "The function did not rotate left the bits of the value as supposed to be" );
}

/**
 * @brief   **Test copying bits from one number to another**
 *
 * Test if function copies a bit 1 from source data from bit position to destination data at bit
 * position
 */
void test__Bfx_CopyBit_u8u8u8u8__0to1( void )
{
    uint8 Data = 0x88;
    Bfx_CopyBit_u8u8u8u8( &Data, 0, 0xAA, 1 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x89, "The bit isnt copying correctly" );
}

/**
 * @brief   **Test copying bits from one number to another**
 *
 * Test if function copies a bit 0 from source data from bit position to destination data at bit
 * position
 */
void test__Bfx_CopyBit_u8u8u8u8__1to0( void )
{
    uint8 Data = 0x88;
    Bfx_CopyBit_u8u8u8u8( &Data, 3, 0xAA, 2 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x80, "The bit isnt copying correctly" );
}

/**
 * @brief   **Test putting bits as in Pattern from the bit position**
 *
 * Test if function put bits as mentioned in Pattern to the input Data from the
 * specified bit position
 */
void test__Bfx_PutBits_u8u8u8u8__specs( void )
{
    uint8 Data = 0xF0;
    Bfx_PutBits_u8u8u8u8( &Data, 1, 3, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF6, "The bit or pattern are incorrect" );
}

/**
 * @brief   **Test putting bits as in Pattern from the bit position (changing postion and length)**
 *
 * Test if function put bits as mentioned in Pattern to the input Data from the
 * specified bit swaping the previous starting position and length
 */
void test__Bfx_PutBits_u8u8u8u8__specsinv( void )
{
    uint8 Data = 0xF0;
    Bfx_PutBits_u8u8u8u8( &Data, 3, 1, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF8, "The bit or pattern are incorrect" );
}

/**
 * @brief   **Test changing bits with a pattert and mask**
 *
 * The test validates if function changes bits with a pattert and mask
 */
void test__Bfx_PutBitsMask_u8u8u8__specs( void )
{
    uint8 Data = 0xE0;
    Bfx_PutBitsMask_u8u8u8( &Data, 0xCD, 0x0F );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xED, "The mask or pattern are incorrect" );
}

/**
 * @brief   **Test changing bits with a pattert and mask inverted**
 *
 * The test validates if function changes bits with a pattert and mask inverted
 */
void test__Bfx_PutBitsMask_u8u8u8__specsinv( void )
{
    uint8 Data = 0xE0;
    Bfx_PutBitsMask_u8u8u8( &Data, 0x0F, 0xCD );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x2D, "The mask or pattern are incorrect" );
}

/**
 * @brief   **Test putting a bit to zero on the 7 position**
 *
 * The test validates if function puts a bit to zero on the 7 position
 */
void test__Bfx_PutBit_u8u8u8__0on7( void )
{
    uint8 Data = 0xFF;
    Bfx_PutBit_u8u8u8( &Data, 7, 0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x7F, "The bit wasnt put on the 7 position" );
}

/**
 * @brief   **Test putting a bit to one on the 6 position**
 *
 * The test validates if function puts a bit to one on the 16 position
 */
void test__Bfx_PutBit_u8u8u8__1on6( void )
{
    uint8 Data = 0x00;
    Bfx_PutBit_u8u8u8( &Data, 6, 1 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x40, "The bit wasnt put on the 6 position" );
}

/**
 * @brief   **Test Count Leading ones with 2**
 *
 * The test validates if function counts 2 ones from left to right
 */
void test__Bfx_CountLeadingOnes_u8__2ones( void )
{
    uint8 Data   = 0xCC;
    uint8 Result = Bfx_CountLeadingOnes_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x02, "There are no 2 ones from left to right" );
}

/**
 * @brief   **Test Count Leading ones with 7**
 *
 * The test validates if function counts 7 ones from left to right
 */
void test__Bfx_CountLeadingOnes_u8__10ones( void )
{
    uint8 Data   = 0xFE;
    uint8 Result = Bfx_CountLeadingOnes_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x07, "There are no 7 ones from left to right" );
}

/**
 * @brief   **Test Count Leading Signs with 4**
 *
 * The test validates if function counts 3 ones after the sign bit (1)
 */
void test__CountLeadingSigns_s8__3ones( void )
{
    sint8 Data   = 0xF0;
    uint8 Result = Bfx_CountLeadingSigns_s8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x03, "There are no 4 ones after de MSB" );
}

/**
 * @brief   **Test Count Leading Signs with 2**
 *
 * The test validates if function counts 2 zeros after the sign bit (0)
 */
void test__CountLeadingSigns_s8__2zeros( void )
{
    sint8 Data   = 0x1F;
    uint8 Result = Bfx_CountLeadingSigns_s8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x02, "There are no 2 zeros after de MSB" );
}

/**
 * @brief   **Test Count Leading Zeros with 6**
 *
 * The test validates if function counts 6 zeros from left to right
 */
void test__Bfx_CountLeadingZeros_u8__6zeros( void )
{
    uint8 Data   = 0x03;
    uint8 Result = Bfx_CountLeadingZeros_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x06, "There are no 6 zeros from left to right" );
}

/**
 * @brief   **Test Count Leading Zeros with 1**
 *
 * The test validates if function counts 1 zero from left to right
 */
void test__Bfx_CountLeadingZeros_u8__1zero( void )
{
    uint32 Data  = 0x40;
    uint8 Result = Bfx_CountLeadingZeros_u8( Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x01, "There is no zero from left to right" );
}
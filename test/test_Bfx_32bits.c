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
 * @brief   **Test set bit 19**
 *
 * The test validates if bit 2 is set over a varible with value 0x00000000, to pass the test data
 * should have a value of 0x00080000.
 */
void test__Bfx_SetBit_u32u8__bit19( void )
{
    uint32 Data = 0x00000000u;
    Bfx_SetBit_u32u8( &Data, 19u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00080000, "Bit 19 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 10**
 *
 * The test validates if bit 10 is set over a varible with value 0x00000000, to pass data tested
 * should have a value of 0x00000400.
 */
void test__Bfx_SetBit_u32u8__bit10( void )
{
    uint32 Data = 0x00000000u;
    Bfx_SetBit_u32u8( &Data, 10u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00000400, "Bit 10 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 31**
 *
 * The test validates if the bit 31 of the value 0x80000005 is cleared, resulting in 0x00000005
 */
void test__Bfx_ClrBit_u32u8__bit31( void )
{
    uint32 Data = 0x80000005;
    Bfx_ClrBit_u32u8( &Data, 31u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00000005, "Bit 31 was not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit 28**
 *
 * The test validates if the bit 28 of the value 0xF00000FA is cleared, resulting in 0xE00000FA
 */
void test__Bfx_ClrBit_u32u8__bit28( void )
{
    uint32 Data = 0xF00000FA;
    Bfx_ClrBit_u32u8( &Data, 28u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xE00000FA, "Bit 28 was not cleared as supposed to be" );
}

/**
 * @brief   **Test get bit 28**
 *
 * The test validates if the bit 28 of the value 0x200000FA is read correctly, resulting in FALSE
 */
void test__Bfx_GetBit_u32u8_u8__bit28( void )
{
    uint32 Data    = 0x200000FA;
    boolean Result = Bfx_GetBit_u32u8_u8( &Data, 28u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bit 28 was not read as supposed to be" );
}

/**
 * @brief   **Test get bit 29**
 *
 * The test validates if the bit 29 of the value 0x200000FA is read correctly, resulting in TRUE
 */
void test__Bfx_GetBit_u32u8_u8__bit29( void )
{
    uint32 Data    = 0x200000FA;
    boolean Result = Bfx_GetBit_u32u8_u8( &Data, 29u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bit 29 was not read as supposed to be" );
}

/**
 * @brief   **Test set bits 25-31 to 0**
 *
 * The test validates if the bits 25 to 31 of the value 0xFF0000AF are set to 0 correctly,
 * resulting in 0x010000AF
 */
void test__Bfx_SetBits_u32u8u8u8__bits25to31( void )
{
    uint32 Data = 0xFF0000AF;
    Bfx_SetBits_u32u8u8u8( &Data, 25u, 7u, 0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x010000AF, "Bits 25-31 were not set as supposed to be" );
}

/**
 * @brief   **Test set bits 20-23 to 1**
 *
 * The test validates if the bits 20 to 23 of the value 0x000000AF are set to 1 correctly,
 * resulting in 0x00F000AF
 */
void test__Bfx_SetBits_u32u8u8u8__bits20to23( void )
{
    uint32 Data = 0x000000AF;
    Bfx_SetBits_u32u8u8u8( &Data, 20u, 4u, 1 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00F000AF, "Bits 20-23 were not set as supposed to be" );
}

/**
 * @brief   **Test get bits 28-31**
 *
 * The test validates if the bits 28 to 31 of the value 0x89000000 are read correctly, resulting in
 * 0x08
 */
void test__GetBits_u32u8u8_u32__bits28to31( void )
{
    uint32 Data   = 0x89000000;
    uint32 Result = Bfx_GetBits_u32u8u8_u32( Data, 28, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x08, "Bits 28-31 were not read as supposed to be" );
}

/**
 * @brief   **Test get bits 0-7**
 *
 * The test validates if the bits 0 to 7 of the value 0x00000FB9 are read correctly, resulting in
 * 0xB9
 */
void test__GetBits_u32u8u8_u32__bits0to7( void )
{
    uint32 Data   = 0x00000FB9;
    uint32 Result = Bfx_GetBits_u32u8u8_u32( Data, 0, 8u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0xB9, "Bits 0-7 were not read as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 0-31**
 *
 * The test validates if the bits 0 to 31 of the value 0x81000081 are getting set correctly with
 * the mask 0x7C00007C resulting in 0xFD0000FD
 */
void test__SetBitMask_u32u32__bits0to31( void )
{
    uint32 Data = 0x81000081;
    Bfx_SetBitMask_u32u32( &Data, 0x7C0F007C );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFD0F00FD, "Bits 0-31 were not set as supposed to be" );
}

/**
 * @brief   **Test set bit mask bits 0-31**
 *
 * The test validates if the bits 0 to 31 of the value 0x81000081 are getting set correctly with
 * the mask 0x81000081 resulting in 0x81000081
 */
void test__SetBitMask_u32u32__bits0to31_2( void )
{
    uint32 Data = 0x81000081;
    Bfx_SetBitMask_u32u32( &Data, 0x81000081 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x81000081, "Bits 0-31 were not set as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 0-31**
 *
 * The test validates if the bits 0 to 31 of the value 0x81000081 are getting cleared correctly with
 * the mask 0x81000081 resulting in 0000 0000 = 0x00
 */
void test__ClrBitMask_u32u32__bits0to31( void )
{
    uint32 Data = 0x81000081;
    Bfx_ClrBitMask_u32u32( &Data, 0x81000081 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x00000000, "Bits 0-31 were not cleared as supposed to be" );
}

/**
 * @brief   **Test clear bit mask bits 24-31**
 *
 * The test validates if the bits 24 to 31 of the value 0xB9000000 are getting cleared correctly
 * with the mask 0x28000000 resulting in 0x91000000
 */
void test__ClrBitMask_u32u32__bits24to31( void )
{
    uint32 Data = 0xB9000000;
    Bfx_ClrBitMask_u32u32( &Data, 0x28000000 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x91000000, "Bits 24-31 were not cleared as supposed to be" );
}

/**
 * @brief   **Test of test bit mask bits 3-25**
 *
 * The test validates if the bits 3 to 25 of the value 0x12345678 are already set compared to
 * the mask 0x02040608 resulting in TRUE
 */
void test__TstBitMask_u32u32_u8__bits3to25( void )
{
    uint32 Data    = 0x12345678;
    boolean Result = Bfx_TstBitMask_u32u32_u8( Data, 0x02040608 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, TRUE, "Bits 3-25 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit mask bits 3-29**
 *
 * The test validates if the bits 3 to 29 of the value 0x12345678 are already set compared to
 * the mask 0x22040608 resulting in FALSE
 */
void test__TstBitMask_u32u32_u8__bits3to29( void )
{
    uint32 Data    = 0x12345678;
    boolean Result = Bfx_TstBitMask_u32u32_u8( Data, 0x22040608 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, FALSE, "Bits 3-29 were not already set as supposed to be vs the mask" );
}

/**
 * @brief   **Test of test bit length mask bits 0-31**
 *
 * The test validates if at least one bit of the value 0x330000CC is set as per the mask 0xCC000033
 * resulting in a FALSE
 */
void test__TstBitLnMask_u32u32_u8__bits0to31( void )
{
    uint32 Data    = 0x330000CC;
    boolean Result = Bfx_TstBitLnMask_u32u32_u8( Data, 0xCC000033 );
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

/**
 * @brief   **Test Shift Bit Sat (signed) - Arithmetical shift**
 *
 * The test validates if the value in Data = 0xFFFF0000 had a correct arithmetic shift when
 * ShiftCnt = -4 resulting in 0xFFFFFFFF
 */
void test__Bfx_ShiftBitSat_s32s8_s32__arithshift( void )
{
    sint32 Data   = 0xFFFF0000; // 1111 0000
    sint32 Result = Bfx_ShiftBitSat_s32s8_s32( -16, Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0xFFFFFFFF, "The arithmetic shift wasn't performed correctly" );
}

/**
 * @brief   **Test Shift Bit Sat (signed) - Saturation**
 *
 * The test validates if the value in Data = 0x55AA55AA had a correct saturation when
 * ShiftCnt = 3 resulting in 0x7FFFFFFF
 */
void test__Bfx_ShiftBitSat_s32s8_s32__saturation( void )
{
    sint32 Data   = 0x55AA55AA; // 0101 0101
    sint32 Result = Bfx_ShiftBitSat_s32s8_s32( 3, Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0x7FFFFFFF, "The saturation wasn't performed correctly" );
}

/**
 * @brief   **Test Shift Bit Sat (unsigned) - Saturation**
 *
 * The test validates if the value in Data = 0x2A2A2A2A had a correct saturation when
 * ShiftCnt = 3 resulting in 0xFFFFFFFF
 */
void test__Bfx_ShiftBitSat_u32s8_u32__saturation( void )
{
    sint32 Data   = 0x2A2A2A2A; // 0010 1010
    sint32 Result = Bfx_ShiftBitSat_u32s8_u32( 3, Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0xFFFFFFFF, "The saturation wasn't performed correctly" );
}

/**
 * @brief   **Test Shift Bit Sat (unsigned) - No saturation**
 *
 * The test validates if the value in Data = 0x2A2A2A2A had a correct left shift when
 * ShiftCnt = 2 resulting in 0xA8A8A8A8
 */
void test__Bfx_ShiftBitSat_u32s8_u32__nosaturation( void )
{
    sint32 Data   = 0x2A2A2A2A; // 0010 1010
    sint32 Result = Bfx_ShiftBitSat_u32s8_u32( 2, Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Result, 0xA8A8A8A8, "The left shift wasn't performed correctly" );
}
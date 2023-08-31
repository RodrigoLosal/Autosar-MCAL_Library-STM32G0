/**
 * @file    Bfx_32bits.h
 * @brief   **This file contains the Bitfield functions for fixed point for 32 bit registers.**
 *
 * Bfx routines specification specifies the functionality, API and the configuration of the
 * AUTOSAR library for BIT functionality dedicated to fixed-point arithmetic routines.
 * All bit functions are re-entrant and can handle several simultaneous requests from the
 * application.
 */
#include "Std_Types.h"

/**
 * @brief   **Set a single bit in Data pointer**
 *
 * This function shall set the logical status of input data as ’1’ at the requested bit position.
 *
 * @param   Data Unsigned integer to modify
 * @param   BitPn Number of bit to modify
 * 
 * @reqs   SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
static inline void Bfx_SetBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data |= ( 0x01 << BitPn );
}

/**
 * @brief   **Clears a single bit in Data pointer**
 *
 * This function shall clear the logical status of the input data to ’0’ at the requested bit
 * position.
 *
 * @param   Data Unsigned integer to modify
 * @param   BitPn Number of bit to modify
 *
 * @reqs   SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
static inline void Bfx_ClrBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data &= ~( 0x01 << BitPn );
}

/**
 * @brief   **Obtain one bit especified**
 *
 * This function shall return the logical status of the input data for the requested bit position.
 *
 * @param   Data Unsigned integer containing the bit
 * @param   BitPn Number of bit to obtain
 *
 * @retval  Result
 *
 * @reqs   SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
static inline boolean Bfx_GetBit_u32u8_u8( uint32 *Data, uint8 BitPn )
{
    boolean Result;

    Result = ( *Data >> BitPn ) & 1;
    return Result;
}

/**
 * @brief   **Modifies consecutive bits acording to status**
 *
 * This function shall set the input data as ’1’ or ’0’ as per ’Status’ value starting from
 * ’BitStartPn’ for the length ’BitLn’.
 *
 * @param   Data Unsigned integer to modify
 * @param   BitStartPn Bit that indicates the start of the bits to modify
 * @param   BitLn Number of bits to modify
 * @param   Status Value that the bits will take
 *
 * @reqs   SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
static inline void Bfx_SetBits_u32u8u8u8( uint32 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Status )
{
    uint32 Mask = ( ( 1u << BitLn ) - 1 ) << BitStartPn;

    if( Status == 0 )
    {
        *Data &= ~Mask;
    }
    else if( Status == 1 )
    {
        *Data |= Mask;
    }
}

/**
 * @brief   **Obtains consecutive bits from an unsigned integer**
 *
 * This function shall return the Bits of the input data starting from ’BitStartPn’ for the
 * length of ’BitLn’.
 *
 * @param   Data Unsigned integer with the bits
 * @param   BitStartPn Bit that indicates the start of the bits to obtain
 * @param   BitLn Number of bits to obtain
 *
 * @retval  Result
 *
 * @reqs   SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
static inline uint8 Bfx_GetBits_u32u8u8_u32( uint32 Data, uint8 BitStartPn, uint8 BitLn )
{
    uint32 Result;

    Result = ( Data >> BitStartPn ) & ( ( 1u << BitLn ) - 1u );
    return Result;
}

/**
 * @brief   **Using a mask to set bits**
 *
 * This function shall set the data to logical status ’1’ as per the corresponding Mask bits when
 * set to value 1 and remaining bits will retain their original values.
 *
 * @param   Data Unsigned integer to modify
 * @param   Mask Mask that indicates the bits to set
 *
 * @reqs   SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
static inline void Bfx_SetBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data |= Mask;
}

/**
 * @brief   **Using a mask to clear bits**
 *
 * This function shall clear the logical status to ’0’ for the input data for all the bit
 * positions as per the mask.
 *
 * @param   Data Unsigned integer to modify
 * @param   Mask Mask that indicates the bits to clear
 *
 * @reqs   SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045
 */
static inline void Bfx_ClrBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data &= ~Mask;
}

/**
 * @brief   **Compare a mask with a seccion of an unsigned integer**
 *
 * This function shall return TRUE, if all bits defined in Mask value are set in the input Data
 * value. In all other cases this function shall return FALSE.
 *
 * @param   Data Unsigned integer to compare
 * @param   Mask Mask used to compare
 *
 * @retval  Result
 *
 * @reqs   SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
static inline boolean Bfx_TstBitMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    Result = ( Data & Mask ) == Mask;
    return Result;
}

/**
 * @brief   **Compare any bit of a mask with a seccion of an unsigned integer**
 *
 * This function makes a test on the input data and if at least one bit is set as per the mask,
 * then the function shall return TRUE, otherwise it shall return FALSE.
 *
 * @param   Data Unsigned integer to compare
 * @param   Mask Mask used to compare
 *
 * @retval  Result
 *
 * @reqs   SWS_Bfx_00051, SWS_Bfx_00055
 */
static inline boolean Bfx_TstBitLnMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    Result = ( Data & Mask ) > 0;
    return Result;
}

/**
 * @brief   **Determines if an unsigned integer has even parity**
 *
 * This function tests the number of bits set to 1. If this number is even, it shall return TRUE,
 * otherwise it returns FALSE.
 *
 * @param   Data Unsigned integer to compare
 *
 * @retval  Result
 *
 * @reqs   SWS_Bfx_00056, SWS_Bfx_00060
 */
static inline boolean Bfx_TstParityEven_u32_u8( uint32 Data )
{
    boolean parity = FALSE;
    boolean Result;

    while( Data > 0 )
    {
        parity = !parity;
        Data &= ( Data - 1 );
    }
    Result = !parity;
    return Result;
}

/**
 * @brief   **Changes the value of every bit of an unsigned integer**
 *
 * This function toggles all the bits of data (1’s Complement Data).
 *
 * @param   Data Unsigned integer to modify
 *
 * @reqs   SWS_Bfx_00061, SWS_Bfx_00065
 */
static inline void Bfx_ToggleBits_u32( uint32 *Data )
{
    *Data = ~*Data;
}

/**
 * @brief   **Using a mask to toggle bits**
 *
 * This function toggles the bits of data when the corresponding bit of the mask is enabled and
 * set to 1.
 *
 * @param   Data Unsigned integer to modify
 * @param   Mask Mask that indicates the bits to toggle
 *
 * @reqs   SWS_Bfx_00066, SWS_Bfx_00069
 */
static inline void Bfx_ToggleBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data ^= Mask;
}

/**
 * @brief   **Shifts a unsigned integer to the right acourding to ShiftCnt**
 *
 * This function shall shift data to the right by ShiftCnt. The most significant bit (left-most
 * bit) is replaced by a ’0’ bit and the least significant bit (right-most bit) is discarded for
 * every single bit shift cycle.
 *
 * @param   Data Unsigned integer to modify
 * @param   ShiftCnt Number of shifts to perform
 *
 * @reqs   SWS_Bfx_00070, SWS_Bfx_00075
 */
static inline void Bfx_ShiftBitRt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data >>= ShiftCnt;
}

/**
 * @brief   **Shifts a unsigned integer to the left acourding to ShiftCnt**
 *
 * This function shall shift data to the left by ShiftCnt. The least significant bit (right-most
 * bit) is replaced by a ’0’ bit and the most significant bit (left-most bit) is discarded for
 * every single bit shift cycle.
 *
 * @param   Data Unsigned integer to modify
 * @param   ShiftCnt Number of shifts to perform
 *
 * @reqs   SWS_Bfx_00076, SWS_Bfx_00080
 */
static inline void Bfx_ShiftBitLt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data <<= ShiftCnt;
}

/**
 * @brief   **Rotates a unsigned integer to the right acourding to ShiftCnt**
 *
 * This function shall rotate data to the right by ShiftCnt. The least significant bit is rotated
 * to the most significant bit location for every single bit shift cycle.
 *
 * @param   Data Unsigned integer to modify
 * @param   ShiftCnt Number of shifts to perform
 *
 * @reqs   SWS_Bfx_00086, SWS_Bfx_00090
 */
static inline void Bfx_RotBitRt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data >> ShiftCnt ) | ( *Data << ( 32 - ShiftCnt ) );
}

/**
 * @brief   **Rotates a unsigned integer to the left acourding to ShiftCnt**
 *
 * This function shall rotate data to the right by ShiftCnt. The least significant bit is rotated
 * to the most significant bit location for every single bit shift cycle.
 *
 * @param   Data Unsigned integer to modify
 * @param   ShiftCnt Number of shifts to perform
 *
 * @reqs   SWS_Bfx_00095, SWS_Bfx_00098
 */
static inline void Bfx_RotBitLt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data << ShiftCnt ) | ( *Data >> ( 32 - ShiftCnt ) );
}

/**
 * @brief   **Copies a bit from an integer to another**
 *
 * This function shall copy a bit from source data from bit position to destination data at bit
 * position.
 *
 * @param   DestinationData Unsigned integer receptor
 * @param   DestinationPosition Destination bit
 * @param   SourceData Unsigned integer source
 * @param   SourcePosition Source bit
 *
 * @reqs   SWS_Bfx_00101, SWS_Bfx_00108
 */
static inline void Bfx_CopyBit_u32u8u32u8( uint32 *DestinationData, uint8 DestinationPosition, uint32 SourceData, uint8 SourcePosition )
{
    boolean Buffer;

    Buffer = ( ( SourceData & ( 0x01 << SourcePosition ) ) != 0 ) ? TRUE : FALSE;
    if( Buffer == FALSE )
    {
        *DestinationData = ( *DestinationData & ~( 0x01 << DestinationPosition ) );
    }
    else
    {
        *DestinationData = *DestinationData | ( 0x01 << DestinationPosition );
    }
}

/**
 * @brief   **Takes a pattern and puts it in an unsigned integer**
 *
 * This function shall put bits as mentioned in Pattern to the input Data from the specified bit
 * position.
 *
 * @param   Data Unsigned integer to modify
 * @param   BitStartPn LSB to start
 * @param   BitLn Lenght of the chain of bits
 * @param   Pattern Pattern to partially copy
 *
 * @reqs   SWS_Bfx_00110, SWS_Bfx_00112
 */
static inline void Bfx_PutBits_u32u8u8u32( uint32 *Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern )
{
    uint32 Mask = ( ( 1u << BitLn ) - 1u ) << BitStartPn;
    *Data       = ( *Data & ~Mask ) | ( ( Pattern << BitStartPn ) & Mask );
}

/**
 * @brief   **Takes a pattern and a mask and puts it in an unsigned integer**
 *
 * This function shall put all bits defined in Pattern and for which the corresponding Mask bit
 * is set to 1 in the input Data.
 *
 * @param   Data Unsigned integer to modify
 * @param   Pattern Pattern to partially copy
 * @param   Mask Mask that indicates the bits to copy
 *
 * @reqs   SWS_Bfx_00120, SWS_Bfx_00124
 */
static inline void Bfx_PutBitsMask_u32u32u32( uint32 *Data, uint32 Pattern, uint32 Mask )
{
    *Data = ( *Data & ~Mask ) | ( Pattern & Mask );
}

/**
 * @brief   **Sets the bit of an unsigned integer according to Status**
 *
 * This function shall update the bit specified by BitPn of input data as ’1’ or ’0’ as per
 * ’Status’ value.
 *
 * @param   Data Unsigned integer to modify
 * @param   BitPn Pin to modify
 * @param   Status boolean value to set
 *
 * @reqs   SWS_Bfx_00130, SWS_Bfx_00132
 */
static inline void Bfx_PutBit_u32u8u8( uint32 *Data, uint8 BitPn, boolean Status )
{
    if( Status == FALSE )
    {
        *Data &= ~( 0x01 << BitPn );
    }
    else
    {
        *Data |= 0x01 << BitPn;
    }
}

/**
 * @brief   **Counts consecutive ones**
 *
 * Count the number of consecutive ones in Data starting with the most significant bit and return
 * the result.
 *
 * @param   Data Unsigned integer to check
 *
 * @retval  Counter
 *
 * @reqs   SWS_Bfx_91003, SWS_Bfx_00137
 */
static inline uint8 Bfx_CountLeadingOnes_u32( uint32 Data )
{
    uint8 Counter = 0;

    for( uint8 i = 32; i > 0; i-- )
    {
        if( ( Data & ( 0x01 << ( i - 1 ) ) ) != 0 )
        {
            Counter++;
        }
        else
        {
            i = 1;
        }
    }
    return Counter;
}

/**
 * @brief   **Counts consecutive zeros**
 *
 * Count the number of consecutive zeros in Data starting with the most significant bit and return
 * the result.
 *
 * @param   Data Unsigned integer to check
 *
 * @retval  Counter
 *
 * @reqs   SWS_Bfx_91005, SWS_Bfx_00141
 */
static inline uint8 Bfx_CountLeadingZeros_u32( uint32 Data )
{
    uint8 Counter = 0;

    for( uint8 i = 32; i > 0; i-- )
    {
        if( ( Data & ( 0x01 << ( i - 1 ) ) ) != 0 )
        {
            i = 1;
        }
        else
        {
            Counter++;
        }
    }
    return Counter;
}

/**
 * @brief   **Counts leading signs**
 *
 * Count the number of consecutive bits which have the same value as most significant bit in Data,
 * starting with bit at position msb minus one. Put the result in Data. It is the number of
 * leading sign bits minus one, giving the number of redundant sign bits in Data.
 *
 * @param   Data Signed integer to count from
 *
 * @retval  Counter
 *
 * @reqs   SWS_Bfx_91004, SWS_Bfx_00139
 */
static inline uint8 Bfx_CountLeadingSigns_s32( sint32 Data )
{
    uint8 Count = 0;
    sint32 Mask = 0x80000000;

    if( Data >= 0 )
    {
        while( ( Data & Mask ) == 0 )
        {
            Count++;
            Mask >>= 1;
        }
    }
    else
    {
        while( ( Data & Mask ) == Mask )
        {
            Count++;
            Mask >>= 1;
        }
    }
    Data = Count - 1;
    return Data;
}

/**
 * @brief   **Arithmetic shift with saturation**
 *
 * If the shift count is greater than or equal to zero, then shift the value in Data by the
 * amount specified by shift count to left.
 * For this function, arithmetic shift is performed. The vacated bits are filled with zeros
 * and the result is saturated if its sign bit differs from the sign bits that are shifted out.
 * If the shift count is less than zero, right-shift the value in Data by the absolute value of
 * the shift count. The vacated bits are filled with the sign-bit (the most significant bit) and
 * bits shifted out are discarded.
 *
 * @param   ShiftCnt Shift count
 * @param   Data Signed integer to check
 *
 * @retval  Data
 *
 * @reqs   SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
static inline sint32 Bfx_ShiftBitSat_s32s8_s32( sint8 ShiftCnt, sint32 Data )
{
    uint32 Mask            = 0x80000000;
    boolean DataIsNegative = ( Data < 0 );

    if( ShiftCnt >= 0 )
    {
        Data <<= ShiftCnt;
        if( ( DataIsNegative == FALSE ) && ( Data < 0 ) )
        {
            Data = 0x7FFFFFFF;
        }
        else if( ( DataIsNegative == TRUE ) && ( Data >= 0 ) )
        {
            Data = 0xFFFFFFFF;
        }
    }
    else
    {
        ShiftCnt *= -1;
        if( Data > 0 )
        {
            Data >>= ShiftCnt;
        }
        else
        {
            Data >>= ShiftCnt;
            for( uint8 i = 0; i < ShiftCnt; i++ )
            {
                Data |= Mask;
                Mask >>= 1;
            }
        }
    }
    return Data;
}

/**
 * @brief   **Arithmetic shift with saturation**
 *
 * If the shift count is greater than or equal to zero, then shift the value in Data by the
 * amount specified by shift count to left.
 * For this function a logical shift is performed. In this case the result is saturated, if the
 * leading one bit is shifted out.
 * If the shift count is less than zero, right-shift the value in Data by the absolute value of
 * the shift count. The vacated bits are filled with the sign-bit (the most significant bit) and
 * bits shifted out are discarded.
 *
 * @param   ShiftCnt Shift count
 * @param   Data Unsigned integer to check
 *
 * @retval  Data
 *
 * @reqs   SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
static inline uint32 Bfx_ShiftBitSat_u32s8_u32( sint8 ShiftCnt, uint32 Data )
{
    uint32 Mask        = 0x80000000;
    uint8 MaxShiftLeft = 0;

    while( ( Data & Mask ) == 0 )
    {
        MaxShiftLeft++;
        Mask >>= 1;
    }
    if( ShiftCnt >= 0 )
    {
        if( ShiftCnt > MaxShiftLeft )
        {
            Data = 0xFFFFFFFF;
        }
        else
        {
            Data <<= ShiftCnt;
        }
    }
    else
    {
        ShiftCnt *= -1;
        Data >>= ShiftCnt;
    }
    return Data;
}
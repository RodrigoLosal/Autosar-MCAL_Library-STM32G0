#include "Std_Types.h"

static inline void Bfx_SetBit_u8u8( uint8 *Data, uint8 BitPn )
{
    *Data |= ( 0x01 << BitPn );
}

static inline void Bfx_ClrBit_u8u8( uint8 *Data, uint8 BitPn )
{
    *Data &= ~( 0x01 << BitPn );
}

static inline boolean Bfx_GetBit_u8u8_u8( uint8 *Data, uint8 BitPn )
{
    boolean Result;

    Result = ( *Data >> BitPn ) & 1u;

    return Result;
}

static inline void Bfx_SetBits_u8u8u8u8( uint8 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Status )
{
    uint8 Mask = ( ( 1u << BitLn ) - 1u ) << BitStartPn;

    if( Status == 0 )
    {
        *Data = *Data & ~Mask;
    }
    else if( Status == 1 )
    {
        *Data = *Data | Mask;
    }
}

static inline uint8 Bfx_GetBits_u8u8u8_u8( uint8 Data, uint8 BitStartPn, uint8 BitLn )
{
    uint8 Result;

    uint8 Mask = ( ( 1u << BitLn ) - 1u );

    Result = ( Data >> BitStartPn ) & Mask;

    return Result;
}

static inline void Bfx_SetBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data |= Mask;
}

static inline void Bfx_ClrBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data &= ~Mask;
}

static inline boolean Bfx_TstBitMask_u8u8_u8( uint8 Data, uint8 Mask )
{
    boolean Result;

    Result = ( Data & Mask ) == Mask;

    return Result;
}

static inline boolean Bfx_TstBitLnMask_u8u8_u8( uint8 Data, uint8 Mask )
{
    boolean Result;

    Result = ( Data & Mask ) > 0;

    return Result;
}

static inline boolean Bfx_TstParityEven_u8_u8( uint8 Data )
{
    boolean Parity = FALSE;
    boolean Result;

    while( Data > 0 )
    {
        Parity = !Parity;
        Data   = Data & ( Data - 1 );
    }

    Result = !Parity;
    return Result;
}

static inline void Bfx_ToggleBits_u8( uint8 *Data )
{
    *Data = ~*Data;
}

static inline void Bfx_ToggleBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data ^= Mask;
}

static inline void Bfx_ShiftBitRt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data >>= ShiftCnt;
}

static inline void Bfx_ShiftBitLt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data <<= ShiftCnt;
}

static inline void Bfx_RotBitRt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data >> ShiftCnt ) | ( *Data << ( 8 - ShiftCnt ) );
}

static inline void Bfx_RotBitLt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data << ShiftCnt ) | ( *Data >> ( 8 - ShiftCnt ) );
}

static inline void Bfx_CopyBit_u8u8u8u8( uint8 *DestinationData, uint8 DestinationPosition, uint8 SourceData, uint8 SourcePosition )
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

static inline void Bfx_PutBits_u8u8u8u8( uint8 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern )
{
    uint8 Mask = ( ( 1u << BitLn ) - 1u ) << BitStartPn;
    *Data      = ( *Data & ~Mask ) | ( ( Pattern << BitStartPn ) & Mask );
}

static inline void Bfx_PutBitsMask_u8u8u8( uint8 *Data, uint8 Pattern, uint8 Mask )
{
    *Data = ( *Data & ~Mask ) | ( Pattern & Mask );
}

static inline void Bfx_PutBit_u8u8u8( uint8 *Data, uint8 BitPn, boolean Status )
{
    if( Status == FALSE )
    {
        *Data = ( *Data & ~( 0x01 << BitPn ) );
    }
    else
    {
        *Data = *Data | ( 0x01 << BitPn );
    }
}

static inline uint8 Bfx_CountLeadingOnes_u8( uint8 Data )
{
    uint8 Counter = 0;
    for( uint8 i = 8; i > 0; i-- )
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

static inline uint8 Bfx_CountLeadingSigns_s8( sint8 Data )
{
    uint8 Count = 0;
    sint8 Mask = 0x80;

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

static inline uint8 Bfx_CountLeadingZeros_u8( uint8 Data )
{
    uint8 Counter = 0;
    for( uint8 i = 8; i > 0; i-- )
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

static inline sint8 Bfx_ShiftBitSat_s8s8_s8(sint8 ShiftCnt, sint8 Data)
{
    sint8 Mask = 0x80;
    boolean DataIsNegative = (Data < 0);

    // Perform shift left if ShiftCnt >= 0
    if ( ShiftCnt >= 0 )
    {
        Data <<= ShiftCnt;

        // Saturation when Data was originally positive and had a sign change after the shift
        if ( ( DataIsNegative == FALSE ) && ( Data < 0 ) )
        {
            Data = 0x7F; //+127
        }
        // Saturation when Data was originally negative and had a sign change after the shift
        else if ( ( DataIsNegative == TRUE ) && ( Data >= 0 ) )
        {
            Data = 0x80; //-128
        }
    }
    // Perform right shift if ShiftCnt < 0
    else
    {
        // Absolute value of ShiftCnt
        ShiftCnt *= -1;

        // Fill with 0's when Data is positive
        if ( Data > 0 )
        {
            Data >>= ShiftCnt;
        }
        // Fill with 1's when Data is negative
        else
        {
            Data >>= ShiftCnt;

            for( uint8 i = 0 ; i < ShiftCnt ; i++ )
            {
                Data |= Mask;
                Mask >>= 1;
            }
        }
    }

    return Data;
}
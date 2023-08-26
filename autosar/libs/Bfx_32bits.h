#include "Std_Types.h"

static inline void Bfx_SetBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data |= ( 0x01 << BitPn );
}

static inline void Bfx_ClrBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data &= ~( 0x01 << BitPn );
}

static inline boolean Bfx_GetBit_u32u8_u8( uint32 *Data, uint8 BitPn )
{
    boolean Result;

    Result = ( *Data >> BitPn ) & 1;
    return Result;
}

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

static inline uint8 Bfx_GetBits_u32u8u8_u32( uint32 Data, uint8 BitStartPn, uint8 BitLn )
{
    uint32 Result;

    Result = ( Data >> BitStartPn ) & ( ( 1u << BitLn ) - 1u );
    return Result;
}

static inline void Bfx_SetBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data |= Mask;
}

static inline void Bfx_ClrBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data &= ~Mask;
}

static inline boolean Bfx_TstBitMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    
    Result = ( Data & Mask ) == Mask;
    return Result;
}

static inline boolean Bfx_TstBitLnMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    Result = ( Data & Mask ) > 0;
    return Result;
}

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

static inline void Bfx_ToggleBits_u32( uint32 *Data )
{
    *Data = ~*Data;
}

static inline void Bfx_ToggleBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data ^= Mask;
}

static inline void Bfx_ShiftBitRt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data >>= ShiftCnt;
}

static inline void Bfx_ShiftBitLt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data <<= ShiftCnt;
}

static inline void Bfx_RotBitRt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data >> ShiftCnt ) | ( *Data << ( 32 - ShiftCnt ) );
}

static inline void Bfx_RotBitLt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data << ShiftCnt ) | ( *Data >> ( 32 - ShiftCnt ) );
}

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

static inline void Bfx_PutBits_u32u8u8u32( uint32 *Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern )
{
    uint32 Mask = ( ( 1u << BitLn ) - 1u ) << BitStartPn;
    *Data      = ( *Data & ~Mask ) | ( ( Pattern << BitStartPn ) & Mask );
}

static inline void Bfx_PutBitsMask_u32u32u32( uint32 *Data, uint32 Pattern, uint32 Mask )
{
    *Data = ( *Data & ~Mask ) | ( Pattern & Mask );
}

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
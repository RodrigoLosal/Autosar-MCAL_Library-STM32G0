#include "Std_Types.h"

static inline void Bfx_SetBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data = *Data | ( 0x01 << BitPn );
}

static inline void Bfx_ClrBit_u32u8( uint32 *Data, uint8 BitPn )
{
    *Data = ( *Data & ~( 0x01 << BitPn ) );
}

static inline boolean Bfx_GetBit_u32u8_u8( uint32 *Data, uint8 BitPn )
{
    boolean Result;
    if( ( *Data & ( 0x01 << BitPn ) ) != 0 )
    {
        Result = TRUE;
    }
    else
    {
        Result = FALSE;
    }
    return Result;
}

static inline void Bfx_SetBits_u32u8u8u8( uint32 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Status )
{
    for( uint8 i = BitStartPn; i < ( BitStartPn + BitLn ); i++ )
    {
        if( Status == 0 )
        {
            *Data = ( *Data & ~( 0x01 << i ) );
        }
        else if( Status == 1 )
        {
            *Data = *Data | ( 0x01 << i );
        }
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
    *Data = *Data | Mask;
}

static inline void Bfx_ClrBitMask_u32u32( uint32 *Data, uint32 Mask )
{
    *Data = *Data & ~Mask;
}

static inline boolean Bfx_TstBitMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    if( ( Data & Mask ) == Mask )
    {
        Result = TRUE;
    }
    else
    {
        Result = FALSE;
    }
    return Result;
}

static inline boolean Bfx_TstBitLnMask_u32u32_u8( uint32 Data, uint32 Mask )
{
    boolean Result;
    if( ( Data & Mask ) > 0 )
    {
        Result = TRUE;
    }
    else
    {
        Result = FALSE;
    }
    return Result;
}

static inline boolean Bfx_TstParityEven_u32_u8( uint32 Data )
{
    boolean parity = FALSE;
    while( Data > 0 )
    {
        parity = !parity;
        Data = Data & ( Data - 1 );
    }
    return !parity;
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
    *Data = *Data >> ShiftCnt;
}

static inline void Bfx_ShiftBitLt_u32u8( uint32 *Data, uint8 ShiftCnt )
{
    *Data = *Data << ShiftCnt;
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
    if( ( SourceData & ( 0x01 << SourcePosition ) ) != 0 )
    {
        Buffer = TRUE;
    }
    else
    {
        Buffer = FALSE;
    }
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
    for( uint8 i = BitLn; i < ( BitLn + ( 32 - BitLn ) ); i++ )
    {
        Pattern = ( Pattern & ~( 0x01 << i ) );
    }
    Pattern = Pattern << BitStartPn;
    for( uint8 i = BitStartPn; i < ( BitStartPn + BitLn ); i++ )
    {
        *Data = ( *Data & ~( 0x01 << i ) );
    }
    *Data = *Data | Pattern;
}

static inline void Bfx_PutBitsMask_u32u32u32( uint32 *Data, uint32 Pattern, uint32 Mask )
{
    boolean Buffer;
    boolean Buffer2;
    for( uint8 i = 0; i <= 31; i++ )
    {
        if( ( Mask & ( 0x01 << i ) ) != 0 )
        {
            Buffer = TRUE;
        }
        else
        {
            Buffer = FALSE;
        }
        if( ( Pattern & ( 0x01 << i ) ) != 0 )
        {
            Buffer2 = TRUE;
        }
        else
        {
            Buffer2 = FALSE;
        }
        if( ( Buffer == TRUE ) && ( Buffer2 == TRUE ) )
        {
            *Data = *Data | ( 0x01 << i );
        }
        else if( ( Buffer == TRUE ) && ( Buffer2 == FALSE ) )
        {
            *Data = ( *Data & ~( 0x01 << i ) );
        }
    }
}

static inline void Bfx_PutBit_u32u8u8( uint32 *Data, uint8 BitPn, boolean Status )
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
    uint8 Counter = 0;
    sint32 msb;
    msb = Data >> 31;
    if( msb == 0 )
    {
        for( uint8 i = 32; i > 0; i-- )
        {
            if( ( ( Data << 1 ) & ( 0x01 << ( i - 1 ) ) ) != 0 )
            {
                i = 1;
            }
            else
            {
                Counter++;
            }
        }
        if( Counter == 32 )
        {
            Counter = 31;
        }
    }
    else
    {
        for( uint8 i = 32; i > 0; i-- )
        {
            if( ( ( Data << 1 ) & ( 0x01 << ( i - 1 ) ) ) != 0 )
            {
                Counter++;
            }
            else
            {
                i = 1;
            }
        }
    }
    return Counter;
}
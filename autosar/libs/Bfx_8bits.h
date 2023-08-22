static inline void Bfx_SetBit_u8u8( uint8 *Data, uint8 BitPn )
{
    *Data = *Data | ( 0x01 << BitPn );
}

static inline void Bfx_ClrBit_u8u8( uint8 *Data, uint8 BitPn )
{
    *Data = ( *Data & ~( 0x01 << BitPn ) );
}

static inline boolean Bfx_GetBit_u8u8_u8( uint8 *Data, uint8 BitPn )
{
    boolean Result;
    if( ( *Data & ( 0x01 << BitPn ) ) != 0 )
    {
        Result = TRUE;
        Result = FALSE;
    }
    else
    {
        Result = FALSE;
    }
    return Result; 
}

static inline void Bfx_SetBits_u8u8u8u8( uint8 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Status )
{
    for( uint8 i = BitStartPn; i <= ( BitStartPn + BitLn ); i++ )
    {
        if( Status == 0 )
        {
            Bfx_ClrBit_u8u8( Data, i );
        }
        else if( Status == 1 )
        {
            Bfx_SetBit_u8u8( Data, i );
        }
    }
}

static inline uint8 Bfx_GetBits_u8u8u8_u8( uint8 Data, uint8 BitStartPn, uint8 BitLn )
{
    uint32 Result = 0;
    for( uint8 i = ( BitStartPn + BitLn ); i >= BitStartPn; i-- )
    {
        Result = Result + Bfx_GetBit_u8u8_u8( &Data, i );
        Result = Result << 1;
    }
    Result = Result >> 1;
    return Result;
}

static inline void  Bfx_SetBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data = *Data | Mask;
}

static inline void Bfx_ClrBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data = *Data & ~Mask;
}

static inline boolean Bfx_TstBitMask_u8u8_u8( uint8 Data, uint8 Mask )
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

static inline boolean Bfx_TstBitLnMask_u8u8_u8( uint8 Data, uint8 Mask )
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

static inline boolean Bfx_TstParityEven_u8_u8( uint8 Data )
{
    boolean Result;
    uint8 counter = 0;
    for( uint8 i = 0; i <= 7; i++ )
    {
        counter = counter + Bfx_GetBit_u8u8_u8( &Data, i );
    }
    if( ( counter % 2 ) == 1 )
    {
        Result = FALSE;
    }
    else
    {
        Result = TRUE;
    }
    return Result;
}

static inline void Bfx_ToggleBits_u8( uint8 *Data )
{
    *Data = ~*Data;
}

static inline void Bfx_ToggleBitMask_u8u8( uint8 *Data, uint8 Mask )
{
    *Data = ~( *Data | ~Mask );
}

static inline void Bfx_ShiftBitRt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data = *Data >> ShiftCnt;
}

static inline void Bfx_ShiftBitLt_u8u8( uint8 *Data, uint8 ShiftCnt )
{
    *Data = *Data << ShiftCnt;
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
    if( Bfx_GetBit_u8u8_u8( &SourceData, SourcePosition ) == FALSE )
    {
        Bfx_ClrBit_u8u8( DestinationData, DestinationPosition );
    }
    else
    {
        Bfx_SetBit_u8u8( DestinationData, DestinationPosition );
    }
}

static inline void Bfx_PutBits_u8u8u8u8( uint8 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern )
{
    Bfx_SetBits_u8u8u8u8( &Pattern, BitLn, ( 8 - BitLn ), 0 );
    Pattern = Pattern << BitStartPn;
    Bfx_SetBits_u8u8u8u8( Data, BitStartPn, BitLn, 0 );
    *Data = *Data | Pattern;
}

static inline void Bfx_PutBitsMask_u8u8u8( uint8 *Data, uint8 Pattern, uint8 Mask )
{
    for( uint8 i = 0; i <= 7; i++ )
    {
        if( ( Bfx_GetBit_u8u8_u8( &Mask, i ) == TRUE ) && ( Bfx_GetBit_u8u8_u8( &Pattern, i ) == TRUE ) )
        {
            Bfx_SetBit_u8u8( Data, i );
        }
        else if( ( Bfx_GetBit_u8u8_u8( &Mask, i ) == TRUE ) && ( Bfx_GetBit_u8u8_u8( &Pattern, i ) == FALSE ) )
        {
            Bfx_ClrBit_u8u8( Data, i );
        }
    }
}

static inline void Bfx_PutBit_u8u8u8( uint8 *Data, uint8 BitPn, boolean Status )
{
    if( Status == FALSE )
    {
        Bfx_ClrBit_u8u8( Data, BitPn );
    }
    else
    {
        Bfx_SetBit_u8u8( Data, BitPn );
    }
}

static inline uint8 Bfx_CountLeadingOnes_u8( uint8 Data )
{
    uint8 Counter = 0;
    for( uint8 i = 8; i < 0; i-- )
    {
        if( Bfx_GetBit_u8u8_u8( &Data, ( i - 1 ) ) == TRUE )
        {
            Counter++;
        }
        else
        {
            i = 0;
        }
    }
    return Counter;
}

static inline sint8 Bfx_ShiftBitSat_s8s8_s8(sint8 ShiftCnt, sint8 Data) {
    sint8 result;

    if ( ShiftCnt >= 0 )
    {
        result = Data << ShiftCnt;
        if ( ( ShiftCnt < 8 ) && ( Data < 0 ) && ( ( result & 0x80 ) != ( Data & 0x80 ) ) )
        {
            result = (Data < 0) ? -128 : 127;
        }
    }
    else
    {
        ShiftCnt = -ShiftCnt;
        result = Data >> ShiftCnt;
        sint8 sign_mask = ( Data < 0 ) ? ( ( 1 << ShiftCnt ) - 1 ) : 0;
        result |= ( sign_mask << ( 8 - ShiftCnt ) );
    }

    return result;
}

static inline uint8 Bfx_CountLeadingSigns_s8( sint8 Data )
{
    uint8 Counter = 0;
    uint8 Mask = 0x40; // Máscara para el bit de signo en un sint8:0100 0000b (Posición MSB - 1)

    // Contar los bits de signo consecutivos
    while ( (Data & Mask) == Mask )
    {
        Counter++;
        Data <<= 1; // Desplazar a la izquierda para verificar el siguiente bit
    }

    return Counter;
}

static inline uint8 Bfx_CountLeadingZeros_u8( uint8 Data )
{
    uint8 Counter = 0;
    for( uint8 i = 8; i < 0; i-- )
    {
        if( Bfx_GetBit_u8u8_u8( &Data, ( i - 1 ) ) == FALSE )
        {
            Counter++;
        }
        else
        {
            i = 0;
        }
    }
    return Counter;
}
#ifndef BFX_8BITS_H
#define BFX_8BITS_H

#include "Std_Types.h"

typedef struct {
    bool bit0 = 1;
    bool bit1 = 1;
    bool bit2 = 1;
    bool bit3 = 1;
    bool bit4 = 1;
    bool bit5 = 1;
    bool bit6 = 1;
    bool bit7 = 1;
} BfxData;

static inline void Bfx_SetBit_u8( BfxData *Data, uint8 BitPn );
static inline void Bfx_ClrBit_u8( BfxData *Data, uint8_t BitPn );
static inline bool Bfx_GetBit_u8( BfxData Data, uint8_t BitPn );
static inline void Bfx_SetBits_u8( BfxData *Data, uint8_t BitStartPn, uint8_t BitLn, uint8_t Status );
static inline uint8_t Bfx_GetBits_u8( BfxData Data, uint8_t BitStartPn, uint8_t BitLn );
static inline void Bfx_SetBitMask( BfxData *Data, BfxData Mask );
static inline void Bfx_ClrBitMask( BfxData *Data, BfxData Mask );
static inline bool Bfx_TstBitMask_<InTypeMn><InTypeMn>_u8( <InType> Data, <InType> Mask );
static inline bool Bfx_TstBitLnMask_<InTypeMn><InTypeMn>_u8( <InType> Data, <InType> Mask );
static inline void Bfx_ToggleBits_<TypeMn>( <Type>* Data );
static inline void Bfx_ToggleBitMask_<TypeMn><TypeMn>( <Type>* Data, <Type> Mask );
static inline void Bfx_ShiftBitRt_<TypeMn>u8( <Type>* Data, uint8 ShiftCnt );
static inline void Bfx_ShiftBitLt_<TypeMn>u8( <Type>* Data, uint8 ShiftCnt );
static inline void Bfx_PutBit_<TypeMn>u8u8( <Type>* Data, uint8 BitPn, boolean Status );

static inline void Bfx_SetBit_u8( BfxData *Data, uint8_t BitPn )
{
    if ( Data && BitPn < 8 )
    {
        *Data |= ( 1u << BitPn );
    }
}

static inline void Bfx_ClrBit_u8( BfxData *Data, uint8_t BitPn )
{
    if (Data && BitPn < 8) 
    {
        *Data &= ~( 1u << BitPn );
    }
}

static inline bool Bfx_GetBit_u8( BfxData Data, uint8_t BitPn )
{
    if (BitPn < 8)
    {
        return (Data >> BitPn) & 1u;
    }
    return false;   
}

static inline void Bfx_SetBits_u8( BfxData *Data, uint8_t BitStartPn, uint8_t BitLn, uint8_t Status )
{
    if ( Data && BitStartPn < 8 && BitLn <= 8 )
    {
        uint8_t Mask = ( ( 1U << BitLn ) - 1u ) << BitStartPn;
        Data = ( Data & ~Mask ) | ( ( Status << BitStartPn ) & Mask );
    }
}

static inline uint8_t Bfx_GetBits_u8( BfxData Data, uint8_t BitStartPn, uint8_t BitLn )
{
    if (BitStartPn < 8 && BitLn <= 8) 
    {
        uint8_t Mask = ( (1u << BitLn) - 1u ) << BitStartPn;
        return (Data & Mask) >> BitStartPn;
    }
    return 0; //Default value in case of wrong input values.
}

static inline void Bfx_SetBitMask( BfxData *Data, BfxData Mask )
{
    *Data = *Data | Mask;
}

static inline void Bfx_ClrBitMask( BfxData *Data, BfxData Mask )
{
    *Data = *Data & ~Mask;
}



#endif 
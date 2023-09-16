/**
 * @file    Crc.c
 * @brief   **This file contains the API and the configuration of the AUTOSAR Basic Software module CRC.**
 *
 * The Crc library contains the following routines for CRC calculation
 * • CRC8: SAEJ1850
 * • CRC8H2F: CRC8 0x2F polynomial
 * • CRC16
 * • CRC32
 * • CRC32P4: CRC32 0xF4ACFB13 polynomial
 * • CRC64: CRC-64-ECMA
 *
 * This library was designed like a Runtime calculation:
 * Slower execution, but small code size (no ROM table)
 */

#include "Std_Types.h"
#include "Crc.h"

/**
  * @defgroup Values_CRC8_SAEJ1850 this defines are values for the calculation of CRC with 8 bits
  @{ */
#define CRC8_SAEJ1850_POLYNOMIAL          0x1D /*!< Polynomial of CRC8_SAEJ1850 */
#define FIRSTCALLCRC8                     0xFF /*!< Value of CRC if is first call */
#define CRC8NBITS                         8    /*!< Number of bits of a byte */
#define CRC8MSB                           0x80 /*!< Most significant bit of a byte */
/**
  @} */

/**
  * @defgroup Values_CRC8H2F this defines are values for the calculation of CRC with 8 bits
  @{ */
#define CRC8H2F_POLYNOMIAL                0x2F /*!< Polynomial of CRC8H2F */
#define FIRSTCALLCRC8H2F                  0xFF /*!< Value of CRC if is first call */
#define CRC8H2FNBITS                      8    /*!< Number of bits of a byte */
#define CRC8H2NMSB                        0x80 /*!< Most significant bit of a byte */
/**
  @} */

/**
  * @defgroup Values_CRC16 this defines are values for the calculation of CRC with 16 bits
  @{ */
#define CRC16_POLYNOMIAL                  0x1021 /*!< Polynomial of CRC16 */
#define FIRSTCALLCRC16                    0xFFFF /*!< Value of CRC if is first call */
#define CRC16NBITS                        8      /*!< Number of bits of a byte */
#define CRC16MSB                          0x8000 /*!< Most significant bit of 2 bytes */
#define CRC16_8LEFT                       8      /*!< Number of shift bits on crc calculation */
/**
  @} */

/**
  * @defgroup Values_CRC16ARC this defines are values for the calculation of CRC with 16 bits and data reflected
  @{ */
#define CRC_16BITARC_POLYNOMIAL_REFLECTED (uint16)0xA001 /*!< Polynomial of CRC16ARC */
#define CRC_16BITARC_LSB                  0x00001        /*!< Less significant bit */
/**
  @} */

/**
  * @defgroup Values_CRC32 this defines are values for the calculation of CRC with 16 bits and data reflected
  @{ */
#define CRC_32BIT_POLYNOMIAL_REFLECTED    (uint32)0xEDB88320u /*!< Polynomial of CRC32 */
#define CRC_32BIT_XORVALUE                0xFFFFFFFFu         /*!< Value of CRC if is first call */
#define CRC_32BIT_LSB                     0x00000001u         /*!< Less significant bit */
/**
  @} */

/**
  * @defgroup Values_CRC32P4 this defines are values for the calculation of CRC with 16 bits and data reflected
  @{ */
#define CRC_CRC32P4_POLYNOMIAL_REFLECTED  (uint32)0xC8DF352Fu /*!< Polynomial of CRC32P4 */
#define CRC_32BITP4_XORVALUE              0xFFFFFFFFu         /*!< Value of CRC if is first call */
#define CRC_32BITP4_LSB                   0x00000001u         /*!< Less significant bit */
/**
  @} */

/**
  * @defgroup Values_CRC64 this defines are values for the calculation of CRC with 16 bits and data reflected
  @{ */
#define CRC_CRC64_POLYNOMIAL_REFLECTED    (uint64)0xC96C5795D7870F42UL /*!< Polynomial of CRC64 */
#define CRC_64BIT_XORVALUE                0xFFFFFFFFFFFFFFFFUL         /*!< Value of CRC if is first call */
#define CRC_64BIT_LSB                     0x0000000000000001UL         /*!< Less significant bit */
/**
  @} */

/**
  * @defgroup CRC_VERSION_INFO this defines are values to know the version info about CRC
  @{ */
#define VENDOR_ID                         0x0000 /*!< CRC Vendor ID VALUE */
#define MODULE_ID                         0x0000 /*!< CRC MODULE ID VALUE */
#define CRC_SW_MAJOR_VERSION              0      /*!< CRC_SW_MAJOR_VERSION ID VALUE */
#define CRC_SW_MINOR_VERSION              0      /*!< CRC_SW_MINOR_VERSION ID VALUE */
#define CRC_SW_PATCH_VERSION              0      /*!< CRC_SW_PATCH_VERSION ID VALUE */
/**
  @} */

/**
 * @brief   **Calculate a CRC of 8 bits**
 *
 * The function calculates the a 8 bit CRC according to the standard of AUTOSAR with their respective
 * paramters.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue8 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (8 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00031
 */
uint8 Crc_CalculateCRC8( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = CRC8_SAEJ1850_POLYNOMIAL;
    uint8 crcValue             = Crc_StartValue8;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = FIRSTCALLCRC8;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ];

        for( uint8 bit = 0; bit < CRC8NBITS; bit++ )
        {
            if( ( crcValue & CRC8MSB ) != FALSE )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue ^ 0xFF;
}

/**
 * @brief   **Calculate a CRC of 8 bits with other polynomial 0x2F**
 *
 * The function calculates the a 8 bit CRC according to the standard of AUTOSAR with their respective
 * paramters.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue8H2F Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (8 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00043, SWS_Crc_00044
 */
uint8 Crc_CalculateCRC8H2F( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall )
{
    const uint8 Crc_Polynomial = CRC8H2F_POLYNOMIAL;
    uint8 crcValue             = Crc_StartValue8H2F;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = FIRSTCALLCRC8H2F;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= Crc_DataPtr[ i ];

        for( uint8 bit = 0; bit < CRC8H2FNBITS; bit++ )
        {
            if( ( crcValue & CRC8H2NMSB ) != FALSE )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }
    return ~crcValue;
}

/**
 * @brief   **Calculate a CRC of 16 bits and polynomial of 0x1021**
 *
 * The function calculates the a 16 bit CRC according to the standard of AUTOSAR with their respective
 * paramters.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue16 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (16 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00019, SWS_Crc_00015
 */
uint16 Crc_CalculateCRC16( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall )
{
    const uint16 Crc_Polynomial = CRC16_POLYNOMIAL;
    uint16 crcValue             = Crc_StartValue16;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = FIRSTCALLCRC16;
    }

    for( uint32 i = 0; i < Crc_Length; i++ )
    {
        crcValue ^= (uint16)Crc_DataPtr[ i ] << CRC16_8LEFT;

        for( uint8 bit = 0; bit < CRC16NBITS; bit++ )
        {
            if( ( crcValue & CRC16MSB ) != FALSE )
            {
                crcValue = ( crcValue << 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue <<= 1;
            }
        }
    }

    return crcValue;
}

/**
 * @brief   **Calculate a CRC of 16 bits and polynomial of 0xA001**
 *
 * The function calculates the a 16 bit CRC with data reflected according to the standard of
 * AUTOSAR with their respective paramters.
 *
 * In this case AUTOSAR specify a 0x8005 polynomial but the function need that the input data
 * are relfected so the reflected data of 0x8005 is 0xA001.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue16 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (16 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00071, SWS_Crc_00069
 */
uint16 Crc_CalculateCRC16ARC( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall )
{
    const uint16 Crc_Polynomial = CRC_16BITARC_POLYNOMIAL_REFLECTED;
    uint16 crcValue             = Crc_StartValue16;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = (uint16)0x0000;
    }
    for( uint32 i = Crc_Length; i != 0; i-- )
    {
        crcValue ^= (uint16)*Crc_DataPtr;

        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( ( (crcValue)&CRC_16BITARC_LSB ) != FALSE )
            {
                crcValue = ( crcValue >> 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue >>= 1;
            }
        }
        /* cppcheck-suppress misra-c2012-17.8 ; It's needed to increment the value of the variable*/
        Crc_DataPtr++;
    }
    return crcValue;
}

/**
 * @brief   **Calculate a CRC of 32 bits and polynomial of 0x04C11DB7**
 *
 * The function calculates the a 32 bit CRC with data reflected according to the standard of
 * AUTOSAR with their respective paramters.
 *
 * In this case AUTOSAR specify a 0x04C11DB7 polynomial but the function need that the input data
 * are relfected so the reflected data of 0x04C11DB7 is 0xEDB88320.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue32 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (32 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00020, SWS_Crc_00016
 */
uint32 Crc_CalculateCRC32( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall )
{
    const uint32 Crc_Polynomial = CRC_32BIT_POLYNOMIAL_REFLECTED;
    uint32 crcValue             = Crc_StartValue32;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = CRC_32BIT_XORVALUE;
    }
    else
    {
        crcValue ^= CRC_32BIT_XORVALUE;
    }

    for( uint32 i = Crc_Length; i != 0; i-- )
    {
        crcValue ^= (uint32)*Crc_DataPtr;

        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( ( crcValue & CRC_32BIT_LSB ) != FALSE )
            {
                crcValue = ( crcValue >> 1 ) ^ Crc_Polynomial;
            }
            else
            {
                crcValue >>= 1;
            }
        }
        /* cppcheck-suppress misra-c2012-17.8 ; It's needed to increment the value of the variable*/
        Crc_DataPtr++;
    }
    crcValue ^= CRC_32BIT_XORVALUE;

    return crcValue;
}

/**
 * @brief   **Calculate a CRC of 32 bits and polynomial of F4’AC’FB’13h**
 *
 * The function calculates the a 32 bit CRC with data reflected according to the standard of
 * AUTOSAR with their respective paramters.
 *
 * In this case AUTOSAR specify a F4’AC’FB’13h polynomial but the function need that the input data
 * are relfected so the reflected and is needed to assign the first CRC value the value of their
 * XOR in this case 0xFFFFFFFF.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue32 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (32 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00058
 */
uint32 Crc_CalculateCRC32P4( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall )
{
    uint32 crcValue;
    crcValue = Crc_StartValue32;

    if( Crc_IsFirstCall == TRUE )
    {
        crcValue = CRC_32BITP4_XORVALUE;
    }
    else
    {
        crcValue ^= CRC_32BITP4_XORVALUE;
    }
    for( uint32 i = Crc_Length; i != 0; i-- )
    {
        crcValue ^= (uint32)*Crc_DataPtr;
        for( uint8 bit = 0; bit < 8; bit++ )
        {
            if( ( crcValue & CRC_32BITP4_LSB ) != FALSE )
            {
                crcValue = ( crcValue >> 1 ) ^ CRC_CRC32P4_POLYNOMIAL_REFLECTED;
            }
            else
            {
                crcValue >>= 1;
            }
        }
        /* cppcheck-suppress misra-c2012-17.8 ; It's needed to increment the value of the variable*/
        Crc_DataPtr++;
    }
    crcValue ^= CRC_32BITP4_XORVALUE;

    return crcValue;
}

/**
 * @brief   **Calculate a CRC of 64 bits and polynomial of 42’F0’E1’EB’A9’EA’36’93h**
 *
 * The function calculates the a 32 bit CRC with data reflected according to the standard of
 * AUTOSAR with their respective paramters.
 *
 * In this case AUTOSAR specify a 42’F0’E1’EB’A9’EA’36’93h polynomial but the function need that the input data
 * are relfected so the reflected and is needed to assign the first CRC value the value of their
 * XOR in this case 0xFFFFFFFFFFFFFFFF.
 *
 * First is necessary to know if is the first time to use the function and it is assigned a value
 * for our CRC calculation.
 * The function calculates the CRC through a for cycle, one of them is to know what of all bytes
 * is in the calculation and the other is to move the bit of the respective byte.
 *
 * The function uses bit shift to calculate the CRC according with the process.
 *
 * @param   Crc_DataPtr Pointer to start address of data block to be calculated.
 * @param   Crc_Length Length of data block to be calculated in bytes.
 * @param   Crc_StartValue64 Start value when the algorithm starts.
 * @param   Crc_IsFirstCall boolean variable to know if is the first time that we used the function.
 *
 * @retval  crcValue the value of crc (64 bits) according with parameters and specifications of this function 
 *
 * @reqs   SWS_Crc_00061
 */
uint64 Crc_CalculateCRC64( const uint8 *Crc_DataPtr, uint32 Crc_Length, uint64 Crc_StartValue64, boolean Crc_IsFirstCall )
{
    uint64 crcValue;
    crcValue = Crc_StartValue64;
    if( Crc_Length != 0 )
    {
        if( Crc_IsFirstCall == TRUE )
        {
            crcValue = CRC_64BIT_XORVALUE;
        }
        else
        {
            crcValue ^= CRC_64BIT_XORVALUE;
        }
        for( uint32 i = Crc_Length; i != 0; i-- )
        {
            crcValue ^= (uint64)*Crc_DataPtr;
            for( uint8 bit = 0; bit < 8; bit++ )
            {
                if( ( crcValue & CRC_64BIT_LSB ) != FALSE )
                {
                    crcValue = ( crcValue >> 1 ) ^ CRC_CRC64_POLYNOMIAL_REFLECTED;
                }
                else
                {
                    crcValue >>= 1;
                }
            }
            /* cppcheck-suppress misra-c2012-17.8 ; It's needed to increment the value of the variable*/
            Crc_DataPtr++;
        }
        crcValue ^= CRC_64BIT_XORVALUE;
    }
    return crcValue;
}

/**
 * @brief   **Fuunction to assign values to VersionInfo structure**
 *
 * This service returns the version information of this module.
 *
 * The function assign values to VersionInfo structure to know the vendorID, moduleID,
 * sw_major_version, sw_minor_version and sw_patch_version.
 *
 * The function returns a TRUE if the members of structure have a value this part of
 * code is inly for test porpuses.
 *
 * @param   Versioninfo Variable that locates the version information of CRC.
 *
 * @retval  status
 *
 * @reqs   SWS_Crc_00021
 */
uint8 Crc_GetVersionInfo( Std_VersionInfoType *Versioninfo )
{
    /*For test only*/
    uint8 status = FALSE;

    /*Real code*/
    Versioninfo->vendorID         = VENDOR_ID;
    Versioninfo->moduleID         = MODULE_ID;
    Versioninfo->sw_major_version = CRC_SW_MAJOR_VERSION;
    Versioninfo->sw_minor_version = CRC_SW_MINOR_VERSION;
    Versioninfo->sw_patch_version = CRC_SW_PATCH_VERSION;

    /*For test only*/

    if( ( ( Versioninfo->vendorID ) && ( Versioninfo->moduleID ) ) == FALSE )
    {
        status = TRUE;
    }

    return status;
}
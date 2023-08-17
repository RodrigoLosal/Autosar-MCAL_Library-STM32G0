/**
 * @file    Platform_Types.h
 * @brief   **Specification of Platform Types**
 *
 * This file contains all platform dependent types and symbols. Those types must be abstracted in
 * order to be-come platform and compiler independent. It is required that all platform types files
 * are unique within the AUTOSAR community to guarantee unique types per platform and to avoid type
 * changes when moving a software module from platform A to B.
 */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#include <stdbool.h>

/**
 * @name   CPU_Types
 * Symbols that specify the CPU type according to its own arquitecture (8, 16, 32 or 64 bits)
 *
 * @reqs    SWS_Platform_00045, SWS_Platform_00064
 */
/**@{*/
#define CPU_TYPE_8      8  /*!< Define a 8 bit CPU, ejem. PIC18F, ATmega, STM8 etc.. */
#define CPU_TYPE_16     16 /*!< Define a 16 bit CPU, ejem. PIC24F, S12, xMega etc.. */
#define CPU_TYPE_32     32 /*!< Define a 32 bit CPU, ejem. PIC132MX, STM32, TC2xx etc.. */
#define CPU_TYPE_64     64 /*!< Define a 64 bit CPU, ejem. ARMv8, x86 etc.. */
/**@}*/


/**
 * @name    Bit_order
 * Symbols to specify the bit order according to the CPU endianess, LSB for little endian and MSB
 * for big endian
 *
 * @reqs    SWS_Platform_00038
 */
/**@{*/
#define MSB_FIRST       0 /*!< CPU with most significant bit aranged first */
#define LSB_FIRST       1 /*!< CPU with least significant bit aranged first */
/**@}*/


/**
 * @name    Byte_order
 * Symbols to specify the endianess types of the CPU
 *
 * @reqs    SWS_Platform_00039
 */
/**@{*/
#define HIGH_BYTE_FIRST 0 /*!< Define a CPU with a big endian arquitecture */
#define LOW_BYTE_FIRST  1 /*!< Define a CPU with a little endian arquitecture */
/**@}*/


/**
 * @name    CPU_Definition
 * Specifies the CPU data and endianess arquitecture. In this case the values correspond to the mcu
 * stm32g0xx wich has a little endian 32 bits CPU
 *
 * @reqs    SWS_Platform_00046, SWS_Platform_00043, SWS_Platform_00044, SWS_Platform_00048,
 *          SWS_Platform_00049, SWS_Platform_00050, SWS_Platform_00051, SWS_Platform_00052
 */
/**@{*/
#define CPU_TYPE        CPU_TYPE_32    /*!< Indicate the CPU type (8,16,32 or 64 bits) */
#define CPU_BIT_ORDER   LSB_FIRST      /*!< CPU bit order (lsb or msb) */
#define CPU_BYTE_ORDER  LOW_BYTE_FIRST /*!< Endianess type little or big */
/**@}*/

/**
 * @name    boolean_values
 * Symbols to specify true and false values
 *
 * @reqs    SWS_Platform_00056, SWS_Platform_00054, SWS_Platform_00055
 */
/**@{*/
#ifndef TRUE
#define TRUE 1 /*!< Boolean representation of true */
#endif

#ifndef FALSE
#define FALSE 0 /*!< Boolean representation of false */
#endif
/**@}*/

/**
 * @name    unsigned_types
 * Cross platform type definitions to declare unsigned integer variables of  8, 16, 32, 64 and
 * boolean values
 *
 * @reqs    SWS_Platform_00027, SWS_Platform_00034, SWS_Platform_00026, SWS_Platform_00013,
 *          SWS_Platform_00014, SWS_Platform_00015, SWS_Platform_00066
 */
/**@{*/
typedef bool boolean;              /*!< standar type that represents values TRUE or FALSE */
typedef unsigned char uint8;       /*!< standar type to declare one byte variables that store values
                                    in the range 0..255*/
typedef unsigned short uint16;     /*!< standar type to declare two byte variables that store values
                                    in the range 0..65,535 */
typedef unsigned int uint32;       /*!< standar type to declare four byte variables that store values
                                    in the range 0..4,294,967,295 */
typedef unsigned long long uint64; /*!< standar type to declare eight byte variables that store
                                    values in the range 0..18,446,744,073,709,551,615 */
/**@}*/


/**
 * @name    signed_types
 * Cross platform type definitions to declare signed integer variables of  8, 16, 32 and 64 values
 *
 * @reqs    SWS_Platform_00016, SWS_Platform_00017, SWS_Platform_00018, SWS_Platform_00067
 */
/**@{*/
typedef signed char sint8;       /*!< standar type to declare one byte variables that store values in the
                                range 128..+127 */
typedef signed short sint16;     /*!< standar type to declare two byte variables that store values in
                                the range -32,768..+32,767 */
typedef signed int sint32;       /*!< standar type to declare four byte variables that store values in the
                                range -2,147,483,648..+2,147,483,647 */
typedef signed long long sint64; /*!< standar type to declare eight byte variables that store values
                                in the range -9,223,372,036,854,775,808..+9,223,372,036,854,775,807 */
/**@}*/


/**
 * @name    unsigned_least
 * Cross platform type definitions to declare max or min ranges of unsigned 8, 16 and 32 values
 *
 * @reqs    SWS_Platform_00020, SWS_Platform_00021, SWS_Platform_00022
 */
/**@{*/
typedef unsigned long uint8_least;  /*!< standar type to declare max or min ranges for an unsigned
                                       one byte variable */
typedef unsigned long uint16_least; /*!< standar type to declare max or min ranges for an unsigned
                                        two byte variable */
typedef unsigned long uint32_least; /*!< standar type to declare max or min ranges for an unsigned
                                       four byte variable */
/**@}*/


/**
 * @name    signed_least
 * Cross platform type definitions to declare max or min ranges of signed 8, 16 and 32 values
 *
 * @reqs    SWS_Platform_00023, SWS_Platform_00024, SWS_Platform_00025
 */
/**@{*/
typedef signed long sint8_least;  /*!< standar type to declare max or min ranges for a signed one
                                   byte variable */
typedef signed long sint16_least; /*!< standar type to declare max or min ranges for a signed two
                                    byte variable */
typedef signed long sint32_least; /*!< standar type to declare max or min ranges for a signed four
                                   byte variable */
/**@}*/


/**
 * @name    floating_point
 * Cross platform type definitions to declare floating point variables of single and double presicion
 *
 * @reqs    SWS_Platform_00041, SWS_Platform_00042
 */
/**@{*/
typedef float float32;  /*!< standar type to declare single precision floating point variables in the
                          range of -3.4028235e+38..+3.4028235e+38 */
typedef double float64; /*!< standar type to declare double precision floating point variables in
                           the range of -1.7976931348623157e+308..+1.7976931348623157e+308 */
/**@}*/


/**
 * @name    void_pointers
 * Cross platform type definitions to declare void pointers
 *
 * @reqs    SWS_Platform_91001, SWS_Platform_91002
 */
/**@{*/
typedef void *VoidPtr;            /*!< standar type to declare void pointers, his type shall be used
                                    for buffers that contain data returned to the caller */
typedef const void *ConstVoidPtr; /*!< standar type to declare constant void pointers. This type
                                    shall be used for buffers that are passed to the callee */
/**@}*/


#endif /* PLATFORM_TYPES_H */

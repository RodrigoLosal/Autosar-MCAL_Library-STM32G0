/**
 * @file    Gpt_Types.h
 * @brief   **Gpt Driver Types**
 * @author  Rodrigo Lopez
 *
 * The header contains the type definitions that are used by the Gpt module. The file is implemented
 * as a means of abstraction from the hardware, making the low level interfaces available for upper layers.
 */
#ifndef GPT_TYPES_H__
#define GPT_TYPES_H__

#include "Registers.h"

/**
 * @brief **Definition of the external data structure containing the initialization data**
 *
 * This is the type of the data structure including the configuration set required for
 * initializing the GPT timer unit.
 *
 * @note It is the responsibility of the user to ensure that the values defined in this structure are
 * valid and appropriate, as the GPT Driver does not perform any validation. The values must be generated
 * and validated within the code generation tool.
 *
 * @reqs   SWS_Gpt_00357
 */
typedef struct _Gpt_ConfigType
{
    uint8 GptChannelId;                /*!< Gpt Channel to be configured */
    uint8 GptReference;                /*!< Microcontroller specific Timer reference */
    uint8 GptChannelMode;              /*!< Continuous or One-Pulse mode*/
    uint16 GptChannelPrescaler;        /*!< Prescaler from 0x0 to 0xFFFF*/
    void ( *GptNotification )( void ); /*!< Array of Pointers to user-defined functions*/
} Gpt_ConfigType;

/**
 * @brief **Numeric ID of a GPT channel**
 *
 * @reqs   SWS_Gpt_00358
 */
typedef enum
{
    GPT_CHANNEL_0 = 0,  /*!< Gpt Channel 0 */
    GPT_CHANNEL_1,      /*!< Gpt Channel 1 */
} Gpt_ChannelType;

/**
 * @brief **Type for reading and setting the timer values (in number of ticks).**
 *
 * @reqs   SWS_Gpt_00359
 */
typedef uint32 Gpt_ValueType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware
 * unit pointers to controller structures.
 */
typedef struct _Gpt_HwUnit
{
    const Gpt_ConfigType *Config; /*!< Pointer to the configuration structure */
} Gpt_HwUnit;

#endif /* GPT_TYPES_H__ */
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
 * @defgroup GPT_Ids GPT Id number for module and each API service
 *
 * @{ */
#define GPT_ID_                      0x00u /*!< Gpt_Init() api service id */
#define GPT_ID_INIT                  0x01u /*!< Gpt_DeInit() api service id */
#define GPT_ID_DEINIT                0x02u /*!< Gpt_GetTimeElapsed() api service id */
#define GPT_ID_GET_TIME_REMAINING    0x03u /*!< Gpt_GetTimeRemaining() api service id */
#define GPT_ID_START_TIMER           0x04u /*!< Gpt_StartTimer() api service id */
#define GPT_ID_STOP_TIMER            0x05u /*!< Gpt_StopTimer() api service id */
#define GPT_ID_GET_VERSION_INFO      0x06u /*!< Gpt_GetVersionInfo() api service id */
#define GPT_ID_ENABLE_NOTIFICATION   0x07u /*!< Gpt_EnableNotification() api service id */
#define GPT_ID_DISABLE_NOTIFICATION  0x08u /*!< Gpt_DisableNotification() api service id */
#define GPT_ID_NOTIFICATION_CHANNEL0 0x09u /*!< Gpt_Notification_Channel0() api service id */
#define GPT_ID_NOTIFICATION_CHANNEL1 0x0Au /*!< Gpt_Notification_Channel1() api service id */
/**
 * @} */

/**
 * @brief **Config Elements of a GPT**
 *
 * @reqs   SWS_Gpt_00358
 */
typedef struct _Gpt_ChannelType
{
    uint8 GptChannelId;                /*!< Gpt Channel to be configured */
    uint8 GptReference;                /*!< Microcontroller specific Timer reference */
    uint8 GptChannelMode;              /*!< Continuous or One-Pulse mode*/
    uint16 GptChannelPrescaler;        /*!< Prescaler from 0x0 to 0xFFFF*/
    void ( *GptNotification )( void ); /*!< Array of Pointers to user-defined functions*/
} Gpt_ChannelConfigType;

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
    Gpt_ChannelConfigType *Channels; /*!< Pointer to the structure with the channel configuration elements. */
    uint8 NumberOfChannels;          /*!< Total number of GPT channels available. */
} Gpt_ConfigType;

/**
 * @brief **Numeric ID of a GPT channel**
 *
 * @reqs   SWS_Gpt_00358
 */
typedef enum
{
    GPT_CHANNEL_0 = 0, /*!< Gpt Channel 0 */
    GPT_CHANNEL_1      /*!< Gpt Channel 1 */
} Gpt_ChannelType;

/**
 * @brief **Type for reading and setting the timer values (in number of ticks).**
 *
 * @reqs   SWS_Gpt_00359
 */
typedef uint32 Gpt_ValueType;

#endif /* GPT_TYPES_H__ */
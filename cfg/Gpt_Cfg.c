#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"

// clang-format off
const Gpt_ConfigType GptConfig[ GPT_NUMBER_OF_CHANNELS ] =
{
    {
        .GptChannelId                       = GPT_CHANNEL_0,
        .GptChannelMode                     = TEST_GPT_CH_MODE_CONTINUOUS,
        .GptChannelPrescaler                = 0x0000FFFF,
        .GptNotification[ GPT_CHANNEL_0 ]   = NULL_PTR
    },
    {
        .GptChannelId                       = GPT_CHANNEL_1,
        .GptChannelMode                     = TEST_GPT_CH_MODE_ONESHOT,
        .GptChannelPrescaler                = 0x000000001,
        .GptNotification[ GPT_CHANNEL_1 ]   = NULL_PTR
    }
};
// clang-format on
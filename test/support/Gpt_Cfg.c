#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"

const Gpt_ConfigType GptConfig[ GPT_NUMBER_OF_CHANNELS ] =
{
{ .GptChannelId        = GPT_CHANNEL_0,
  .GptChannelMode      = GPT_CH_MODE_CONTINUOUS,
  .GptChannelPrescaler = 0x0000FFFF },
{ .GptChannelId        = GPT_CHANNEL_1,
  .GptChannelMode      = GPT_CH_MODE_ONESHOT,
  .GptChannelPrescaler = 0x000000001 } };
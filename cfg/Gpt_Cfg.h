#ifndef GPT_CFG_H_
#define GPT_CFG_H_

#define GPT_NUMBER_OF_CHANNELS              2u

#define TEST_GPT_CH_MODE_CONTINUOUS         0
#define TEST_GPT_CH_MODE_ONESHOT            1u

#define GPT_DEINIT_API                      STD_ON
#define GPT_TIME_ELAPSED_API                STD_ON
#define GPT_TIME_REMAINING_API              STD_ON
#define GPT_VERSION_INFO_API                STD_ON
#define GPT_ENABLE_DISABLE_NOTIFICATION_API STD_ON

#define GPT_VENDOR_ID                       (uint16)1000u
#define GPT_MODULE_ID                       (uint16)120u
#define GPT_SW_MAJOR_VERSION                (uint8)1u
#define GPT_SW_MINOR_VERSION                (uint8)0u
#define GPT_SW_PATCH_VERSION                (uint8)0u

extern const Gpt_ConfigType GptConfig[ GPT_NUMBER_OF_CHANNELS ];

#endif /* GPT_CFG_H_ */
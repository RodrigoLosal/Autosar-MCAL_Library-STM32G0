/**
 * @file    test_Gpt.c
 * @brief   **Unit testing for the GPT (General Purpose Timer) module in AUTOSAR.**
 *
 * This file contains unit tests for the GPT module functionality. It includes test cases for various
 * features such as initialization, deinitialization, start, stop, get timer values, etc. The tests
 * are designed to ensure the correct behavior and reliability of the GPT module in compliance with
 * AUTOSAR standards.
 */
#include "unity.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"

/*mock microcontroller registers with its initial values*/
/*                             CR1     CR2     Res0  DIER    SR      EGR        Res1     CNT         PSC     ARR */
Gpt_RegisterType TIM6_BASE = { 0x0000, 0x0000, 0x00, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00000000, 0x0000, 0xFFFF };
Gpt_RegisterType TIM7_BASE = { 0x0000, 0x0000, 0x00, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00000000, 0x0000, 0xFFFF };

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    Gpt_Init( GptConfig );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct channel ID in the config
 * structure of the Channel 0.
 */
void test__Gpt_Init__CH0_CHID( void )
{
    TEST_ASSERT_EQUAL_HEX32( GPT_CHANNEL_0, GptConfig[ GPT_CHANNEL_0 ].GptChannelId );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct values in the register
 * PSC from the TIM6 module.
 */
void test__Gpt_Init__CH0_PSC( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0xFFFF, TIM6->PSC );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct value in the bit OPM
 * of the register CR1 from the TIM6 module.
 */
void test__Gpt_Init__CH0_CR1_OPM( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct value in the register
 * SR from the TIM6 module.
 */
void test__Gpt_Init__CH0_SR( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->SR );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct channel ID in the config
 * structure of the Channel 1.
 */
void test__Gpt_Init__CH1_CHID( void )
{
    TEST_ASSERT_EQUAL_HEX32( GPT_CHANNEL_1, GptConfig[ GPT_CHANNEL_1 ].GptChannelId );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct values in the register
 * PSC from the TIM7 module.
 */
void test__Gpt_Init__CH1_PSC( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x0F, TIM7->PSC );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct value in the bit OPM
 * of the register CR1 from the TIM7 module.
 */
void test__Gpt_Init__CH1_CR1_OPM( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x08, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_Init function
 *
 * This test will check if the Gpt_Init function is setting the correct value in the register
 * SR from the TIM7 module.
 */
void test__Gpt_Init__CH1_SR( void )
{
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM7->SR );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct values in the register
 * PSC from the TIM6 module.
 */
void test__Gpt_DeInit__CH0_PSC( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->PSC );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct value in the bit OPM
 * of the register CR1 from the TIM6 module.
 */
void test__Gpt_DeInit__CH0_CR1_OPM( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct value in the register
 * SR from the TIM6 module.
 */
void test__Gpt_DeInit__CH0_SR( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->SR );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct values in the register
 * ARR from the TIM6 module.
 */
void test__Gpt_DeInit__CH0_ARR( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFF, TIM6->ARR );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct values in the register
 * PSC from the TIM7 module.
 */
void test__Gpt_DeInit__CH1_PSC( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM7->PSC );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct value in the bit OPM
 * of the register CR1 from the TIM6 module.
 */
void test__Gpt_DeInit__CH1_CR1_OPM( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct value in the register
 * SR from the TIM7 module.
 */
void test__Gpt_DeInit__CH1_SR( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM7->SR );
}

/**
 * @brief   Test the Gpt_DeInit function
 *
 * This test will check if the Gpt_DeInit function is resetting the correct values in the register
 * ARR from the TIM7 module.
 */
void test__Gpt_DeInit__CH1_ARR( void )
{
    Gpt_DeInit( );
    TEST_ASSERT_EQUAL_HEX32( 0xFFFF, TIM7->ARR );
}

/**
 * @brief   Test the Gpt_GetTimeElapsed function
 *
 * This test will check if the Gpt_GetTimeElapsed function is delivering the correct values from the
 * CNT register of the TIM6 module.
 */
void test__Gpt_GetTimeElapsed__CH0( void )
{
    TIM6->CNT                     = 0xAAAA;
    Gpt_ValueType TestTimeElapsed = Gpt_GetTimeElapsed( GPT_CHANNEL_0 );
    TEST_ASSERT_EQUAL_HEX32( 0xAAAA, TestTimeElapsed );
}

/**
 * @brief   Test the Gpt_GetTimeElapsed function
 *
 * This test will check if the Gpt_GetTimeElapsed function is delivering the correct values from the
 * CNT register of the TIM7 module.
 */
void test__Gpt_GetTimeElapsed__CH1( void )
{
    TIM7->CNT                     = 0x0101;
    Gpt_ValueType TestTimeElapsed = Gpt_GetTimeElapsed( GPT_CHANNEL_1 );
    TEST_ASSERT_EQUAL_HEX32( 0x0101, TestTimeElapsed );
}

/**
 * @brief   Test the Gpt_GetTimeRemaining function
 *
 * This test will check if the Gpt_GetTimeRemaining function is delivering the correct result by
 * making the following operation with the values of these registers of the TIM6 module:
 * ARR - CNT
 */
void test__Gpt_GetTimeRemaining__CH0( void )
{
    TIM6->ARR                       = 0xBBBB;
    Gpt_ValueType TestTimeRemaining = Gpt_GetTimeRemaining( GPT_CHANNEL_0 );
    TEST_ASSERT_EQUAL_HEX32( 0x1111, TestTimeRemaining );
}

/**
 * @brief   Test the Gpt_GetTimeRemaining function
 *
 * This test will check if the Gpt_GetTimeRemaining function is delivering the correct result by
 * making the following operation with the values of these registers of the TIM7 module:
 * ARR - CNT
 */
void test__Gpt_GetTimeRemaining__CH1( void )
{
    TIM7->ARR                       = 0x2222;
    Gpt_ValueType TestTimeRemaining = Gpt_GetTimeRemaining( GPT_CHANNEL_1 );
    TEST_ASSERT_EQUAL_HEX32( 0x2121, TestTimeRemaining );
}

/**
 * @brief   Test the Gpt_StartTimer function
 *
 * This test will check if the Gpt_StartTimer function is loading the correct values to the
 * ARR register of the TIM6 module.
 */
void test__Gpt_StartTimer__CH0_ARR( void )
{
    Gpt_StartTimer( GPT_CHANNEL_0, 0xF000 );
    TEST_ASSERT_EQUAL_HEX32( 0xF000, TIM6->ARR );
}

/**
 * @brief   Test the Gpt_StartTimer function
 *
 * This test will check if the Gpt_StartTimer function is setting the correct value in the bit CEN
 * of the register CR1 from the TIM6 module.
 */
void test__Gpt_StartTimer__CH0_CR1_CEN( void )
{
    Gpt_StartTimer( GPT_CHANNEL_0, 0xF000 );
    TEST_ASSERT_EQUAL_HEX32( 0x01, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_StartTimer function
 *
 * This test will check if the Gpt_StartTimer function is loading the correct values to the
 * ARR register of the TIM7 module.
 */
void test__Gpt_StartTimer__CH1_ARR( void )
{
    Gpt_StartTimer( GPT_CHANNEL_1, 0xF0 );
    TEST_ASSERT_EQUAL_HEX32( 0xF0, TIM7->ARR );
}

/**
 * @brief   Test the Gpt_StartTimer function
 *
 * This test will check if the Gpt_StartTimer function is setting the correct value in the bit CEN
 * of the register CR1 from the TIM7 module.
 */
void test__Gpt_StartTimer__CH1_CR1_CEN( void )
{
    Gpt_StartTimer( GPT_CHANNEL_1, 0xF000 );
    TEST_ASSERT_EQUAL_HEX32( 0x09, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_StopTimer function
 *
 * This test will check if the Gpt_StopTimer function is resetting the value in the bit CEN
 * of the register CR1 from the TIM6 module.
 */
void test__Gpt_StopTimer__CH0_CR1_CEN( void )
{
    Gpt_StopTimer( GPT_CHANNEL_0 );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_StopTimer function
 *
 * This test will check if the Gpt_StopTimer function is resetting the value in the bit CEN
 * of the register CR1 from the TIM7 module.
 */
void test__Gpt_StopTimer__CH1_CR1_CEN( void )
{
    Gpt_StopTimer( GPT_CHANNEL_1 );
    TEST_ASSERT_EQUAL_HEX32( 0x08, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_GetVersionInfo
 *
 * This test will check if the Gpt_GetVersionInfo function is giving the correct values
 */
void test__Gpt_GetVersionInfo( void )
{
    Std_VersionInfoType test;
    Gpt_GetVersionInfo( &test );
    TEST_ASSERT_EQUAL_HEX32( 0, test.moduleID );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_major_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_minor_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.sw_patch_version );
    TEST_ASSERT_EQUAL_HEX32( 0, test.vendorID );
}

/**
 * @brief   Test the Gpt_EnableNotification function
 *
 * This test will check if the Gpt_EnableNotification function is resetting the value in the bit UDIS
 * of the register CR1 from the TIM6 module. Note that this bit requires a 0 to enable and a 1 to
 * disable notifications.
 */
void test__Gpt_EnableNotification__CH0_CR1_UDIS( void )
{
    Gpt_EnableNotification( GPT_CHANNEL_0 );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_EnableNotification function
 *
 * This test will check if the Gpt_EnableNotification function is resetting the value in the bit UDIS
 * of the register CR1 from the TIM7 module. Note that this bit requires a 0 to enable and a 1 to
 * disable notifications.
 */
void test__Gpt_EnableNotification__CH1_CR1_UDIS( void )
{
    Gpt_EnableNotification( GPT_CHANNEL_1 );
    TEST_ASSERT_EQUAL_HEX32( 0x08, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_DisableNotification function
 *
 * This test will check if the Gpt_DisableNotification function is setting the value in the bit UDIS
 * of the register CR1 from the TIM6 module. Note that this bit requires a 0 to enable and a 1 to
 * disable notifications.
 */
void test__Gpt_DisableNotification__CH0_CR1_UDIS( void )
{
    Gpt_DisableNotification( GPT_CHANNEL_0 );
    TEST_ASSERT_EQUAL_HEX32( 0x02, TIM6->CR1 );
}

/**
 * @brief   Test the Gpt_DisableNotification function
 *
 * This test will check if the Gpt_DisableNotification function is setting the value in the bit UDIS
 * of the register CR1 from the TIM7 module. Note that this bit requires a 0 to enable and a 1 to
 * disable notifications.
 */
void test__Gpt_DisableNotification__CH1_CR1_UDIS( void )
{
    Gpt_DisableNotification( GPT_CHANNEL_1 );
    TEST_ASSERT_EQUAL_HEX32( 0x0A, TIM7->CR1 );
}

/**
 * @brief   Test the Gpt_Notification_Channel0 function
 *
 * The test will check if, when the TIMx_SR interruptions flag is activated, its verification
 * and reset are carried out correctly within the notification function.
 */
void test__Gpt_Notification__CH0( void )
{
    TIM6->SR = 0x01;
    Gpt_Notification_Channel0( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM6->SR );
}

/**
 * @brief   Test the Gpt_Notification_Channel1 function
 *
 * The test will check if, when the TIMx_SR interruptions flag is activated, its verification
 * and reset are carried out correctly within the notification function.
 */
void test__Gpt_Notification__CH1( void )
{
    TIM7->SR = 0x01;
    Gpt_Notification_Channel1( );
    TEST_ASSERT_EQUAL_HEX32( 0x00, TIM7->SR );
}
#include "unity.h"
#include "Registers.h"
#include "Nvic.h"

/*mock microcontroller registers with its initial values*/
/*                         ISER  RESERVED  ICER RESERVED ISPR RESERVED ICPR RESERVED RESERVED IP*/
Nvic_RegisterType NVIC_BASE = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };

/**
  * @defgroup MinMaxValues representing the minimum and maximum irq value
  @{ */
#define NVIC_MIN_IRQ     16U /*!< Minimum IQR value */
#define NVIC_MAX_IRQ     30U /*!< Maximum IRQ value*/
#define NVIC_IRQ         23U /*!< IRQ value within the accepted range*/
/**
  @} */

/**
* @defgroup Values representing return values
@{ */
#define IRQ_NOT_PENDING  0UL   /*!< Value to specifie IRQ is not pending */
#define INVALID_PRIORITY 0xFFU /*!< Invalid priority indicator */
/**
@} */

#define IP_IDX( irq )    ( ( ( (uint32)( irq ) ) >> 2UL ) ) /*!< Calculate the index for IRQ priority register */
#define FIRST_INDEX      0U                                 /*!< Starting index for NVIC register */


/**
 * @brief   **setUp**
 *
 * This function is required by Ceedling to run any code before the test cases.
 */
void setUp( void )
{
}

/**
 * @brief   **tearDown**
 *
 * This function is required by Ceedling to run any code before the test cases.
 */
void tearDown( void )
{
}

/**
 * @brief   **Test priority setting for an upper NVIC_MAX_IRQ irq**
 *
 * This test validates if setting the priority 2 of an upper NVIC_MAX_IRQ irq is not reflected in
 * the IP register.
 */
void test__CDD_Nvic_SetPriority_UpperMaxIrq( void )
{
    Nvic_IrqType irq    = NVIC_MAX_IRQ + 1;
    uint32 priority     = 2;
    uint32 expected_IPR = 0x00000000;

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, NVIC->IP[ IP_IDX( irq ) ] );
}

/**
 * @brief   **Test priority setting for NVIC_MAX_IRQ irq**
 *
 * This test validates if setting the priority 2 of NVIC_MAX_IRQ irq is correctly reflected in
 * the IP register.
 */
void test__CDD_Nvic_SetPriority_MaxIrq( void )
{
    Nvic_IrqType irq    = NVIC_MAX_IRQ;
    uint32 priority     = 2;
    uint32 expected_IPR = 0x00800000;

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, NVIC->IP[ IP_IDX( irq ) ] );
}

/**
 * @brief   **Test priority setting for NVIC_MIN_IRQ irq**
 *
 * This test validates if setting the priority 2 of NVIC_MIN_IRQ irq is correctly reflected in
 * the IP register.
 */
void test__CDD_Nvic_SetPriority_MinIrq( void )
{
    Nvic_IrqType irq    = NVIC_MIN_IRQ;
    uint32 priority     = 2;
    uint32 expected_IPR = 0x00000080;

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, NVIC->IP[ IP_IDX( irq ) ] );
}

/**
 * @brief   **Test set priority checks the used register is correct **
 *
 * This test checks if the priority is setting in the right register IP_IDX ( irq ) .
 */
void test__CDD_Nvic_SetPriority_IP_IDX( void )
{
    Nvic_IrqType irq    = NVIC_IRQ;
    uint32 priority     = 2;
    uint32 expected_IPR = 5;

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, IP_IDX( irq ) );
}

/**
 * @brief   **Test priority setting for a valid IRQ**
 *
 * This test validates if setting the priority 2 of IRQ number 23 is correctly reflected in
 * the IP register.
 */
void test__CDD_Nvic_SetPriority_ValidIrq( void )
{
    Nvic_IrqType irq    = NVIC_IRQ;
    uint32 priority     = 2;
    uint32 expected_IPR = 0x80000000; /* 1000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, NVIC->IP[ IP_IDX( irq ) ] );
}

/**
 * @brief   **Test priority setting for a minior NVIC_MIN_IRQ irq**
 *
 * This test validates if setting the priority 2 of a minior NVIC_MIN_IRQ irq is not reflected
 * in the IP register.
 */
void test__CDD_Nvic_SetPriority_MiniorMinIrq( void )
{
    Nvic_IrqType irq    = NVIC_MIN_IRQ - 1;
    uint32 priority     = 2;
    uint32 expected_IPR = 0x0000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_SetPriority( irq, priority );
    TEST_ASSERT_EQUAL_HEX32( expected_IPR, NVIC->IP[ IP_IDX( irq ) ] );
}

/**
 * @brief   **Test get the priority for an upper NVIC_Max_IRQ irq**
 *
 * This test validates if the function CDD_Nvic_GetPriority gets the INVALID_PRIORITY value
 * for a invalid IRQ number.
 */
void test__CDD_Nvic_GetPriority_UpperMaxIrq( void )
{
    Nvic_IrqType irq        = NVIC_MAX_IRQ + 1;
    uint32 expectedPriority = INVALID_PRIORITY;

    uint32 priority = CDD_Nvic_GetPriority( irq );
    TEST_ASSERT_EQUAL_HEX32( expectedPriority, priority );
}

/**
 * @brief   **Test get the priority for a valid IRQ**
 *
 * This test validates if the function CDD_Nvic_GetPriority gets correctly the priority for a
 * valid IRQ number.
 */
void test__CDD_Nvic_GetPriority_ValidIrqPriotity( void )
{
    Nvic_IrqType irq        = NVIC_IRQ;
    uint32 expectedPriority = 2;

    uint32 priority = CDD_Nvic_GetPriority( irq );
    TEST_ASSERT_EQUAL_HEX32( expectedPriority, priority );
}

/**
 * @brief   **Test get the priority for a minior NVIC_Min_IRQ irq**
 *
 * This test validates if the function CDD_Nvic_GetPriority gets the INVALID_PRIORITY value
 * for a minior NVIC_Min_IRQ irq.
 */
void test__CDD_Nvic_GetPriority_MiniorMinIrq( void )
{
    Nvic_IrqType irq        = NVIC_MIN_IRQ - 1;
    uint32 expectedPriority = CDD_Nvic_GetPriority( irq );

    TEST_ASSERT_EQUAL_HEX32( INVALID_PRIORITY, expectedPriority );
}

/**
 * @brief   **Test enable an upper NVIC_Min_IRQ irq**
 *
 *This test validates that when enabling a Upper NVIC_Max_IRQ irq using the CDD_Nvic_EnableIrq function,
 *the corresponding value in the ISER register is not updated.
 */
void test__CDD_Nvic_EnableIrq_MaxIrq( void )
{
    Nvic_IrqType irq     = NVIC_MAX_IRQ + 1;
    uint32 expected_ISER = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_EnableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISER, NVIC->ISER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test enable a minior NVIC_Min_IRQ irq**
 *
 *This test validates that when enabling a minior NVIC_Min_IRQ irq using the CDD_Nvic_EnableIrq function,
 *the corresponding value in the ISER register is not updated.
 */
void test__CDD_Nvic_EnableIrq_MiniorMinIrq( void )
{
    Nvic_IrqType irq     = NVIC_MIN_IRQ - 1;
    uint32 expected_ISER = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_EnableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISER, NVIC->ISER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test enable a valid IRQ**
 *
 *This test validates that when enabling a valid IRQ using the CDD_Nvic_EnableIrq function,
 *the corresponding value in the ISER register is updated correctly.
 */
void test__CDD_Nvic_EnableIrq_ValidIrq( void )
{
    Nvic_IrqType irq     = NVIC_IRQ;
    uint32 expected_ISER = 0x00800000; /* 0000 0000 1000 0000 0000 0000 0000 0000 */

    CDD_Nvic_EnableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISER, NVIC->ISER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test disable a valid IRQ**
 *
 *This test validates that when disabling a valid IRQ using the CDD_Nvic_DisableIrq function,
 *the corresponding value in the ICER register is updated correctly.
 */
void test__CDD_Nvic_DisableIrq_ValidIrq( void )
{
    NVIC->ICER[ FIRST_INDEX ] = 0x00000000;
    Nvic_IrqType irq          = NVIC_IRQ;
    uint32 expected_ICER      = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_DisableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICER, NVIC->ICER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test disable NVIC_MAX_IRQ **
 *
 *This test validates that when disabling NVIC_MAX_IRQ irq using the CDD_Nvic_DisableIrq function,
 *the corresponding value in the ICER register is updated correctly.
 */
void test__CDD_Nvic_DisableIrq_LimitMaxIrq( void )
{
    NVIC->ICER[ FIRST_INDEX ] = 0x00000000;
    Nvic_IrqType irq          = NVIC_MAX_IRQ;
    uint32 expected_ICER      = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_DisableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICER, NVIC->ICER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test disable a minior NVIC_Min_IRQ irq**
 *
 *This test validates that when disabling  a minior NVIC_Min_IRQ irq using the CDD_Nvic_DisableIrq
 *function, the corresponding value in the ICER register is not updated.
 */
void test__CDD_Nvic_DisableIrq_MiniorMinIrq( void )
{
    Nvic_IrqType irq     = NVIC_MIN_IRQ - 1;
    uint32 expected_ICER = 0x00000000;

    CDD_Nvic_DisableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICER, NVIC->ICER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test disable an upper NVIC_Max_IRQ irq**
 *
 *This test validates that when disabling  an upper NVIC_Max_IRQ irq using the CDD_Nvic_DisableIrq
 *function, the corresponding value in the ICER register is not updated.
 */
void test__CDD_Nvic_DisableIrq_UpperMaxIrq( void )
{
    Nvic_IrqType irq     = NVIC_MAX_IRQ + 1;
    uint32 expected_ICER = 0x00000000;

    CDD_Nvic_DisableIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICER, NVIC->ICER[ FIRST_INDEX ] );
}

/**
 * @brief   **Test set pending for an upper NVIC_Max_IRQ irq**
 *
 * This test validates that when an upper NVIC_Max_IRQ irq is set as pending using the
 * CDD_Nvic_SetPendingIrq function, the corresponding value in the ISPR register is not updated.
 */
void test_CDD_Nvic_SetPendingIrq_UpperMaxIrq( void )
{
    Nvic_IrqType irq     = NVIC_MAX_IRQ + 1;
    uint32 expected_ISPR = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_SetPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISPR, NVIC->ISPR[ FIRST_INDEX ] );
}

/**
 * @brief   **Test set pending for a minior NVIC_MIN_IRQ irq**
 *
 * This test validates that when an minior NVIC_MIN_IRQ irq is set as pending using the
 * CDD_Nvic_SetPendingIrq function, the corresponding value in the ISPR register is not updated.
 */
void test_CDD_Nvic_SetPendingIrq_MiniorMinIrq( void )
{
    Nvic_IrqType irq     = NVIC_MIN_IRQ - 1;
    uint32 expected_ISPR = 0x00000000; /* 0000 0000 0000 0000 0000 0000 0000 0000 */

    CDD_Nvic_SetPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISPR, NVIC->ISPR[ FIRST_INDEX ] );
}

/**
 * @brief   **Test set pending for a valid IRQ**
 *
 * This test validates that when a valid IRQ is set as pending using the CDD_Nvic_SetPendingIrq
 * function, the corresponding value in the ISPR register is updated correctly.
 */
void test_CDD_Nvic_SetPendingIrq_ValidIrq( void )
{
    Nvic_IrqType irq     = NVIC_IRQ;
    uint32 expected_ISPR = 0x00800000; /* 0000 0000 1000 0000 0000 0000 0000 0000 */

    CDD_Nvic_SetPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ISPR, NVIC->ISPR[ FIRST_INDEX ] );
}

/**
 * @brief   **Test get pending a minior NVIC_Min_IRQ irq**
 *
 * This test checks that the function CDD_Nvic_GetPendingIrq returns a FALSE when querying
 * the pending status of a minior NVIC_Min_IRQ irq
 */
void test_CDD_Nvic_GetPendingIrq_MiniorMinIrq( void )
{
    Nvic_IrqType irq = NVIC_MIN_IRQ - 1;

    uint32 expectedValue = CDD_Nvic_GetPendingIrq( irq );
    TEST_ASSERT_FALSE( expectedValue );
}

/**
 * @brief   **Test get pending an upper NVIC_Max_IRQ irq**
 *
 * This test checks that the function CDD_Nvic_GetPendingIrq returns a FALSE when querying
 * the pending status of an upper NVIC_Max_IRQ irq
 */
void test_CDD_Nvic_GetPendingIrq_UpperMaxIrq( void )
{
    Nvic_IrqType irq = NVIC_MAX_IRQ + 1;

    uint32 expectedValue = CDD_Nvic_GetPendingIrq( irq );
    TEST_ASSERT_FALSE( expectedValue );
}


/**
 * @brief   **Test get pending for a valid IRQ**
 *
 * This test checks that the function CDD_Nvic_GetPendingIrq returns a TRUE when querying
 * the pending status of a valid IRQ number set as pending.
 */
void test_CDD_Nvic_GetPendingIrq_validIrq( void )
{
    Nvic_IrqType irq = NVIC_IRQ;

    uint32 status = CDD_Nvic_GetPendingIrq( irq );
    TEST_ASSERT_TRUE( status );
}

/**
 * @brief   **Test get pending for a IRQ that is not pending**
 *
 * This test checks that the function CDD_Nvic_GetPendingIrq returns an IRQ_NOT_PENDING
 * value when querying the pending status of a valid IRQ number set as not pending.
 */
void test_CDD_Nvic_GetPendingIrq_NotPendingValidIrq( void )
{
    Nvic_IrqType irq = 19;

    uint32 status = CDD_Nvic_GetPendingIrq( irq );
    TEST_ASSERT_EQUAL_UINT32( IRQ_NOT_PENDING, status );
}

/**
 * @brief   **Test get pending for an invalid IRQ**
 *
 * This test checks that the function CDD_Nvic_GetPendingIrq returns an IRQ_NOT_PENDING
 * value when querying the pending status of an invalid IRQ number
 */
void test_CDD_Nvic_GetPendingIrq_NotPendingInvalidIrq( void )
{
    Nvic_IrqType irq = NVIC_MIN_IRQ - 1;

    uint32 result = CDD_Nvic_GetPendingIrq( irq );
    TEST_ASSERT_EQUAL_UINT32( IRQ_NOT_PENDING, result );
}

/**
 * @brief   **Test clear pending for a valid IRQ**
 *
 * This test validates that when clear a valid pending IRQ using the CDD_Nvic_ClearPendingIrq
 * function, the corresponding value in the ICPR register is updated correctly.
 */
void test__CDD_Nvic_ClearPendingIrq_ValidIrq( void )
{
    Nvic_IrqType irq    = NVIC_IRQ;
    uint32 expectedData = 0x00800000; /*0000 0000 1000 0000 0000 0000 0000 0000*/

    CDD_Nvic_ClearPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expectedData, NVIC->ICPR[ FIRST_INDEX ] );
}

/**
 * @brief   **Test clear pending for a minior NVIC_MIN_IRQ irq**
 *
 * This test validates that when clear a minior NVIC_Min_IRQ irq using the CDD_Nvic_ClearPendingIrq
 * function, the corresponding value in the ICPR register is not updated.
 */
void test__CDD_Nvic_ClearPendingIrq_MiniorMinIrq( void )
{
    Nvic_IrqType irq          = NVIC_MIN_IRQ - 1;
    NVIC->ICPR[ FIRST_INDEX ] = 0;
    uint32 expected_ICRP      = 0x00000000; /*0000 0000 0000 0000 0000 0000 0000 0000*/

    CDD_Nvic_ClearPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICRP, NVIC->ICPR[ FIRST_INDEX ] );
}

/**
 * @brief   **Test clear pending for an upper NVIC_MAX_IRQ irq**
 *
 * This test validates that when clear an upper NVIC_MAX_IRQ irq using the CDD_Nvic_ClearPendingIrq
 * function, the corresponding value in the ICPR register is not updated.
 */
void test__CDD_Nvic_ClearPendingIrq_UpperrManIrq( void )
{
    Nvic_IrqType irq          = NVIC_MAX_IRQ + 1;
    NVIC->ICPR[ FIRST_INDEX ] = 0;
    uint32 expected_ICRP      = 0x00000000; /*0000 0000 0000 0000 0000 0000 0000 0000*/

    CDD_Nvic_ClearPendingIrq( irq );
    TEST_ASSERT_EQUAL_HEX32( expected_ICRP, NVIC->ICPR[ FIRST_INDEX ] );
}

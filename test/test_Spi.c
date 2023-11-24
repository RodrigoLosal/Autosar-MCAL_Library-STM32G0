/**
 * @file    test_Spi.c
 * @brief   **Unit testing for Spi Driver**
 * @author  Manuel ALejandro Ascencio Ysordia
 *
 * group of unit test cases for Spi.h file
 */
#include "unity.h"
#include "Std_Types.h"
#include "Spi.h"
#include "Spi_Cfg.h"
#include "mock_Spi_Arch.h"
#include "mock_Det.h"

extern Spi_HwUnit HwUnit_Spi;

#define SPI_HWUNIT_INVALID      0x01u /*!< Invalid driver/controller state */
#define SPI_VALID_HWUNIT_ID     0x00u /*!< Valid HWUNIT ID */
#define SPI_INVALID_HWUNIT_ID   0xFFu /*!< Valid HWUNIT ID */
#define SPI_VALID_CHANEL_ID     0x00u /*!< Valid Channel ID */
#define SPI_INVALID_CHANEL_ID   0xFFu /*!< Valid Channel ID */
#define SPI_VALID_SEQUENCE_ID   0x00u /*!< Valid SEQUENCE ID */
#define SPI_INVALID_SEQUENCE_ID 0xFFu /*!< Valid SEQUENCE ID */
#define SPI_VALID_JOB_ID        0x00u /*!< Valid JOB ID */
#define SPI_INVALID_JOB_ID      0xFFu /*!< Valid JOB ID */
#define SPI_VALID_LENGTH        0x01u /*!< Valid LENGTH ID */
#define SPI_INVALID_LENGTH      0x0Bu /*!< Valid LENGTH ID */
#define SPI_MODE_OK             0x00u /*!< Indicate a value valid for the parameter mode */


/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;
    HwUnit_Spi.Config      = NULL_PTR;

    Spi_Arch_Init_Ignore( );

    Spi_Init( &SpiConfig );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   **Test Init when not SPI_UNINIT**
 *
 * The test checks that the function does not call the Spi_Arch_Init function and HwUnit structure
 * does not set to Spi_IDLE, plus Config pointer is not set.
 */
void test__Spi_Init__when_not_uninit_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_HWUNIT_INVALID;
    HwUnit_Spi.Config      = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Spi_Init( HwUnit_Spi.Config );

    TEST_ASSERT_EQUAL_MESSAGE( SPI_HWUNIT_INVALID, HwUnit_Spi.HwUnitState, "Unit state should not change" );
    TEST_ASSERT_EQUAL_MESSAGE( NULL_PTR, HwUnit_Spi.Config, "Config pointer should not change" );
}

/**
 * @brief   ** Test Init when HwUnit has all the right values **
 *
 * The test checks that the function calls the Spi_Arch_DeInit function and HwUnit structure
 * sets to SPI_IDLE, plus Config pointer is set.
 */
void test__Spi_Init__when_value_is_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;
    HwUnit_Spi.Config      = NULL_PTR;

    Spi_Arch_Init_Ignore( );

    Spi_Init( &SpiConfig );

    TEST_ASSERT_EQUAL_MESSAGE( SPI_IDLE, HwUnit_Spi.HwUnitState, "Unit state should change" );
    TEST_ASSERT_EQUAL_MESSAGE( &SpiConfig, HwUnit_Spi.Config, "Config pointer should change" );
}


/**
 * @brief   **Test DeInit when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_DeInit function and HwUnit structure
 * does not set to SPI_IDLE.
 */
void test__Spi_DeInit__when_not_uninit_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Unit state should not change" );
}

/**
 * @brief   **Test DeInit when HwUnit has all the right values**
 *
 * The test checks that the function calls the Spi_Arch_DeInit function and HwUnit structure
 * sets to SPI_IDLE.
 */
void test__Spi_DeInit__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_DeInit_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_DeInit( );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, Return, "Unit state should change" );
}


/**
 * @brief   **Test WriteIB when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_WriteIB function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_WriteIB__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Spi_DataBufferType Databuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_WriteIB( SPI_VALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test WriteIB when Channel is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_WriteIB function when the Channel
 * is out of range.
 */
void test__Spi_WriteIB__when_Channel_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType Databuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_WriteIB( SPI_INVALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test WriteIB when Databuffer is NULL**
 *
 * The test checks that the function does not call the Spi_Arch_WriteIB function when the Databuffer
 * is NULL.
 */
void test__Spi_WriteIB__when_Databuffer_is_NULL( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_WriteIB( SPI_VALID_CHANEL_ID, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test WriteIB when all values are correct**
 *
 * The test checks that the function calls the Spi_Arch_WriteIB function when all values are correct.
 */
void test__Spi_WriteIB__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType Databuffer;

    Spi_Arch_WriteIB_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_WriteIB( SPI_VALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test AsyncTransmit when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_AsyncTransmit function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_AsyncTransmit__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_AsyncTransmit( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test AsyncTransmit when Sequence is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_AsyncTransmitfunction when the Sequence
 * is out of range.
 */
void test__Spi_Spi_AsyncTransmit__when_Sequence_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_AsyncTransmit( SPI_INVALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test AsyncTransmit when all values are correct**
 *
 * The test checks that the function calls the Spi_Arch_AsyncTransmit function when all values are correct.
 */
void test__Spi_AsyncTransmit__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_AsyncTransmit_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_AsyncTransmit( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test ReadIB when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_ReadIB function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_ReadIB__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Spi_DataBufferType Databuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_ReadIB( SPI_VALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test ReadIB when Channel is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_ReadIB function when the Channel
 * is out of range.
 */
void test__Spi_ReadIB__when_Channel_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType Databuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_ReadIB( SPI_INVALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test ReadIB when Databuffer is NULL**
 *
 * The test checks that the function does not call the Spi_Arch_ReadIB function when the Databuffer
 * is NULL.
 */
void test__Spi_ReadIB__when_Databuffer_is_NULL( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_ReadIB( SPI_VALID_CHANEL_ID, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test ReadIB when all values are correct**
 *
 * The test checks that the function calls the Spi_Arch_ReadIB function when all values are correct.
 */
void test__Spi_ReadIB__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType Databuffer;

    Spi_Arch_ReadIB_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_ReadIB( SPI_VALID_CHANEL_ID, &Databuffer );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Spi_SetupEB when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_SetupEB function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_SetupEB__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Spi_DataBufferType SrcDataBuffer;
    Spi_DataBufferType DesDataBuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_VALID_CHANEL_ID, &SrcDataBuffer, &DesDataBuffer, SPI_VALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetupEB when Channel is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_SetupEB function when the Channel
 * is out of range.
 */
void test__Spi_SetupEB__when_Channel_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType SrcDataBuffer;
    Spi_DataBufferType DesDataBuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_INVALID_CHANEL_ID, &SrcDataBuffer, &DesDataBuffer, SPI_VALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetupEB when SrcDataBuffer is NULL**
 *
 * The test checks that the function does not call the Spi_Arch_SetupEB function when the SrcDataBuffer
 * is NULL.
 */
void test__Spi_SetupEB__when_SrcDataBuffer_is_NULL( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType DesDataBuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_VALID_CHANEL_ID, NULL_PTR, &DesDataBuffer, SPI_VALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetupEB when DesDataBuffer is NULL**
 *
 * The test checks that the function does not call the Spi_Arch_SetupEB function when the DesDataBuffer
 * is NULL.
 */
void test__Spi_SetupEB__when_DesDataBuffer_is_NULL( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType SrcDataBuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_VALID_CHANEL_ID, &SrcDataBuffer, NULL_PTR, SPI_VALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetupEB when Length is NULL**
 *
 * The test checks that the function does not call the Spi_Arch_SetupEB function when the Length
 * is NULL.
 */
void test__Spi_SetupEB__when_Length_is_invalid( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType SrcDataBuffer;
    Spi_DataBufferType DesDataBuffer;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_VALID_CHANEL_ID, &SrcDataBuffer, &DesDataBuffer, SPI_INVALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test SetupEB when all values are correct**
 *
 * The test checks that the function calls the Spi_Arch_SetupEB function when all values are correct.
 */
void test__Spi_SetupEB__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_DataBufferType SrcDataBuffer;
    Spi_DataBufferType DesDataBuffer;

    Spi_Arch_SetupEB_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetupEB( SPI_VALID_CHANEL_ID, &SrcDataBuffer, &DesDataBuffer, SPI_VALID_LENGTH );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test Spi_GetStatus return a E_OK**
 *
 * The test checks that the function calls the Spi_Arch_GetStatus function when all values are correct.
 */
void test__Spi_GetStatus__when_value_is_correct( void )
{
    Spi_Arch_GetStatus_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetStatus( );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_OK" );
}

/**
 * @brief   **Test GetJobResult when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_GetJobResult function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_GetJobResult__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetJobResult( SPI_VALID_JOB_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetJobResult when Job is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_GetJobResult function when the Job
 * is out of range.
 */
void test__Spi_GetJobResult__when_Job_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetJobResult( SPI_INVALID_JOB_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetJobResult when all values are correct**
 *
 * The test checks that the function does call the Spi_Arch_GetJobResult function when all values are correct.
 */
void test__Spi_GetJobResult__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_GetJobResult_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetJobResult( SPI_VALID_JOB_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetSequenceResult when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_GetSequenceResult function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_GetSequenceResult__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetSequenceResult( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetSequenceResult when Sequence is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_GetSequenceResult function when the Sequence
 * is out of range.
 */
void test__Spi_GetSequenceResult__when_Sequence_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetSequenceResult( SPI_INVALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetSequenceResult when all values are correct**
 *
 * The test checks that the function does call the Spi_Arch_GetSequenceResult function when all values are correct.
 */
void test__Spi_GetSequenceResult__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_GetSequenceResult_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetSequenceResult( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test GetVersionInfo when null**
 *
 * The test checks that the function does not call the Spi_Arch_GetVersionInfo function when the versioninfo
 * is NULL.
 */
void test__Spi_GetVersionInfo__when_null( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    Spi_GetVersionInfo( NULL_PTR );

    /* test is testing if Det_ReportError was called */
}

/**
 * @brief   **Test GetVersionInfo when all values are correct**
 *
 * The test checks that the function calls the Spi_Arch_GetVersionInfo function when all values are correct.
 */
void test__Spi_GetVersionInfo__when_all_values_are_correct( void )
{
    Std_VersionInfoType versioninfo;

    Spi_GetVersionInfo( &versioninfo );

    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.vendorID, SPI_MODULE_ID, "vendorID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.moduleID, SPI_VENDOR_ID, "moduleID should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_major_version, SPI_SW_MAJOR_VERSION, "sw_major_version should be 1" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_minor_version, SPI_SW_MINOR_VERSION, "sw_minor_version should be 0" );
    TEST_ASSERT_EQUAL_MESSAGE( versioninfo.sw_patch_version, SPI_SW_PATCH_VERSION, "sw_patch_version should be 0" );
}

/**
 * @brief   **Test Spi_SyncTransmit when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_SyncTransmit function when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_SyncTransmit__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SyncTransmit( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_SyncTransmit when Sequence is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_SyncTransmit function when the Sequence
 * is out of range.
 */
void test__Spi_SyncTransmit__when_Sequence_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SyncTransmit( SPI_INVALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_SyncTransmit when all values are correct**
 *
 * The test checks that the function does call the Spi_Arch_SyncTransmit function when all values are correct.
 */
void test__Spi_SyncTransmit__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_SyncTransmit_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SyncTransmit( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_GetHWUnitStatus when not SPI_IDLE**
 *
 * The test checks that the function does not call the Spi_Arch_GetHWUnitStatusfunction when SPI module
 * is not intialized (when HwUnitState is not SPI_IDLE).
 */
void test__Spi_GetHWUnitStatus__when_not_ready_value_in_HwUnitState( void )
{
    HwUnit_Spi.HwUnitState = SPI_UNINIT;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetHWUnitStatus( SPI_VALID_HWUNIT_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_GetHWUnitStatus when Sequence is unkown**
 *
 * The test checks that the function does not call the Spi_Arch_GetHWUnitStatus function when the Sequence
 * is out of range.
 */
void test__Spi_GetHWUnitStatus__when_Sequence_is_unkown( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Det_ReportError_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetHWUnitStatus( SPI_INVALID_HWUNIT_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_NOT_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_GetHWUnitStatus when all values are correct**
 *
 * The test checks that the function does call the Spi_Arch_GetHWUnitStatusfunction when all values are correct.
 */
void test__Spi_GetHWUnitStatus__when_all_values_are_correct( void )
{
    HwUnit_Spi.HwUnitState = SPI_IDLE;

    Spi_Arch_GetHWUnitStatus_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_GetHWUnitStatus( SPI_VALID_HWUNIT_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_NOT_OK" );
}

/**
 * @brief   **Test Spi_Cancel when value is correct**
 *
 * The test checks that the function does call the Spi_Arch_Cancel function when value is correct.
 */
void test__Spi_Cancel__when_value_is_correct( void )
{
    Spi_Arch_Cancel_Ignore( );

    Spi_Cancel( SPI_VALID_SEQUENCE_ID );
}

/**
 * @brief   **Test Spi_SetAsyncMode when value is correct**
 *
 * The test checks that the function does call the Spi_Arch_Cancel function when value is correct.
 */
void test__Spi_SetAsyncMode__when_value_is_correct( void )
{

    Spi_Arch_SetAsyncMode_IgnoreAndReturn( E_OK );

    Std_ReturnType Return = Spi_SetAsyncMode( SPI_VALID_SEQUENCE_ID );

    TEST_ASSERT_EQUAL_MESSAGE( Return, E_OK, "Return value should be E_NOT_OK" );
}

/**
 * @file    test_Can.c
 * @brief   **Unit testing for Can Driver**
 * @author  Diego Perez
 *
 * group of unit test cases for Can.h file
 */
#include "unity.h"
#include "CanIf_Cfg.h"
#include "CanIf.h"
#include "CanIf_Can.h"
#include "mock_Det.h"

#define CANIF_CONTROLLER_INVALID 0xffu /*!< Controller Invalid */
#define CANIF_VALID_TX_PDU       1u    /*!< Controller 1 */

extern const CanIf_ConfigType *LocalConfigPtr;

/*this function is required by Ceedling to run any code before the test cases*/
void setUp( void )
{
    CanIf_Init( &CanIfConfig );
}

/*this function is required by Ceedling to run any code after the test cases*/
void tearDown( void )
{
}

/**
 * @brief   Test case for CanIf_Init function
 *
 * Empty test cases for an empty function
 */
void test__CanIf_Init__empty_test( void )
{
    CanIf_Init( NULL_PTR );
}

/**
 * @brief   Test case for CanIf_DeInit function with unvalid pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_DeInit__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_DeInit( );
}

/**
 * @brief   Test case for CanIf_DeInit function with valid pointer
 *
 * This test case check if the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_DeInit__valid_ptr( void )
{
    CanIf_DeInit( );

    TEST_ASSERT_EQUAL( NULL_PTR, LocalConfigPtr );
}

/**
 * @brief   Test case for CanIf_SetControllerMode function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_SetControllerMode__null_ptr( void )
{
    Std_ReturnType ret;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetControllerMode( CANIF_CONTROLLER_0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetControllerMode function with invalid controller id
 *
 * This test case only check if Det_ReportError is called when the controller id is invalid
 */
void test__CanIf_SetControllerMode__invalid_controller_id( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetControllerMode( CANIF_CONTROLLER_INVALID, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetControllerMode function with invalid controller mode
 *
 * This test case only check if Det_ReportError is called when the controller mode is invalid
 */
void test__CanIf_SetControllerMode__invalid_controller_mode( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetControllerMode( CANIF_CONTROLLER_0, CAN_CS_UNINIT );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetControllerMode function with invalid controller mode
 *
 * This test case only check if Det_ReportError is called when the controller mode is invalid
 */
void test__CanIf_SetControllerMode__invalid_controller_mode_2( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetControllerMode( CANIF_CONTROLLER_0, CAN_CS_READY );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetControllerMode function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_SetControllerMode__valid_parameters( void )
{
    Std_ReturnType ret;

    ret = CanIf_SetControllerMode( CANIF_CONTROLLER_0, CAN_CS_STARTED );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_SetControllerMode() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerMode function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetControllerMode__null_ptr( void )
{
    Std_ReturnType ret;
    Can_ControllerStateType mode;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerMode( CANIF_CONTROLLER_0, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerMode function with invalid controller id
 *
 * This test case only check if Det_ReportError is called when the controller id is invalid
 */
void test__CanIf_GetControllerMode__invalid_controller_id( void )
{
    Std_ReturnType ret;
    Can_ControllerStateType mode;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerMode( CANIF_CONTROLLER_INVALID, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerMode function with null pointer
 *
 * This test case only check if Det_ReportError is called when the mode pointer is invalid
 */
void test__CanIf_GetControllerMode__null_pointer( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerMode( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerMode function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetControllerMode__valid_parameters( void )
{
    Std_ReturnType ret;
    Can_ControllerStateType mode;

    ret = CanIf_GetControllerMode( CANIF_CONTROLLER_0, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_GetControllerMode() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerErrorState function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetControllerErrorState__null_ptr( void )
{
    Std_ReturnType ret;
    Can_ErrorStateType error;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerErrorState( CANIF_CONTROLLER_0, &error );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerErrorState() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerErrorState function with invalid controller id
 *
 * This test case only check if Det_ReportError is called when the controller id is invalid
 */
void test__CanIf_GetControllerErrorState__invalid_controller_id( void )
{
    Std_ReturnType ret;
    Can_ErrorStateType error;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerErrorState( CANIF_CONTROLLER_INVALID, &error );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerErrorState() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerErrorState function with null pointer
 *
 * This test case only check if Det_ReportError is called when the error pointer is invalid
 */
void test__CanIf_GetControllerErrorState__null_pointer( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetControllerErrorState( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetControllerErrorState() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerErrorState function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetControllerErrorState__valid_parameters( void )
{
    Std_ReturnType ret;
    Can_ErrorStateType error;

    ret = CanIf_GetControllerErrorState( CANIF_CONTROLLER_0, &error );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_GetControllerErrorState() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_Transmit function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_Transmit__null_ptr( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_Transmit( CANIF_VALID_TX_PDU, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_Transmit() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_Transmit function with invalid PduInfoPtr
 *
 * This test case only check if Det_ReportError is called when the PduInfoPtr is invalid
 */
void test__CanIf_Transmit__invalid_PduInfoPtr( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_Transmit( CANIF_VALID_TX_PDU, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_Transmit() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_Transmit function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_Transmit__invalid_PduId( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo = { .SduLength = 9 };

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_Transmit( CANIF_NUMBER_OF_TX_PDUS, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_Transmit() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_Transmit function with invalid length
 *
 * This test case only check if Det_ReportError is called when the length is invalid
 */
void test__CanIf_Transmit__invalid_PduId_2( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo = { .SduLength = 9 };

    Det_ReportRuntimeError_IgnoreAndReturn( E_OK );

    ret = CanIf_Transmit( CANIF_VALID_TX_PDU, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_Transmit() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_Transmit function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_Transmit__valid_parameters( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo = { .SduLength = 8 };

    ret = CanIf_Transmit( CANIF_VALID_TX_PDU, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_Transmit() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxPduData function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ReadRxPduData__null_ptr( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadRxPduData( CANIF_VALID_TX_PDU, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_ReadRxPduData() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxPduData function with invalid PduInfoPtr
 *
 * This test case only check if Det_ReportError is called when the PduInfoPtr is invalid
 */
void test__CanIf_ReadRxPduData__invalid_PduInfoPtr( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadRxPduData( CANIF_VALID_TX_PDU, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_ReadRxPduData() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxPduData function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_ReadRxPduData__invalid_PduId( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo = { .SduLength = 9 };

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadRxPduData( CANIF_NUMBER_OF_RX_PDUS, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_ReadRxPduData() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxPduData function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ReadRxPduData__valid_parameters( void )
{
    Std_ReturnType ret;
    PduInfoType pduInfo = { .SduLength = 8 };

    ret = CanIf_ReadRxPduData( CANIF_VALID_TX_PDU, &pduInfo );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_ReadRxPduData() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_ReadTxNotifStatus function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ReadTxNotifStatus__null_ptr( void )
{
    Std_ReturnType ret;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadTxNotifStatus( CANIF_VALID_TX_PDU );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_ReadTxNotifStatus() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadTxNotifStatus function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_ReadTxNotifStatus__invalid_PduId( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadTxNotifStatus( CANIF_NUMBER_OF_TX_PDUS );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_ReadTxNotifStatus() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadTxNotifStatus function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ReadTxNotifStatus__valid_parameters( void )
{
    Std_ReturnType ret;

    ret = CanIf_ReadTxNotifStatus( CANIF_VALID_TX_PDU );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_TX_RX_NOTIFICATION, ret, "CanIf_ReadTxNotifStatus() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxNotifStatus function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ReadRxNotifStatus__null_ptr( void )
{
    Std_ReturnType ret;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadRxNotifStatus( CANIF_VALID_TX_PDU );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_ReadRxNotifStatus() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxNotifStatus function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_ReadRxNotifStatus__invalid_PduId( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_ReadRxNotifStatus( CANIF_NUMBER_OF_RX_PDUS );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_ReadRxNotifStatus() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_ReadRxNotifStatus function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ReadRxNotifStatus__valid_parameters( void )
{
    Std_ReturnType ret;

    ret = CanIf_ReadRxNotifStatus( CANIF_VALID_TX_PDU );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_TX_RX_NOTIFICATION, ret, "CanIf_ReadRxNotifStatus() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_SetPduMode function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_SetPduMode__null_ptr( void )
{
    Std_ReturnType ret;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetPduMode( CANIF_CONTROLLER_0, CANIF_OFFLINE );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetPduMode function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_SetPduMode__invalid_controller( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetPduMode( CANIF_CONTROLLER_INVALID, CANIF_OFFLINE );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetPduMode function with invalid PduModeRequest
 *
 * This test case only check if Det_ReportError is called when the PduModeRequest is invalid
 */
void test__CanIf_SetPduMode__invalid_PduModeRequest( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_SetPduMode( CANIF_CONTROLLER_0, CANIF_ONLINE + 1 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_SetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetPduMode function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_SetPduMode__valid_parameters( void )
{
    Std_ReturnType ret;

    ret = CanIf_SetPduMode( CANIF_CONTROLLER_0, CANIF_OFFLINE );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_SetPduMode() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetPduMode function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetPduMode__null_ptr( void )
{
    Std_ReturnType ret;
    CanIf_PduModeType mode;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetPduMode( CANIF_CONTROLLER_0, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetPduMode function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_GetPduMode__invalid_controller( void )
{
    Std_ReturnType ret;
    CanIf_PduModeType mode;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetPduMode( CANIF_CONTROLLER_INVALID, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetPduMode function with invalid PduModePtr
 *
 * This test case only check if Det_ReportError is called when the mode pointer is invalid
 */
void test__CanIf_GetPduMode__invalid_PduModePtr( void )
{
    Std_ReturnType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetPduMode( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, ret, "CanIf_GetPduMode() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetPduMode function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetPduMode__valid_parameters( void )
{
    Std_ReturnType ret;
    CanIf_PduModeType mode;

    ret = CanIf_GetPduMode( CANIF_CONTROLLER_0, &mode );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, ret, "CanIf_GetPduMode() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetVersionInfo function with null pointer
 *
 * This test case only check if Det_ReportError is called when the versioninfo pointer is invalid
 */
void test__CanIf_GetVersionInfo__null_ptr( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_GetVersionInfo( NULL_PTR );
}

/**
 * @brief   Test case for CanIf_GetVersionInfo function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetVersionInfo__valid_parameters( void )
{
    Std_VersionInfoType versioninfo;

    CanIf_GetVersionInfo( &versioninfo );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_VENDOR_ID, versioninfo.vendorID, "CanIf_GetVersionInfo() should return CANIF_VENDOR_ID" );
    TEST_ASSERT_EQUAL_MESSAGE( CANIF_MODULE_ID, versioninfo.moduleID, "CanIf_GetVersionInfo() should return CANIF_MODULE_ID" );
    TEST_ASSERT_EQUAL_MESSAGE( CANIF_SW_MAJOR_VERSION, versioninfo.sw_major_version, "CanIf_GetVersionInfo() should return CANIF_SW_MAJOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( CANIF_SW_MINOR_VERSION, versioninfo.sw_minor_version, "CanIf_GetVersionInfo() should return CANIF_SW_MINOR_VERSION" );
    TEST_ASSERT_EQUAL_MESSAGE( CANIF_SW_PATCH_VERSION, versioninfo.sw_patch_version, "CanIf_GetVersionInfo() should return CANIF_SW_PATCH_VERSION" );
}

/**
 * @brief   Test case for CanIf_SetDynamicTxId function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_SetDynamicTxId__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_SetDynamicTxId( CANIF_VALID_TX_PDU, 0x12345678 );
}

/**
 * @brief   Test case for CanIf_SetDynamicTxId function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_SetDynamicTxId__invalid_PduId( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_SetDynamicTxId( CANIF_NUMBER_OF_TX_PDUS, 0x12345678 );
}

/**
 * @brief   Test case for CanIf_SetDynamicTxId function with invalid canId
 *
 * This test case only check if Det_ReportError is called when the canId is invalid
 */
void test__CanIf_SetDynamicTxId__invalid_canId( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_SetDynamicTxId( CANIF_VALID_TX_PDU, 0x00 );
}

/**
 * @brief   Test case for CanIf_SetDynamicTxId function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_SetDynamicTxId__valid_parameters( void )
{
    CanIf_SetDynamicTxId( CANIF_VALID_TX_PDU, 0x12345678 );
}

/**
 * @brief   Test case for CanIf_GetTxConfirmationState function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetTxConfirmationState__null_ptr( void )
{
    CanIf_NotifStatusType ret;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetTxConfirmationState( CANIF_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_GetTxConfirmationState() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetTxConfirmationState function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_GetTxConfirmationState__invalid_controller( void )
{
    CanIf_NotifStatusType ret;

    Det_ReportError_IgnoreAndReturn( E_OK );

    ret = CanIf_GetTxConfirmationState( CANIF_CONTROLLER_INVALID );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_NO_NOTIFICATION, ret, "CanIf_GetTxConfirmationState() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetTxConfirmationState function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetTxConfirmationState__valid_parameters( void )
{
    CanIf_NotifStatusType ret;

    ret = CanIf_GetTxConfirmationState( CANIF_CONTROLLER_0 );

    TEST_ASSERT_EQUAL_MESSAGE( CANIF_TX_RX_NOTIFICATION, ret, "CanIf_GetTxConfirmationState() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_SetBaudrate function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_SetBaudrate__null_ptr( void )
{
    Std_ReturnType RetVal;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_SetBaudrate( CANIF_CONTROLLER_0, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_SetBaudrate() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetBaudrate function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_SetBaudrate__invalid_controller( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_SetBaudrate( CANIF_CONTROLLER_INVALID, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_SetBaudrate() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_SetBaudrate function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_SetBaudrate__valid_parameters( void )
{
    Std_ReturnType RetVal;

    RetVal = CanIf_SetBaudrate( CANIF_CONTROLLER_0, 0 );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_SetBaudrate() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerRxErrorCounter function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetControllerRxErrorCounter__null_ptr( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerRxErrorCounter( CANIF_CONTROLLER_0, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerRxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerRxErrorCounter function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_GetControllerRxErrorCounter__invalid_controller( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerRxErrorCounter( CANIF_CONTROLLER_INVALID, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerRxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerRxErrorCounter function with null pointer
 *
 * This test case only check if Det_ReportError is called when the ErrorCounter pointer is invalid
 */
void test__CanIf_GetControllerRxErrorCounter__null_pointer2( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerRxErrorCounter( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerRxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerRxErrorCounter function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetControllerRxErrorCounter__valid_parameters( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;

    RetVal = CanIf_GetControllerRxErrorCounter( CANIF_CONTROLLER_0, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_GetControllerRxErrorCounter() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerTxErrorCounter function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetControllerTxErrorCounter__null_ptr( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerTxErrorCounter( CANIF_CONTROLLER_0, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerTxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerTxErrorCounter function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_GetControllerTxErrorCounter__invalid_controller( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerTxErrorCounter( CANIF_CONTROLLER_INVALID, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerTxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerTxErrorCounter function with null pointer
 *
 * This test case only check if Det_ReportError is called when the ErrorCounter pointer is invalid
 */
void test__CanIf_GetControllerTxErrorCounter__null_pointer2( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetControllerTxErrorCounter( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetControllerTxErrorCounter() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetControllerTxErrorCounter function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetControllerTxErrorCounter__valid_parameters( void )
{
    Std_ReturnType RetVal;
    uint8 ErrorCounter;

    RetVal = CanIf_GetControllerTxErrorCounter( CANIF_CONTROLLER_0, &ErrorCounter );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_GetControllerTxErrorCounter() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_DisableBusMirroring function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_EnableBusMirroring__null_ptr( void )
{
    Std_ReturnType RetVal;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_EnableBusMirroring( CANIF_CONTROLLER_0, STD_ON );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_EnableBusMirroring() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_DisableBusMirroring function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_EnableBusMirroring__invalid_controller( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_EnableBusMirroring( CANIF_CONTROLLER_INVALID, STD_ON );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_EnableBusMirroring() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_DisableBusMirroring function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_EnableBusMirroring__valid_parameters( void )
{
    Std_ReturnType RetVal;

    RetVal = CanIf_EnableBusMirroring( CANIF_CONTROLLER_0, STD_ON );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_EnableBusMirroring() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_GetCurrentTime function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetCurrentTime__null_ptr( void )
{
    Std_ReturnType RetVal;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetCurrentTime( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetCurrentTime() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetCurrentTime function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_GetCurrentTime__invalid_controller( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType CurrentTime;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetCurrentTime( CANIF_CONTROLLER_INVALID, &CurrentTime );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetCurrentTime() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetCurrentTime function with NULL parameters
 *
 * This test case check if the function return E_NOT_OK when the parameter timeStampPtr
 * is invalid
 */
void test__CanIf_GetCurrentTime__null_pointer( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetCurrentTime( CANIF_CONTROLLER_0, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetCurrentTime() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetCurrentTime function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetCurrentTime__valid_parameters( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType CurrentTime;

    RetVal = CanIf_GetCurrentTime( CANIF_CONTROLLER_0, &CurrentTime );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_GetCurrentTime() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_EnableEgressTimeStamp function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_EnableEgressTimeStamp__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_EnableEgressTimeStamp( CANIF_VALID_TX_PDU );
}

/**
 * @brief   Test case for CanIf_EnableEgressTimeStamp function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_EnableEgressTimeStamp__invalid_PduId( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_EnableEgressTimeStamp( CANIF_NUMBER_OF_TX_PDUS );
}

/**
 * @brief   Test case for CanIf_EnableEgressTimeStamp function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_EnableEgressTimeStamp__valid_parameters( void )
{
    CanIf_EnableEgressTimeStamp( CANIF_VALID_TX_PDU );
}

/**
 * @brief   Test case for CanIf_GetEgressTimeStamp function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetEgressTimeStamp__null_ptr( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType EgressTimeStamp;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetEgressTimeStamp( CANIF_VALID_TX_PDU, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetEgressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetEgressTimeStamp function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_GetEgressTimeStamp__invalid_PduId( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType EgressTimeStamp;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetEgressTimeStamp( CANIF_NUMBER_OF_TX_PDUS, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetEgressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetEgressTimeStamp function with null pointer
 *
 * This test case only check if Det_ReportError is called when the EgressTimeStamp pointer is invalid
 */
void test__CanIf_GetEgressTimeStamp__null_pointer2( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetEgressTimeStamp( CANIF_VALID_TX_PDU, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetEgressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetEgressTimeStamp function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetEgressTimeStamp__valid_parameters( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType EgressTimeStamp;

    RetVal = CanIf_GetEgressTimeStamp( CANIF_VALID_TX_PDU, &EgressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_GetEgressTimeStamp() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_SetEgressTimeStamp function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_GetIngressTimeStamp__null_ptr( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType IngressTimeStamp;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetIngressTimeStamp( CANIF_VALID_TX_PDU, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetIngressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetIngressTimeStamp function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_GetIngressTimeStamp__invalid_PduId( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType IngressTimeStamp;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetIngressTimeStamp( CANIF_NUMBER_OF_TX_PDUS, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetIngressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetIngressTimeStamp function with null pointer
 *
 * This test case only check if Det_ReportError is called when the IngressTimeStamp pointer is invalid
 */
void test__CanIf_GetIngressTimeStamp__null_pointer2( void )
{
    Std_ReturnType RetVal;

    Det_ReportError_IgnoreAndReturn( E_OK );

    RetVal = CanIf_GetIngressTimeStamp( CANIF_VALID_TX_PDU, NULL_PTR );

    TEST_ASSERT_EQUAL_MESSAGE( E_NOT_OK, RetVal, "CanIf_GetIngressTimeStamp() should return E_NOT_OK" );
}

/**
 * @brief   Test case for CanIf_GetIngressTimeStamp function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_GetIngressTimeStamp__valid_parameters( void )
{
    Std_ReturnType RetVal;
    Can_TimeStampType IngressTimeStamp;

    RetVal = CanIf_GetIngressTimeStamp( CANIF_VALID_TX_PDU, &IngressTimeStamp );

    TEST_ASSERT_EQUAL_MESSAGE( E_OK, RetVal, "CanIf_GetIngressTimeStamp() should return E_OK" );
}

/**
 * @brief   Test case for CanIf_TxConfirmation function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_TxConfirmation__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_TxConfirmation( CANIF_VALID_TX_PDU );
}

/**
 * @brief   Test case for CanIf_TxConfirmation function with invalid PduId
 *
 * This test case only check if Det_ReportError is called when the PduId is invalid
 */
void test__CanIf_TxConfirmation__invalid_PduId( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_TxConfirmation( CANIF_NUMBER_OF_TX_PDUS );
}

/**
 * @brief   Test case for CanIf_TxConfirmation function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_TxConfirmation__valid_parameters( void )
{
    CanIf_TxConfirmation( CANIF_VALID_TX_PDU );
}

/**
 * @brief   Test case for CanIf_RxIndication function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_RxIndication__null_ptr( void )
{
    const Can_HwType Mailbox;
    const PduInfoType PduInfoPt;
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_RxIndication( &Mailbox, &PduInfoPt );
}

/**
 * @brief   Test case for CanIf_RxIndication function with invalid Mailbox
 *
 * This test case only check if Det_ReportError is called when the Mailbox is invalid
 */
void test__CanIf_RxIndication__invalid_Mailbox( void )
{
    const PduInfoType PduInfoPt;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_RxIndication( NULL_PTR, &PduInfoPt );
}

/**
 * @brief   Test case for CanIf_RxIndication function with invalid PduInfoPt
 *
 * This test case only check if Det_ReportError is called when the PduInfoPt is invalid
 */
void test__CanIf_RxIndication__invalid_PduInfoPt( void )
{
    const Can_HwType Mailbox;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_RxIndication( &Mailbox, NULL_PTR );
}

/**
 * @brief   Test case for CanIf_RxIndication function with invalid Hoh
 *
 * This test case only check if Det_ReportError is called when the Hoh is invalid
 */
void test__CanIf_RxIndication__invalid_Hoh( void )
{
    const Can_HwType Mailbox = { .Hoh = 0xFFu, .CanId = 0x10, .ControllerId = 0 };
    const PduInfoType PduInfoPt;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_RxIndication( &Mailbox, &PduInfoPt );
}

/**
 * @brief   Test case for CanIf_RxIndication function with invalid CanId
 *
 * This test case only check if Det_ReportError is called when the CanId is invalid
 */
void test__CanIf_RxIndication__invalid_CanId( void )
{
    const Can_HwType Mailbox = { .Hoh = 0, .CanId = 0x00, .ControllerId = 0 };
    const PduInfoType PduInfoPt;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_RxIndication( &Mailbox, &PduInfoPt );
}

/**
 * @brief   Test case for CanIf_RxIndication function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_RxIndication__valid_parameters( void )
{
    const Can_HwType Mailbox    = { .Hoh = 0, .CanId = 0x10, .ControllerId = 0 };
    const PduInfoType PduInfoPt = { .SduDataPtr = NULL_PTR, .SduLength = 0 };

    CanIf_RxIndication( &Mailbox, &PduInfoPt );
}

/**
 * @brief   Test case for CanIf_ControllerBusOff function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ControllerBusOff__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerBusOff( CANIF_CONTROLLER_0 );
}

/**
 * @brief   Test case for CanIf_ControllerBusOff function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_ControllerBusOff__invalid_controller( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerBusOff( CANIF_CONTROLLER_INVALID );
}

/**
 * @brief   Test case for CanIf_ControllerBusOff function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ControllerBusOff__valid_parameters( void )
{
    CanIf_ControllerBusOff( CANIF_CONTROLLER_0 );
}

/**
 * @brief   Test case for CanIf_ControllerModeIndication function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ControllerModeIndication__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerModeIndication( CANIF_CONTROLLER_0, CAN_CS_STARTED );
}

/**
 * @brief   Test case for CanIf_ControllerModeIndication function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_ControllerModeIndication__invalid_controller( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerModeIndication( CANIF_CONTROLLER_INVALID, CAN_CS_STARTED );
}

/**
 * @brief   Test case for CanIf_ControllerModeIndication function with invalid ControllerMode
 *
 * This test case only check if Det_ReportError is called when the ControllerMode is invalid
 */
void test__CanIf_ControllerModeIndication__invalid_ControllerMode( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerModeIndication( CANIF_CONTROLLER_0, CAN_CS_UNINIT );
}

/**
 * @brief   Test case for CanIf_ControllerModeIndication function with invalid ControllerMode
 *
 * This test case only check if Det_ReportError is called when the ControllerMode is invalid
 */
void test__CanIf_ControllerModeIndication__invalid_ControllerMode2( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerModeIndication( CANIF_CONTROLLER_0, CAN_CS_READY );
}

/**
 * @brief   Test case for CanIf_ControllerModeIndication function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ControllerModeIndication__valid_parameters( void )
{
    CanIf_ControllerModeIndication( CANIF_CONTROLLER_0, CAN_CS_STARTED );
}

/**
 * @brief   Test case for CanIf_ControllerErrorStatePassive function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ControllerErrorStatePassive__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerErrorStatePassive( CANIF_CONTROLLER_0, 5, 5 );
}

/**
 * @brief   Test case for CanIf_ControllerErrorStatePassive function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_ControllerErrorStatePassive__invalid_controller( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ControllerErrorStatePassive( CANIF_CONTROLLER_INVALID, 5, 5 );
}

/**
 * @brief   Test case for CanIf_ControllerErrorStatePassive function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ControllerErrorStatePassive__valid_parameters( void )
{
    CanIf_ControllerErrorStatePassive( CANIF_CONTROLLER_0, 5, 5 );
}

/**
 * @brief   Test case for CanIf_ControllerErrorStateWarning function with null pointer
 *
 * This test case only check if Det_ReportError is called when the CanbIf is not intialized
 * the global pointer LocalConfigPtr is set to NULL_PTR
 */
void test__CanIf_ErrorNotification__null_ptr( void )
{
    LocalConfigPtr = NULL_PTR;

    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ErrorNotification( CANIF_CONTROLLER_0, CAN_ERROR_BIT );
}

/**
 * @brief   Test case for CanIf_ErrorNotification function with invalid controller
 *
 * This test case only check if Det_ReportError is called when the controller is invalid
 */
void test__CanIf_ErrorNotification__invalid_controller( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ErrorNotification( CANIF_CONTROLLER_INVALID, CAN_ERROR_BIT );
}

/**
 * @brief   Test case for CanIf_ErrorNotification function with invalid error
 *
 * This test case only check if Det_ReportError is called when the error is invalid
 */
void test__CanIf_ErrorNotification__invalid_error( void )
{
    Det_ReportError_IgnoreAndReturn( E_OK );

    CanIf_ErrorNotification( CANIF_CONTROLLER_0, CAN_ERROR_BUS_LOCK + 1 );
}

/**
 * @brief   Test case for CanIf_ErrorNotification function with valid parameters
 *
 * This test case check if the function return E_OK when the parameters are valid
 */
void test__CanIf_ErrorNotification__valid_parameters( void )
{
    CanIf_ErrorNotification( CANIF_CONTROLLER_0, CAN_ERROR_BIT );
}
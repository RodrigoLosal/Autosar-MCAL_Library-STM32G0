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
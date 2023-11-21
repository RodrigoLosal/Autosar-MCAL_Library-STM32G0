/**
 * @file    Adc_Arch.c
 * @brief   **Adc Architecture Driver**
 * @author  Naim Leon
 *
 * Adc driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the Adc driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Adc_Cfg.h"
#include "Adc_Arch.h"
#include "Bfx.h"

/**
 * @brief    **Adc low level Initialization**
 *
 * This function Initializes the ADC hardware units and driver.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Config Pointer to driver configuration
 */
void Adc_Arch_Init( Adc_HwUnit *HwUnit, const Adc_ConfigType *Config )
{
    (void)HwUnit;
    (void)Config;
}

/**
 * @brief    **ADC low level Result Buffer**
 *
 * This function initializes ADC driver with the group specific result buffer start address where
 * the conversion results will be stored. The application has to ensure that the application
 * buffer, where DataBufferPtr points to, can hold all the conversion results of the specified
 * group. The initialization with Adc_SetupResultBuffer is required after reset, before a group
 * conversion can be started.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC channel group.
 * @param    DataBufferPtr Pointer to result data buffer.
 *
 * @retval  E_OK: result buffer pointer initialized correctly
 *          E_NOT_OK: operation failed or development error occured
 *
 * @reqs    SWS_Adc_91000
 */
Std_ReturnType Adc_Arch_SetupResultBuffer( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    (void)HwUnit;
    (void)Group;
    (void)DataBufferPtr;
    return E_OK;
}

/**
 * @brief    **ADC low level Deinitialization**
 *
 * This function Returns all ADC HW Units to a state comparable to their power on reset state.
 * 
 * @param    HwUnit Pointer to the hardware unit configuration
 *
 * @reqs    SWS_Adc_00366 SWS_Adc_00228
 */
void Adc_Arch_DeInit( Adc_HwUnit *HwUnit )
{
    (void)HwUnit;
}

/**
 * @brief    **ADC low level Start Group Conversion**
 *
 * Starts the conversion of all channels of the requested ADC Channel group.
 * 
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_00367 SWS_Adc_00259
 */
void Adc_Arch_StartGroupConversion( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Stop Group Conversion**
 *
 * Stops the conversion of the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_00368 SWS_Adc_00260
 */
void Adc_Arch_StopGroupConversion( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Read Group**
 *
 * Reads the group conversion result of the last completed conversion round of the requested group
 * and stores the channel values starting at the DataBufferPtr address. The group channel values
 * are stored in ascending channel number order (in contrast to the storage layout of the result
 * buffer if streaming access is configured).
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC channel group.
 * @param    DataBufferPtr ADC results of all channels of the selected group are stored in the data
 *                          buffer addressed with the pointer.
 *
 * @retval  E_OK: results are available and written to the data buffer
 *          E_NOT_OK: no results are available or development error occured
 *
 * @reqs    SWS_Adc_00369 SWS_Adc_00359
 */
Std_ReturnType Adc_Arch_ReadGroup( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr )
{
    (void)HwUnit;
    (void)Group;
    (void)DataBufferPtr;
    return E_OK;
}

/**
 * @brief    **ADC low level Enable Hardware Trigger**
 *
 * Enables the hardware trigger for the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91001 SWS_Adc_00265
 */
void Adc_Arch_EnableHardwareTrigger( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Disable Hardware Trigger**
 *
 * Disables the hardware trigger for the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91002 SWS_Adc_00266
 */
void Adc_Arch_DisableHardwareTrigger( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Enable Group Notification**
 *
 * Enables the notification mechanism for the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91003 SWS_Adc_00100
 */
void Adc_Arch_EnableGroupNotification( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Disable Group Notification**
 *
 * Disables the notification mechanism for the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @reqs    SWS_Adc_91004 SWS_Adc_00101
 */
void Adc_Arch_DisableGroupNotification( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
}

/**
 * @brief    **ADC low level Get Group Status**
 *
 * Returns the conversion status of the requested ADC Channel group.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 *
 * @retval  Conversion status for the requested group.
 *
 * @reqs    SWS_Adc_00374
 */
Adc_StatusType Adc_Arch_GetGroupStatus( Adc_HwUnit *HwUnit, Adc_GroupType Group )
{
    (void)HwUnit;
    (void)Group;
    return ADC_IDLE;
}

/**
 * @brief    **ADC low level Get Stream Last Pointer**
 *
 * Returns the number of valid samples per channel, stored in the result buffer. Reads a pointer,
 * pointing to a position in the group result buffer. With the pointer position, the results of all
 * group channels of the last completed conversion round can be accessed. With the pointer and the
 * return value, all valid group conversion results can be accessed (the user has to take the
 * layout of the result buffer into account).
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Group Numeric ID of requested ADC Channel group.
 * @param    PtrToSamplePtr Pointer to result buffer pointer.
 *
 * @retval  Number of valid samples per channel.
 *
 * @reqs    SWS_Adc_00375
 */
Adc_StreamNumSampleType Adc_Arch_GetStreamLastPointer( Adc_HwUnit *HwUnit, Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr )
{
    (void)HwUnit;
    (void)Group;
    (void)PtrToSamplePtr;
    return 1u;
}

/**
 * @brief    **ADC low level Get Version Info**
 *
 * Returns the version information of this module.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    versioninfo Pointer to where to store the version information of this module.
 *
 * @reqs    SWS_Adc_00376
 */
void Adc_Arch_GetVersionInfo( Adc_HwUnit *HwUnit, Std_VersionInfoType *versioninfo )
{
    (void)HwUnit;
    (void)versioninfo;
}

/**
 * @brief    **ADC low level Set Power State**
 *
 * This API configures the Adc module so that it enters the already prepared power state, chosen
 * between a predefined set of configured ones.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: Power state change executed.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *                  ADC_SEQUENCE_ERROR: wrong API call sequence. ADC_HW_FAILURE: the HW module has
 *                  a failure which prevents it to enter the required power state.
 *
 * @retval  E_OK: Power Mode changed
 *          E_NOT_OK: request rejected
 *
 * @reqs    SWS_Adc_00475
 */
Std_ReturnType Adc_Arch_SetPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)Result;
    return E_OK;
}

/**
 * @brief    **ADC low level Get Current Power State**
 *
 * This API returns the current power state of the ADC HW unit.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    CurrentPowerState The current power mode of the ADC HW Unit is returned in this
 *                              parameter.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: Current power mode was returned.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00476
 */
Std_ReturnType Adc_Arch_GetCurrentPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)CurrentPowerState;
    (void)Result;
    return E_OK;
}

/**
 * @brief    **ADC low level Get Target Power State**
 *
 * This API returns the Target power state of the ADC HW unit.
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    TargetPowerState The Target power mode of the ADC HW Unit is returned in this
 *                              parameter.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED:Target power mode was returned.
 *                  If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not initialized.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00477
 */
Std_ReturnType Adc_Arch_GetTargetPowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)TargetPowerState;
    (void)Result;
    return E_OK;
}

/**
 * @brief    **ADC low level Prepare Power State**
 *
 * This API starts the needed process to allow the ADC HW module to enter the requested power state
 *
 * @param    HwUnit Pointer to the hardware unit configuration
 * @param    PowerState The target power state intended to be attained.
 * @param    Result If the API returns E_OK: ADC_SERVICE_ACCEPTED: ADC Module power state
 *                  preparation was started. If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module
 *                  not initialized. ADC_SEQUENCE_ERROR: wrong API call sequence (Current Power
 *                  State = Target Power State). ADC_POWER_STATE_NOT_SUPP: ADC Module does not
 *                  support the requested power state. ADC_TRANS_NOT_POSSIBLE: ADC Module cannot
 *                  transition directly from the current power state to the requested power state
 *                  or the HW peripheral is still busy.
 *
 * @retval  E_OK: Mode could be read
 *          E_NOT_OK: Service is rejected
 *
 * @reqs    SWS_Adc_00478
 */
Std_ReturnType Adc_Arch_PreparePowerState( Adc_HwUnit *HwUnit, Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result )
{
    (void)HwUnit;
    (void)PowerState;
    (void)Result;
    return E_OK;
}
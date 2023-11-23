/**
 * @file    MemIf.h
 * @brief   **Memory Abstraction Interface**
 * @author  Christopher Bogarin
 *
 * This specification describes the functionality, API and configuration of the AUTOSAR
 * Basic Software Module “Memory Abstraction Interface” (MemIf). This module allows
 * the NVRAM manager to access several memory abstraction modules (FEE or EA modules).
 */
#ifndef MEMIF_H__
#define MEMIF_H__

#include "Std_Types.h"

/**
  * @defgroup MEMIF_E_PARAM Development errors.
  @{ */
#define MEMIF_E_PARAM_DEVICE  0x01u /*!< API service called with wrong device index parameter */
#define MEMIF_E_PARAM_POINTER 0x02u /*!< API service called with NULL pointer argument */
/**
  @} */

/**
 * @brief   **Denotes the current status of the underlying abstraction module and device drive.**
 *
 * @reqs   SWS_MemIf_00064
 */
typedef enum _MemIf_StatusType
{
    MEMIF_UNINIT = 0x00u, /*!< The underlying abstraction module or device driver has not been initialized (yet).*/
    MEMIF_IDLE,           /*!< The underlying abstraction module or device driver is currently idle.*/
    MEMIF_BUSY,           /*!< The underlying abstraction module or device driver is currently busy.*/
    MEMIF_BUSY_INTERNAL   /*!< The underlying abstraction module is busy with internal
                                management operations. The underlying device driver can be busy or idle.*/
} MemIf_StatusType;

/**
 * @brief   **Denotes the result of the last job.**
 *
 * @reqs   SWS_MemIf_00065
 */
typedef enum _MemIf_JobResultType
{
    MEMIF_JOB_OK = 0x00u,     /*!< The job has been finished successfully.*/
    MEMIF_JOB_FAILED,         /*!< The job has not been finished successfully.*/
    MEMIF_JOB_PENDING,        /*!< The job has not yet been finished.*/
    MEMIF_JOB_CANCELED,       /*!< The job has been canceled.*/
    MEMIF_BLOCK_INCONSISTENT, /*!< 1. The requested block is inconsistent, it may contain corrupted data.
                                   2. Block is NOT found.*/
    MEMIF_BLOCK_INVALID       /*!< The requested block has been marked as invalid,
                                    therequested operation can not be performed.*/
} MemIf_JobResultType;

/**
 * @brief   **Denotes the operation mode of the underlying abstraction modules and device drivers.**
 *
 * @reqs   SWS_MemIf_00066
 */
typedef enum _MemIf_ModeType
{
    MEMIF_MODE_SLOW = 0x00u, /*!< The underlying memory abstraction modules and drivers are working in slow mode.*/
    MEMIF_MODE_FAST          /*!< The underlying memory abstraction modules and drivers are working in fast mode.*/
} MemIf_ModeType;

#endif
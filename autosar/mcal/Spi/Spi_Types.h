/**
 * @file    Spi_Types.h
 * @brief   **Spi Driver**
 * @author  Manuel Alejandro Ascencio Ysordia
 *
 * The header contains the type definitions that are used by the Spi module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */

#ifndef SPI_TYPES_H__
#define SPI_TYPES_H__

#include "Registers.h"

/**
 * @brief **Hardware unit configuration structure**
 *
 * This type of the external data structure shall contain the initialization data for the SPI
 * Handler/Driver.
 *
 * @reqs    SWS_Spi_00372
 */
typedef struct _Spi_ConfigType
{
    uint32 dummy; /*!< dummy element for the moment */
} Spi_ConfigType;

/**
 * @brief States of the controller SPI
 *
 * This type defines a range of specific status for SPI Handler/Driver.
 *
 * @reqs    SWS_Spi_00373
 */
typedef enum _Spi_StatusType
{
    SPI_UNINIT, /*!< The SPI Handler/Driver is not initialized or not usable.*/
    SPI_IDLE,   /*!< The SPI Handler/Driver is not currently transmitting any Job.*/
    SPI_BUSY,   /*!< The SPI Handler/Driver is performing a SPI Job (transmit).*/
} Spi_StatusType;

/**
 * @brief States of the Jobs for the SPI
 *
 * This type defines a range of specific Jobs status for SPI Handler/Driver.
 *
 * @reqs    SWS_Spi_00374
 */
typedef enum _Spi_JobResultType
{
    SPI_JOB_OK,      /*!< The last transmission of the Job has been finished successfully.*/
    SPI_JOB_PENDING, /*!< The SPI Handler/Driver is performing a SPI Job. The meaning of this status is equal to SPI_BUSY.*/
    SPI_JOB_FAILED,  /*!< The last transmission of the Job has failed.*/
    SPI_JOB_QUEUED,  /*!< An asynchronous transmit Job has been accepted, while actual transmission for this Job has not started yet.*/
} Spi_JobResultType;

/**
 * @brief States of the Sequence for the SPI
 *
 * This type defines a range of specific Sequences status for SPI Handler/Driver.
 *
 * @reqs    SWS_Spi_00375
 */
typedef enum _Spi_SeqResultType
{
    SPI_SEQ_OK,       /*!< The last transmission of the Job has been finished successfully.*/
    SPI_SEQ_PENDING,  /*!< The SPI Handler/Driver is performing a SPI Sequence. The meaning of this status is equal to SPI_BUSY.*/
    SPI_SEQ_FAILED,   /*!< The last transmission of the Sequence has failed.*/
    SPI_SEQ_CANCELED, /*!< The last transmission of the Sequence has been canceled by user.*/
} Spi_SeqResultType;

/**
 * @brief  Spi Data Buffer Type
 *
 * Type of application data buffer elements.
 *
 * @reqs    SWS_Spi_00376
 */
typedef uint8 Spi_DataBufferType;

/**
 * @brief  Spi Number Of Data Type
 *
 * Type for defining the number of data elements to send and / or receive by Channel.
 *
 * @reqs    SWS_Spi_00377
 */
typedef uint16 Spi_NumberOfDataType;

/**
 * @brief  Spi Channel Type
 *
 * Specifies the identification (ID) for a Channel.
 *
 * @reqs    SWS_Spi_00378
 */
typedef uint8 Spi_ChannelType;

/**
 * @brief  Spi Job Type
 *
 * Specifies the identification (ID) for a Job.
 *
 * @reqs    SWS_Spi_00379
 */
typedef uint16 Spi_JobType;

/**
 * @brief  Spi Sequence Type
 *
 * Specifies the identification (ID) for a sequence of jobs.
 *
 * @reqs    SWS_Spi_00380
 */
typedef uint8 Spi_SequenceType;

/**
 * @brief  Spi HWUnit Type
 *
 * Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 *
 * @reqs    SWS_Spi_00381
 */
typedef uint8 Spi_HWUnitType;

/**
 * @brief States of the Asynchronoe Mode for the SPI
 *
 * Specifies the asynchronous mechanism mode for SPI busses handled asynchronously.
 *
 * @reqs    SWS_Spi_00382
 */
typedef enum _Spi_AsyncModeType
{
    SPI_POLLING_MODE,   /*!< The asynchronous mechanism is ensured by polling, so interrupts related to SPI busses handled asynchronously are disabled.*/
    SPI_INTERRUPT_MODE, /*!< The asynchronous mechanism is ensured by interrupt, so interrupts related to SPI busses handled asynchronously are enabled.*/
} Spi_AsyncModeType;

#endif /* SPI_TYPES_H__ */

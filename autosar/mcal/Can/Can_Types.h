/**
 * @file    Can_Types.h
 * @brief   **Can Driver**
 * @author  Diego Perez
 *
 * The header contains the type definitions that are used by the Can module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef CAN_TYPES_H__
#define CAN_TYPES_H__

#include "Registers.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/**
 * @brief **CAN Controller**
 *
 * This container contains the configuration parameters of the CAN controller(s).
 *
 * @note the element ID defined by autosar is suppressed due to the fact that the index array it
 *       is used as an ID. the default baud rate element is not a pointer but rather an index to the
 *      baud rate array
 *
 * @todo more elements are still pending to define
 */
typedef struct _Can_Controller
{
    uint32 FrameFormat; /*!< Specifies the CAN frame format FD or Classic.
                            This parameter can be a value of @ref CAN_frame_format     */

    uint8 BaudrateConfigsCount; /*!< Number of baudrate configurations for the controller */
} Can_Controller;


/**
 * @brief **CAN Hardware Object**
 *
 * This container contains the configuration parameters of the CAN hardware objects.
 *
 * @todo controller and HOH base address are still pending to define
 */
typedef struct _Can_HardwareObject
{
    uint8 ObjectType;                    /*!< Select the type of HOH object, for Tx or Rx
                                             This paramter can be a set of  @ref CAN_Hardware_Object_Type */
    const Can_Controller *ControllerRef; /*!< Reference to CAN Controller to which the HOH is associated to
                                         this paramter must be a address of a valid controller structure  */
} Can_HardwareObject;


/**
 * @brief **Hardware unit configuration structure**
 *
 * This structure contains the paramters to configure the hardware unit incuding the controllers and the
 * hardware objects
 *
 * @reqs    SWS_Can_00413
 */
typedef struct _Can_ConfigType
{
    const Can_Controller *Controllers; /*!< Pointer to the controller structure */
    const Can_HardwareObject *Hohs;    /*!< Pointer to the hardware object structure */
} Can_ConfigType;

/**
 * @brief **Hardware control unit structure**
 *
 * This structure contains the hardware unit configuration and the state of the hardware unit
 * pointers to controller extructure s
 */
typedef struct _Can_HwUnit
{
    const Can_ConfigType *Config;             /*!< Pointer to the configuration structure */
    uint8 HwUnitState;                        /*!< CAN hardware unit state */
    Can_ControllerStateType *ControllerState; /*!< CAN controller states */
} Can_HwUnit;

#endif /* CAN_TYPES_H__ */

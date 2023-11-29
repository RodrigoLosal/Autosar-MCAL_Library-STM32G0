/**
 * @file    Nvic_Types.h
 * @brief   **Nvic Driver**
 * @author  Diego Perez
 *
 * The header contains the type definitions that are used by the Can module. The file is implemnted
 * as a means of abstraction from the hardware, this way we can avoid to include Arch headers in
 * the actual driver header, making the low level interfaces available for upper layers.
 */
#ifndef NVIC_TYPES_H__
#define NVIC_TYPES_H__

/**
 * @defgroup NVIC_Ids Nvic Id number for module and each API
 *
 * @{ */
#define NVIC_ID_SET_PRIORITY      0x00u /*!< CDD_Nvic_SetPriority() api service id */
#define NVIC_ID_GET_PRIORITY      0x01u /*!< CDD_Nvic_GetPriority() api service id */
#define NVIC_ID_ENABLE_IRQ        0x02u /*!< CDD_Nvic_EnableIrq() api service id */
#define NVIC_ID_DISABLE_IRQ       0x03u /*!< CDD_Nvic_DisableIrq() api service id */
#define NVIC_ID_GET_PENDING_IRQ   0x04u /*!< CDD_Nvic_GetPendingIrq() api service id */
#define NVIC_ID_SET_PENDING_IRQ   0x05u /*!< CDD_Nvic_SetPendingIrq() api service id */
#define NVIC_ID_CLEAR_PENDING_IRQ 0x06u /*!< CDD_Nvic_ClearPendingIrq() api service id */
#define NVIC_ID_NMI_HANDLER       0x07u /*!< NMI_Handler api service id */
#define NVIC_ID_HARDFAULT_HANDLER 0x08u /*!< HardFault_Handler api service id */
/**
 * @} */

/**
 * @defgroup NVIC_Error_Typse Nvic Developtmnet Error Types
 *
 * @{ */
#define NVIC_E_PARAM_IRQ          0x00u /*!< API Service called with wrong parameter */
#define NVIC_E_PARAM_PRIORITY     0x01u /*!< API Service called with wrong parameter */
#define NVIC_E_NMI_ENTRY          0x02u /*!< NMI vector called unnecesary */
#define NVIC_E_HARDFAULT_ENTRY    0x03u /*!< HardFault vector called unnecesary */
/**
 * @} */

#endif /* NVIC_TYPES_H__ */

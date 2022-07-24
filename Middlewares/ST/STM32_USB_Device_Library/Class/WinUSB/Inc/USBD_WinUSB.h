/**
  ******************************************************************************
  * @file    usbd_cdc.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_cdc.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_WinUSB_H
#define __USBD_WinUSB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup usbd_cdc
  * @brief This file is the Header file for usbd_cdc.c
  * @{
  */


/** @defgroup usbd_cdc_Exported_Defines
  * @{
  */
#define USBD_WinUSB_IN_EP                                   0x81U  /* EP1 for data IN */
#define USBD_WinUSB_OUT_EP                                  0x01U  /* EP1 for data OUT */
//#define CDC_CMD_EP                                  0x82U  /* EP2 for CDC commands */

//#ifndef CDC_HS_BINTERVAL
//#define CDC_HS_BINTERVAL                            0x10U
//#endif /* CDC_HS_BINTERVAL */

//#ifndef CDC_FS_BINTERVAL
//#define CDC_FS_BINTERVAL                            0x10U
//#endif /* CDC_FS_BINTERVAL */

/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
#define USBD_WinUSB_DATA_HS_MAX_PACKET_SIZE                 512U  /* Endpoint IN & OUT Packet size */
#define USBD_WinUSB_DATA_FS_MAX_PACKET_SIZE                 64U  /* Endpoint IN & OUT Packet size */

#define USBD_WinUSB_DATA_HS_IN_PACKET_SIZE                  USBD_WinUSB_DATA_HS_MAX_PACKET_SIZE
#define USBD_WinUSB_DATA_HS_OUT_PACKET_SIZE                 USBD_WinUSB_DATA_HS_MAX_PACKET_SIZE

#define USBD_WinUSB_DATA_FS_IN_PACKET_SIZE                  USBD_WinUSB_DATA_FS_MAX_PACKET_SIZE
#define USBD_WinUSB_DATA_FS_OUT_PACKET_SIZE                 USBD_WinUSB_DATA_FS_MAX_PACKET_SIZE

//#define CDC_REQ_MAX_DATA_SIZE                       0x7U
///*---------------------------------------------------------------------*/
///*  CDC definitions                                                    */
///*---------------------------------------------------------------------*/
//#define CDC_SEND_ENCAPSULATED_COMMAND               0x00U
//#define CDC_GET_ENCAPSULATED_RESPONSE               0x01U
//#define CDC_SET_COMM_FEATURE                        0x02U
//#define CDC_GET_COMM_FEATURE                        0x03U
//#define CDC_CLEAR_COMM_FEATURE                      0x04U
//#define CDC_SET_LINE_CODING                         0x20U
//#define CDC_GET_LINE_CODING                         0x21U
//#define CDC_SET_CONTROL_LINE_STATE                  0x22U
//#define CDC_SEND_BREAK                              0x23U

/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */

/**
  * @}
  */
//typedef struct
//{
//  uint32_t bitrate;
//  uint8_t  format;
//  uint8_t  paritytype;
//  uint8_t  datatype;
//} USBD_CDC_LineCodingTypeDef;

typedef struct _USBD_WinUSB_Itf
{
  int8_t (* Init)(void);
  int8_t (* DeInit)(void);
//  int8_t (* Control)(uint8_t cmd, uint8_t *pbuf, uint16_t length);
  int8_t (* Receive)(uint8_t *Buf, uint32_t *Len);
  int8_t (* TransmitCplt)(uint8_t *Buf, uint32_t *Len, uint8_t epnum);
} USBD_WinUSB_ItfTypeDef;


typedef struct
{
  uint32_t data[USBD_WinUSB_DATA_HS_MAX_PACKET_SIZE / 4U];      /* Force 32bits alignment */
  uint8_t  CmdOpCode;
  uint8_t  CmdLength;
  uint8_t  *RxBuffer;
  uint8_t  *TxBuffer;
  uint32_t RxLength;
  uint32_t TxLength;

  __IO uint32_t TxState;
  __IO uint32_t RxState;
} USBD_WinUSB_HandleTypeDef;



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef USBD_WinUSB;
#define USBD_WinUSB_CLASS &USBD_WinUSB
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
uint8_t USBD_WinUSB_RegisterInterface(USBD_HandleTypeDef *pdev,
                                   USBD_WinUSB_ItfTypeDef *fops);

uint8_t USBD_WinUSB_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff,
                             uint32_t length);

uint8_t USBD_WinUSB_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff);
uint8_t USBD_WinUSB_ReceivePacket(USBD_HandleTypeDef *pdev);
uint8_t USBD_WinUSB_TransmitPacket(USBD_HandleTypeDef *pdev);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_CDC_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

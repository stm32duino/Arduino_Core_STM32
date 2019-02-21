/**
  ******************************************************************************
  * @file    usbh_core.c
  * @author  MCD Application Team
  * @brief   This file implements the functions for the core state machine process
  *          the enumeration and the control transfer process
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "usbh_core.h"


/** @addtogroup USBH_LIB
  * @{
  */

/** @addtogroup USBH_LIB_CORE
  * @{
  */

/** @defgroup USBH_CORE
  * @brief This file handles the basic enumeration when a device is connected
  *          to the host.
  * @{
  */


/** @defgroup USBH_CORE_Private_Defines
  * @{
  */
#define USBH_ADDRESS_DEFAULT                     0x00U
#define USBH_ADDRESS_ASSIGNED                    0x01U
#define USBH_MPS_DEFAULT                         0x40U
/**
  * @}
  */

/** @defgroup USBH_CORE_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup USBH_CORE_Private_Variables
  * @{
  */
#if (USBH_USE_OS == 1U)
#if (osCMSIS >= 0x20000U)
osThreadAttr_t USBH_Thread_Atrr;
#endif
#endif


/**
  * @}
  */


/** @defgroup USBH_CORE_Private_Functions
  * @{
  */
static USBH_StatusTypeDef  USBH_HandleEnum(USBH_HandleTypeDef *phost);
static void                USBH_HandleSof(USBH_HandleTypeDef *phost);
static USBH_StatusTypeDef  DeInitStateMachine(USBH_HandleTypeDef *phost);

#if (USBH_USE_OS == 1U)
#if (osCMSIS < 0x20000U)
static void USBH_Process_OS(void const *argument);
#else
static void USBH_Process_OS(void *argument);
#endif
#endif

/**
  * @brief  HCD_Init
  *         Initialize the HOST Core.
  * @param  phost: Host Handle
  * @param  pUsrFunc: User Callback
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_Init(USBH_HandleTypeDef *phost, void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t id), uint8_t id)
{
  /* Check whether the USB Host handle is valid */
  if (phost == NULL) {
    USBH_ErrLog("Invalid Host handle");
    return USBH_FAIL;
  }

  /* Set DRiver ID */
  phost->id = id;

  /* Unlink class*/
  phost->pActiveClass = NULL;
  phost->ClassNumber = 0U;

  /* Restore default states and prepare EP0 */
  DeInitStateMachine(phost);

  /* Assign User process */
  if (pUsrFunc != NULL) {
    phost->pUser = pUsrFunc;
  }

#if (USBH_USE_OS == 1U)
#if (osCMSIS < 0x20000U)

  /* Create USB Host Queue */
  osMessageQDef(USBH_Queue, MSGQUEUE_OBJECTS, uint16_t);
  phost->os_event = osMessageCreate(osMessageQ(USBH_Queue), NULL);

  /* Create USB Host Task */
#if defined (USBH_PROCESS_STACK_SIZE)
  osThreadDef(USBH_Thread, USBH_Process_OS, USBH_PROCESS_PRIO, 0U, USBH_PROCESS_STACK_SIZE);
#else
  osThreadDef(USBH_Thread, USBH_Process_OS, USBH_PROCESS_PRIO, 0U, 8U * configMINIMAL_STACK_SIZE);
#endif /* defined (USBH_PROCESS_STACK_SIZE) */

  phost->thread = osThreadCreate(osThread(USBH_Thread), phost);

#else

  /* Create USB Host Queue */
  phost->os_event = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(uint32_t), NULL);

  /* Create USB Host Task */
  USBH_Thread_Atrr.name = "USBH_Queue";

#if defined (USBH_PROCESS_STACK_SIZE)
  USBH_Thread_Atrr.stack_size = USBH_PROCESS_STACK_SIZE;
#else
  USBH_Thread_Atrr.stack_size = (8U * configMINIMAL_STACK_SIZE);
#endif /* defined (USBH_PROCESS_STACK_SIZE) */

  USBH_Thread_Atrr.priority = USBH_PROCESS_PRIO;
  phost->thread = osThreadNew(USBH_Process_OS, phost, &USBH_Thread_Atrr);

#endif /* (osCMSIS < 0x20000U) */
#endif /* (USBH_USE_OS == 1U) */

  /* Initialize low level driver */
  USBH_LL_Init(phost);

  return USBH_OK;
}

/**
  * @brief  HCD_Init
  *         De-Initialize the Host portion of the driver.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_DeInit(USBH_HandleTypeDef *phost)
{
  DeInitStateMachine(phost);

  if (phost->pData != NULL) {
    USBH_free(phost->pActiveClass->pData);
    phost->pActiveClass->pData = NULL;
    USBH_LL_Stop(phost);
  }

  return USBH_OK;
}

/**
  * @brief  DeInitStateMachine
  *         De-Initialize the Host state machine.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef  DeInitStateMachine(USBH_HandleTypeDef *phost)
{
  uint32_t i = 0U;

  /* Clear Pipes flags*/
  for (; i < USBH_MAX_PIPES_NBR; i++) {
    phost->Pipes[i] = 0U;
  }

  for (i = 0U; i < USBH_MAX_DATA_BUFFER; i++) {
    phost->device.Data[i] = 0U;
  }

  phost->gState = HOST_IDLE;
  phost->EnumState = ENUM_IDLE;
  phost->RequestState = CMD_SEND;
  phost->Timer = 0U;

  phost->Control.state = CTRL_SETUP;
  phost->Control.pipe_size = USBH_MPS_DEFAULT;
  phost->Control.errorcount = 0U;

  phost->device.address = USBH_ADDRESS_DEFAULT;
  phost->device.speed   = USBH_SPEED_FULL;

  return USBH_OK;
}

/**
  * @brief  USBH_RegisterClass
  *         Link class driver to Host Core.
  * @param  phost : Host Handle
  * @param  pclass: Class handle
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_RegisterClass(USBH_HandleTypeDef *phost, USBH_ClassTypeDef *pclass)
{
  USBH_StatusTypeDef   status = USBH_OK;

  if (pclass != 0) {
    if (phost->ClassNumber < USBH_MAX_NUM_SUPPORTED_CLASS) {
      /* link the class to the USB Host handle */
      phost->pClass[phost->ClassNumber++] = pclass;
      status = USBH_OK;
    } else {
      USBH_ErrLog("Max Class Number reached");
      status = USBH_FAIL;
    }
  } else {
    USBH_ErrLog("Invalid Class handle");
    status = USBH_FAIL;
  }

  return status;
}

/**
  * @brief  USBH_SelectInterface
  *         Select current interface.
  * @param  phost: Host Handle
  * @param  interface: Interface number
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_SelectInterface(USBH_HandleTypeDef *phost, uint8_t interface)
{
  USBH_StatusTypeDef   status = USBH_OK;

  if (interface < phost->device.CfgDesc.bNumInterfaces) {
    phost->device.current_interface = interface;
    USBH_UsrLog("Switching to Interface (#%d)", interface);
    USBH_UsrLog("Class    : %xh", phost->device.CfgDesc.Itf_Desc[interface].bInterfaceClass);
    USBH_UsrLog("SubClass : %xh", phost->device.CfgDesc.Itf_Desc[interface].bInterfaceSubClass);
    USBH_UsrLog("Protocol : %xh", phost->device.CfgDesc.Itf_Desc[interface].bInterfaceProtocol);
  } else {
    USBH_ErrLog("Cannot Select This Interface.");
    status = USBH_FAIL;
  }
  return status;
}

/**
  * @brief  USBH_GetActiveClass
  *         Return Device Class.
  * @param  phost: Host Handle
  * @param  interface: Interface index
  * @retval Class Code
  */
uint8_t USBH_GetActiveClass(USBH_HandleTypeDef *phost)
{
  return (phost->device.CfgDesc.Itf_Desc[0].bInterfaceClass);
}
/**
  * @brief  USBH_FindInterface
  *         Find the interface index for a specific class.
  * @param  phost: Host Handle
  * @param  Class: Class code
  * @param  SubClass: SubClass code
  * @param  Protocol: Protocol code
  * @retval interface index in the configuration structure
  * @note : (1)interface index 0xFF means interface index not found
  */
uint8_t  USBH_FindInterface(USBH_HandleTypeDef *phost, uint8_t Class, uint8_t SubClass, uint8_t Protocol)
{
  USBH_InterfaceDescTypeDef    *pif ;
  USBH_CfgDescTypeDef          *pcfg ;
  uint8_t                        if_ix = 0U;

  pif = (USBH_InterfaceDescTypeDef *)0;
  pcfg = &phost->device.CfgDesc;

  while (if_ix < USBH_MAX_NUM_INTERFACES) {
    pif = &pcfg->Itf_Desc[if_ix];
    if (((pif->bInterfaceClass == Class) || (Class == 0xFFU)) &&
        ((pif->bInterfaceSubClass == SubClass) || (SubClass == 0xFFU)) &&
        ((pif->bInterfaceProtocol == Protocol) || (Protocol == 0xFFU))) {
      return  if_ix;
    }
    if_ix++;
  }
  return 0xFFU;
}

/**
  * @brief  USBH_FindInterfaceIndex
  *         Find the interface index for a specific class interface and alternate setting number.
  * @param  phost: Host Handle
  * @param  interface_number: interface number
  * @param  alt_settings    : alternate setting number
  * @retval interface index in the configuration structure
  * @note : (1)interface index 0xFF means interface index not found
  */
uint8_t  USBH_FindInterfaceIndex(USBH_HandleTypeDef *phost, uint8_t interface_number, uint8_t alt_settings)
{
  USBH_InterfaceDescTypeDef    *pif ;
  USBH_CfgDescTypeDef          *pcfg ;
  uint8_t                        if_ix = 0U;

  pif = (USBH_InterfaceDescTypeDef *)0;
  pcfg = &phost->device.CfgDesc;

  while (if_ix < USBH_MAX_NUM_INTERFACES) {
    pif = &pcfg->Itf_Desc[if_ix];
    if ((pif->bInterfaceNumber == interface_number) && (pif->bAlternateSetting == alt_settings)) {
      return  if_ix;
    }
    if_ix++;
  }
  return 0xFFU;
}

/**
  * @brief  USBH_Start
  *         Start the USB Host Core.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_Start(USBH_HandleTypeDef *phost)
{
  /* Start the low level driver  */
  USBH_LL_Start(phost);

  /* Activate VBUS on the port */
  USBH_LL_DriverVBUS(phost, TRUE);

  return USBH_OK;
}

/**
  * @brief  USBH_Stop
  *         Stop the USB Host Core.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_Stop(USBH_HandleTypeDef *phost)
{
  /* Stop and cleanup the low level driver  */
  USBH_LL_Stop(phost);

  /* DeActivate VBUS on the port */
  USBH_LL_DriverVBUS(phost, FALSE);

  /* FRee Control Pipes */
  USBH_FreePipe(phost, phost->Control.pipe_in);
  USBH_FreePipe(phost, phost->Control.pipe_out);

  return USBH_OK;
}

/**
  * @brief  HCD_ReEnumerate
  *         Perform a new Enumeration phase.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_ReEnumerate(USBH_HandleTypeDef *phost)
{
  /*Stop Host */
  USBH_Stop(phost);

  /*Device has disconnected, so wait for 200 ms */
  USBH_Delay(200U);

  /* Set State machines in default state */
  DeInitStateMachine(phost);

  /* Start again the host */
  USBH_Start(phost);

#if (USBH_USE_OS == 1U)
  phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
  (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
  (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif

  return USBH_OK;
}

/**
  * @brief  USBH_Process
  *         Background process of the USB Core.
  * @param  phost: Host Handle
  * @retval USBH Status
  */
USBH_StatusTypeDef  USBH_Process(USBH_HandleTypeDef *phost)
{
  __IO USBH_StatusTypeDef status = USBH_FAIL;
  uint8_t idx = 0U;

  /* check for Host port events */
  if (((USBH_IsPortEnabled(phost) == 0U)) && (phost->gState != HOST_IDLE)) {
    if (phost->gState != HOST_DEV_DISCONNECTED) {
      phost->gState = HOST_DEV_DISCONNECTED;
    }
  }

  switch (phost->gState) {
    case HOST_IDLE :

      if (phost->device.is_connected) {
        /* Wait for 200 ms after connection */
        phost->gState = HOST_DEV_WAIT_FOR_ATTACHMENT;
        USBH_Delay(200U);
        USBH_LL_ResetPort(phost);

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }
      break;

    case HOST_DEV_WAIT_FOR_ATTACHMENT: /* Wait for Port Eabled */

      if (phost->device.PortEnabled == 1U) {
        phost->gState = HOST_DEV_ATTACHED;
      }
      break;

    case HOST_DEV_ATTACHED :

      USBH_UsrLog("USB Device Attached");

      /* Wait for 100 ms after Reset */
      USBH_Delay(100U);

      phost->device.speed = USBH_LL_GetSpeed(phost);

      phost->gState = HOST_ENUMERATION;

      phost->Control.pipe_out = USBH_AllocPipe(phost, 0x00U);
      phost->Control.pipe_in  = USBH_AllocPipe(phost, 0x80U);


      /* Open Control pipes */
      USBH_OpenPipe(phost,
                    phost->Control.pipe_in,
                    0x80U,
                    phost->device.address,
                    phost->device.speed,
                    USBH_EP_CONTROL,
                    (uint16_t)phost->Control.pipe_size);

      /* Open Control pipes */
      USBH_OpenPipe(phost,
                    phost->Control.pipe_out,
                    0x00U,
                    phost->device.address,
                    phost->device.speed,
                    USBH_EP_CONTROL,
                    (uint16_t)phost->Control.pipe_size);

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      break;

    case HOST_ENUMERATION:
      /* Check for enumeration status */
      if (USBH_HandleEnum(phost) == USBH_OK) {
        /* The function shall return USBH_OK when full enumeration is complete */
        USBH_UsrLog("Enumeration done.");
        phost->device.current_interface = 0U;
        if (phost->device.DevDesc.bNumConfigurations == 1U) {
          USBH_UsrLog("This device has only 1 configuration.");
          phost->gState  = HOST_SET_CONFIGURATION;

        } else {
          phost->gState  = HOST_INPUT;
        }

      }
      break;

    case HOST_INPUT: {
        /* user callback for end of device basic enumeration */
        if (phost->pUser != NULL) {
          phost->pUser(phost, HOST_USER_SELECT_CONFIGURATION);
          phost->gState = HOST_SET_CONFIGURATION;

#if (USBH_USE_OS == 1U)
          phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
          (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
          (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
        }
      }
      break;

    case HOST_SET_CONFIGURATION:
      /* set configuration */
      if (USBH_SetCfg(phost, (uint16_t)phost->device.CfgDesc.bConfigurationValue) == USBH_OK) {
        phost->gState  = HOST_SET_WAKEUP_FEATURE;
        USBH_UsrLog("Default configuration set.");
      }

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      break;

    case  HOST_SET_WAKEUP_FEATURE:

      if ((phost->device.CfgDesc.bmAttributes) & (1U << 5)) {
        if (USBH_SetFeature(phost, FEATURE_SELECTOR_REMOTEWAKEUP) == USBH_OK) {
          USBH_UsrLog("Device remote wakeup enabled");
          phost->gState  = HOST_CHECK_CLASS;
        }
      } else {
        phost->gState  = HOST_CHECK_CLASS;
      }

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      break;

    case HOST_CHECK_CLASS:

      if (phost->ClassNumber == 0U) {
        USBH_UsrLog("No Class has been registered.");
      } else {
        phost->pActiveClass = NULL;

        for (idx = 0U; idx < USBH_MAX_NUM_SUPPORTED_CLASS; idx++) {
          if (phost->pClass[idx]->ClassCode == phost->device.CfgDesc.Itf_Desc[0].bInterfaceClass) {
            phost->pActiveClass = phost->pClass[idx];
          }
        }

        if (phost->pActiveClass != NULL) {
          if (phost->pActiveClass->Init(phost) == USBH_OK) {
            phost->gState  = HOST_CLASS_REQUEST;
            USBH_UsrLog("%s class started.", phost->pActiveClass->Name);

            /* Inform user that a class has been activated */
            phost->pUser(phost, HOST_USER_CLASS_SELECTED);
          } else {
            phost->gState  = HOST_ABORT_STATE;
            USBH_UsrLog("Device not supporting %s class.", phost->pActiveClass->Name);
          }
        } else {
          phost->gState  = HOST_ABORT_STATE;
          USBH_UsrLog("No registered class for this device.");
        }
      }

#if (USBH_USE_OS == 1U)
      phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
      (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
      (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      break;

    case HOST_CLASS_REQUEST:
      /* process class standard control requests state machine */
      if (phost->pActiveClass != NULL) {
        status = phost->pActiveClass->Requests(phost);

        if (status == USBH_OK) {
          phost->gState  = HOST_CLASS;
        }
      } else {
        phost->gState  = HOST_ABORT_STATE;
        USBH_ErrLog("Invalid Class Driver.");

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }

      break;
    case HOST_CLASS:
      /* process class state machine */
      if (phost->pActiveClass != NULL) {
        phost->pActiveClass->BgndProcess(phost);
      }
      break;

    case HOST_DEV_DISCONNECTED :

      DeInitStateMachine(phost);

      /* Re-Initilaize Host for new Enumeration */
      if (phost->pActiveClass != NULL) {
        phost->pActiveClass->DeInit(phost);
        phost->pActiveClass = NULL;
      }
      break;

    case HOST_ABORT_STATE:
    default :
      break;
  }
  return USBH_OK;
}


/**
  * @brief  USBH_HandleEnum
  *         This function includes the complete enumeration process
  * @param  phost: Host Handle
  * @retval USBH_Status
  */
static USBH_StatusTypeDef USBH_HandleEnum(USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef Status = USBH_BUSY;

  switch (phost->EnumState) {
    case ENUM_IDLE:
      /* Get Device Desc for only 1st 8 bytes : To get EP0 MaxPacketSize */
      if (USBH_Get_DevDesc(phost, 8U) == USBH_OK) {
        phost->Control.pipe_size = phost->device.DevDesc.bMaxPacketSize;

        phost->EnumState = ENUM_GET_FULL_DEV_DESC;

        /* modify control channels configuration for MaxPacket size */
        USBH_OpenPipe(phost,
                      phost->Control.pipe_in,
                      0x80U,
                      phost->device.address,
                      phost->device.speed,
                      USBH_EP_CONTROL,
                      (uint16_t)phost->Control.pipe_size);

        /* Open Control pipes */
        USBH_OpenPipe(phost,
                      phost->Control.pipe_out,
                      0x00U,
                      phost->device.address,
                      phost->device.speed,
                      USBH_EP_CONTROL,
                      (uint16_t)phost->Control.pipe_size);

      }
      break;

    case ENUM_GET_FULL_DEV_DESC:
      /* Get FULL Device Desc  */
      if (USBH_Get_DevDesc(phost, USB_DEVICE_DESC_SIZE) == USBH_OK) {
        USBH_UsrLog("PID: %xh", phost->device.DevDesc.idProduct);
        USBH_UsrLog("VID: %xh", phost->device.DevDesc.idVendor);

        phost->EnumState = ENUM_SET_ADDR;

      }
      break;

    case ENUM_SET_ADDR:
      /* set address */
      if (USBH_SetAddress(phost, USBH_DEVICE_ADDRESS) == USBH_OK) {
        USBH_Delay(2U);
        phost->device.address = USBH_DEVICE_ADDRESS;

        /* user callback for device address assigned */
        USBH_UsrLog("Address (#%d) assigned.", phost->device.address);
        phost->EnumState = ENUM_GET_CFG_DESC;

        /* modify control channels to update device address */
        USBH_OpenPipe(phost,
                      phost->Control.pipe_in,
                      0x80U,
                      phost->device.address,
                      phost->device.speed,
                      USBH_EP_CONTROL,
                      (uint16_t)phost->Control.pipe_size);

        /* Open Control pipes */
        USBH_OpenPipe(phost,
                      phost->Control.pipe_out,
                      0x00U,
                      phost->device.address,
                      phost->device.speed,
                      USBH_EP_CONTROL,
                      (uint16_t)phost->Control.pipe_size);
      }
      break;

    case ENUM_GET_CFG_DESC:
      /* get standard configuration descriptor */
      if (USBH_Get_CfgDesc(phost,
                           USB_CONFIGURATION_DESC_SIZE) == USBH_OK) {
        phost->EnumState = ENUM_GET_FULL_CFG_DESC;
      }
      break;

    case ENUM_GET_FULL_CFG_DESC:
      /* get FULL config descriptor (config, interface, endpoints) */
      if (USBH_Get_CfgDesc(phost,
                           phost->device.CfgDesc.wTotalLength) == USBH_OK) {
        phost->EnumState = ENUM_GET_MFC_STRING_DESC;
      }
      break;

    case ENUM_GET_MFC_STRING_DESC:
      if (phost->device.DevDesc.iManufacturer != 0U) {
        /* Check that Manufacturer String is available */

        if (USBH_Get_StringDesc(phost,
                                phost->device.DevDesc.iManufacturer,
                                phost->device.Data,
                                0xFFU) == USBH_OK) {
          /* User callback for Manufacturing string */
          USBH_UsrLog("Manufacturer : %s", (char *)(void *)phost->device.Data);
          phost->EnumState = ENUM_GET_PRODUCT_STRING_DESC;

#if (USBH_USE_OS == 1U)
          phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
          (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
          (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
        }
      } else {
        USBH_UsrLog("Manufacturer : N/A");
        phost->EnumState = ENUM_GET_PRODUCT_STRING_DESC;

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }
      break;

    case ENUM_GET_PRODUCT_STRING_DESC:
      if (phost->device.DevDesc.iProduct != 0U) {
        /* Check that Product string is available */
        if (USBH_Get_StringDesc(phost,
                                phost->device.DevDesc.iProduct,
                                phost->device.Data,
                                0xFFU) == USBH_OK) {
          /* User callback for Product string */
          USBH_UsrLog("Product : %s", (char *)(void *)phost->device.Data);
          phost->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;
        }
      } else {
        USBH_UsrLog("Product : N/A");
        phost->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }
      break;

    case ENUM_GET_SERIALNUM_STRING_DESC:
      if (phost->device.DevDesc.iSerialNumber != 0U) {
        /* Check that Serial number string is available */
        if (USBH_Get_StringDesc(phost,
                                phost->device.DevDesc.iSerialNumber,
                                phost->device.Data,
                                0xFFU) == USBH_OK) {
          /* User callback for Serial number string */
          USBH_UsrLog("Serial Number : %s", (char *)(void *)phost->device.Data);
          Status = USBH_OK;
        }
      } else {
        USBH_UsrLog("Serial Number : N/A");
        Status = USBH_OK;

#if (USBH_USE_OS == 1U)
        phost->os_msg = (uint32_t)USBH_STATE_CHANGED_EVENT;
#if (osCMSIS < 0x20000U)
        (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
        (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif
      }
      break;

    default:
      break;
  }
  return Status;
}

/**
  * @brief  USBH_LL_SetTimer
  *         Set the initial Host Timer tick
  * @param  phost: Host Handle
  * @retval None
  */
void  USBH_LL_SetTimer(USBH_HandleTypeDef *phost, uint32_t time)
{
  phost->Timer = time;
}
/**
  * @brief  USBH_LL_IncTimer
  *         Increment Host Timer tick
  * @param  phost: Host Handle
  * @retval None
  */
void  USBH_LL_IncTimer(USBH_HandleTypeDef *phost)
{
  phost->Timer ++;
  USBH_HandleSof(phost);
}

/**
  * @brief  USBH_HandleSof
  *         Call SOF process
  * @param  phost: Host Handle
  * @retval None
  */
static void  USBH_HandleSof(USBH_HandleTypeDef *phost)
{
  if ((phost->gState == HOST_CLASS) && (phost->pActiveClass != NULL)) {
    phost->pActiveClass->SOFProcess(phost);
  }
}

/**
  * @brief  USBH_PortEnabled
  *         Port Enabled
  * @param  phost: Host Handle
  * @retval None
  */
void USBH_LL_PortEnabled(USBH_HandleTypeDef *phost)
{
  phost->device.PortEnabled = 1U;

  return;
}

/**
  * @brief  USBH_LL_PortDisabled
  *         Port Disabled
  * @param  phost: Host Handle
  * @retval None
  */
void USBH_LL_PortDisabled(USBH_HandleTypeDef *phost)
{
  phost->device.PortEnabled = 0U;

  return;
}

/**
  * @brief  HCD_IsPortEnabled
  *         Is Port Enabled
  * @param  phost: Host Handle
  * @retval None
  */
uint8_t USBH_IsPortEnabled(USBH_HandleTypeDef *phost)
{
  return (phost->device.PortEnabled);
}


/**
  * @brief  USBH_LL_Connect
  *         Handle USB Host connexion event
  * @param  phost: Host Handle
  * @retval USBH_Status
  */
USBH_StatusTypeDef  USBH_LL_Connect(USBH_HandleTypeDef *phost)
{
  if (phost->gState == HOST_IDLE) {
    phost->device.is_connected = 1U;

    if (phost->pUser != NULL) {
      phost->pUser(phost, HOST_USER_CONNECTION);
    }
  } else {
    if (phost->device.PortEnabled == 1U) {
      phost->gState = HOST_DEV_ATTACHED;
    }
  }

#if (USBH_USE_OS == 1U)
  phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
  (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
  (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif

  return USBH_OK;
}

/**
  * @brief  USBH_LL_Disconnect
  *         Handle USB Host disconnection event
  * @param  phost: Host Handle
  * @retval USBH_Status
  */
USBH_StatusTypeDef  USBH_LL_Disconnect(USBH_HandleTypeDef *phost)
{
  /*Stop Host */
  USBH_LL_Stop(phost);

  /* FRee Control Pipes */
  USBH_FreePipe(phost, phost->Control.pipe_in);
  USBH_FreePipe(phost, phost->Control.pipe_out);

  phost->device.is_connected = 0U;

  if (phost->pUser != NULL) {
    phost->pUser(phost, HOST_USER_DISCONNECTION);
  }
  USBH_UsrLog("USB Device disconnected");

  /* Start the low level driver  */
  USBH_LL_Start(phost);

  phost->gState = HOST_DEV_DISCONNECTED;

#if (USBH_USE_OS == 1U)
  phost->os_msg = (uint32_t)USBH_PORT_EVENT;
#if (osCMSIS < 0x20000U)
  (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
  (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif
#endif

  return USBH_OK;
}


#if (USBH_USE_OS == 1U)
/**
  * @brief  USB Host Thread task
  * @param  pvParameters not used
  * @retval None
  */

#if (osCMSIS < 0x20000U)
static void USBH_Process_OS(void const *argument)
{
  osEvent event;

  for (;;) {
    event = osMessageGet(((USBH_HandleTypeDef *)argument)->os_event, osWaitForever);
    if (event.status == osEventMessage) {
      USBH_Process((USBH_HandleTypeDef *)argument);
    }
  }
}
#else
static void USBH_Process_OS(void *argument)
{
  osStatus_t status;

  for (;;) {
    status = osMessageQueueGet(((USBH_HandleTypeDef *)argument)->os_event,
                               &((USBH_HandleTypeDef *)argument)->os_msg, NULL, osWaitForever);
    if (status == osOK) {
      USBH_Process((USBH_HandleTypeDef *)argument);
    }
  }
}
#endif /* (osCMSIS < 0x20000U) */

/**
* @brief  USBH_LL_NotifyURBChange
*         Notify URB state Change
* @param  phost: Host handle
* @retval USBH Status
*/
USBH_StatusTypeDef  USBH_LL_NotifyURBChange(USBH_HandleTypeDef *phost)
{
  phost->os_msg = (uint32_t)USBH_PORT_EVENT;

#if (osCMSIS < 0x20000U)
  (void)osMessagePut(phost->os_event, phost->os_msg, 0U);
#else
  (void)osMessageQueuePut(phost->os_event, &phost->os_msg, 0U, NULL);
#endif

  return USBH_OK;
}
#endif
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

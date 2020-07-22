/**
  ******************************************************************************
  * @file    interrupt.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide an interface to enable/disable interruptions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "interrupt.h"
#if defined(STM32MP1xx)
  #include "lock_resource.h"
#endif
#if !defined(HAL_EXTI_MODULE_DISABLED)

/* Private Types */

/*As we can have only one interrupt/pin id, don't need to get the port info*/
typedef struct {
  IRQn_Type irqnb;
  std::function<void(void)> callback;
} gpio_irq_conf_str;

/* Private_Defines */
#define NB_EXTI   (16)

/* Private Variables */
static gpio_irq_conf_str gpio_irq_conf[NB_EXTI] = {
#if defined (STM32F0xx) || defined (STM32G0xx) || defined (STM32L0xx)
  {.irqnb = EXTI0_1_IRQn,   .callback = NULL}, //GPIO_PIN_0
  {.irqnb = EXTI0_1_IRQn,   .callback = NULL}, //GPIO_PIN_1
  {.irqnb = EXTI2_3_IRQn,   .callback = NULL}, //GPIO_PIN_2
  {.irqnb = EXTI2_3_IRQn,   .callback = NULL}, //GPIO_PIN_3
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_4
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_5
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_6
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_7
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_8
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_9
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_10
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_11
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_12
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_13
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}, //GPIO_PIN_14
  {.irqnb = EXTI4_15_IRQn,  .callback = NULL}  //GPIO_PIN_15
#elif defined (STM32MP1xx)
  {.irqnb = EXTI0_IRQn,     .callback = NULL}, //GPIO_PIN_0
  {.irqnb = EXTI1_IRQn,     .callback = NULL}, //GPIO_PIN_1
  {.irqnb = EXTI2_IRQn,     .callback = NULL}, //GPIO_PIN_2
  {.irqnb = EXTI3_IRQn,     .callback = NULL}, //GPIO_PIN_3
  {.irqnb = EXTI4_IRQn,     .callback = NULL}, //GPIO_PIN_4
  {.irqnb = EXTI5_IRQn,     .callback = NULL}, //GPIO_PIN_5
  {.irqnb = EXTI6_IRQn,     .callback = NULL}, //GPIO_PIN_6
  {.irqnb = EXTI7_IRQn,     .callback = NULL}, //GPIO_PIN_7
  {.irqnb = EXTI8_IRQn,     .callback = NULL}, //GPIO_PIN_8
  {.irqnb = EXTI9_IRQn,     .callback = NULL}, //GPIO_PIN_9
  {.irqnb = EXTI10_IRQn,    .callback = NULL}, //GPIO_PIN_10
  {.irqnb = EXTI11_IRQn,    .callback = NULL}, //GPIO_PIN_11
  {.irqnb = EXTI12_IRQn,    .callback = NULL}, //GPIO_PIN_12
  {.irqnb = EXTI13_IRQn,    .callback = NULL}, //GPIO_PIN_13
  {.irqnb = EXTI14_IRQn,    .callback = NULL}, //GPIO_PIN_14
  {.irqnb = EXTI15_IRQn,    .callback = NULL}  //GPIO_PIN_15
#else
  {.irqnb = EXTI0_IRQn,     .callback = NULL}, //GPIO_PIN_0
  {.irqnb = EXTI1_IRQn,     .callback = NULL}, //GPIO_PIN_1
  {.irqnb = EXTI2_IRQn,     .callback = NULL}, //GPIO_PIN_2
  {.irqnb = EXTI3_IRQn,     .callback = NULL}, //GPIO_PIN_3
  {.irqnb = EXTI4_IRQn,     .callback = NULL}, //GPIO_PIN_4
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_5
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_6
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_7
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_8
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_9
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_10
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_11
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_12
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_13
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_14
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}  //GPIO_PIN_15
#endif
};

/* Private Functions */
/**
  * @brief  This function returns the pin ID function of the HAL PIN definition
  * @param  pin : one of the gpio pin
  * @retval None
  */
static uint8_t get_pin_id(uint16_t pin)
{
  uint8_t id = 0;

  while (pin != 0x0001) {
    pin = pin >> 1;
    id++;
  }

  return id;
}
void stm32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, callback_function_t callback, uint32_t mode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t id = get_pin_id(pin);

#ifdef STM32F1xx
  uint8_t position;
  uint32_t CRxRegOffset = 0;
  uint32_t ODRRegOffset = 0;
  volatile uint32_t *CRxRegister;
  const uint32_t ConfigMask = 0x00000008; //MODE0 == 0x0 && CNF0 == 0x2
#else
  uint32_t pull;
#endif /* STM32F1xx */

  // GPIO pin configuration
  GPIO_InitStruct.Pin       = pin;
  GPIO_InitStruct.Mode      = mode;

  //read the pull mode directly in the register as no function exists to get it.
  //Do it in case the user already defines the IO through the digital io
  //interface
#ifndef STM32F1xx
  pull = port->PUPDR;
#ifdef GPIO_PUPDR_PUPD0
  pull &= (GPIO_PUPDR_PUPD0 << (id * 2));
  GPIO_InitStruct.Pull = (GPIO_PUPDR_PUPD0 & (pull >> (id * 2)));
#else
  pull &= (GPIO_PUPDR_PUPDR0 << (id * 2));
  GPIO_InitStruct.Pull = (GPIO_PUPDR_PUPDR0 & (pull >> (id * 2)));
#endif /* GPIO_PUPDR_PUPD0 */
#else
  CRxRegister = (pin < GPIO_PIN_8) ? &port->CRL : &port->CRH;

  for (position = 0; position < 16; position++) {
    if (pin == (0x0001 << position)) {
      CRxRegOffset = (pin < GPIO_PIN_8) ? (position << 2) : ((position - 8) << 2);
      ODRRegOffset = position;
    }
  }

  if ((*CRxRegister & ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << CRxRegOffset)) == (ConfigMask << CRxRegOffset)) {
    if ((port->ODR & (GPIO_ODR_ODR0 << ODRRegOffset)) == (GPIO_ODR_ODR0 << ODRRegOffset)) {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
    } else {
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
  } else {
    GPIO_InitStruct.Pull = GPIO_NOPULL;
  }
#endif /* STM32F1xx */

  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;

#if defined(STM32MP1xx)
  PERIPH_LOCK(port);
#endif

  HAL_GPIO_Init(port, &GPIO_InitStruct);

#if defined(STM32MP1xx)
  PERIPH_UNLOCK(port);
#endif

  gpio_irq_conf[id].callback = callback;

  // Enable and set EXTI Interrupt
  HAL_NVIC_SetPriority(gpio_irq_conf[id].irqnb, EXTI_IRQ_PRIO, EXTI_IRQ_SUBPRIO);
  HAL_NVIC_EnableIRQ(gpio_irq_conf[id].irqnb);
}

/**
  * @brief  This function enable the interruption on the selected port/pin
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  **@param  callback : callback to call when the interrupt falls
  * @param  mode : one of the supported interrupt mode defined in stm32_hal_gpio
  * @retval None
  */
void stm32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, void (*callback)(void), uint32_t mode)
{
  std::function<void(void)> _c = callback;
  stm32_interrupt_enable(port, pin, _c, mode);

}

/**
  * @brief  This function disable the interruption on the selected port/pin
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval None
  */
void stm32_interrupt_disable(GPIO_TypeDef *port, uint16_t pin)
{
  UNUSED(port);
  uint8_t id = get_pin_id(pin);
  gpio_irq_conf[id].callback = NULL;

  for (int i = 0; i < NB_EXTI; i++) {
    if (gpio_irq_conf[id].irqnb == gpio_irq_conf[i].irqnb
        && gpio_irq_conf[i].callback != NULL) {
      return;
    }
  }
  HAL_NVIC_DisableIRQ(gpio_irq_conf[id].irqnb);
}

/**
  * @brief This function his called by the HAL if the IRQ is valid
  * @param  GPIO_Pin : one of the gpio pin
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint8_t irq_id = get_pin_id(GPIO_Pin);

  if (gpio_irq_conf[irq_id].callback != NULL) {
    gpio_irq_conf[irq_id].callback();
  }
}

#if defined (STM32G0xx) || defined (STM32MP1xx)
/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  HAL_GPIO_EXTI_Callback(GPIO_Pin);
}
#endif

#if defined (STM32F0xx) || defined (STM32G0xx) || defined (STM32L0xx)
#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief This function handles external line 0 to 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_PIN_0; pin <= GPIO_PIN_1; pin = pin << 1) {
    HAL_GPIO_EXTI_IRQHandler(pin);
  }
}


/**
  * @brief This function handles external line 2 to 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_PIN_2; pin <= GPIO_PIN_3; pin = pin << 1) {
    HAL_GPIO_EXTI_IRQHandler(pin);
  }
}

/**
  * @brief This function handles external line 4 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_PIN_4; pin <= GPIO_PIN_15; pin = pin << 1) {
    HAL_GPIO_EXTI_IRQHandler(pin);
  }
}
#ifdef __cplusplus
}
#endif
#else
#ifdef __cplusplus
extern "C" {
#endif
/**
  * @brief This function handles external line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
  * @brief This function handles external line 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

/**
  * @brief This function handles external line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

/**
  * @brief This function handles external line 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

/**
  * @brief This function handles external line 4 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

#if !defined(STM32MP1xx)
/**
  * @brief This function handles external line 5 to 9 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_PIN_5; pin <= GPIO_PIN_9; pin = pin << 1) {
    HAL_GPIO_EXTI_IRQHandler(pin);
  }
}

/**
  * @brief This function handles external line 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_PIN_10; pin <= GPIO_PIN_15; pin = pin << 1) {
    HAL_GPIO_EXTI_IRQHandler(pin);
  }
}
#else /* STM32MP1xx */

/**
  * @brief This function handles external line 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

/**
  * @brief This function handles external line 6 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI6_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
}

/**
  * @brief This function handles external line 7 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI7_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}

/**
  * @brief This function handles external line 8 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI8_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
}

/**
  * @brief This function handles external line 9 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

/**
  * @brief This function handles external line 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}

/**
  * @brief This function handles external line 11 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI11_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}

/**
  * @brief This function handles external line 12 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI12_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}

/**
  * @brief This function handles external line 13 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI13_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

/**
  * @brief This function handles external line 14 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI14_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
}

/**
  * @brief This function handles external line 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}

#endif /* !STM32MP1xx */
#ifdef __cplusplus
}
#endif
#endif /* !HAL_EXTI_MODULE_DISABLED */
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

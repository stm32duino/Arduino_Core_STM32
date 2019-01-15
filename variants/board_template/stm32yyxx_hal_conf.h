/*
 * Copy the STM32 HAL config file from the targeted MCU Series HAL
 * from ../../system/Drivers/STM32YYxx_HAL_Driver/Inc/stm32yyxx_hal_conf_template.h
 * to
 * stm32yyxx_hal_conf.h
 * where 'yy' could be f0, f1, f2, f3, f4, f7, h7, l0, l1, l4)
 *
 * Example for a STM32 F4 based board:
 * cp ../../system/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_conf_template.h stm32f4xx_hal_conf.h
 *
 * Then edit it in order to:
 * - Disable undesired HAL modules by commenting line like:
 * "#define HAL_XXX_MODULE_ENABLED"
 * where "XXX" is the feature (ETH, I2S,...)
 * - Adjust HSE/HSI Values adaptation if needed
 * - Update any other configurations
 *
 * Note:
 * Below HAL module have to be disabled, they are handled thanks Arduino menu:
 *	HAL_UART_MODULE_ENABLED
 *	HAL_PCD_MODULE_ENABLED
 *
 */

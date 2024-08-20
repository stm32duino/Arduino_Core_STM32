# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(SrcWrapper INTERFACE)
add_library(SrcWrapper_usage INTERFACE)

target_include_directories(SrcWrapper_usage INTERFACE
  src
)


target_link_libraries(SrcWrapper_usage INTERFACE
  base_config
)

target_link_libraries(SrcWrapper INTERFACE SrcWrapper_usage)



add_library(SrcWrapper_bin OBJECT EXCLUDE_FROM_ALL
  src/HAL/stm32yyxx_hal.c
  src/HAL/stm32yyxx_hal_adc.c
  src/HAL/stm32yyxx_hal_adc_ex.c
  src/HAL/stm32yyxx_hal_can.c
  src/HAL/stm32yyxx_hal_cec.c
  src/HAL/stm32yyxx_hal_comp.c
  src/HAL/stm32yyxx_hal_comp_ex.c
  src/HAL/stm32yyxx_hal_cordic.c
  src/HAL/stm32yyxx_hal_cortex.c
  src/HAL/stm32yyxx_hal_crc.c
  src/HAL/stm32yyxx_hal_crc_ex.c
  src/HAL/stm32yyxx_hal_cryp.c
  src/HAL/stm32yyxx_hal_cryp_ex.c
  src/HAL/stm32yyxx_hal_dac.c
  src/HAL/stm32yyxx_hal_dac_ex.c
  src/HAL/stm32yyxx_hal_dcache.c
  src/HAL/stm32yyxx_hal_dcmi.c
  src/HAL/stm32yyxx_hal_dcmi_ex.c
  src/HAL/stm32yyxx_hal_dfsdm.c
  src/HAL/stm32yyxx_hal_dfsdm_ex.c
  src/HAL/stm32yyxx_hal_dma.c
  src/HAL/stm32yyxx_hal_dma2d.c
  src/HAL/stm32yyxx_hal_dma_ex.c
  src/HAL/stm32yyxx_hal_dsi.c
  src/HAL/stm32yyxx_hal_dts.c
  src/HAL/stm32yyxx_hal_eth.c
  src/HAL/stm32yyxx_hal_eth_ex.c
  src/HAL/stm32yyxx_hal_exti.c
  src/HAL/stm32yyxx_hal_fdcan.c
  src/HAL/stm32yyxx_hal_firewall.c
  src/HAL/stm32yyxx_hal_flash.c
  src/HAL/stm32yyxx_hal_flash_ex.c
  src/HAL/stm32yyxx_hal_flash_ramfunc.c
  src/HAL/stm32yyxx_hal_fmac.c
  src/HAL/stm32yyxx_hal_fmpi2c.c
  src/HAL/stm32yyxx_hal_fmpi2c_ex.c
  src/HAL/stm32yyxx_hal_fmpsmbus.c
  src/HAL/stm32yyxx_hal_fmpsmbus_ex.c
  src/HAL/stm32yyxx_hal_gfxmmu.c
  src/HAL/stm32yyxx_hal_gfxtim.c
  src/HAL/stm32yyxx_hal_gpio.c
  src/HAL/stm32yyxx_hal_gpio_ex.c
  src/HAL/stm32yyxx_hal_gpu2d.c
  src/HAL/stm32yyxx_hal_gtzc.c
  src/HAL/stm32yyxx_hal_hash.c
  src/HAL/stm32yyxx_hal_hash_ex.c
  src/HAL/stm32yyxx_hal_hcd.c
  src/HAL/stm32yyxx_hal_hrtim.c
  src/HAL/stm32yyxx_hal_hsem.c
  src/HAL/stm32yyxx_hal_i2c.c
  src/HAL/stm32yyxx_hal_i2c_ex.c
  src/HAL/stm32yyxx_hal_i2s.c
  src/HAL/stm32yyxx_hal_i2s_ex.c
  src/HAL/stm32yyxx_hal_i3c.c
  src/HAL/stm32yyxx_hal_icache.c
  src/HAL/stm32yyxx_hal_ipcc.c
  src/HAL/stm32yyxx_hal_irda.c
  src/HAL/stm32yyxx_hal_iwdg.c
  src/HAL/stm32yyxx_hal_jpeg.c
  src/HAL/stm32yyxx_hal_lcd.c
  src/HAL/stm32yyxx_hal_lptim.c
  src/HAL/stm32yyxx_hal_ltdc.c
  src/HAL/stm32yyxx_hal_ltdc_ex.c
  src/HAL/stm32yyxx_hal_mdf.c
  src/HAL/stm32yyxx_hal_mdios.c
  src/HAL/stm32yyxx_hal_mdma.c
  src/HAL/stm32yyxx_hal_mmc.c
  src/HAL/stm32yyxx_hal_mmc_ex.c
  src/HAL/stm32yyxx_hal_nand.c
  src/HAL/stm32yyxx_hal_nor.c
  src/HAL/stm32yyxx_hal_opamp.c
  src/HAL/stm32yyxx_hal_opamp_ex.c
  src/HAL/stm32yyxx_hal_ospi.c
  src/HAL/stm32yyxx_hal_otfdec.c
  src/HAL/stm32yyxx_hal_pccard.c
  src/HAL/stm32yyxx_hal_pcd.c
  src/HAL/stm32yyxx_hal_pcd_ex.c
  src/HAL/stm32yyxx_hal_pka.c
  src/HAL/stm32yyxx_hal_pssi.c
  src/HAL/stm32yyxx_hal_pwr.c
  src/HAL/stm32yyxx_hal_pwr_ex.c
  src/HAL/stm32yyxx_hal_qspi.c
  src/HAL/stm32yyxx_hal_ramcfg.c
  src/HAL/stm32yyxx_hal_ramecc.c
  src/HAL/stm32yyxx_hal_rcc.c
  src/HAL/stm32yyxx_hal_rcc_ex.c
  src/HAL/stm32yyxx_hal_rng.c
  src/HAL/stm32yyxx_hal_rng_ex.c
  src/HAL/stm32yyxx_hal_rtc.c
  src/HAL/stm32yyxx_hal_rtc_ex.c
  src/HAL/stm32yyxx_hal_sai.c
  src/HAL/stm32yyxx_hal_sai_ex.c
  src/HAL/stm32yyxx_hal_sd.c
  src/HAL/stm32yyxx_hal_sd_ex.c
  src/HAL/stm32yyxx_hal_sdadc.c
  src/HAL/stm32yyxx_hal_sdio.c
  src/HAL/stm32yyxx_hal_sdram.c
  src/HAL/stm32yyxx_hal_smartcard.c
  src/HAL/stm32yyxx_hal_smartcard_ex.c
  src/HAL/stm32yyxx_hal_smbus.c
  src/HAL/stm32yyxx_hal_smbus_ex.c
  src/HAL/stm32yyxx_hal_spdifrx.c
  src/HAL/stm32yyxx_hal_spi.c
  src/HAL/stm32yyxx_hal_spi_ex.c
  src/HAL/stm32yyxx_hal_sram.c
  src/HAL/stm32yyxx_hal_subghz.c
  src/HAL/stm32yyxx_hal_swpmi.c
  src/HAL/stm32yyxx_hal_tim.c
  src/HAL/stm32yyxx_hal_tim_ex.c
  src/HAL/stm32yyxx_hal_tsc.c
  src/HAL/stm32yyxx_hal_uart.c
  src/HAL/stm32yyxx_hal_uart_ex.c
  src/HAL/stm32yyxx_hal_usart.c
  src/HAL/stm32yyxx_hal_usart_ex.c
  src/HAL/stm32yyxx_hal_wwdg.c
  src/HAL/stm32yyxx_hal_xspi.c
  src/HardwareTimer.cpp
  src/LL/stm32yyxx_ll_adc.c
  src/LL/stm32yyxx_ll_bdma.c
  src/LL/stm32yyxx_ll_comp.c
  src/LL/stm32yyxx_ll_cordic.c
  src/LL/stm32yyxx_ll_crc.c
  src/LL/stm32yyxx_ll_crs.c
  src/LL/stm32yyxx_ll_dac.c
  src/LL/stm32yyxx_ll_delayblock.c
  src/LL/stm32yyxx_ll_dlyb.c
  src/LL/stm32yyxx_ll_dma.c
  src/LL/stm32yyxx_ll_dma2d.c
  src/LL/stm32yyxx_ll_exti.c
  src/LL/stm32yyxx_ll_fmac.c
  src/LL/stm32yyxx_ll_fmc.c
  src/LL/stm32yyxx_ll_fmpi2c.c
  src/LL/stm32yyxx_ll_fsmc.c
  src/LL/stm32yyxx_ll_gpio.c
  src/LL/stm32yyxx_ll_hrtim.c
  src/LL/stm32yyxx_ll_i2c.c
  src/LL/stm32yyxx_ll_i3c.c
  src/LL/stm32yyxx_ll_icache.c
  src/LL/stm32yyxx_ll_lpgpio.c
  src/LL/stm32yyxx_ll_lptim.c
  src/LL/stm32yyxx_ll_lpuart.c
  src/LL/stm32yyxx_ll_mdma.c
  src/LL/stm32yyxx_ll_opamp.c
  src/LL/stm32yyxx_ll_pka.c
  src/LL/stm32yyxx_ll_pwr.c
  src/LL/stm32yyxx_ll_rcc.c
  src/LL/stm32yyxx_ll_rng.c
  src/LL/stm32yyxx_ll_rtc.c
  src/LL/stm32yyxx_ll_sdmmc.c
  src/LL/stm32yyxx_ll_spi.c
  src/LL/stm32yyxx_ll_swpmi.c
  src/LL/stm32yyxx_ll_tim.c
  src/LL/stm32yyxx_ll_ucpd.c
  src/LL/stm32yyxx_ll_usart.c
  src/LL/stm32yyxx_ll_usb.c
  src/LL/stm32yyxx_ll_utils.c
  src/new.cpp
  src/stm32/analog.cpp
  src/stm32/bootloader.c
  src/stm32/clock.c
  src/stm32/core_callback.c
  src/stm32/dwt.c
  src/stm32/hw_config.c
  src/stm32/interrupt.cpp
  src/stm32/otp.c
  src/stm32/pinmap.c
  src/stm32/PortNames.c
  src/stm32/stm32_def.c
  src/stm32/system_stm32yyxx.c
  src/stm32/timer.c
  src/stm32/uart.c
  src/syscalls.c
)
target_link_libraries(SrcWrapper_bin PUBLIC SrcWrapper_usage)

target_link_libraries(SrcWrapper INTERFACE
  SrcWrapper_bin
  $<TARGET_OBJECTS:SrcWrapper_bin>
)


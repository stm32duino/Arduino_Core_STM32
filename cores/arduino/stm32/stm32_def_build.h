#ifndef _STM32_DEF_BUILD_
#define _STM32_DEF_BUILD_

#if !defined(CMSIS_STARTUP_FILE) && !defined(CUSTOM_STARTUP_FILE)
  #if defined(STM32F030x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f030x6.s"
  #elif defined(STM32F030x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f030x8.s"
  #elif defined(STM32F030xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f030xc.s"
  #elif defined(STM32F031x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f031x6.s"
  #elif defined(STM32F038xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f038xx.s"
  #elif defined(STM32F042x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f042x6.s"
  #elif defined(STM32F048xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f048xx.s"
  #elif defined(STM32F051x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f051x8.s"
  #elif defined(STM32F058xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f058xx.s"
  #elif defined(STM32F070x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f070x6.s"
  #elif defined(STM32F070xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f070xb.s"
  #elif defined(STM32F071xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f071xb.s"
  #elif defined(STM32F072xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f072xb.s"
  #elif defined(STM32F078xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f078xx.s"
  #elif defined(STM32F091xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f091xc.s"
  #elif defined(STM32F098xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f098xx.s"
  #elif defined(STM32F100xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f100xb.s"
  #elif defined(STM32F100xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f100xe.s"
  #elif defined(STM32F101x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f101x6.s"
  #elif defined(STM32F101xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f101xb.s"
  #elif defined(STM32F101xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f101xe.s"
  #elif defined(STM32F101xG)
    #define CMSIS_STARTUP_FILE "startup_stm32f101xg.s"
  #elif defined(STM32F102x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f102x6.s"
  #elif defined(STM32F102xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f102xb.s"
  #elif defined(STM32F103x6)
    #define CMSIS_STARTUP_FILE "startup_stm32f103x6.s"
  #elif defined(STM32F103xB)
    #define CMSIS_STARTUP_FILE "startup_stm32f103xb.s"
  #elif defined(STM32F103xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f103xe.s"
  #elif defined(STM32F103xG)
    #define CMSIS_STARTUP_FILE "startup_stm32f103xg.s"
  #elif defined(STM32F105xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f105xc.s"
  #elif defined(STM32F107xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f107xc.s"
  #elif defined(STM32F205xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f205xx.s"
  #elif defined(STM32F207xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f207xx.s"
  #elif defined(STM32F215xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f215xx.s"
  #elif defined(STM32F217xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f217xx.s"
  #elif defined(STM32F301x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f301x8.s"
  #elif defined(STM32F302x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f302x8.s"
  #elif defined(STM32F302xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f302xc.s"
  #elif defined(STM32F302xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f302xe.s"
  #elif defined(STM32F303x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f303x8.s"
  #elif defined(STM32F303xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f303xc.s"
  #elif defined(STM32F303xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f303xe.s"
  #elif defined(STM32F318xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f318xx.s"
  #elif defined(STM32F328xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f328xx.s"
  #elif defined(STM32F334x8)
    #define CMSIS_STARTUP_FILE "startup_stm32f334x8.s"
  #elif defined(STM32F358xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f358xx.s"
  #elif defined(STM32F373xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f373xc.s"
  #elif defined(STM32F378xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f378xx.s"
  #elif defined(STM32F398xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f398xx.s"
  #elif defined(STM32F401xC)
    #define CMSIS_STARTUP_FILE "startup_stm32f401xc.s"
  #elif defined(STM32F401xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f401xe.s"
  #elif defined(STM32F405xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f405xx.s"
  #elif defined(STM32F407xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f407xx.s"
  #elif defined(STM32F410Cx)
    #define CMSIS_STARTUP_FILE "startup_stm32f410cx.s"
  #elif defined(STM32F410Rx)
    #define CMSIS_STARTUP_FILE "startup_stm32f410rx.s"
  #elif defined(STM32F410Tx)
    #define CMSIS_STARTUP_FILE "startup_stm32f410tx.s"
  #elif defined(STM32F411xE)
    #define CMSIS_STARTUP_FILE "startup_stm32f411xe.s"
  #elif defined(STM32F412Cx)
    #define CMSIS_STARTUP_FILE "startup_stm32f412cx.s"
  #elif defined(STM32F412Rx)
    #define CMSIS_STARTUP_FILE "startup_stm32f412rx.s"
  #elif defined(STM32F412Vx)
    #define CMSIS_STARTUP_FILE "startup_stm32f412vx.s"
  #elif defined(STM32F412Zx)
    #define CMSIS_STARTUP_FILE "startup_stm32f412zx.s"
  #elif defined(STM32F413xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f413xx.s"
  #elif defined(STM32F415xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f415xx.s"
  #elif defined(STM32F417xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f417xx.s"
  #elif defined(STM32F423xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f423xx.s"
  #elif defined(STM32F427xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f427xx.s"
  #elif defined(STM32F429xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f429xx.s"
  #elif defined(STM32F437xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f437xx.s"
  #elif defined(STM32F439xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f439xx.s"
  #elif defined(STM32F446xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f446xx.s"
  #elif defined(STM32F469xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f469xx.s"
  #elif defined(STM32F479xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f479xx.s"
  #elif defined(STM32F722xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f722xx.s"
  #elif defined(STM32F723xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f723xx.s"
  #elif defined(STM32F730xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f730xx.s"
  #elif defined(STM32F732xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f732xx.s"
  #elif defined(STM32F733xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f733xx.s"
  #elif defined(STM32F745xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f745xx.s"
  #elif defined(STM32F746xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f746xx.s"
  #elif defined(STM32F750xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f750xx.s"
  #elif defined(STM32F756xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f756xx.s"
  #elif defined(STM32F765xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f765xx.s"
  #elif defined(STM32F767xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f767xx.s"
  #elif defined(STM32F769xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f769xx.s"
  #elif defined(STM32F777xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f777xx.s"
  #elif defined(STM32F779xx)
    #define CMSIS_STARTUP_FILE "startup_stm32f779xx.s"
  #elif defined(STM32G030xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g030xx.s"
  #elif defined(STM32G031xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g031xx.s"
  #elif defined(STM32G041xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g041xx.s"
  #elif defined(STM32G070xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g070xx.s"
  #elif defined(STM32G071xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g071xx.s"
  #elif defined(STM32G081xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g081xx.s"
  #elif defined(STM32G431xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g431xx.s"
  #elif defined(STM32G441xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g441xx.s"
  #elif defined(STM32G471xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g471xx.s"
  #elif defined(STM32G473xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g473xx.s"
  #elif defined(STM32G474xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g474xx.s"
  #elif defined(STM32G483xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g483xx.s"
  #elif defined(STM32G484xx)
    #define CMSIS_STARTUP_FILE "startup_stm32g484xx.s"
  #elif defined(STM32GBK1CB)
    #define CMSIS_STARTUP_FILE "startup_stm32gbk1cb.s"
  #elif defined(STM32H742xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h742xx.s"
  #elif defined(STM32H743xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h743xx.s"
  #elif defined(STM32H745xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h745xx.s"
  #elif defined(STM32H747xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h747xx.s"
  #elif defined(STM32H750xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h750xx.s"
  #elif defined(STM32H753xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h753xx.s"
  #elif defined(STM32H755xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h755xx.s"
  #elif defined(STM32H757xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h757xx.s"
  #elif defined(STM32H7A3xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h7a3xx.s"
  #elif defined(STM32H7A3xxQ)
    #define CMSIS_STARTUP_FILE "startup_stm32h7a3xxq.s"
  #elif defined(STM32H7B0xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h7b0xx.s"
  #elif defined(STM32H7B0xxQ)
    #define CMSIS_STARTUP_FILE "startup_stm32h7b0xxq.s"
  #elif defined(STM32H7B3xx)
    #define CMSIS_STARTUP_FILE "startup_stm32h7b3xx.s"
  #elif defined(STM32H7B3xxQ)
    #define CMSIS_STARTUP_FILE "startup_stm32h7b3xxq.s"
  #elif defined(STM32L010x4)
    #define CMSIS_STARTUP_FILE "startup_stm32l010x4.s"
  #elif defined(STM32L010x6)
    #define CMSIS_STARTUP_FILE "startup_stm32l010x6.s"
  #elif defined(STM32L010x8)
    #define CMSIS_STARTUP_FILE "startup_stm32l010x8.s"
  #elif defined(STM32L010xB)
    #define CMSIS_STARTUP_FILE "startup_stm32l010xb.s"
  #elif defined(STM32L011xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l011xx.s"
  #elif defined(STM32L021xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l021xx.s"
  #elif defined(STM32L031xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l031xx.s"
  #elif defined(STM32L041xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l041xx.s"
  #elif defined(STM32L051xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l051xx.s"
  #elif defined(STM32L052xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l052xx.s"
  #elif defined(STM32L053xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l053xx.s"
  #elif defined(STM32L061xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l061xx.s"
  #elif defined(STM32L062xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l062xx.s"
  #elif defined(STM32L063xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l063xx.s"
  #elif defined(STM32L071xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l071xx.s"
  #elif defined(STM32L072xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l072xx.s"
  #elif defined(STM32L073xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l073xx.s"
  #elif defined(STM32L081xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l081xx.s"
  #elif defined(STM32L082xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l082xx.s"
  #elif defined(STM32L083xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l083xx.s"
  #elif defined(STM32L100xB)
    #define CMSIS_STARTUP_FILE "startup_stm32l100xb.s"
  #elif defined(STM32L100xBA)
    #define CMSIS_STARTUP_FILE "startup_stm32l100xba.s"
  #elif defined(STM32L100xC)
    #define CMSIS_STARTUP_FILE "startup_stm32l100xc.s"
  #elif defined(STM32L151xB)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xb.s"
  #elif defined(STM32L151xBA)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xba.s"
  #elif defined(STM32L151xC)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xc.s"
  #elif defined(STM32L151xCA)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xca.s"
  #elif defined(STM32L151xD)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xd.s"
  #elif defined(STM32L151xDx)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xdx.s"
  #elif defined(STM32L151xE)
    #define CMSIS_STARTUP_FILE "startup_stm32l151xe.s"
  #elif defined(STM32L152xB)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xb.s"
  #elif defined(STM32L152xBA)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xba.s"
  #elif defined(STM32L152xC)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xc.s"
  #elif defined(STM32L152xCA)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xca.s"
  #elif defined(STM32L152xD)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xd.s"
  #elif defined(STM32L152xDx)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xdx.s"
  #elif defined(STM32L152xE)
    #define CMSIS_STARTUP_FILE "startup_stm32l152xe.s"
  #elif defined(STM32L162xC)
    #define CMSIS_STARTUP_FILE "startup_stm32l162xc.s"
  #elif defined(STM32L162xCA)
    #define CMSIS_STARTUP_FILE "startup_stm32l162xca.s"
  #elif defined(STM32L162xD)
    #define CMSIS_STARTUP_FILE "startup_stm32l162xd.s"
  #elif defined(STM32L162xDx)
    #define CMSIS_STARTUP_FILE "startup_stm32l162xdx.s"
  #elif defined(STM32L162xE)
    #define CMSIS_STARTUP_FILE "startup_stm32l162xe.s"
  #elif defined(STM32L412xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l412xx.s"
  #elif defined(STM32L422xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l422xx.s"
  #elif defined(STM32L431xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l431xx.s"
  #elif defined(STM32L432xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l432xx.s"
  #elif defined(STM32L433xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l433xx.s"
  #elif defined(STM32L442xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l442xx.s"
  #elif defined(STM32L443xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l443xx.s"
  #elif defined(STM32L451xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l451xx.s"
  #elif defined(STM32L452xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l452xx.s"
  #elif defined(STM32L462xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l462xx.s"
  #elif defined(STM32L471xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l471xx.s"
  #elif defined(STM32L475xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l475xx.s"
  #elif defined(STM32L476xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l476xx.s"
  #elif defined(STM32L485xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l485xx.s"
  #elif defined(STM32L486xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l486xx.s"
  #elif defined(STM32L496xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l496xx.s"
  #elif defined(STM32L4A6xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4a6xx.s"
  #elif defined(STM32L4P5xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4p5xx.s"
  #elif defined(STM32L4Q5xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4q5xx.s"
  #elif defined(STM32L4R5xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4r5xx.s"
  #elif defined(STM32L4R7xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4r7xx.s"
  #elif defined(STM32L4R9xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4r9xx.s"
  #elif defined(STM32L4S5xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4s5xx.s"
  #elif defined(STM32L4S7xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4s7xx.s"
  #elif defined(STM32L4S9xx)
    #define CMSIS_STARTUP_FILE "startup_stm32l4s9xx.s"
  #elif defined(STM32MP1xx)
    #define CMSIS_STARTUP_FILE "startup_stm32mp15xx.s"
  #elif defined(STM32WB30xx)
    #define CMSIS_STARTUP_FILE "startup_stm32wb30xx_cm4.s"
  #elif defined(STM32WB35xx)
    #define CMSIS_STARTUP_FILE "startup_stm32wb35xx_cm4.s"
  #elif defined(STM32WB50xx)
    #define CMSIS_STARTUP_FILE "startup_stm32wb50xx_cm4.s"
  #elif defined(STM32WB55xx)
    #define CMSIS_STARTUP_FILE "startup_stm32wb55xx_cm4.s"
  #elif defined(STM32WB5Mxx)
    #define CMSIS_STARTUP_FILE "startup_stm32wb5mxx_cm4.s"
  #else
    #error UNKNOWN CHIP
  #endif
#else
  #warning "No CMSIS startup file defined, custom one should be used"
#endif /* !CMSIS_STARTUP_FILE && !CUSTOM_STARTUP_FILE */
#endif /* _STM32_DEF_BUILD_ */

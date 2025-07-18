/* Alternate pin name */
PA_0_ALT1  = PA_0  | ALT1,
PA_1_ALT1  = PA_1  | ALT1,
PA_1_ALT2  = PA_1  | ALT2,
PA_2_ALT1  = PA_2  | ALT1,
PA_15_ALT1 = PA_15 | ALT1,
PB_1_ALT1  = PB_1  | ALT1,
PB_2_ALT1  = PB_2  | ALT1,
PB_3_ALT1  = PB_3  | ALT1,
PB_4_ALT1  = PB_4  | ALT1,
PB_6_ALT1  = PB_6  | ALT1,
PB_7_ALT1  = PB_7  | ALT1,
PB_8_ALT1  = PB_8  | ALT1,
PB_8_ALT2  = PB_8  | ALT2,
PB_9_ALT1  = PB_9  | ALT1,
PB_9_ALT2  = PB_9  | ALT2,
PB_9_ALT3  = PB_9  | ALT3,
PB_10_ALT1 = PB_10 | ALT1,
PB_11_ALT1 = PB_11 | ALT1,
PB_15_ALT1 = PB_15 | ALT1,
PC_3_ALT1  = PC_3  | ALT1,
PD_9_ALT1  = PD_9  | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PB_2,
#endif
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1_1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PA_4,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2_1 = PC_13,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PA_1,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3_1 = PB_6,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PB_1,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4_1 = PA_2,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = PA_3,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5_1 = PB_7,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = PA_5,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6_1 = PA_12,
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = PB_14,
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7_1 = PA_6,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = PA_7,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8_1 = PB_9,
#endif

/* USB */
#ifdef USBCON
  USB_OTG_HS_DM   = PD_7,
  USB_OTG_HS_DP   = PD_6,
  USB_OTG_HS_ID   = PD_8,
  #ifdef USB_OTG_HS_SOF_PA_8
    USB_OTG_HS_SOF  = PA_8,
  #endif
  #ifdef USB_OTG_HS_SOF_PA_14
    USB_OTG_HS_SOF  = PA_14,
  #endif
  USB_OTG_HS_VBUS = PD_9,
#endif

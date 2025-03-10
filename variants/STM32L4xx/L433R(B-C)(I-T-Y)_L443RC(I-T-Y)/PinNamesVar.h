/* Alternate pin name */
PA_1_ALT1  = PA_1  | ALT1,
PA_2_ALT1  = PA_2  | ALT1,
PA_3_ALT1  = PA_3  | ALT1,
PA_4_ALT1  = PA_4  | ALT1,
PA_6_ALT1  = PA_6  | ALT1,
PA_15_ALT1 = PA_15 | ALT1,
PB_1_ALT1  = PB_1  | ALT1,
PB_3_ALT1  = PB_3  | ALT1,
PB_4_ALT1  = PB_4  | ALT1,
PB_5_ALT1  = PB_5  | ALT1,
PB_13_ALT1 = PB_13 | ALT1,
PB_14_ALT1 = PB_14 | ALT1,
PB_15_ALT1 = PB_15 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PC_13,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = NC,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PA_2,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = PC_5,
#endif

/* USB */
#ifdef USBCON
  USB_DM  = PA_11,
  USB_DP  = PA_12,
  #ifdef USB_NOE_PA_13
    USB_NOE = PA_13,
  #endif
  #ifdef USB_NOE_PC_9
    USB_NOE = PC_9,
  #endif
#endif

/* Remap pin name */
PA_9_R     = PA_9  | PREMAP,
PA_10_R    = PA_10 | PREMAP,

/* Alternate pin name */
PA_0_ALT1  = PA_0  | ALT1,
PA_1_ALT1  = PA_1  | ALT1,
PA_2_ALT1  = PA_2  | ALT1,
PA_8_ALT1  = PA_8  | ALT1,
PA_8_ALT2  = PA_8  | ALT2,
PA_8_ALT3  = PA_8  | ALT3,
PA_8_ALT4  = PA_8  | ALT4,
PA_8_ALT5  = PA_8  | ALT5,
PB_6_ALT1  = PB_6  | ALT1,
PB_6_ALT2  = PB_6  | ALT2,
PB_6_ALT3  = PB_6  | ALT3,
PB_6_ALT4  = PB_6  | ALT4,
PB_6_ALT5  = PB_6  | ALT5,
PB_7_ALT1  = PB_7  | ALT1,
PB_7_ALT2  = PB_7  | ALT2,
PB_7_ALT3  = PB_7  | ALT3,
PB_7_ALT4  = PB_7  | ALT4,
PC_14_ALT1 = PC_14 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = NC,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PB_6,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PA_2,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = NC,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = NC,
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = NC,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = NC,
#endif

/* No USB */

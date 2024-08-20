/* Alternate pin name */
PB_8_ALT1 = PB_8 | ALT1,
PB_9_ALT1 = PB_9 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = NC,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PA_1,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PA_2,
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = NC,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = PA_5,
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6_1 = PA_12,
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = PA_6,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = PA_7,
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8_1 = PB_9,
#endif

/* No USB */

/* Alternate pin name */
PA_7_ALT1 = PA_7 | ALT1,
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
  SYS_WKUP3 = NC,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PA_2,
#endif

/* No USB */

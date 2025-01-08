/* Alternate pin name */
PA_0_ALT1  = PA_0  | ALT1,
PA_10_ALT1 = PA_10 | ALT1,
PA_14_ALT1 = PA_14 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif

/* No USB */

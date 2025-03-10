/* Alternate pin name */
PA_2_ALT1  = PA_2  | ALT1,
PA_3_ALT1  = PA_3  | ALT1,
PA_14_ALT1 = PA_14 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PC_13,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PA_2,
#endif

/* No USB */

/* Alternate pin name */
PA_2_ALT1 = PA_2 | ALT1,
PA_3_ALT1 = PA_3 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PB_0, /* SYS_WKUP0 */
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = NC,
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = NC,
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = NC,
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
  SYS_WKUP8 = PA_7, /* SYS_WKUP7 */
#endif
#ifdef PWR_WAKEUP_PIN9
  SYS_WKUP9 = PA_8, /* SYS_WKUP8 */
#endif
#ifdef PWR_WAKEUP_PIN10
  SYS_WKUP10 = PA_9, /* SYS_WKUP9 */
#endif
#ifdef PWR_WAKEUP_PIN11
  SYS_WKUP11 = NC,
#endif
#ifdef PWR_WAKEUP_PIN12
  SYS_WKUP12 = PA_11, /* SYS_WKUP11 */
#endif
#ifdef PWR_WAKEUP_PIN13
  SYS_WKUP13 = PA_0, /* SYS_WKUP12 */
#endif

/* No USB */

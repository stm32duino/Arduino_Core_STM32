/* Alternate pin name */
PA_2_ALT1 = PA_2 | ALT1,
PA_3_ALT1 = PA_3 | ALT1,

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PB_0, /* SYS_WKUP0 */
#endif
#ifdef PWR_WAKEUP_PIN2
  SYS_WKUP2 = PB_1, /* SYS_WKUP1 */
#endif
#ifdef PWR_WAKEUP_PIN3
  SYS_WKUP3 = PB_2, /* SYS_WKUP2 */
#endif
#ifdef PWR_WAKEUP_PIN4
  SYS_WKUP4 = PB_3, /* SYS_WKUP3 */
#endif
#ifdef PWR_WAKEUP_PIN5
  SYS_WKUP5 = PB_4, /* SYS_WKUP4 */
#endif
#ifdef PWR_WAKEUP_PIN6
  SYS_WKUP6 = PB_5, /* SYS_WKUP5 */
#endif
#ifdef PWR_WAKEUP_PIN7
  SYS_WKUP7 = PB_6, /* SYS_WKUP6 */
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8 = PA_7, /* SYS_WKUP7 */
#endif
#ifdef PWR_WAKEUP_PIN8
  SYS_WKUP8_1 = PB_7, /* SYS_WKUP7 */
#endif
#ifdef PWR_WAKEUP_PIN9
  SYS_WKUP9 = PA_8, /* SYS_WKUP8 */
#endif
#ifdef PWR_WAKEUP_PIN10
  SYS_WKUP10 = PA_9, /* SYS_WKUP9 */
#endif
#ifdef PWR_WAKEUP_PIN11
  SYS_WKUP11 = PA_10, /* SYS_WKUP10 */
#endif
#ifdef PWR_WAKEUP_PIN12
  SYS_WKUP12 = PA_11, /* SYS_WKUP11 */
#endif
#ifdef PWR_WAKEUP_PIN13
  SYS_WKUP13 = PA_0, /* SYS_WKUP12 */
#endif
#ifdef PWR_WAKEUP_PIN14
  SYS_WKUP14 = PA_1, /* SYS_WKUP13 */
#endif
#ifdef PWR_WAKEUP_PIN15
  SYS_WKUP15 = PA_2, /* SYS_WKUP14 */
#endif
#ifdef PWR_WAKEUP_PIN16
  SYS_WKUP16 = PA_3, /* SYS_WKUP15 */
#endif

/* No USB */

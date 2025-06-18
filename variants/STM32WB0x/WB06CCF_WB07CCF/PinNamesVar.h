/* Alternate pin name */
PB_8_ALT1 = PB_8 | ALT1,
PB_9_ALT1 = PB_9 | ALT1,

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
  SYS_WKUP8 = PB_7, /* SYS_WKUP7 */
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
#ifdef PWR_WAKEUP_PIN17
  SYS_WKUP17 = PA_4, /* SYS_WKUP16 */
#endif
#ifdef PWR_WAKEUP_PIN18
  SYS_WKUP18 = PA_5, /* SYS_WKUP17 */
#endif
#ifdef PWR_WAKEUP_PIN19
  SYS_WKUP19 = NC,
#endif
#ifdef PWR_WAKEUP_PIN20
  SYS_WKUP20 = PA_7, /* SYS_WKUP19 */
#endif
#ifdef PWR_WAKEUP_PIN21
  SYS_WKUP21 = PB_8, /* SYS_WKUP20 */
#endif
#ifdef PWR_WAKEUP_PIN22
  SYS_WKUP22 = PB_9, /* SYS_WKUP21 */
#endif
#ifdef PWR_WAKEUP_PIN23
  SYS_WKUP23 = NC,
#endif
#ifdef PWR_WAKEUP_PIN24
  SYS_WKUP24 = NC,
#endif
#ifdef PWR_WAKEUP_PIN25
  SYS_WKUP25 = PA_12, /* SYS_WKUP24 */
#endif
#ifdef PWR_WAKEUP_PIN26
  SYS_WKUP26 = PA_13, /* SYS_WKUP25 */
#endif
#ifdef PWR_WAKEUP_PIN27
  SYS_WKUP27 = PA_14, /* SYS_WKUP26 */
#endif
#ifdef PWR_WAKEUP_PIN28
  SYS_WKUP28 = PA_15, /* SYS_WKUP27 */
#endif

/* No USB */

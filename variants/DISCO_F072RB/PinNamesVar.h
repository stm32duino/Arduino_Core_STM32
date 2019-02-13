/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
SYS_WKUP2 = PC_13,
#endif
#ifdef PWR_WAKEUP_PIN3
SYS_WKUP3 = PE_6, /* Manually updated */
#endif
#ifdef PWR_WAKEUP_PIN4
SYS_WKUP4 = PA_2,
#endif
#ifdef PWR_WAKEUP_PIN5
SYS_WKUP5 = PC_5,
#endif
#ifdef PWR_WAKEUP_PIN6
SYS_WKUP6 = PB_5,
#endif
#ifdef PWR_WAKEUP_PIN7
SYS_WKUP7 = PB_15,
#endif
#ifdef PWR_WAKEUP_PIN8
SYS_WKUP8 = PF_2, /* Manually updated */
#endif
/* USB */
#ifdef USBCON
USB_DM = PA_11,
USB_DP = PA_12,
USB_NOE = PA_13,
#endif

/* SYS_WKUP */
#ifdef PWR_WAKEUP_PIN1
  SYS_WKUP1 = PA_0,
#endif
#ifdef PWR_WAKEUP_PIN2
  #ifdef ARDUINO_THUNDERPACK_L072
    SYS_WKUP2 = PC_13,
  #else /* ARDUINO_THUNDERPACK_F411 */
    SYS_WKUP2 = NC,
  #endif
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
  SYS_WKUP8 = NC,
#endif
/* USB */
#ifdef USBCON
  #ifdef ARDUINO_THUNDERPACK_L072
    USB_DM = PA_11,
    USB_DP = PA_12,
    USB_NOE = PA_13,
  #else /* ARDUINO_THUNDERPACK_F411 */
    USB_OTG_FS_SOF = PA_8,
    USB_OTG_FS_VBUS = PA_9,
    USB_OTG_FS_ID = PA_10,
    USB_OTG_FS_DM = PA_11,
    USB_OTG_FS_DP = PA_12,
  #endif
#endif
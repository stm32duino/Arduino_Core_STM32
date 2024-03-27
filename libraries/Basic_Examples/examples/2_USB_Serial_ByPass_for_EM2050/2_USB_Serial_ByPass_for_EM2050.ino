/**
 * @brief This example will forward serial signal from the USB to EchoStar module and vice versa.
 *        In another word, it will by pass the MCU.
 *
 *        The DPDT RF Switch control signal can be reversed by sending '*' character to the USB USB_SERIAL.
 *
 * @author mtnguyen
 * @version 1.1.0
 */

#define SWITCH_REVERSING_CONTROL_DEFAULT_VALUE true
volatile int switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

void setup(void)
{
  switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

#if defined(ECHOSTAR_PWR_ENABLE_PIN)
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
#endif

#if defined(DPDT_PWR_ENABLE_PIN)
  pinMode(DPDT_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(DPDT_PWR_ENABLE_PIN, HIGH);
#endif
  pinMode(DPDT_CTRL_PIN, OUTPUT);
  digitalWrite(DPDT_CTRL_PIN, HIGH);

  pinMode(ECHOSTAR_SWCTRL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHOSTAR_SWCTRL_PIN), swctrl_change_isr, CHANGE);

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;

  USB_SERIAL.println("Starting...");

  do_switch_ctrl_update();
  USB_SERIAL.print("RF Switch reverse control: ");
  USB_SERIAL.println(switch_reversing_control ? "ENABLE" : "DISABLE");

  ECHOSTAR_SERIAL.begin(115200);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop(void)
{
  if (ECHOSTAR_SERIAL.available())
  {
    USB_SERIAL.write(ECHOSTAR_SERIAL.read());
  }

  if (USB_SERIAL.available())
  {
    char c = USB_SERIAL.read();
    ECHOSTAR_SERIAL.write(c);

    if (c == '*')
    {
      switch_reversing_control ^= true;
      do_switch_ctrl_update();

      USB_SERIAL.print("RF Switch reverse control: ");
      USB_SERIAL.println(switch_reversing_control ? "ENABLE" : "DISABLE");
    }
  }
}

void swctrl_change_isr(void)
{
  do_switch_ctrl_update();
}

void do_switch_ctrl_update(void)
{
  if (digitalRead(ECHOSTAR_SWCTRL_PIN) == LOW)
  {
    digitalWrite(DPDT_CTRL_PIN, switch_reversing_control ? HIGH : LOW);
    digitalWrite(LED_BUILTIN, switch_reversing_control ? HIGH : LOW);
  }
  else
  {
    digitalWrite(DPDT_CTRL_PIN, switch_reversing_control ? LOW : HIGH);
    digitalWrite(LED_BUILTIN, switch_reversing_control ? LOW : HIGH);
  }
}
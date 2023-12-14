/**
 * @brief This example will forward serial signal from the USB to EchoStar module and vice versa.
 *        In another word, it will by pass the MCU.
 *
 *        The DPDT RF Switch control signal can be reversed by sending '*' character to the USB Serial.
 *
 * @author mtnguyen
 * @version 1.0.0
 */

#define SWITCH_REVERSING_CONTROL_DEFAULT_VALUE true
volatile int switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

void setup()
{
  switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(DPDT_CTRL_PIN, OUTPUT);
  digitalWrite(DPDT_CTRL_PIN, HIGH);

  pinMode(ECHOSTAR_SWCTRL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHOSTAR_SWCTRL_PIN), swctrl_change_isr, CHANGE);

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Starting...");

  do_switch_ctrl_update();
  Serial.print("RF Switch reverse control: ");
  Serial.println(switch_reversing_control ? "ENABLE" : "DISABLE");

  SerialLP1.begin(115200);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  if (SerialLP1.available())
  {
    Serial.write(SerialLP1.read());
  }

  if (Serial.available())
  {
    char c = Serial.read();
    SerialLP1.write(c);

    if (c == '*')
    {
      switch_reversing_control ^= true;
      do_switch_ctrl_update();

      Serial.print("RF Switch reverse control: ");
      Serial.println(switch_reversing_control ? "ENABLE" : "DISABLE");
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
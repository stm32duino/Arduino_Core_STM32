/**
 * @brief This example aims to test the RF Switch. The integrated LED show the current status of the controlling signal.
 *
 *        The DPDT RF Switch control signal can be reversed by pressing the USER_BUTTON.
 *
 * @author mtnguyen
 * @version 1.1.0
 */

volatile int current_value;
volatile bool button_flag;

void setup(void) {
  button_flag = false;
  current_value = LOW;

  gpio_init();

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;
  USB_SERIAL.println("Starting...");

  led_blink(3);
  delay(500);
}

void loop(void) {
  if (button_flag) {    
    current_value ^= HIGH;
    set_switch_ctrl_value(current_value);
    USB_SERIAL.print("Changing RFSW CTRL to ");
    USB_SERIAL.println((current_value == HIGH) ? "HIGH" : "LOW");

    delay(100); // Debounce
    button_flag = false;
  }
}

void gpio_init(void) {
  // LEDs
  pinMode(LED_BUILTIN, OUTPUT);

  // Button
  pinMode(USER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN), button_1_isr, RISING);

  // Switch POWER
#if defined(ECHOSTAR_PWR_ENABLE_PIN)
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
#endif

  // Switch CTRL pin
  pinMode(DPDT_CTRL_PIN, OUTPUT);
}

void set_switch_ctrl_value(bool value) {
  digitalWrite(DPDT_CTRL_PIN, value);
  digitalWrite(LED_BUILTIN, value);
}

void button_1_isr(void) {
  button_flag = true;
}

void led_blink(uint8_t num_of_blink) {
  for (; num_of_blink > 0; num_of_blink--) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
  }
}

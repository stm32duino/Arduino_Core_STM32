/**
 * @brief This example demonstrates how to use integrated LED & button on EchoStar-term-6 board.
 * The integrated LED blinks X time(s) every 2 seconds. X vary from 1 to 3 and increase when User Button pressed.
 * 
 * @author mtnguyen
 * @version 1.0.0
 * 
 */

volatile int num_of_blink = 1;

void setup()
{
  num_of_blink = 1;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(USER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN), button_1_isr, RISING);
}

void loop()
{
  for (int i = 0; i < num_of_blink; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);

    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
  }

  delay(2000);
}

void button_1_isr(void)
{
  num_of_blink = (num_of_blink++ % 3) + 1;
}
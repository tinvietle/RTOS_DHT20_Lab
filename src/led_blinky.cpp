#include <Arduino.h>
#include <led_blinky.h>

int led_status = 0;

void led_blinky()
{
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}
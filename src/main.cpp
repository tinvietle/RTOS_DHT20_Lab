#include <Arduino.h>
#include <scheduler.h>
#include <Wire.h>
#include <htsensor.h>
#include <led_blinky.h>
#include <light_control.h>

int state = 0;
int counter = 0;
int num = 3;

void task()
{
  switch (state)
  {
  case 0: // red-green for 3s
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    counter++;
    if (counter >= num)
    {
      state = 1;
      counter = 0;
      num = 2;
    }
    break;
  case 1: // red-yellow for 2s
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    counter++;
    if (counter >= num)
    {
      state = 2;
      counter = 0;
      num = 3;
    }
    break;
  case 2: // green-red for 3s
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    counter++;
    if (counter >= num)
    {
      state = 3;
      counter = 0;
      num = 2;
    }
    break;
  case 3: // yellow-red for 2s
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    counter++;
    if (counter >= num)
    {
      state = 0;
      counter = 0;
      num = 3;
    }
    break;
  default:
    state = 0;
    break;
  }
}


void TIMER_ISR(void *pvParameters)
{

  while (1)
  {
    SCH_Update();
    vTaskDelay(10);
  }
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);


  Wire.begin(GPIO_NUM_11, GPIO_NUM_12);
  dht20.begin();

  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  SCH_Init();
  SCH_Add_Task(led_blinky, 0, 100);
  // SCH_Add_Task(task, 0, 100);
  SCH_Add_Task(readDHT, 0, 200);

  Serial.begin(115200);
}

void loop()
{
  SCH_Dispatch_Tasks();
}
#include <Arduino.h>
#include <scheduler.h>
#include <Wire.h>
#include <htsensor.h>
#include <led_blinky.h>
#include <light_control.h>
#include <software_timer.h>
#include <heater.h>
#include <cooler.h>
#include <globals.h>


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
  SCH_Add_Task(readDHT, 0, 500);
  SCH_Add_Task(handleHeater, 0, 100);
  SCH_Add_Task(handleCooler, 0, 1);
  SCH_Add_Task(Timer_Run, 0, 1);

  Serial.begin(115200);
}

void loop()
{
  SCH_Dispatch_Tasks();
}
#include <Arduino.h>
#include <heater.h>
#include <light_control.h>
#include <globals.h>

int coolerActive = 0;

void handleHeater()
{

    if (globalTemperature < 25)
    {
        // Heater green
        lightLED1(2);
        Serial.println("Heater is green");
    }
    else if (globalTemperature >= 25 && globalTemperature < 26)
    {
        // Heater yellow
        lightLED1(1);
        Serial.println("Heater is yellow");
    }
    else
    {
        // Heater red
        lightLED1(0);
        Serial.println("Heater is red");
    }
}
#include <Arduino.h>
#include <heater.h>
#include <light_control.h>

int coolerActive = 0;

void handleHeater(float temperature)
{
    if (coolerActive)
    {
        Serial.println("Cooler is active, heater is off");
    }
    else
    {
        if (temperature < 25)
        {
            // Heater green
            lightLED1(2);
            Serial.println("Heater is green");
        }
        else if (temperature >= 25 && temperature < 26)
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
}
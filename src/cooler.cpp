#include <Arduino.h>
#include <cooler.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

int coolerTimerIndex = 0; // Index for the software timer

void handleCooler()
{
    if (globalTemperature <= 30)
    {
        deactivateCooler();
    }
    else
    {
        activateCooler();
    }
}

void activateCooler()
{
    // Cooler green
    lightLED2(2);

    // Turn off the cooler
    Set_Timer(coolerTimerIndex, 50);
}

void deactivateCooler()
{
    // Cooler red
    lightLED2(0);
}
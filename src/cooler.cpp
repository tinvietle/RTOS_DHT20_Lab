#include <Arduino.h>
#include <cooler.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

#define COOLER_ON 1
#define COOLER_OFF 2

int coolerTimerIndex = 0; // Index for the software timer
int coolerState = COOLER_OFF;

void handleCooler()
{
    switch (coolerState){
        case COOLER_OFF:
            if (globalTemperature > 30) {
                activateCooler();
                coolerState = 1;
            }
            break;
        case COOLER_ON:
            if (Is_Timer_Expired(coolerTimerIndex) != 1){break;}
            deactivateCooler();
            coolerState = 0;
            break;
    }
}

void activateCooler()
{
    // Cooler green
    lightLED2(2);

    // Turn off the cooler
    Set_Timer(coolerTimerIndex, 500);
}

void deactivateCooler()
{
    // Cooler red
    lightLED2(0);
}
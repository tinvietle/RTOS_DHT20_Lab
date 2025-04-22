#include <Arduino.h>
#include <cooler.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

#define INIT 0
#define COOLER_ON 1
#define COOLER_OFF 2

int coolerTimerIndex = 0; // Index for the software timer
int coolerState = INIT;

void handleCooler()
{
    switch (coolerState){
        case INIT:
            lightLED2(0); // Turn off the cooler LED
            coolerState = COOLER_OFF; // Set to COOLER_OFF state
            break;
        case COOLER_OFF:
            if (globalTemperature > 28) {
                activateCooler();
                coolerState = COOLER_ON; // Set to COOLER_ON state
            }
            break;
        case COOLER_ON:
            if (Is_Timer_Expired(coolerTimerIndex) != 1){break;}
            deactivateCooler();
            coolerState = COOLER_OFF; // Set to COOLER_OFF state
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
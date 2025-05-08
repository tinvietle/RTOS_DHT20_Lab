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
                lightLED2(2);
                Set_Timer(coolerTimerIndex, 500);
                coolerState = COOLER_ON; // Set to COOLER_ON state
            }
            break;
        case COOLER_ON:
            if (Is_Timer_Expired(coolerTimerIndex) != 1){break;}
            lightLED2(0);
            coolerState = COOLER_OFF; // Set to COOLER_OFF state
            break;
    }
}

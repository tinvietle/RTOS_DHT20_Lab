#include <Arduino.h>
#include <cooler.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

enum class CoolerState {
    COOLER_INIT,
    COOLER_ON,
    COOLER_OFF
};

#define TEMPERATURE_THRESHOLD 27  // predefined temperature threshold
#define COOLER_DURATION 500  // predefined cooler duration 

int coolerTimerIndex = COOLER_INDEX; // Index for the software timer
CoolerState coolerState = CoolerState::COOLER_INIT; // Initial state

void handleCooler()
{
    switch (coolerState){
        case CoolerState::COOLER_INIT:
            lightLED2(0); // Turn off the cooler LED
            coolerState = CoolerState::COOLER_OFF; // Set to COOLER_OFF state
            break;
        case CoolerState::COOLER_OFF:
            if (globalTemperature > TEMPERATURE_THRESHOLD) {
                Serial.println("Cooler ON");
                // Cooler green
                lightLED2(2);
                // Turn on the cooler
                Set_Timer(coolerTimerIndex, COOLER_DURATION);
                coolerState = CoolerState::COOLER_ON; // Set to COOLER_ON state
            }
            break;
        case CoolerState::COOLER_ON:
            if (Is_Timer_Expired(coolerTimerIndex) != 1){break;}
            // Check if the temperature is still above 30
            if (globalTemperature <= TEMPERATURE_THRESHOLD){
                Serial.println("Cooler OFF");
                // Cooler red
                lightLED2(0);
                coolerState = CoolerState::COOLER_OFF;
            }
            else {
                // If the temperature is still above 30, reset the timer
                Serial.println("Cooler ON");
                // Cooler green
                lightLED2(2);
                // Turn on the cooler
                Set_Timer(coolerTimerIndex, COOLER_DURATION);
            }
            break;
    }
}

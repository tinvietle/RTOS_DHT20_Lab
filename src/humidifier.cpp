#include <Arduino.h>
#include <humidifier.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

#define HUMIDITY_THRESHOLD 60  // predefined humidity threshold

// Humidifier state definitions
#define HUMIDIFIER_IDLE    0
#define HUMIDIFIER_GREEN   1
#define HUMIDIFIER_YELLOW  2
#define HUMIDIFIER_RED     3

int humidifierTimerIndex = 11; // Index for the software timer
int humidifierState = HUMIDIFIER_IDLE;

void handleHumidifier()
{

    switch (humidifierState){
        case HUMIDIFIER_IDLE:
            if (globalHumidity < HUMIDITY_THRESHOLD) {
                // Start humidifier cycle with GREEN color for 5 seconds
                lightLED3(2);
                Set_Timer(humidifierTimerIndex, 500);
                humidifierState = HUMIDIFIER_GREEN;
            }
            else {
                // Humidity is sufficient; turn off the humidifier LED
                lightLED3(0); // Turn off the humidifier LED when idle
            }
            break;
        case HUMIDIFIER_GREEN:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Switch to YELLOW for 3 seconds
                lightLED3(1);
                Set_Timer(humidifierTimerIndex, 300);
                humidifierState = HUMIDIFIER_YELLOW;
            }
            break;
        case HUMIDIFIER_YELLOW:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Switch to RED for 2 seconds
                lightLED3(0);
                Set_Timer(humidifierTimerIndex, 200);
                humidifierState = HUMIDIFIER_RED;
            }
            break;
        case HUMIDIFIER_RED:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Re-check humidity to determine whether to repeat cycle
                if (globalHumidity < HUMIDITY_THRESHOLD) {
                    // Restart cycle: GREEN for 5 seconds
                    lightLED3(2);
                    Set_Timer(humidifierTimerIndex, 500);
                    humidifierState = HUMIDIFIER_GREEN;
                } else {
                    // Humidity is now sufficient; stop cycle
                    humidifierState = HUMIDIFIER_IDLE;
                }
            }
            break;
        default:
            break;
    }
}

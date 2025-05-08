#include <Arduino.h>
#include <humidifier.h>
#include <light_control.h>
#include <software_timer.h>
#include <globals.h>

#define HUMIDITY_THRESHOLD 60  // predefined humidity threshold

// Humidifier state definitions
enum class HumidifierState {
    HUMIDIFIER_IDLE,
    HUMIDIFIER_GREEN,
    HUMIDIFIER_YELLOW,
    HUMIDIFIER_RED
};

int humidifierTimerIndex = HUMID_INDEX; // Index for the software timer
HumidifierState humidifierState = HumidifierState::HUMIDIFIER_IDLE;

void handleHumidifier()
{

    switch (humidifierState){
        case HumidifierState::HUMIDIFIER_IDLE:
            if (globalHumidity < HUMIDITY_THRESHOLD) {
                // Start humidifier cycle with GREEN color for 5 seconds
                lightLED3(2);
                Set_Timer(humidifierTimerIndex, 500);
                humidifierState = HumidifierState::HUMIDIFIER_GREEN;
            }
            else {
                // Humidity is sufficient; turn off the humidifier LED
                lightLED3(3); // Turn off the humidifier LED when idle
            }
            break;
        case HumidifierState::HUMIDIFIER_GREEN:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Switch to YELLOW for 3 seconds
                lightLED3(1);
                Set_Timer(humidifierTimerIndex, 300);
                humidifierState = HumidifierState::HUMIDIFIER_YELLOW;
            }
            break;
        case HumidifierState::HUMIDIFIER_YELLOW:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Switch to RED for 2 seconds
                lightLED3(0);
                Set_Timer(humidifierTimerIndex, 200);
                humidifierState = HumidifierState::HUMIDIFIER_RED;
            }
            break;
        case HumidifierState::HUMIDIFIER_RED:
            if (Is_Timer_Expired(humidifierTimerIndex)) {
                // Re-check humidity to determine whether to repeat cycle
                if (globalHumidity < HUMIDITY_THRESHOLD) {
                    // Restart cycle: GREEN for 5 seconds
                    lightLED3(2);
                    Set_Timer(humidifierTimerIndex, 500);
                    humidifierState = HumidifierState::HUMIDIFIER_GREEN;
                } else {
                    // Humidity is now sufficient; stop cycle
                    humidifierState = HumidifierState::HUMIDIFIER_IDLE;
                }
            }
            break;
        default:
            break;
    }
}

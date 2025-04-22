#include <Arduino.h>
#include <heater.h>
#include <light_control.h>
#include <globals.h>

enum class HeaterState {
    SAFE_TEMP,      // Green LED
    MID_TEMP,      // Yellow LED
    DANGER_TEMP      // Red LED
};

HeaterState currentHeaterState = HeaterState::SAFE_TEMP;  // Default state

void handleHeater() {
    HeaterState newState;

    // Determine the new state based on global temperature
    if (globalTemperature < 25) {
        newState = HeaterState::SAFE_TEMP;
    } else if (globalTemperature < 31) {
        newState = HeaterState::MID_TEMP;
    } else {
        newState = HeaterState::DANGER_TEMP;
    }

    // If state has changed, update LEDs and print
    if (newState != currentHeaterState) {
        currentHeaterState = newState;

        switch (currentHeaterState) {
            case HeaterState::SAFE_TEMP:
                lightLED1(2);  // Green
                Serial.println("Heater turns GREEN");
                break;
            case HeaterState::MID_TEMP:
                lightLED1(1);  // Yellow
                Serial.println("Heater turns YELLOW");
                break;
            case HeaterState::DANGER_TEMP:
                lightLED1(0);  // Red
                Serial.println("Heater turns RED");
                break;
        }
    }
}

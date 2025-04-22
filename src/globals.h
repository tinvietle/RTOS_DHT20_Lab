#ifndef GLOBALS_H
#define GLOBALS_H

extern float globalTemperature; // Declare global temperature
extern float globalHumidity;    // Declare global humidity

enum TimerIndex {
    HUMID_INDEX = 0,
    COOLER_INDEX = 2
};

#endif // GLOBALS_H
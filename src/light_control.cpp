#include <Arduino.h>
#include <light_control.h>

void lightLED1(int state)
{
    switch (state)
    {
        case 0: // red
            digitalWrite(D3, HIGH);
            digitalWrite(D4, HIGH);
            break;
        case 1: // yellow
            digitalWrite(D3, LOW);
            digitalWrite(D4, HIGH);
            break;
        case 2: // green
            digitalWrite(D3, HIGH);
            digitalWrite(D4, LOW);
            break;
        default: // off
            digitalWrite(D3, LOW);
            digitalWrite(D4, LOW);
            break;
    }
}

void lightLED2(int state)
{
    switch (state)
    {
        case 0: // red
            digitalWrite(D5, HIGH);
            digitalWrite(D6, HIGH);
            break;
        case 1: // yellow
            digitalWrite(D5, LOW);
            digitalWrite(D6, HIGH);
            break;
        case 2: // green
            digitalWrite(D5, HIGH);
            digitalWrite(D6, LOW);
            break;
        default: // off
            digitalWrite(D5, LOW);
            digitalWrite(D6, LOW);
            break;
    }
}
void lightLED3(int state)
{
    switch (state)
    {
        case 0: // red
            digitalWrite(D7, HIGH);
            digitalWrite(D8, HIGH);
            break;
        case 1: // yellow
            digitalWrite(D7, LOW);
            digitalWrite(D8, HIGH);
            break;
        case 2: // green
            digitalWrite(D7, HIGH);
            digitalWrite(D8, LOW);
            break;
        default: // off
            digitalWrite(D7, LOW);
            digitalWrite(D8, LOW);
            break;
    }
}
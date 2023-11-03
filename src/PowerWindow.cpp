#include <Arduino.h>
#include "PowerWindow.h"

PowerWindow::PowerWindow(){}

void PowerWindow::begin()
{
    pinMode(PIN_POWERWINDOW_UP, OUTPUT);
    pinMode(PIN_POWERWINDOW_DOWN, OUTPUT);
}

void PowerWindow::controlMotor(bool LimitSwitchUP, bool LimitSwitchDown)
{
    const int halfSpeedPWM = 2048;
    const int zeroSpeedPWM = 2048;

    if(LimitSwitchUP)
    {
        digitalWrite(PIN_POWERWINDOW_UP,     1);
        digitalWrite(PIN_POWERWINDOW_DOWN,   0);
        // Serial.println("Sweep UP!");
    }
    else if(LimitSwitchDown)
    {
        digitalWrite(PIN_POWERWINDOW_UP,     0);
        digitalWrite(PIN_POWERWINDOW_DOWN,   1);
        // Serial.println("Sweep DOWN!");
    }
    else
    {
        digitalWrite(PIN_POWERWINDOW_UP,     0);
        digitalWrite(PIN_POWERWINDOW_DOWN,   0);
        // Serial.println("Sweep STOP!");
    }
}
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
        analogWrite(PIN_POWERWINDOW_UP,     halfSpeedPWM);
        analogWrite(PIN_POWERWINDOW_DOWN,   zeroSpeedPWM);
        // Serial.println("Sweep UP!");
    }
    else if(LimitSwitchDown)
    {
        analogWrite(PIN_POWERWINDOW_UP,     zeroSpeedPWM);
        analogWrite(PIN_POWERWINDOW_DOWN,   halfSpeedPWM);
        // Serial.println("Sweep DOWN!");
    }
    else
    {
        analogWrite(PIN_POWERWINDOW_UP,     zeroSpeedPWM);
        analogWrite(PIN_POWERWINDOW_DOWN,   zeroSpeedPWM);
        // Serial.println("Sweep STOP!");
    }
}
#include "newMotor.h"
#include <Arduino.h>

Motor::Motor(){}

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

MainMotorLeft::MainMotorLeft():left(10, 32, 21, 3){}

void MainMotorLeft::begin()
{
    pinMode(left.PIN_LEN,  OUTPUT);
    pinMode(left.PIN_REN,  OUTPUT);
    pinMode(left.PIN_LPWM, OUTPUT);
    pinMode(left.PIN_RPWM, OUTPUT);

    digitalWrite(left.PIN_LEN, HIGH);
    digitalWrite(left.PIN_REN, HIGH);
}

MainMotorRight::MainMotorRight():right(33, 27, 25, 26){}

void MainMotorRight::begin()
{
    pinMode(right.PIN_LEN,  OUTPUT);
    pinMode(right.PIN_REN,  OUTPUT);
    pinMode(right.PIN_LPWM, OUTPUT);
    pinMode(right.PIN_RPWM, OUTPUT);

    digitalWrite(right.PIN_LEN, HIGH);
    digitalWrite(right.PIN_REN, HIGH);
}
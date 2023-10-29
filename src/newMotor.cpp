#include "newMotor.h"
#include <Arduino.h>

Motor::Motor(){}

MainMotorLeft::MainMotorLeft():left(10, 32, 21, 3){}

void MainMotorLeft::begin()
{
    pinMode(left.PIN_LEN,  OUTPUT);
    pinMode(left.PIN_REN,  OUTPUT);
    pinMode(left.PIN_LPWM, OUTPUT);
    pinMode(left.PIN_RPWM, OUTPUT);

    digitalWrite(left.PIN_LEN, HIGH);
    digitalWrite(left.PIN_REN, HIGH);
    analogWriteResolution(12);
    analogWriteFrequency(10000);
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
    analogWriteResolution(12);
    analogWriteFrequency(10000);
}
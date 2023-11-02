#include <Arduino.h>
#include "MyMotor.h"

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

void MainMotorLeft::controlMotor(int input)
{
    if (input >= 2200)             // Forward
    {
        digitalWrite(SEN_LEFT, LOW);
        digitalWrite(SEN_RIGHT, LOW);

        input -= 2200;
        analogWrite (left.PIN_LPWM, 0);
        digitalWrite(left.PIN_LPWM, LOW);
        analogWrite (left.PIN_RPWM, 300);
        //analogWrite(left.PIN_RPWM, input);
    }
    else if (input <= 1900)                     // Backward
    {
        digitalWrite(SEN_LEFT, HIGH);
        digitalWrite(SEN_RIGHT, HIGH);

        input *= -1;
        input += 1900;
        analogWrite (left.PIN_RPWM, 0);
        digitalWrite(left.PIN_RPWM, LOW);
        analogWrite (left.PIN_LPWM, 300);
        //analogWrite(left.PIN_LPWM, input);
    }
    else 
    {
        analogWrite(left.PIN_LPWM, 0);
        analogWrite(left.PIN_RPWM, 0);
        digitalWrite(5, LOW);
        digitalWrite(18, LOW);
    }
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

void MainMotorRight::controlMotor(int input)
{
    if (input >= 2200)             // Forward
    {
        digitalWrite(SEN_LEFT, LOW);

        input -= 2200;
        analogWrite (right.PIN_LPWM, 0);
        digitalWrite(right.PIN_LPWM, LOW);
        analogWrite (right.PIN_RPWM, 300);
        //analogWrite(right.PIN_RPWM, input);
    }
    else if (input <= 1900)                     // Backward
    {
        digitalWrite(SEN_RIGHT, HIGH);

        input *= -1;
        input += 1900;
        analogWrite (right.PIN_RPWM, 0);
        digitalWrite(right.PIN_RPWM, LOW);
        analogWrite (right.PIN_LPWM, 300);
        //analogWrite(right.PIN_LPWM, input);
    }
    else 
    {
        analogWrite(right.PIN_LPWM, 0);
        analogWrite(right.PIN_RPWM, 0);
        digitalWrite(5, LOW);
        digitalWrite(18, LOW);
    }
}

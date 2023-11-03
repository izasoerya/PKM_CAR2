#include <Arduino.h>
#include "MotorController.h"

MotorController::MotorController():leftMotor(MainMotorLeft()), rightMotor(MainMotorRight()){}

void MotorController::begin()
{
    leftMotor.begin();
    rightMotor.begin();
}

void MotorController::moveForward(int input)
{
    leftMotor.controlMotor(input);
    rightMotor.controlMotor(input);
    if(input < 2048) Serial.println("Mundur");
    else Serial.println("Maju");

}

void MotorController::moveTurning(int input)
{
    if (input > 2200)
    {
        leftMotor.controlMotor(input);
        rightMotor.controlMotor(stopValue - input);
        Serial.println("Belok kanan");
    }
    else if (input < 1900)
    {
        leftMotor.controlMotor(stopValue - input);
        rightMotor.controlMotor(input);    
        Serial.println("Belok kiri");
    }
    else emergencyStop();
}

void MotorController::emergencyStop()
{
    leftMotor.controlMotor(stopValue);
    rightMotor.controlMotor(stopValue);
    Serial.println("Stop now");
}
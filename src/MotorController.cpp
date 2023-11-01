#include <Arduino.h>
#include "MotorController.h"

MotorController::MotorController(){}

void MotorController::begin()
{
    left.begin();
    right.begin();
}

void MotorController::moveForward(int input)
{
    left.controlMotor(input);
    right.controlMotor(input);
}
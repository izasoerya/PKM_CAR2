#ifndef CONTROLL_MOTOR_H
#define CONTROLL_MOTOR_H

#include "MyMotor.h"

class MotorController
{
private:
    const int stopValue = 2048;
    MainMotorLeft leftMotor;
    MainMotorRight rightMotor;

public:
    MotorController();
    void begin();
    void moveForward(int input);
    void moveTurning(int input);
    void emergencyStop();
};

#endif

#ifndef CONTROLL_MOTOR_H
#define CONTROLL_MOTOR_H

#include "newMotor.h"

class MotorController
{
private:
    const int stopValue = 2048;
    MainMotorLeft left;
    MainMotorRight right;
    
public:
    MotorController();
    void begin();
    void moveForward(int input);
    void moveTurning(int input);
    void emergencyStop();
};

#endif
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class MotorDC 
{
private:
    const byte powerWindowA = 2;
    const byte powerWindowB = 22;
public:
    MotorDC();
    void begin();
    void controlMotor(bool runConveyor, bool stopConveyor);
};

class MotorBLDC
{
private:
    uint16_t analogLeft = 0, analogRight = 0;
public:
    MotorBLDC();
    
    void beginMotorLeft();
    int controlMotorLeft(uint16_t remoteLeft);
    int sCurveLeft(float currentValue, float inputValue);
    
    void beginMotorRight();
    int controlMotorRight(uint16_t remoteRight);
    int sCurveRight(float currentValue, float inputValue);

    int controlMotorTurning(uint16_t input);
    void controlSetZero();
};


#endif
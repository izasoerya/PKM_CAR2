#include <Arduino.h>
#include "Motor.h"

#define CHANNEL_0 0

MotorDC :: MotorDC(){}     

void MotorDC::begin()
{
    pinMode(powerWindowA, OUTPUT);
    pinMode(powerWindowB, OUTPUT);
}

void MotorDC::controlMotor(bool runConveyor, bool stopConveyor)
{
    if (runConveyor)
    {
        analogWrite(powerWindowA, 2400);
        analogWrite(powerWindowB, 0);
        Serial.println("Sweep UP");
    }
    else if (stopConveyor)
    {
        analogWrite(powerWindowA, 0);
        analogWrite(powerWindowB, 1200);
        Serial.println("Sweep DOWN");
    }
    else
    {
        analogWrite(powerWindowA, 0); 
        analogWrite(powerWindowB, 0);
        Serial.println("Sweep STOP");
    }
}


#define RPWM_LEFT       25
#define RPWM_RIGHT      21

#define LPWM_LEFT       26
#define LPWM_RIGHT      3

#define REN_LEFT        19       
#define REN_RIGHT       33       

#define LEN_LEFT        32       
#define LEN_RIGHT       27       

#define SEN_LEFT        5
#define SEN_RIGHT       18

MotorBLDC :: MotorBLDC(){}

void MotorBLDC::beginMotorLeft()
{   
    pinMode(REN_LEFT, OUTPUT);
    pinMode(LEN_LEFT, OUTPUT);
    pinMode(SEN_LEFT, OUTPUT);

    digitalWrite(REN_LEFT, HIGH);
    digitalWrite(LEN_LEFT, HIGH);
    analogWriteResolution(12);
    analogWriteFrequency(10000);
}

void MotorBLDC::beginMotorRight() 
{
    pinMode(REN_RIGHT, OUTPUT);
    pinMode(LEN_RIGHT, OUTPUT);
    pinMode(SEN_RIGHT, OUTPUT);

    digitalWrite(REN_RIGHT, HIGH);
    digitalWrite(LEN_RIGHT, HIGH);
    analogWriteResolution(12);
    analogWriteFrequency(10000);
}

int MotorBLDC::controlMotorLeft(uint16_t inputLeft)
{
    analogLeft = inputLeft;
    if (analogLeft >= 2200)             // Forward
    {
        digitalWrite(SEN_LEFT, LOW);
        digitalWrite(SEN_RIGHT, LOW);

        analogLeft -= 2200;
        analogWrite(LPWM_LEFT, 0);
        digitalWrite(LPWM_LEFT, LOW);
        analogWrite(RPWM_LEFT, 300);
        //analogWrite(RPWM_LEFT, inputLeft);
    }
    else if (analogLeft <= 1900)                     // Backward
    {
        digitalWrite(SEN_LEFT, HIGH);
        digitalWrite(SEN_RIGHT, HIGH);

        analogLeft *= -1;
        analogLeft += 1900;
        analogWrite(RPWM_LEFT, 0);
        digitalWrite(RPWM_LEFT, LOW);
        analogWrite(LPWM_LEFT, 300);
        //analogWrite(LPWM_LEFT, inputLeft);
    }
    else 
    {
        analogWrite(LPWM_LEFT, 0);
        analogWrite(RPWM_LEFT, 0);
        digitalWrite(5, LOW);
        digitalWrite(18, LOW);
    }
    return (analogLeft);           
}

int MotorBLDC::controlMotorTurning(uint16_t input)
{
    analogLeft = input;
    const int upperThreshold = 2200, lowerThreshold = 1900;
    
    if(input > upperThreshold)        // turn right
    {
        digitalWrite(SEN_LEFT, HIGH);
        digitalWrite(SEN_RIGHT, LOW);

        analogLeft -= upperThreshold;
        // left is faster
        digitalWrite(RPWM_LEFT, LOW);
        analogWrite (RPWM_LEFT, 0);
        analogWrite (LPWM_LEFT, 400);   

        // right is slower
        digitalWrite(LPWM_RIGHT, LOW);
        analogWrite (LPWM_RIGHT, 0);
        analogWrite (RPWM_RIGHT, 400);  
    }
    else if(input < lowerThreshold)       // turn left
    {
        digitalWrite(SEN_LEFT, LOW);
        digitalWrite(SEN_RIGHT, HIGH);

        analogLeft *= -1;
        analogLeft += lowerThreshold;
        digitalWrite(RPWM_RIGHT, LOW);
        analogWrite (RPWM_RIGHT, 0);
        analogWrite (LPWM_RIGHT, 400);  

        // right is faster
        digitalWrite(LPWM_LEFT, LOW);
        analogWrite (LPWM_LEFT, 0);
        analogWrite (RPWM_LEFT, 400);   
    }
    else        // stop
    {
        digitalWrite(SEN_LEFT, LOW);
        digitalWrite(SEN_RIGHT, LOW);

        digitalWrite(LPWM_LEFT, LOW);
        analogWrite (LPWM_LEFT, 0);
        digitalWrite(RPWM_LEFT, LOW);
        analogWrite (RPWM_LEFT, 0);
    }
    return analogLeft;
}

int MotorBLDC::sCurveLeft(float currentValue, float inputValue)
{
    float velocity, accelerationFactor, deccelerationFactor, changeStep;
    float currentTime = 0, duration = 1, interval = 0.05;
    while (currentTime <= duration)
    {
        velocity = (inputValue - currentValue) / duration;
        if (currentTime <= duration / 3)            //* Build Up Phase
        {
            accelerationFactor =  currentTime / (duration / 3);
            changeStep = accelerationFactor * velocity * interval;
        }
        else if (currentTime <= 2/3 * duration)     //* Linear Phase
        {
            changeStep =  velocity * interval;
        }
        else                                        //* Deccel Phase
        {
            deccelerationFactor = 3 * (duration - currentTime) / (duration / 3);
            changeStep =  deccelerationFactor * velocity * interval;
        }
        Serial.println(currentValue);
        controlMotorLeft(currentValue);
        currentValue += changeStep;
        currentTime += interval;
        delay(5);
    }
    if (inputValue != currentValue)
    {
        changeStep = inputValue - currentValue;
        currentValue += changeStep;
        controlMotorLeft(currentValue);
        Serial.println(currentValue);
        delay(5);
    }
    return currentValue;
}

int MotorBLDC::controlMotorRight(uint16_t inputRight)
{
    analogRight = inputRight;
    const int upperThreshold = 2200, lowerThreshold = 1900;
    if (analogRight >= upperThreshold)              //! Forward
    {
        analogRight -= upperThreshold;
        analogWrite (LPWM_RIGHT, 0);
        digitalWrite(LPWM_RIGHT, LOW);
        analogWrite (RPWM_RIGHT, 300);
        // analogWrite (RPWM_RIGHT, inputRight);
    }
    else if (analogRight <= lowerThreshold)         //! Backward
    {
        analogRight *= -1;
        analogRight += lowerThreshold;
        analogWrite (RPWM_RIGHT, 0);
        digitalWrite(RPWM_RIGHT, LOW);
        analogWrite (LPWM_RIGHT, 300);
        // analogWrite (LPWM_RIGHT, inputRight);
    }
    else 
    {
        analogWrite(LPWM_RIGHT, 0);
        analogWrite(RPWM_RIGHT, 0);
    }        

    return (analogRight);           //* Backward
}

int MotorBLDC::sCurveRight(float currentValue, float inputValue)
{
    float velocity, accelerationFactor, deccelerationFactor, changeStep;
    float currentTime = 0, duration = 1, interval = 0.05;
    while (currentTime <= duration)
    {
        velocity = (inputValue - currentValue) / duration;
        if (currentTime <= duration / 3)            //* Build Up Phase
        {
            accelerationFactor =  currentTime / (duration / 3);
            changeStep = accelerationFactor * velocity * interval;
        }
        else if (currentTime <= 2/3 * duration)     //* Linear Phase
        {
            changeStep =  velocity * interval;
        }
        else                                        //* Deccel Phase
        {
            deccelerationFactor = 3 * (duration - currentTime) / (duration / 3);
            changeStep =  deccelerationFactor * velocity * interval;
        }
        controlMotorLeft(currentValue);
        currentValue += changeStep;
        currentTime += interval;
        
        delay(5);
    }
    if (inputValue != currentValue)
    {
        changeStep = inputValue - currentValue;
        currentValue += changeStep;
        controlMotorLeft(currentValue);
        Serial.println(currentValue);
        
        delay(5);
    }
    return currentValue;
}

void MotorBLDC::controlSetZero()
{
    const int stopValue = 2048;
	controlMotorLeft(stopValue);
	controlMotorRight(stopValue);
}


#include <Arduino.h>
#include "Sensor.h"

#define PIN_BATT 18
#define PIN_TRIG 13
#define PIN_ECHO 14

CalculateBattery::CalculateBattery(){}

void CalculateBattery::getVoltage(float &batteryValue)
{
    // uint16_t dividerOutput = analogRead(PIN_BATT);
    batteryValue = 2.3;//(dividerOutput/4095) * 5;
}

UltrasonicTrash::UltrasonicTrash(){}

void UltrasonicTrash::begin() 
{
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, OUTPUT);
}

bool UltrasonicTrash::trashIsFull()
{   
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5); 
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(15);
    digitalWrite(PIN_TRIG, LOW);
    
    uint16_t distance = pulseIn(PIN_ECHO, HIGH, 10000);
    if ((distance /= 50) != 0) {
        if (distance < 50) return true; 
    }
    return false;
}
#ifndef SENSOR_H
#define SENSOR_H

class CalculateBattery
{
private:
    float batteryVoltage;
public:
    CalculateBattery();
    void getVoltage(float &batteryValue);
};

class UltrasonicTrash
{
private:
    
public:
    UltrasonicTrash();
    void begin(); 
    bool trashIsFull();
};




#endif
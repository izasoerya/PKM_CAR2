#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

class Telemetry 
{
private: 
    char* tempReadGCS;
    String* finalResult;
    byte Counter, wordCounter = 0;
    const String StatusOK = "Success";
    byte timeOut = 0;
    struct receiveGCSControl 
    {
        uint16_t leftAnalog;
        uint16_t rightAnalog;
        bool conveyer;
        bool signalLeft;
        bool signalRight;
        uint16_t cameraAngle;
        bool buzzer;
        bool conveyerStop;
    };
    receiveGCSControl GCS;
public:
    Telemetry();
    String fetchLoraData    (bool &isReceive, HardwareSerial &Serial);
    bool timeOutCounter     (bool reset);
    void parsingFromGCS     (String receiveGCS);
    void listCommand        (String leftSpeed, String rightSpeed, String Conveyer,
                            String leftTurn, String rightTurn, String cameraAngle, String conveyerStop);
    void collectControlData (uint16_t &leftMotor, uint16_t &rightMotor, bool &conveyer,
                             bool &leftTurn, bool &rightTurn, int &cameraAngle, bool &conveyerStop);
    String constructMessage (float batteryPercentage, bool conveyer,
                             bool leftTurn, bool rightTurn, bool forward);
};

#endif
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include "Models.h"

class Telemetry 
{
private: 
    const String StatusOK = "Success";
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
    void listCommand(String leftSpeed, String rightSpeed, String Conveyer,
                    String leftTurn, String rightTurn, String cameraAngle, String conveyerStop);

public:
    Telemetry();
    String fetchLoraData    (bool &isReceive, HardwareSerial &Serial);
    bool timeOutCounter     (bool reset);
    void parsingFromGCS     (String receiveGCS);

    void collectControlData (ControlData &data);
    String constructMessage (float batteryPercentage, bool conveyer,
                             bool leftTurn, bool rightTurn, bool forward);
};

#endif
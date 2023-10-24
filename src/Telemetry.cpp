#include "Telemetry.h"

Telemetry::Telemetry(){}

String Telemetry::fetchLoraData(bool &isReceive, HardwareSerial &Serial)
{
    String data = "";
	while (Serial.available() > 0) 
		data += (char)Serial.read();
	if (data != "") 
		isReceive = true;
	return data;
}

bool Telemetry::timeOutCounter(bool reset)
{
    bool isTimeout;
    timeOut = reset ? 0 : timeOut;
    isTimeout = timeOut > 5 ?  true :  false;
    timeOut++;
    return isTimeout;
}

void Telemetry::parsingFromGCS(String receiveGCS)
{   
    String finalResult[receiveGCS.length() + 1]; // Use an array of String objects
    char tempReadGCS  [receiveGCS.length() + 1];

    strcpy(tempReadGCS, receiveGCS.c_str());
    for (Counter = 0, wordCounter = 0; Counter < receiveGCS.length(); Counter++)
    {
        if (tempReadGCS[Counter] != ',') 
        {
            finalResult[wordCounter] += tempReadGCS[Counter];
            finalResult[wordCounter].trim();
        }
        else {
            wordCounter++;
        }
    }
    listCommand(finalResult[0], finalResult[1], finalResult[2],                      //* LeftSpeed, RightSpeed, Conveyer1, 
                finalResult[3], finalResult[4], finalResult[5], finalResult[6]);     //* leftSignal, RightSignal, CameraAngle, Conveyer2
}

void Telemetry::listCommand(String leftSpeed, String rightSpeed, String Conveyer,
                            String leftTurn, String rightTurn, String cameraAngle, String conveyerStop)
{
    GCS.leftAnalog      = leftSpeed.toInt();
    GCS.rightAnalog     = rightSpeed.toInt();
    GCS.conveyer        = Conveyer == "ON" ? true : false;
    GCS.signalLeft      = leftTurn == "ON" ? true : false;
    GCS.signalRight     = rightTurn == "ON" ? true : false;
    GCS.cameraAngle     = cameraAngle.toInt();
    GCS.conveyerStop    = conveyerStop == "ON" ? true : false;
}

void Telemetry::collectControlData(uint16_t &leftMotor, uint16_t &rightMotor, bool &conveyer,
                                   bool &leftTurn, bool &rightTurn, int &cameraAngle, bool &conveyerStop)
{
    leftTurn = false, rightTurn = false;
    leftMotor    = GCS.leftAnalog;
    rightMotor   = GCS.rightAnalog;
    conveyer     = GCS.conveyer;
    leftTurn     = GCS.leftAnalog  > (GCS.rightAnalog + 500) ? true : false;
    rightTurn    = GCS.rightAnalog > (GCS.leftAnalog + 500)  ? true : false;
    cameraAngle  = GCS.cameraAngle;
    conveyerStop = GCS.conveyerStop;
}


String Telemetry::constructMessage(float batteryPercentage, bool conveyer, 
                                   bool leftTurn, bool rightTurn, bool trash)
{
    char buffer[256];
    String iConveyer, iLeft, iRight, iTrash, remoteID = "S";
    iConveyer = conveyer? "ON" : "OFF";
    iLeft = leftTurn ? "YES" : "NO";
    iRight = rightTurn ? "YES" : "NO";
    iTrash = trash ? "YES" : "NO";
    String comma = ",";
    snprintf(buffer, sizeof(buffer),
            "%0.1f,"
            "%s,%s,"
            "%s",
            batteryPercentage,
            iLeft.c_str(), iRight.c_str(),
            iTrash.c_str()
    );
    return buffer;
}


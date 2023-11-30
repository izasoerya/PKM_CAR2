#ifndef TASK_H
#define TASK_H

#include "MotorController.h"
#include "PowerWindow.h"
#include "Telemetry.h"
#include "Sensor.h"
#include "Models.h"

Telemetry Tele;
CalculateBattery Batt;
UltrasonicTrash Trash;
MotorController Motor;
PowerWindow PW;

void loraFetchData()
{
	String loraData = "";
	bool isReceive = false;

	//* Fetch lora data from the GCS
	loraData = Tele.fetchLoraData(isReceive, LORA);
	if(loraData != "")Serial.println(loraData);

	if(isReceive)
	{
		Tele.parsingFromGCS(loraData);
		Tele.collectControlData(data.leftJoystick, data.rightJoystick, data.conveyer,
								data.leftTurn, data.rightTurn, data.cameraAngle, data.conveyerStop);
	}
	PW.controlMotor(data.conveyer, data.conveyerStop);
}

void controlMotorDC()
{	
	const int turnLeftThreshold = 1900;
	const int turnRightThreshold = 2200;
	const int stopValue = 2048;

	if(data.rightJoystick < turnLeftThreshold || data.rightJoystick > turnRightThreshold) 
		Motor.moveTurning(data.rightJoystick);
	else 
		Motor.moveForward(data.leftJoystick);
	if(data.isTimeOut) 
	{
		data.leftJoystick = stopValue;
		data.rightJoystick = stopValue;
		Motor.emergencyStop();
	}
}

void loraTransmittData()
{
	//* Get data and print in message2GCS
	bool trashCondition = false, conveyerCondition = false;
	float battValue;
	
	Batt.getVoltage(battValue);
	conveyerCondition = data.conveyer ? true : false;
	trashCondition = Trash.trashIsFull();

	//* Print the data for response
	String message2GCS = Tele.constructMessage(battValue, conveyerCondition, data.leftTurn, data.rightTurn, trashCondition);	
	LORA.println(message2GCS);			
}



#endif
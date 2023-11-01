#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>
#include "Motor.h"
#include "MotorController.h"
#include "PowerWindow.h"
#include "Telemetry.h"
#include "Sensor.h"
#include "Models.h"

Telemetry Tele;
CalculateBattery Batt;
UltrasonicTrash Trash;
MotorBLDC Wheel;
MotorDC Conveyer;
MotorController Motor;
PowerWindow PW;


void loraFetchData()
{
	String loraData = "";
	bool isReceive = false;

	//* Fetch lora data from the GCS
	loraData = Tele.fetchLoraData(isReceive, LORA);
	Serial.println(loraData);

	if(isReceive)
	{
		Tele.parsingFromGCS(loraData);
		Tele.collectControlData(data.leftMotor, data.rightMotor, data.conveyer,
								data.leftTurn, data.rightTurn, data.cameraAngle, data.conveyerStop);
	}

	//* Control the RATS parts here
	Conveyer.controlMotor(data.conveyer, data.conveyerStop);
}

ControlMotor motorLeft;
ControlMotor motorRight;

void controlMotorDC()
{	
	const int turnLeftThreshold = 1900;
	const int turnRightThreshold = 2200;

	if(data.rightMotor < turnLeftThreshold || data.rightMotor > turnRightThreshold)
	{
		// Wheel.controlMotorTurning(data.rightMotor);
		Motor.moveTurning(data.rightMotor);
	}
	else 
	{
		// motorLeft.speed = Wheel.controlMotorLeft(data.leftMotor);
		// motorRight.speed = Wheel.controlMotorRight(data.leftMotor);
		Motor.moveForward(data.leftMotor);
	}
	if(motorLeft.speed == 6969 || motorRight.speed == 6969) 
	{
		// Wheel.controlSetZero();
		Motor.emergencyStop();
		LORA.println("Burn Condition");
		while(1);
	}
	if(data.isTimeOut) 
	{
		data.leftMotor = 2048;
		data.rightMotor = 2048;
		Motor.emergencyStop();
		// Wheel.controlSetZero();
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

void setup() {
	// Communication initialization
  	Serial.begin(57600);
	LORA.begin(57600);

	// Disable WiFi and Bluetooth
	BluetoothSerial bt;
	WiFi.disconnect(true);
	bt.end();

	// Object initialization
	Wheel.beginMotorLeft();
	Wheel.beginMotorRight();
	Conveyer.begin();
	Trash.begin();
}

unsigned long previousReceive = 0;
unsigned long previousTransmit = 0;
unsigned long previousMotor = 0;

const long intervalReceive = 200;
const long intervalTransmit = 10000;
const long intervalMotor = 10;

void loop() {
	if (millis() - previousMotor >= intervalMotor) 
	{
		controlMotorDC();
	    previousMotor = millis();
	}
	
	if (millis() - previousReceive >= intervalReceive) 
	{
		loraFetchData();
		previousReceive = millis();
	}
	// if (currentMillis - previousTransmit >= intervalTransmit) 
	// {
	// 	loraTransmittData();
	// 	previousTransmit = currentMillis;
	// }
}

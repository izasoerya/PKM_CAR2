#ifndef MODELS_H
#define MODELS_H

#include <Arduino.h>

#define LORA Serial2
#define PIN_CONVEYER 	1
#define PIN_TURNLEFT 	18
#define PIN_TURNRIGHT 	5

struct ControlData
{
	uint16_t leftJoystick = 2048, rightJoystick = 2048; 
	int cameraAngle = 0;
	float battery = 0.0f;
	bool leftTurn = false, rightTurn = false;
	bool conveyer = false;
	bool isTimeOut = false;
	bool conveyerStop = false;
};
ControlData data;

struct ControlMotor
{
	int speed;
	int prevSpeed;
	bool forward;
};

uint32_t randNum[4];




#endif
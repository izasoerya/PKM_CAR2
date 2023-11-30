#include <Arduino.h>
#include <WiFi.h>
#include <scheduler.h>

#include "Task.h"

void setup() {
	// Communication initialization
  	Serial.begin(57600);
	LORA.begin(57600);
	WiFi.disconnect(true);

	// Object initialization
	Motor.begin();
	PW.begin();
	Trash.begin();
}

TaskScheduler ControlMotor(1, "Motor Controller", 500, controlMotorDC);
TaskScheduler SendLoraData(2, "Transmitter Handler", 200, loraTransmittData);
TaskScheduler ReceiveLoraData(3, "Receiver Handler", 10000, loraFetchData);

void loop() {
	ControlMotor.runTask();
	SendLoraData.runTask();
	ReceiveLoraData.runTask();
}

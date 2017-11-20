#pragma once
#include "ofMain.h"

#define BUFFER_SIZE 30
#define STARTCHAR 197
#define ENDCHAR 165

class SerialCommOFW
{
private:
	ofSerial serial;
	unsigned char incomingBuffer[BUFFER_SIZE];
public:
	SerialCommOFW(char *port, int baud);
	bool GetAllSensorsV2(char & sensors);
	bool GetAllSensors(char& sensors);
	bool ReadAll(unsigned char* buffer);
	~SerialCommOFW();
};


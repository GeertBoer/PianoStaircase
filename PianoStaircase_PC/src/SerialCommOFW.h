#pragma once
#include "ofMain.h"

#define BUFFER_SIZE 4
#define STARTCHAR 197
#define ENDCHAR 165

class SerialCommOFW
{
private:
	ofSerial serial;
	unsigned char incomingBuffer[BUFFER_SIZE];
	unsigned char outgoingBuffer[BUFFER_SIZE];
	
public:
	SerialCommOFW(char *port, int baud);
	bool SendSensors(char & sensors);
	bool GetAllSensorsV2(char & sensors);
	bool GetAllSensors(char& sensors);
	bool ReadAll(unsigned char* buffer);
	~SerialCommOFW();

};


#include "SerialCommOFW.h"
#include <bitset>

SerialCommOFW::SerialCommOFW(char *port, int baud)
{
	serial.setup(port, baud); //Open compoort
	memset(incomingBuffer, 0, BUFFER_SIZE); //Maak buffer leeg en klaar voor gebruik
}

bool SerialCommOFW::GetAllSensorsV2(char& sensors)
{
	memset(incomingBuffer, 0, BUFFER_SIZE);
	if (serial.available() >= 3)
	{
		serial.readBytes(incomingBuffer, 3);
		std::cout << "Just read: " << incomingBuffer << '\n';
	}
	else
	{
		std::cout << "No data available @a\n";
		return false;
	}

	if (incomingBuffer[0] == STARTCHAR && incomingBuffer[2] == ENDCHAR)
	{
		std::bitset<8> dataChar(incomingBuffer[1]);
		std::cout << "Data: " << dataChar << '\n';

		sensors = 0;
		sensors = incomingBuffer[1];
		return true;
	}
	else
	{
		std::cout << "Read error @a\n";
		return false;
	}
}

bool SerialCommOFW::GetAllSensors(char& sensors)
{
	memset(incomingBuffer, 0, BUFFER_SIZE);
	if (serial.available() >= 4)
	{
		serial.readBytes(incomingBuffer, 4);
		std::cout << incomingBuffer;
	}
	else
	{
		return false;
	}

	if (incomingBuffer[0] == STARTCHAR && incomingBuffer[3] == ENDCHAR)
	{
		std::bitset<8> uno(incomingBuffer[1]);
		std::bitset<8> due(incomingBuffer[2]);

		std::cout << '\n' << "buf1: " << uno << "buf2: " << due << '\n';

		sensors = 0;
		sensors |= incomingBuffer[2];
		sensors |= (incomingBuffer[1] << 4);
		return true;
	}
	else
	{


		std::cout << "\nErr. ";
		std::bitset<8> uno(incomingBuffer[1]);
		std::bitset<8> due(incomingBuffer[2]);

		std::cout << '\n' << "buf1: " << uno << "buf2: " << due << '\n';
		//serial.flush(true, false);
		return false;
	}
}

bool SerialCommOFW::ReadAll(unsigned char* buffer)
{
	memset(incomingBuffer, 0, BUFFER_SIZE);
	int amountOfBytesReady = serial.available();

	if (amountOfBytesReady > 0)
	{
		if (amountOfBytesReady >= BUFFER_SIZE)
		{
			amountOfBytesReady = BUFFER_SIZE - 1;
		}

		serial.readBytes(incomingBuffer, amountOfBytesReady);
		//buffer[amountOfBytesReady] = '\n';

		memcpy(buffer, incomingBuffer, BUFFER_SIZE);
	}
	else
	{
		return false; //Something went wrong!
	}

	return true;
}

SerialCommOFW::~SerialCommOFW()
{
	serial.close();
}

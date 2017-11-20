#define STARTCHAR '*'
#define ENDCHAR   '#'

#include "Sensor.hpp"

int duration = 0;
int distance = 0;

uint8_t detectionOld = 0;
uint8_t detectionToSend = 0;

Sensor *sensors[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Sensor *sensor0 = new Sensor(3, 4);
  sensors[0] = sensor0;
  Sensor *sensor1 = new Sensor(12, 13);
  sensors[1] = sensor1;
  Sensor *sensor2 = new Sensor(3, 4);
  sensors[2] = sensor2;
  Sensor *sensor3 = new Sensor(3, 4);
  sensors[3] = sensor3;
  Sensor *sensor4 = new Sensor(3, 4);
  sensors[4] = sensor4;
  Sensor *sensor5 = new Sensor(3, 4);
  sensors[5] = sensor5;
  Sensor *sensor6 = new Sensor(3, 4);
  sensors[6] = sensor6;
  Sensor *sensor7 = new Sensor(3, 4);
  sensors[7] = sensor7;
}

void loop() {
  // put your main code here, to run repeatedly:
  detectionToSend = 0;
  //Serial.println(sensors[1]->readSensorCM());
  for (int i = 0; i < 2; ++i)
  {
    detectionToSend <<= 1;
    if (sensors[i]->readSensorCM() < 90)
    {
      delay(50);
      if (sensors[i]->readSensorCM() < 90)
      {
        detectionToSend |= 0x01;
      }
    }
  }

  //Serial.println(detectionToSend, BIN);

  if (detectionToSend != detectionOld)
  {
    //Serial.println(detectionToSend, BIN);
    SendAllSensors(detectionToSend);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
  detectionOld = detectionToSend;
}

void SendAllSensors(uint8_t allSensors)
{
  uint8_t sendBuf[4];
  memset(sendBuf, 0, 4);
  sendBuf[0] = STARTCHAR;
  sendBuf[1] |= ((allSensors >> 4) & 0x0F);
  sendBuf[2] |= (allSensors & 0x0F);
  sendBuf[3] = ENDCHAR;

  Serial.write(sendBuf, 4);
}

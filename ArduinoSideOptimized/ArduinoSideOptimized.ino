#define STARTCHAR 197
#define ENDCHAR   165

#define COMMON_TRIG 2

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
  Sensor *sensor0 = new Sensor(COMMON_TRIG, 3);
  sensors[0] = sensor0;
  Sensor *sensor1 = new Sensor(COMMON_TRIG, 4);
  sensors[1] = sensor1;
  Sensor *sensor2 = new Sensor(COMMON_TRIG, 5);
  sensors[2] = sensor2;
  Sensor *sensor3 = new Sensor(COMMON_TRIG, 6);
  sensors[3] = sensor3;
  Sensor *sensor4 = new Sensor(COMMON_TRIG, 7);
  sensors[4] = sensor4;
  Sensor *sensor5 = new Sensor(COMMON_TRIG, 8);
  sensors[5] = sensor5;
  Sensor *sensor6 = new Sensor(COMMON_TRIG, 9);
  sensors[6] = sensor6;
  Sensor *sensor7 = new Sensor(COMMON_TRIG, 10);
  sensors[7] = sensor7;
}

void loop() {
  // put your main code here, to run repeatedly:
  detectionToSend = 0;
  //Serial.println(sensors[0]->readSensorCM());
  //Serial.println(sensors[1]->readSensorCM());
  for (int i = 0; i < 8; ++i)
  {
    delay(20);
    /*
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensors[i]->readSensorCM());*/
    
    detectionToSend <<= 1;
    if (sensors[i]->readSensorCM() < 150)
    {
      delay(15);
      if (sensors[i]->readSensorCM() < 150)
      {
        detectionToSend |= 0x01;
      }
    }
  }


  //Serial.println(detectionToSend, BIN);

  if (detectionToSend != detectionOld)
  {
   // Serial.print("BYTE: ");
   // Serial.println(detectionToSend, BIN);
    //Serial.println(detectionToSend, BIN);
    SendAllSensorsV2();
    digitalWrite(13, HIGH);
    delay(5);
    digitalWrite(13, LOW);
  }
  detectionOld = detectionToSend;
}

void SendAllSensorsV2()
{
  uint8_t data = detectionToSend ^ detectionOld;
  uint8_t sendBuf[3];
  memset(sendBuf, 0, 4);
  sendBuf[0] = STARTCHAR;
  sendBuf[1] = data;
  sendBuf[2] = ENDCHAR;

  Serial.write(sendBuf, 3);
}

void SendAllSensors()
{
  uint8_t data = detectionToSend ^ detectionOld;
  if (detectionOld == 0x00)
  {
    return;
  }
  
  uint8_t sendBuf[4];
  memset(sendBuf, 0, 4);
  sendBuf[0] = STARTCHAR;
  sendBuf[1] |= (((data >> 4) & 0x0F) | 0x90);
  sendBuf[2] |= ((data & 0x0F) | 0x90);
  sendBuf[3] = ENDCHAR;

  Serial.write(sendBuf, 4);
}

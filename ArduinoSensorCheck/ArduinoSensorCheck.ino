#define STARTCHAR 197
#define ENDCHAR   165

#define COMMON_TRIG 2

#include "Sensor.hpp"

int duration = 0;
int distance = 0;

uint8_t detectionOld = 0; // 'Vorige' verstuurde bericht
uint8_t detectionToSend = 0; // 'Huidige' verstuurde bericht

int ayy = 0;

Sensor *sensors[8]; // het array met alle sensoren

void setup() {
  delay(1000);
  Serial.begin(9600); //Maak de serial wakker zodat er berichten verstuurd kunnen worden
  pinMode(13, OUTPUT); //Maak ledje op de arduino beschikbaar voor bediening vanuit software
  digitalWrite(13, LOW); // Zet ledje op de arduino uit

  // hier worden alle sensoren aangesloten: Allen dezelfde trigger, ieder een unieke echo
  Sensor *sensor0 = new Sensor(2, 3);
  sensors[0] = sensor0;
  Sensor *sensor1 = new Sensor(2, 4);
  sensors[1] = sensor1;
  Sensor *sensor2 = new Sensor(6, 7);
  sensors[2] = sensor2;
  Sensor *sensor3 = new Sensor(8, 9);
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
  for(int i = 0; i < 1; i++)
  {
    ayy = sensors[i]->readSensorCM();
    Serial.print("Sensor nr.");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(ayy);
    delay(10);
    /*if (ayy < 150)
    {
      Serial.print("GROOT ALORM BIJ SENSOR ");
      Serial.println(i);
    }*/
  }
  //Serial.println();
}

void SendAllSensorsV2()
{
  uint8_t data = detectionToSend ^ detectionOld; //Zorg dat alleen verandering in individuele treden gestuurd wordt.
  uint8_t sendBuf[3]; //Buffer voor de message voor de pc
  memset(sendBuf, 0, 4); //Maak die buffer leeg
  sendBuf[0] = STARTCHAR; // eerste byte buffer is beginkaracter
  sendBuf[1] = data; // de daadwerkelijke data
  sendBuf[2] = ENDCHAR; // laatste byte is eindkarakter

  Serial.write(sendBuf, 3); //Informatie wordt naar ofw app op pc verstuurd
}

void SendAllSensors()
{
  // NEGEER DEZE FUNCTIE, OUDE VERSIE
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

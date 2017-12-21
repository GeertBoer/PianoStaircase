#define STARTCHAR 197
#define ENDCHAR   165

#define COMMON_TRIG 2

#include "Sensor.hpp"

int duration = 0;
int distance = 0;

uint8_t detectionOld = 0; // 'Vorige' verstuurde bericht
uint8_t detectionToSend = 0; // 'Huidige' verstuurde bericht

Sensor *sensors[8]; // het array met alle sensoren

void setup() {

  Serial.begin(9600); //Maak de serial wakker zodat er berichten verstuurd kunnen worden
  pinMode(13, OUTPUT); //Maak ledje op de arduino beschikbaar voor bediening vanuit software
  digitalWrite(13, LOW); // Zet ledje op de arduino uit

  // hier worden alle sensoren aangesloten: Allen dezelfde trigger, ieder een unieke echo
  Sensor *sensor0 = new Sensor(2, 3);
  sensors[0] = sensor0;
  Sensor *sensor1 = new Sensor(4, 5);
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

  detectionToSend = 0; // maak buffer voor huidige metingen leeg
  //Serial.println(sensors[0]->readSensorCM());

  for (int i = 0; i < 3; ++i)
  {
    delay(20); // Wacht 20ms: storing voorkomen

    detectionToSend <<= 1;  //Schuif in deze byte alles 1 plek naar links; bijvoorbeeld 1001 1111 wordt 0011 1110.
    //Dit is omdat de resultaten van de lezing van de sensor, altijd naar de meest rechtse bit worden geschreven.

    if (sensors[i]->readSensorCM() < 150) // Als de sensor binnen 150cm 'iets' ziet, ga hier in
    {
      delay(30);
      if (sensors[i]->readSensorCM() < 150) // Als er na 15ms nog steeds iets zit, ga in if. Dit is om per ongelukke positieven te verminderen
      {
        detectionToSend |= 0x01; // Zet in de byte, de allerlaatste bit op 1. bv. 1001 1000 wordt 1001 1001
      }
    }
  }
  // for loop is afgelopen, de byte met de huidige 'positieve' treden is klaar.
  //bv. als op trede 0, 3 en 5 mensen stonden is de byte 0001 0101.


  //Serial.println(detectionToSend, BIN);

  if (detectionToSend != detectionOld) //als er niets veranders is, tov de vorige meting, verstuur niets.
  {
    // Serial.print("BYTE: ");
    // Serial.println(detectionToSend, BIN);
    //Serial.println(detectionToSend, BIN);

    SendAllSensorsV2(); //De functie die de byte opbreekt in een verstuurbare message wordt aangeroepen
    digitalWrite(13, HIGH); //Knipper lampje op de arduino om aan te geven dat er iets veranderd is.
    delay(5);
    digitalWrite(13, LOW);
  }
  detectionOld = detectionToSend; // Overschrijf oude meting met nieuwe meting
}

void SendAllSensorsV3()
{
  uint8_t data = detectionToSend ^ detectionOld; //Zorg dat alleen verandering in individuele treden gestuurd wordt.

  int a = 0;
  for (int i = 0; i < 8; ++i)
  {
    a += (0x01 & (data >> i));
  }
  if (a > 2)
  {
    Serial.println("DATA WAS");
    return;
  }

  uint8_t sendBuf[3]; //Buffer voor de message voor de pc
  memset(sendBuf, 0, 4); //Maak die buffer leeg
  sendBuf[0] = STARTCHAR; // eerste byte buffer is beginkaracter
  sendBuf[1] = data; // de daadwerkelijke data
  sendBuf[2] = ENDCHAR; // laatste byte is eindkarakter

  Serial.write(sendBuf, 3); //Informatie wordt naar ofw app op pc verstuurd
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

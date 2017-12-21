#define STARTCHAR 197
#define ENDCHAR   165

#define COMMON_TRIG 2
#define s_p //Serial.print
#define s_pl //Serial.println

#include "Sensor.hpp"

int duration = 0;
int distance = 0;

uint8_t detectionOld = 0;
uint8_t detectionToSend = 0;

Sensor *sensors[8];

void setup() {

  Serial.begin(115200);

  digitalWrite(13, LOW);

  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Sensor *sensor0 = new Sensor(COMMON_TRIG, 3);
  sensors[0] = sensor0;
  Sensor *sensor1 = new Sensor(COMMON_TRIG, 4);
  sensors[1] = sensor1;
}

void loop() {
  detectionToSend = 0;

  for (int i = 0; i < 2; ++i)
  {
    detectionToSend <<= 1;
    if (analogRead(i) < 850)
    {
      detectionToSend |= 0x01;
      /*delay(20);
      if (analogRead(i) < 800)
      {
        detectionToSend |= 0x01;
      }*/
    }
  }

  /*/ DEBUG
    Serial.print("Pin 1: ");
    Serial.print(analogRead(A0));
    Serial.print(" Pin 2: ");
    Serial.print(analogRead(A1));
    Serial.print(" US0: ");
    Serial.print(sensors[0]->readSensorCM());
    Serial.print(" US1: ");
    Serial.println(sensors[1]->readSensorCM());  */

  if (detectionToSend != detectionOld) //als er niets veranders is, tov de vorige meting, verstuur niets.
  {
    SendAllSensorsV2(); //De functie die de byte opbreekt in een verstuurbare message wordt aangeroepen
    digitalWrite(13, HIGH); //Knipper lampje op de arduino om aan te geven dat er iets veranderd is.
    delay(20);
    digitalWrite(13, LOW);
  }
  detectionOld = detectionToSend; // Overschrijf oude meting met nieuwe meting
}


void SendAllSensorsV2()
{
  s_p("\ndetectionToSend  = 0b");
  s_p(detectionToSend, BIN);
  s_p("\ndetectionOld = 0b");
  s_p(detectionOld, BIN);
  uint8_t data = detectionToSend & ~detectionOld; //Zorg dat alleen verandering in individuele treden gestuurd wordt.
  s_p("\n De data is: 0b");
  s_pl(data, BIN);
  uint8_t sendBuf[3]; //Buffer voor de message voor de pc
  memset(sendBuf, 0, 4); //Maak die buffer leeg
  sendBuf[0] = STARTCHAR; // eerste byte buffer is beginkaracter
  sendBuf[1] = data; // de daadwerkelijke data
  sendBuf[2] = ENDCHAR; // laatste byte is eindkarakter

  Serial.write(sendBuf, 3); //Informatie wordt naar ofw app op pc verstuurd
}

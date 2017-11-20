#include "Sensor.hpp"
#include "Arduino.h"

Sensor::Sensor(int trig, int echo)
{
  triggerPin = trig;
  echoPin = echo;

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

Sensor::~Sensor()
{

}

int Sensor::readSensorCM()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;

  if (distance > 255 || distance < 0)
  {
    return -1;
  }
  else
  {
    return distance;
  }
}

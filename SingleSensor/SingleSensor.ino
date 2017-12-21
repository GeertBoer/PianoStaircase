#include "Sensor.hpp"

Sensor sensor(2,3);/*
Sensor sensor1(A2, A3);
Sensor sensor2(A4, A5);
Sensor sensor3(2, 3);*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(sensor.readSensorCM());
  /*
  Serial.println(sensor1.readSensorCM());
  Serial.println(sensor2.readSensorCM());
  Serial.println(sensor3.readSensorCM());*/
  delay(20);
}

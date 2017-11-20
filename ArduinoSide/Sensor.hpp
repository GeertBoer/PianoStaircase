class Sensor
{
  private:
    int triggerPin;
    int echoPin;

    int duration;
    int distance;
  public:
    Sensor(int trig, int echo);
    int readSensorCM();
    ~Sensor();
};

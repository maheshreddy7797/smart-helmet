#include <SoftwareSerial.h>
SoftwareSerial blueTooth(10, 11); //Connect HC-05 Tx,Rx to pin 10,11
int alcohol_detector = A0; //Alcohol sensor attached to pin A0
int sensor_value = 0;
int red = 7, yel = 8, blue = 9; //Status led's
void setup()
{
  Serial.begin(9600); //Set baudrate 9600 for better transmission
  blueTooth.begin(9600);
}

void loop()
{
  sensor_value = digitalRead(alcohol_detector);
  Serial.println(sensor_value);
  if (sensor_value == 1)
    blueTooth.println("1");
  else
    blueTooth.println("0");
  delay(100);
}

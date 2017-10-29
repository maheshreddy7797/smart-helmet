#include <SoftwareSerial.h>
#include "SIM900.h"
#include "sms.h"
#include "gps.h"
SMSGSM sms;
GPSGSM gps;
/**********************SMS*************************/
int numdata;
boolean started = false;
char smsbuffer[160], buf[160];
char n[20];
String inmsgtext;
/**********************GPS*************************/
char lon[15];
char lat[15];
char alt[15];
char time[20];
char vel[15];
char msg1[5];
char msg2[5];
char stat;
char inSerial[20];
int i = 0;
double longi, lati;
/***************************GENERAL PURPOSE***********************/
int vibration_sensor = 4;
int vibration_sensor_value = 0;
void setup()
{
  pinMode(4, INPUT);
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
  if (gsm.begin(9600)) {
    Serial.println("\nstatus=READY");
    started = true;
  }
  else Serial.println("\nstatus=IDLE");
  if (started) {
    //GPS attach
    if (gps.attachGPS())
      Serial.println("status=GPSREADY");
    else Serial.println("status=ERROR");
    delay(20000);  //Time for fixing
    stat = gps.getStat();
    if (stat == 1)
      Serial.println("NOT FIXED");
    else if (stat == 0)
      Serial.println("GPS OFF");
    else if (stat == 2)
      Serial.println("2D FIXED");
    else if (stat == 3)
      Serial.println("3D FIXED");
    delay(5000);
    //Get data from GPS
    gps.getPar(lon, lat, alt, time, vel);
    Serial.println(lon);
    Serial.println(lat);
    Serial.println(alt);
    Serial.println(time);
    Serial.println(vel);
  }
};

void loop()
{
  vibration_sensor_value = digitalRead(4);
  Serial.print("Vibration value=");
  Serial.println(vibration_sensor_value);
  int a = 0;
  if (started) {
    if (sms.GetSMS(1, n, smsbuffer, 160)) {
      // Serial.println(n);
      Serial.println(smsbuffer);
      for (int k = 9; k < 160; k++) {
        inmsgtext += smsbuffer[k];
      }
      inmsgtext.toLowerCase();
      Serial.println(inmsgtext);
      a = inmsgtext.length();
      Serial.print("length=  ");
      Serial.println(a);
      if (smsbuffer == "MaheshR: trope") {
        Serial.println("Successfull done");
      }
      sms.DeleteSMS(1);
      Serial.println("MESSAGE DELEETED");
    }
    delay(2000);
    if (started) {
      if (vibration_sensor_value == 1) {
        gps.getPar(lon, lat, alt, time, vel);
        Serial.println(lon);
        Serial.println(lat);
        Serial.println(alt);
        Serial.println(time);
        Serial.println(vel);
        String stringOne, stringlon, stringlat;
        stringOne = String("Emergency ! ! ! Accident Occured at ");
        for (int k = 0; k < 16; k++) {
          stringlon += lon[k];
          stringlat += lat[k];
        }
        stringOne = stringOne + stringlon + stringlat;
        stringOne.toCharArray(buf, 160);
        if (sms.SendSMS("7032937625", buf))
          Serial.println("\nSMS sent OK");
      }
    }
  }
}

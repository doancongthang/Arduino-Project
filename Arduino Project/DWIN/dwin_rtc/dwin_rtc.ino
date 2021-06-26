/*
  DS3231_test.pde
  Eric Ayars
  4/11

  Test/demo of read routines for a DS3231 RTC.

  Turn on the serial monitor after loading this to check if things are
  working as they should.

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 clock;
bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;
void setup() {
  // Start the I2C interface
  Wire.begin();

  // Start the serial interface
  Serial.begin(115200);
}

void loop()
{
  delay(200);
  secondrtc();
  minutertc();
  hourrtc();
  monthrtc();
}
//*********************************************************************//
//RTC
void secondrtc()
{
  int i = clock.getSecond();
  Serial.write(0x5A);
  Serial.write(0xA5);
  Serial.write(0x05);
  Serial.write(0x82);
  Serial.write(0x10);
  Serial.write(0x12);
  Serial.write(0x00);
  Serial.write(i);
}
void minutertc()
{
  int i = clock.getMinute();
  Serial.write(0x5A);
  Serial.write(0xA5);
  Serial.write(0x05);
  Serial.write(0x82);
  Serial.write(0x10);
  Serial.write(0x11);
  Serial.write(0x00);
  Serial.write(i);
}
void hourrtc()
{
  int i = 0;
  int h = clock.getHour(h12Flag, pmFlag);
  if(h<=12)
  {
    i = h;
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x10);
    Serial.write(0x00);
    Serial.write(i);
  }
  if((h>12) and (i<=23))
  {
  i = i - 12;
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x10);
    Serial.write(0x00);
    Serial.write(i);
  }
  if(i = 24)
  {
    i = 12;
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x10);
    Serial.write(0x00);
    Serial.write(i);
  }
}
void monthrtc()
{
   int i = clock.getMonth(century);
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x13);
    Serial.write(0x00);
    Serial.write(i);
}
//***************************************************************************************//
void kimgio()
{
  int i = 0;
  while (i < 13)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x10);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kimphut()
{
  int i = 0;
  while (i < 61)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x11);
    Serial.write(0x00);
    Serial.write(i);
    delay(150);
    i = i + 1;
  }
}
void kimgiay()
{
  int i = 0;
  while (i < 61)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x12);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kimthang()
{
  int i = 0;
  while (i < 13)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x13);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kimkg()
{
  int i = 0;
  while (i < 16)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x14);
    Serial.write(0x00);
    Serial.write(i);
    delay(100);
    i = i + 1;
  }
  i = 15;
  while (i >= 0)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x14);
    Serial.write(0x00);
    Serial.write(i);
    delay(100);
    i = i - 1;
  }
}


/////////////////////////////////////
void kim1()
{
  int i = 0;
  while (i < 13)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x15);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kim2()
{
  int i = 0;
  while (i < 13)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x16);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kim3()
{
  int i = 0;
  while (i < 9)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x17);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kim4()
{
  int i = 0;
  while (i < 9)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x18);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kim5()
{
  int i = 0;
  while (i < 9)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x19);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}
void kim6()
{
  int i = 0;
  while (i < 9)
  {
    Serial.write(0x5A);
    Serial.write(0xA5);
    Serial.write(0x05);
    Serial.write(0x82);
    Serial.write(0x10);
    Serial.write(0x1a);
    Serial.write(0x00);
    Serial.write(i);
    delay(200);
    i = i + 1;
  }
}

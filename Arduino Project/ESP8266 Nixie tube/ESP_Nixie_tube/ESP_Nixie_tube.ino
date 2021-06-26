#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "QT";
const char *password = "quynh283";
//GMT +7 = 60*60*7 = 25200
const long utcOffsetInSeconds = 25200;
int p;
int a;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }


  pinMode(29, OUTPUT);  // 74141 A
  pinMode(28, OUTPUT);  // 74141 B
  pinMode(27, OUTPUT);  // 74141 C
  pinMode(26, OUTPUT);   // 74141 D

  pinMode(23, OUTPUT);  //anode Nixie1
  pinMode(22, OUTPUT);  //anode Nixie2
  pinMode(21, OUTPUT);  //anode Nixie3
  pinMode(20, OUTPUT);  //anode Nixie4
  pinMode(19, OUTPUT);  //anode Nixie5
  pinMode(18, OUTPUT);  //anode Nixie6


  digitalWrite(29, 0);
  digitalWrite(28, 0);
  digitalWrite(27, 0);
  digitalWrite(26, 0);

  digitalWrite(23, 0); //anode
  digitalWrite(22, 0); //anode
  digitalWrite(21, 0); //anode
  digitalWrite(20, 0); //anode
  digitalWrite(19, 0); //anode
  digitalWrite(18, 0); //anode


  p = 2; //Multiplex delay time
  a = 1000; //anti poisoning time
  timeClient.begin();
}

void loop()
{
  timeClient.update();

  // For test Serial
  /*
    Serial.print(daysOfTheWeek[timeClient.getDay()]);
    Serial.print(", ");
    Serial.print(timeClient.getHours());
    Serial.print(":");
    Serial.print(timeClient.getMinutes());
    Serial.print(":");
    Serial.println(timeClient.getSeconds());
    //Serial.println(timeClient.getFormattedTime());

    delay(1000);
  */

  //************************************************************
  int hours = timeClient.getHours();
  if (hours > 12)
  {
    hours = hours - 12; //change to 12 hour format
  }
  if (hours < 10)
  {
    nixie1on();     send0();     nixie1off();
    nixie2on();  selectDigit(hours); nixie2off();
  }
  else
  {
    nixie1on();  send1();  nixie1off();
    nixie2on();  selectDigit(hours - 10); nixie2off();
  }

  //if minutes < 10 nixie3 = 0 and nixie4 = minutes
  //  else nixie3 = minutes/10 and nixie4 = minutes%10 (switch)
  int minutes = timeClient.getMinutes();
  if (minutes < 10)
  {
    nixie3on();  send0();  nixie3off();
    nixie4on();  selectDigit(minutes);  nixie4off();
  }
  else
  {
    nixie3on();  selectDigit((int)minutes / 10);  nixie3off();
    nixie4on();  selectDigit(minutes % 10);  nixie4off();
  }

  //if seconds < 10 nixie5 = 0 and nixie6 = minutes
  //else nixie5 = minutes/10 and nixie6 = minutes%10 (switch)
  ///*
  int seconds = timeClient.getSeconds();
  if (seconds < 10)
  {
    nixie5on();  send0();  nixie5off();
    nixie6on();  selectDigit(seconds);  nixie6off();
  }
  else
  {
    nixie5on();  selectDigit((int)seconds / 10);  nixie5off();
    nixie6on();  selectDigit(seconds % 10);  nixie6off();
  }
  //*/

  //call anti poisoning at this time twice a day
  if (hours == 6 && minutes == 30 && seconds == 1)
  {
    cathodeAntiPoising();
  }
}




//*****************************************************//
void send0()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(p); //0
}
void send1()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(p); //1
}
void send2()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 0); delay(p); //2
}
void send3()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 1); delay(p); //3
}
void send4()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 0); delay(p); //4
}
void send5()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 1); delay(p); //5
}
void send6()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 0); delay(p); //6
}
void send7()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 1); delay(p); //7
}
void send8()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(p); //8
}
void send9()  //send binary code to 74141 to activate digit
{
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(p); //9
}



void nixie1on()
{
  digitalWrite(23, 1); //anode on
}
void nixie2on()
{
  digitalWrite(22, 1); //anode on
}
void nixie3on()
{
  digitalWrite(21, 1); //anode on
}
void nixie4on()
{
  digitalWrite(20, 1); //anode on
}
void nixie5on()
{
  digitalWrite(19, 1); //anode on
}
void nixie6on()
{
  digitalWrite(18, 1); //anode on
}




void nixie1off()
{
  digitalWrite(23, 0); //anode off
}
void nixie2off()
{
  digitalWrite(22, 0); //anode off
}
void nixie3off()
{
  digitalWrite(21, 0); //anode off
}
void nixie4off()
{
  digitalWrite(20, 0); //anode  off
}
void nixie5off()
{
  digitalWrite(19, 0); //anode  off
}
void nixie6off()
{
  digitalWrite(18, 0); //anode  off
}

/* Select a digit 0-9 and call the appropriate send function */
void selectDigit(int d)
{
  switch (d)
  {
    case 0: send0(); break;
    case 1: send1(); break;
    case 2: send2(); break;
    case 3: send3(); break;
    case 4: send4(); break;
    case 5: send5(); break;
    case 6: send6(); break;
    case 7: send7(); break;
    case 8: send8(); break;
    case 9: send9(); break;
  }
}
void cathodeAntiPoising()  //cycle nixie 1 and 2 through all numbers
{
  digitalWrite(23, 0); //turn off nixie
  digitalWrite(22, 0); //turn off nixie

  digitalWrite(21, 1); //anode
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //0
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //1
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 0); delay(a); //2
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 1); delay(a); //3
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //4
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //5
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 0); delay(a); //6
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 1); delay(a); //7
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //8
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //9
  digitalWrite(21, 0); //anode

  digitalWrite(20, 1); //anode
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //0
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //1
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 0); delay(a); //2
  digitalWrite(29, 0); digitalWrite(28, 0); digitalWrite(27, 1); digitalWrite(26, 1); delay(a); //3
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //4
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //5
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 0); delay(a); //6
  digitalWrite(29, 0); digitalWrite(28, 1); digitalWrite(27, 1); digitalWrite(26, 1); delay(a); //7
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 0); delay(a); //8
  digitalWrite(29, 1); digitalWrite(28, 0); digitalWrite(27, 0); digitalWrite(26, 1); delay(a); //9
  digitalWrite(20, 0); //anode
}

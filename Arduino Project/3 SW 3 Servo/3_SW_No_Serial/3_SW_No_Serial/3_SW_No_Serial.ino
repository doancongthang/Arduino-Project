# include <Servo.h>
# include <Stepper.h>
#include <DFRobotDFPlayerMini.h>


#define LED 12
#define BUTTON 2
#define SW1 A2    // Che do 1
#define SW2 A3    // Che do 2
#define SW3 A4    // Che do 3

// Wiring:
// Pin 4 to IN1 on the ULN2003 driver
// Pin 5 to IN2 on the ULN2003 driver
// Pin 6 to IN3 on the ULN2003 driver
// Pin 7 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:

int bientro = A0;
int gocquay = 0;
int positioncurent = 0;
int positionold = 0;
int servoPin1 = 9;
int servoPin2 = 10;
int ledcounter = 0;
int value = 0;
int value1 = 0;
int value2 = 0;
int servoPos1 = 0;
int servoPos2 = 0;

const int LONG_PRESS_TIME  = 3000; // 1000 milliseconds
//Define Revolution 2^11 = 2048
const int stepsPerRevolution = 2048;

int lastState = LOW;              // the previous state from the input pin
int currentState;                 // the current reading from the input pin
bool isPressing = false;          // Phat hien dang nhan
bool isLongDetected = false;      // Phat hien thoi gian dai
unsigned long pressedTime  = 0;   // Thời gian nhan

Servo myservo1, myservo2;
Stepper myStepper = Stepper(stepsPerRevolution, 4, 6, 5, 7);
DFRobotDFPlayerMini player;
//****************************************************////****************************************************//
void setup()
{
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  Serial.begin(9600);
  // Serail1 communicate with SD Card Player
  Serial1.begin(9600);

  pinMode(LED, OUTPUT);           // output for the LED
  pinMode(BUTTON, INPUT_PULLUP);  // input for the button
  pinMode(SW1, INPUT_PULLUP);     // input for the SW1
  pinMode(SW2, INPUT_PULLUP);     // input for the SW2
  pinMode(SW3, INPUT_PULLUP);     // input for the SW3
  // Set the max speed to 10 rpm:
  // maximum speed for a 28byj-48 stepper motor is roughly 10-15 rpm at 5 V.
  myStepper.setSpeed(15);


  // Start communication with DFPlayer Mini
  if (player.begin(Serial1))
  {
    //Serial.println("OK");
    // Set volume to maximum (0 to 30).
    player.volume(0);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    //player.playMp3Folder(1);
  }
  else
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}
//****************************************************////****************************************************//
void loop()
{
  // Doc gia tri bien tro
  value = analogRead(bientro);

  // Doc trang thai phim nhan
  currentState = digitalRead(BUTTON);

  // Chuyển giá trị analog (0-1023) đọc được từ biến trở sang số đo độ (0-180độ
  value1 = value;   // chuyen thanh gia tri dieu khien DC
  value2 = value;   // CHuyen thanh gia tri dieu khien servo2
  servoPos1 = map(value1, 0, 1023, 0, 180);         // Cho servo quay một góc là servoPos 1
  servoPos2 = map(value2, 0, 1023, 0, 180);         // Cho servo quay một góc là servoPos 2
  positioncurent = map(value, 0, 1023, 0, 2048);        // Doc gia tri bien tro thanh goc quay 360do
  gocquay = positioncurent - positionold;

  // Defaul with any position
  int mode = readmode();
  switch (mode)
  {
    case 1:
      position1();
      break;
    case 2:
      position2();
      break;
    case 3:
      position3();
      break;
  }
}
//****************************************************//
void position1()
{
  if (value > 100)
  {
    // KIEM TRA PHIM NHAN KHOI DONG MAY
    BUTTONPRESS();

    // KIEM TRA PHIM DUOC NHAN KHONG
    if (ledcounter % 2 == 1)
    {
      digitalWrite(LED, HIGH);    // Bat led khoi dong
    }
    else
    {
      HAMTAT();    // che do 1 chua khoi dong
    }

    // Dieu khien DC  ĐỒNG HỒ VÒNG QUAY
    myStepper.step(gocquay);
    positionold = positioncurent;   // Gan gia tri hien tai bang gia tri

    // Dieu khien servo 1
    myservo1.write(servoPos1);

    // Dieu khien servo 2
    myservo2.write(servoPos2);
    delay(3000);    // delay de dong co quay
  }
  // ket thuc if 1
  else
  {
    HAMTAT();
  }
}
//****************************************************//
void position2()
{
  // KIEM TRA PHIM NHAN KHOI DONG MAY
  BUTTONPRESS();
  if (ledcounter % 2 == 1) {
    digitalWrite(LED, HIGH);
    delay(40000);   // tre 12s
    HAMTAT();   // tat may sau 12 s den khoi dong
  }
  else
  {
    HAMTAT(); // khong phat hien phim duoc nhan khoi dong, tat luon
  }
}
//****************************************************//
void position3()
{
  // KIEM TRA PHIM NHAN KHOI DONG MAY
  BUTTONPRESS();
  if (ledcounter % 2 == 1)
  {
    digitalWrite(LED, HIGH);
    sound();
    delay(12000);   // tre 12s
    HAMTAT();   // tat may sau 12 s den khoi dong
  }
  else
  {
    HAMTAT(); // khong phat hien phim duoc nhan khoi dong, tat luon
  }
}
//****************************************************//
int readmode()
{
  /*
    // Doc gia tri bien tro
    value = analogRead(bientro);
    Serial.print("Gia tri bien tro doc ban dau  ");
    Serial.println(value);

    // Doc trang thai phim nhan
    currentState = digitalRead(BUTTON);
    Serial.print("Gia tri phim nhan doc ban dau  ");
    Serial.println(currentState);

    // Chuyển giá trị analog (0-1023) đọc được từ biến trở sang số đo độ (0-180độ
    value1 = value;   // chuyen thanh gia tri dieu khien DC
    value2 = value;   // CHuyen thanh gia tri dieu khien servo2
    servoPos1 = map(value1, 0, 1023, 0, 180);         // Cho servo quay một góc là servoPos 1
    servoPos2 = map(value2, 0, 1023, 0, 180);         // Cho servo quay một góc là servoPos 2
    positioncurent = map(value, 0, 1023, 0, 2048);        // Doc gia tri bien tro thanh goc quay 360do
    gocquay = positioncurent - positionold;
  */
  if (digitalRead(SW1) == 1)
    return 1;
  if (digitalRead(SW2) == 1)
    return 2;
  if (digitalRead(SW3) == 1)
    return 3;
}
//****************************************************//
void sound()
{
  player.volume(30);
  // Play the "0001.mp3" in the "mp3" folder on the SD card
  player.playMp3Folder(1);
}
//****************************************************//
void BUTTONPRESS()
{
  if (lastState == HIGH && currentState == LOW)
  {
    // button is pressed
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  }
  else if (lastState == LOW && currentState == HIGH)
  {
    // button is released
    isPressing = false;
  }
  // Kiem tra gia tri phim nhan lon hon thoi gian quy dinh
  if (isPressing == true && isLongDetected == false)
  {
    long pressDuration = millis() - pressedTime;
    if (pressDuration > LONG_PRESS_TIME )
    {
      ledcounter++;   // tang gia tri bien dem
      isLongDetected = true;
    }
  }
  // LUU TRANG THAI HIEN TAI SANG TRANG THAI CUOI
  lastState = currentState;
}
//****************************************************//
//****************************************************//
void LEDONOFF ()
{
  if (ledcounter % 2 == 1)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}
//****************************************************//
// HAM KHI KHONG CO DU KIEN NAO
void HAMTAT()
{
  digitalWrite(LED, LOW);   // tat led
  ledcounter = 0;           // Reset lai so dem
  myStepper.step(0);       // keo kim quay ve 0
  myservo1.write(0);        // Kim servo1 ve 0
  myservo2.write(0);        // Kim servo2 ve 0
}

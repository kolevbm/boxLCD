#include <LiquidCrystal.h>
#include <Servo.h>


//========== КОНСТАНТИ ==========
const int posOpened = 165;  //degrees
const int posClosed = 80;   //degrees
const int moveDelay = 10;   //milliseconds
const int distClose = 90;   //centimeters
const int distOpen = 45;    //centimeters

const int servoPin = 5;
const int trigPin = 6;
const int echoPin = 7;


//========== ПРОМЕНЛИВИ ==========
Servo servo;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
long duration = 0;
int distance = 0;
int i = 0;
//int servoPosition = 0;
int opened = 0;
int closed = 0;


//========== ИНИЦИАЛИЗАЦИЯ ==========
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  lcd.begin(16,2);
  //servo.write(posClosed);

#ifdef DEBUG
  Serial.begin(9600);
#endif
}


//========== ГЛАВНА ПРОГРАМА ==========
void loop() {
// измерване на разстоянието от сензора (в см)
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,1);
lcd.print(distance);

lcd.setCursor(0,0);
if(distance < distOpen)
{
  lcd.print("OTBOPEH ");
}
if(distance > distClose)
{
  lcd.print("3ATBOPEH");
}

// отваряне на кутията
//if(distance < 200)
//{

  if(distance < distOpen)
  {
    if(opened == 0)
    {
      for(i = posClosed; i < posOpened; i++)
      {
  
        servo.write(i);
        delay(moveDelay);
      }
        opened=1;
        closed=0;
    }

  }

// затваряне на кутията
  if(distance > distClose)
  {
    if(closed == 0)
    {
      for(i = posOpened; i > posClosed; i--)
      {
        servo.write(i);
        delay(moveDelay);
      }
        opened=0;
        closed=1;
    }
  }
  
//}
delay(1000);
}


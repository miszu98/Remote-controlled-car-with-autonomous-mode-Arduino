#include <NewPing.h>
#include <Servo.h> // Silnik sterujący czujnikiem odległości

#define TRIG_PIN A4 
#define ECHO_PIN A5 
#define MAX_DISTANCE 200 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

int izqA = 5;  // Piny silników 
int izqB = 6;
int derA = 9;
int derB = 10;
int spd = 255; // prędkość 0-255
int sr = 'g'; 

void setup() {
Serial.begin(9600); 
pinMode(derA, OUTPUT);
pinMode(derB, OUTPUT);
pinMode(izqA, OUTPUT);
pinMode(izqB, OUTPUT);

myservo.attach(4);  // Pin servo
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}
void loop() {
if(Serial.available()>0){ // Sekcja sterowania samochodem
sr = Serial.read();
}
    if(sr=='d'){ // prawo
     Serial.println(sr);
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, spd);
    analogWrite(izqA, spd);
    }
    if(sr=='s'){ // tyl
     Serial.println(sr);
    analogWrite(derB, spd); 
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, spd);
    }
    if(sr=='c'){ // Stop
     Serial.println(sr);
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    }
    if(sr=='w'){ // przod
     Serial.println(sr);
    analogWrite(derB, 0);
    analogWrite(izqB, spd);
    analogWrite(izqA, 0);
    analogWrite(derA, spd);
    }
    if(sr=='a'){ // lewo
     Serial.println(sr);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    analogWrite(derB, spd);
    analogWrite(izqB, spd);
    }
  if(sr == 'k'){ // Autonomiczna jazda
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  
  if(distance<=20)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();

}
}
int lookRight()
{ // Patrzy w prawo i zczytuje odległość
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{ // Patrzy w lewo i zczytuje odległość
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70); 
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 500;
  }
  return cm;
}

void moveStop() { // Funkcje wykorzystywane do autonomicznej jazdy
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(izqA, 0);
  } 
  
void moveForward() {


    analogWrite(derB, 0);
    analogWrite(izqB, spd);
    analogWrite(izqA, 0);
    analogWrite(derA, spd); 
  
}

void moveBackward() {
    
    analogWrite(derB, spd); 
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, spd);
  
}  

void turnRight() {
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, spd);
  analogWrite(izqA, spd);
  delay(300);
 moveForward();      
  
} 
 
void turnLeft() {
  analogWrite(derA, 0);
  analogWrite(izqA, 0);
  analogWrite(derB, spd);
  analogWrite(izqB, spd);    
  delay(300);
   moveForward();
}  

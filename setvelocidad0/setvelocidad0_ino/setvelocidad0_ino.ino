#include <Servo.h> 
 
Servo myservo;  // Cremos el objeto de servo
const int speed0 =  74 ; // valor en el que el servo se mantiene quieto (es posible que haga falta variarlo un poco)
const int speedIda = 81;
const int speedVuelta = 61;
int i; // iterador
int potEndStop = 12;
int endstop = 13 ; // logica inversa en el endstop 0=pulsado, 1=no pulsado
int buttonState = 0; 
int vel;
boolean ida ;
boolean repetido;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(potEndStop, OUTPUT);
  digitalWrite(potEndStop, HIGH);
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
  pinMode(endstop, INPUT);
  vel = speedIda;
    ida = true; 
  repetido = false;
} 
 
 
void loop() 
{ 
 
      myservo.write(speed0);
       }
 
  

#include <Servo.h> 
 
Servo myservo;  // Cremos el objeto de servo
const int speed0 = 71; // valor en el que el servo se mantiene quieto (es posible que haga falta variarlo un poco)
int i; // iterador
int potEndStop = 12;
int endstop = 13 ; // logica inversa en el endstop 0=pulsado, 1=no pulsado
int buttonState = 0; 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(potEndStop, OUTPUT);
  digitalWrite(potEndStop, HIGH);
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
  pinMode(endstop, INPUT);
   myservo.write(speed0);
} 
 
 
void loop() 
{ 
// buttonState = digitalRead(endstop);
  if (digitalRead(endstop) == HIGH) {  
   Serial.println("sin pulsar endstop");
 myservo.write(speed0+10);}
 
  else 
   { myservo.write(speed0-10);}
   /* for(i = 0; i < 90; i++) // vamos desde velocidad 0 hasta velocidad 90 (maximo)
  { 
    myservo.write(speed0 + i);
    delay(15); 
  } 
  
  myservo.write(speed0);
  delay(1000);
  
  // sentido contrario
  for(int i = 0; i < 90; i++) // vamos desde velocidad 0 hasta velocidad 90 (maximo)
  { 
    myservo.write(speed0 - i);
    delay(15); 
  } */
// }
 
  delay(1000);
} 

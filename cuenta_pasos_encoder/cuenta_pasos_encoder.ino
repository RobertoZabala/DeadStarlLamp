volatile int unsigned pulsos=0;
#include <Encoder.h>
Encoder myEnc(2, 6);

#include <Servo.h> 
Servo myservo;  // Cremos el objeto de servo
const int speed0 = 71; // valor en el que el servo se mantiene quieto (es posible que haga falta variarlo un poco)
const int speedIda = speed0+90;
const int speedVuelta = speed0-90;
int i; // iterador
int potEndStop = 12;
int endstop = 13 ; // logica inversa en el endstop 0=pulsado, 1=no pulsado
int buttonState = 0; 
int buttonStateOld = 0; 
int posicionfinal = false;
int posicionInicial = true;
int vel;
int cuentapasos;
int posicion ;

int valor = 300;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(potEndStop, OUTPUT);
  digitalWrite(potEndStop, HIGH);
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
  pinMode(endstop, INPUT);
  vel = speedIda;

} 
 
long oldPosition  = myEnc.read();
 
 void loop(){
   //DESENROLLA HASTA EL FINAL
   buttonState = digitalRead(endstop);
    while (buttonState == HIGH || posicionfinal == false){
        myservo.write(speedIda);
        Serial.println("avanza" );
        buttonStateOld = buttonState;
        buttonState = digitalRead(endstop);
        if (buttonState == LOW && buttonStateOld == HIGH){ 
             posicionfinal = true;
             posicionInicial = false;
             cuentapasos=0;
             myservo.write(speed0);
             Serial.println("llegada" );
             delay (1000);
            }
      } 
  
    //ENROLLA CONTANDO PASOS
      while (buttonState ==HIGH || posicionInicial == false){
      myservo.write(speedVuelta);
        Serial.println("enrolla" );
        buttonStateOld = buttonState;
        buttonState = digitalRead(endstop);
        long newPosition = myEnc.read();
        funcionpaso();
        if (buttonState == LOW && buttonStateOld == HIGH){
            posicionInicial = true;
            posicionfinal = false;
            myservo.write(speed0);
            Serial.println("enrollado" );
            Serial.println(cuentapasos);
            delay (5000);
            posicion = 0;
      }   
      }
      
  while (posicion < valor-10 || posicion > valor+10){
     Serial.println("colocar" );
     if  ( posicion < valor-10){
            myservo.write(speedIda);
            funcionpaso();
      }
      else {myservo.write(speedVuelta);}
 };

Serial.print("colocado: " );
Serial.println(posicion);
}

void funcionpaso() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    cuentapasos++;}
    Serial.println(cuentapasos);  
}


 

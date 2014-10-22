#include <Encoder.h>
Encoder myEnc(3, 4);

#include <Servo.h> 
Servo myservo;  // Cremos el objeto de servo
const int speed0 = 71; // valor en el que el servo se mantiene quieto (es posible que haga falta variarlo un poco)
const int speedIda = speed0+90;
const int speedVuelta = speed0-90;
int i; // iterador
int potEndStop = 2;// LED no lo utilizo
int endstop = 7 ; // logica inversa en el endstop 0=pulsado, 1=no pulsado
int buttonState = 0; 
int buttonStateOld = 0; 
boolean posicionfinal = false;
boolean posicionInicial = true;
int vel;
int cuentapasos;
int posicion ;
const int tol = 10; // valor de tolerancia en pasos  para el rebote del endstop
int valor = 300;
int centro;
boolean primeraVez = true;


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
 
/*leer valor

si valor < posicion ;
speedIda

si valor> posicion; 
speedVuelta;

si valor == posicion
speed0*/

 void loop(){
   //DESENROLLA HASTA EL FINAL
  if (primeraVez == true){
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
             Serial.println("llegada al final" );
             delay (1000);
            }
      } 
  
    //ENROLLA CONTANDO PASOS
      cuentapasos=0;
      while (buttonState ==HIGH || posicionInicial == false){
      myservo.write(speedVuelta);
         buttonStateOld = buttonState;
        buttonState = digitalRead(endstop);
        long newPosition = myEnc.read();
        cuentapasos = sumapaso(cuentapasos);
        if (buttonState == LOW && buttonStateOld == HIGH && cuentapasos>tol){
            posicionInicial = true;
            posicionfinal = false;
            myservo.write(speed0);
            Serial.print("enrollado! : " );
            Serial.println(cuentapasos); //cuantos pasos hay de cuerda
            delay (1000);
            posicion = 0;
      }   
      }
     
     // calcula centro
     centro = (cuentapasos/2);
     Serial.print("centro: " );
            Serial.println( centro );
            valor = centro;
            delay (3000);
      
  while (posicion < centro || posicion > centro){
     //Serial.println("colocar" );
     if  ( posicion < centro){
            myservo.write(speedIda);
            posicion = sumapaso(posicion);
      }
      else {myservo.write(speedVuelta);
            posicion = restapaso(posicion);}
 }//Serial.println("colocando" );
    //        Serial.println(posicion);
 

Serial.print("colocado: " );
Serial.println(posicion);
myservo.write(speed0);
valor = posicion;
delay(3000);

  }

primeraVez = false;  


//Serial.print("pide valor: " );

if(Serial.available()>0) //Comprobamos si en el buffer hay datos
  {
    myservo.write(speed0);
    valor= Serial.parseInt();  //Lee cada carácter uno por uno y se almacena en una variable
 
   // Serial.write(dato);  //Imprimimos en la consola el carácter recibido
  }


//valor = 200;

 //PARA POSICIONAR DURANTE EL LOOP
if  ( valor > posicion){
            myservo.write(speedIda);
            posicion = sumapaso(posicion);
            Serial.println(posicion);
}
else if ( valor < posicion){
            myservo.write(speedVuelta);
            posicion = restapaso(posicion);
            Serial.println(posicion);
}
else {
            myservo.write(speed0);
            Serial.print("colocado: " );
            Serial.println(posicion);
}           




//Serial.write(valor);
//PARA POSICION DIRECTA
/*while (posicion < valor || posicion > valor ){
     //Serial.println("colocar" );
     if  (  posicion < valor){
            myservo.write(speedIda);
            posicion = sumapaso(posicion);
      }
      else {myservo.write(speedVuelta);
            posicion = restapaso(posicion);}
 }

*/
// Serial.print("colocando en posicion " );
// Serial.println(posicion);
// myservo.write(speed0);
}




//FUNCIONES

int sumapaso(int paso) {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    paso++;}
    //Serial.println(paso); 
   return paso ;
}

int restapaso(int paso) {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    paso--;}
    //Serial.println(paso); 
   return paso ;
}
 

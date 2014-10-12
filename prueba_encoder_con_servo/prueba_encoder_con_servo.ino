volatile int unsigned pulsos=0;
#include <Encoder.h>

//   Pin 13 is an INPUT indicating if variable "pulsos" has to increase (HIGH) or decrease (LOW)

Encoder myEnc(2, 6);
//   avoid using pins with LEDs attached

void setup() {
  pinMode (13,INPUT);
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = myEnc.read();

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    if (digitalRead (13)){    //when pin 13 is HIGH INCREASE
       pulsos--;}
    else{              //when pin 13 is LOW DECREASE
       pulsos++;}
    Serial.println(pulsos);    
       
}
}

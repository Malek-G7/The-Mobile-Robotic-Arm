#include <Arduino.h>
#include <analogWrite.h>
#include "car.h"

car::car(int e1,int m1,int e2,int m2)
{
  E1 =e1;
  M1=m1;
  E2=e2;
  M2=m2;
}

void car::Forward(int value){
    digitalWrite(M1,HIGH); // M High GOES FORWARD
    digitalWrite(M2,HIGH); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control
}
void car::Backward(int value){
      digitalWrite(M1,LOW); // M low = GOES BACKWARDS
      digitalWrite(M2,LOW); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control
}
void car::forwardLeft(int value){
      digitalWrite(M1,HIGH); 
      digitalWrite(M2,HIGH); 
    analogWrite(E1, value); //PWM Speed Control right m
  analogWrite(E2, (value/2)); //PWM Speed Control
}
void car::forwardRight(int value){
    digitalWrite(M1,HIGH); 
    digitalWrite(M2,HIGH); 
  analogWrite(E1, (value/2)); //PWM Speed Control right m
  analogWrite(E2, value); //PWM Speed Control
}
void car::backwardLeft(int value){
     digitalWrite(M1,LOW); 
     digitalWrite(M2,LOW); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, (value/2)); //PWM Speed Control
}
void car::backwardRight(int value){
     digitalWrite(M1,LOW); 
    digitalWrite(M2,LOW); 
    analogWrite(E1, (value/2)); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control
}


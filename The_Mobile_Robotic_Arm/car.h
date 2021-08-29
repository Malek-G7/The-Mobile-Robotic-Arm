#include "Arduino.h"
#ifndef CAR_H
#define CAR_H
class car{
  private:
   int E1; // Right motor speed control
   int M1; // right motor direction control
   int E2; //left motor speed control
   int M2;// left motor direction control
   public:
   car(int e1,int m1, int e2,int m2); 
   void Forward(int value);
   void Backward(int value);
   void forwardLeft(int value);
   void forwardRight(int value);
   void backwardLeft(int value);
   void backwardRight(int value);

};


#endif


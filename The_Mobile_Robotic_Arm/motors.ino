#include <ESP32Servo.h>
void ArmUp()
{
   for (pos = 1500; pos <= 2500; pos += 10)// arm up
   { 
    myservoV.writeMicroseconds(pos);
    delay(15);
    angle = myservoV.read();
    Serial.println("angle is");
    Serial.println(angle);                                  
    }
}

void ArmDown()
{
     for (pos = 2500; pos >= 1500; pos -= 10) { // arm down
     myservoV.writeMicroseconds(pos);
     delay(15);
     angle = myservoV.read();
     Serial.println("angle is");
     Serial.println(angle);                                    
     }
}

void ArmRight()
{
    for (pos = 2000; pos >= 500; pos -= 10) { // arm right 
    myservoH.writeMicroseconds(pos);
    delay(15);
    angle = myservoH.read();
    Serial.println("angle is");
    Serial.println(angle);   
    }
}

void ArmLeft()
{
    for (pos = 500; pos <= 2000; pos += 10)// arm left 
    { 
    myservoH.writeMicroseconds(pos);
    delay(15);
    angle = myservoH.read();
    Serial.println("angle is");
    Serial.println(angle);                                 
    }
}
void closeGrabber ()
{
    for (pos = 40; pos <= 70; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoGrabber.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }

}
void openGrabber ()
{
    for (pos = 70; pos >= 40; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoGrabber.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }
}

void Forward (int value)
{
    digitalWrite(M1,HIGH); // M High GOES FORWARD
    digitalWrite(M2,HIGH); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control
}
void  Backward  (int value)
{
    digitalWrite(M1,LOW); // M low = GOES BACKWARDS
    digitalWrite(M2,LOW); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control

}
void forwardLeft (int value)
{
    digitalWrite(M1,HIGH); 
    digitalWrite(M2,HIGH); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, (value/2)); //PWM Speed Control

}
void  forwardRight (int value)
{
    digitalWrite(M1,HIGH); 
    digitalWrite(M2,HIGH); 
    analogWrite(E1, (value/2)); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control

}
void  backwardLeft (int value)
{
    digitalWrite(M1,LOW); 
    digitalWrite(M2,LOW); 
    analogWrite(E1, value); //PWM Speed Control right m
    analogWrite(E2, (value/2)); //PWM Speed Control

}
void backwardRight (int value)
{
    digitalWrite(M1,LOW); 
    digitalWrite(M2,LOW); 
    analogWrite(E1, (value/2)); //PWM Speed Control right m
    analogWrite(E2, value); //PWM Speed Control

}

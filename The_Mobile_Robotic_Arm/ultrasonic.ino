#define speedOfSound  340
String UltrasonicS(){
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(echoPin, HIGH);
    // calculate the distance
    distance_cm = ((speedOfSound*10^2/10^6)* duration_us)/2;
    // print the value to Serial Monitor
    Serial.print("distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    String distance =String(distance_cm);
    return distance;
      //distance_cm = 0.017 * duration_us;
} 

#define adcRange 4096
void ldr(){
  

  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= (adcRange/4)) {
  digitalWrite(ledPin, HIGH);
  Serial.print("Its DARK, Turn on the LED : ");
  Serial.println(ldrStatus);
}

else{
  digitalWrite(ledPin, LOW);
  Serial.print("Its BRIGHT, Turn off the LED : ");
  Serial.println(ldrStatus);
}
}

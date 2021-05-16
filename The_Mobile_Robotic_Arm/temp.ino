String temp(){
  
  analogReading = analogRead(TEMP_PIN);
  tempc = FunctionCel(analogReading);
  Serial.print("temp in celsius: ");
  Serial.println(tempc);
  String tempC = String(tempc);
  return tempC;
}

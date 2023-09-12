unsigned long tempoAnteriorTemp = 0; 
const long periodoVerificaTemp = 3000;


void temp(){

  unsigned long tempoAtualTemp = millis();


  if (tempoAtualTemp - tempoAnteriorTemp >= periodoVerificaTemp) {
    tempoAnteriorTemp = tempoAtualTemp;
  
  
  float temperature = bmp.readTemperature();
  Firebase.setFloat(minhaBase, "/leituras/temperatura", temperature);
 
  float pressure = bmp.readPressure() / 100.0F; // Convertendo para hPa

  
  
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Pressão: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Firebase.get(minhaBase, "configuracoes/confgTemp");
  int confgTemp = minhaBase.intData();



 if (temperature > confgTemp) {
    digitalWrite(releVent, LOW);
  } 
  else{
    digitalWrite(releVent, HIGH);
    };
  }

}

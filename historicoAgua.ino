

void hisAgua(void *parameter) {
  for (;;) {

bool forceUpdate();


       while (true){
      
      if (ntp.update()) {
          if (ntp.getDay() == 2){
            if (WiFi.status() == WL_CONNECTED){
                 createNewNodeAgua();
                 delay(86400000); //86400000
          }else {
        Serial.println("Wi-Fi está conectado. Aguardando...");
        delay(60000); //60000 
         }
       }
     }else {
      Serial.println("Erro ao atualizar NTP. Aguardando...");
      delay(60000); //60000 
     }
   }       

       delay(86400000); //86400000

  }
}



void createNewNodeAgua() {
  
  Firebase.pushInt(minhaBase, "/historicosAgua", aguaSemanal);
  Serial.print(aguaSemanal);
  pulseSemanal = 0;
  aguaSemanal = 0;
  if (minhaBase.dataAvailable()) {
    Serial.println("Novo nó de água criado na sexta-feira!");
  } else {
    Serial.println("Falha ao criar o nó de água de sexta-feira!");
  }
}

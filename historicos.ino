


//// 86400000  24h


void hisEnergia(void *parameter) {
  

  for(;;){



     while (true){
      if (ntp.update()) {
          if (ntp.getDay() == 5){
            if (WiFi.status() == WL_CONNECTED){
                 createNewNodeEnergia();
                 delay(86400000);
          }else {
        Serial.println("Wi-Fi está conectado. Aguardando...");
        delay(60000); 
         }
       }
     }else {
      Serial.println("Erro ao atualizar NTP. Aguardando...");
      delay(60000);
     }
   }
         

   
   
  }
}


void createNewNodeEnergia() {
  Firebase.pushInt(minhaBase, "/historicosEnergia", energiaSemanal);
  energiaSemanal = 0;
  if (minhaBase.dataAvailable()) {
    Serial.println("Novo nó de energia criado na sexta-feira!");
  } else {
    Serial.println("Falha ao criar o nó de energia de sexta-feira!");
  }
}

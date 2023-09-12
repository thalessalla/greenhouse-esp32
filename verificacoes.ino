unsigned long tempoAnteriorVerifica = 0; 
const long periodoVerifica = 5000;

void verifica(){

  unsigned long tempoAtualVerifica = millis();

  if (tempoAtualVerifica - tempoAnteriorVerifica >= periodoVerifica) {
    tempoAnteriorVerifica = tempoAtualVerifica;

  if (WiFi.status() != WL_CONNECTED){
     Serial.println("Sem conexão Wifi");
   }else {
    Serial.println("Com conexão Wifi");
    }
  if (Firebase.ready()) {
    Serial.println("Conexão com o Firebase estabelecida!");
} else {
    Serial.println("Erro na conexão com o Firebase.");
}  

    Firebase.setInt(minhaBase, "/conexao/esp32", 0);
    //delay(5000);
    Firebase.setInt(minhaBase, "/conexao/esp32", 1);
  }
  }

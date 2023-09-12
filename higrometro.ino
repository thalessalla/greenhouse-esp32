
unsigned long tempoAnteriorHigro = 0; // 
const long periodoVerificaHigro = 2000; //Tempo de delay




void higrometro(){


   unsigned long tempoAtualHigro = millis();

  if (tempoAtualHigro - tempoAnteriorHigro >= periodoVerificaHigro) {
    tempoAnteriorHigro = tempoAtualHigro;

  
   
     
   int leitura = analogRead(sensorHumidade);
  int umidadeMapeada = map(leitura, 1094, 4095, 100, 0); // Mapear a leitura para a faixa de 0 a 100
  Firebase.setFloat(minhaBase, "leituras/solo", umidadeMapeada);

  Firebase.get(minhaBase, "configuracoes/confgAgua");   //Alterei o direcionamento no FireBase
  int valorAgua = minhaBase.intData();
  
  Serial.println(" ");
  Serial.print("Leitura sonda: ");
  Serial.println(analogRead(sensorHumidade)); 
  Serial.println(" ");
  Serial.print("Umidade mapeada: ");
  Serial.print(umidadeMapeada);
  Serial.println("%");
  
  Firebase.get(minhaBase, "configuracoes/confgAgua");
int confgAgua = minhaBase.intData();

   if (umidadeMapeada < confgAgua) {
    digitalWrite(releAgua, LOW);
  } 
  else{
    digitalWrite(releAgua, HIGH);
    };
  }
  
  }

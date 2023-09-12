
int aguaSemanal = 0;

float volume;
float litros;
float pulso = 0;



unsigned long tempoAnteriorAguaLeitura = 0; 
const long esperaAguaLeitura = 5000; //Tempo de delay



void agua(){


unsigned long tempoAtualAguaLeitura = millis();

  if (tempoAtualAguaLeitura - tempoAnteriorAguaLeitura >= esperaAguaLeitura) {
    tempoAnteriorAguaLeitura = tempoAtualAguaLeitura;

 
  
volume = 2.663 * pulse;
  Firebase.setFloat(minhaBase, "/agua/pulso", pulse);  
  Serial.print(volume);
  Serial.println(" mL");
  Serial.print(litros);
  Serial.println(" L");
  Serial.print(pulse);
  litros = volume / 1000;
  Firebase.setFloat(minhaBase, "/agua/consumo_total", litros);
  
  File file = SPIFFS.open(filePath, "w");
  if (file) {
    file.println(pulse);
    file.close();
  } else {
    Serial.println("Erro ao abrir o arquivo no SPIFFS para escrita.");
  }


 ///Salvar consumo semanal
 File fileAguaSemanal = SPIFFS.open(filePathAguaSemanal, "w");
  if (fileAguaSemanal) {
    fileAguaSemanal.println(pulseSemanal);
    fileAguaSemanal.close();
  } else {
    Serial.println("Erro ao abrir o arquivo no SPIFFS para escrita.");
  }

 aguaSemanal = 2.663 * pulseSemanal ;
 Firebase.setFloat(minhaBase, "/agua/consumo_semanal", aguaSemanal);

  }
}


void increase() {
  pulse++;
  pulseSemanal++;
}

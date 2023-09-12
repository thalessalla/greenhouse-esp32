

float energiaSemanal = 0;

unsigned long tempoAnteriorEnergia = 0; 
const long esperaEnergia = 5000; //Tempo de delay


void energiaKw(){
  
  Firebase.setFloat(minhaBase, "/energia/consumo_total", kwh);
  Firebase.setFloat(minhaBase, "/energia/corrente", corrente_pico);
  Firebase.setFloat(minhaBase, "/energia/watts", potencia);

unsigned long tempoAtualEnergia = millis();

  if (tempoAtualEnergia - tempoAnteriorEnergia >= esperaEnergia) {
    tempoAnteriorEnergia = tempoAtualEnergia;

    //kwh = Firebase.getFloat(minhaBase, "/energia/consumo_total");
  
//Zerar valores
  menor_valor = 4095;
 
  for(int i = 0; i < 1600 ; i++){
  valor_lido = analogRead(pino_sensor);
  if(valor_lido < menor_valor){
  menor_valor = valor_lido;    
  }
  delayMicroseconds(10);  
  }

  
  Serial.print("Menor Valor:");
  Serial.println(menor_valor);

  //Transformar o maior valor em corrente de pico
  corrente_pico = ZERO_SENSOR - menor_valor; // Como o ZERO do sensor é 2,5 V, é preciso remover este OFFSET. Na leitura Analógica do ESp32 com este sensor, vale 2800 (igual a 2,5 V).
  corrente_pico = corrente_pico*0.805; // A resolução mínima de leitura para o ESp32 é de 0.8 mV por divisão. Isso transforma a leitura analógica em valor de tensão em [mV}
  corrente_pico = corrente_pico/185;   // Converter o valor de tensão para corrente de acordo com o modelo do sensor. No meu caso, esta sensibilidade vale 185mV/A
                                      // O modelo dele é ACS712-05B. Logo, precisamos dividir o valor encontrado por 185 para realizar esta conversão                                       



  potencia = abs(corrente_eficaz * tensaoAC);
  energia+=(potencia*1.2/1000);
  kwh = (energia / 3600);


  Serial.print("Energia:   ");
  Serial.print(energia,3);
  Serial.println(" kJ");

  Serial.print("Consumo:   ");
  Serial.print(kwh);
  Serial.println(" kwh");

  Serial.print("Potencia:  ");
  Serial.print(potencia,2);
  Serial.println(" W"); 
 
  
  Serial.print("Corrente de Pico:");
  Serial.print(corrente_pico);
  Serial.print(" A");
  Serial.print(" --- ");
  Serial.print(corrente_pico*1000);
  Serial.println(" mA");
  
 
  //Converter para corrente eficaz  
  corrente_eficaz = abs(corrente_pico / 1.4);
  Serial.print("Corrente Eficaz:");
  Serial.print(corrente_eficaz);
  Serial.print(" A");
  
  Serial.print(" --- ");
  Serial.print(corrente_eficaz*1000);
  Serial.println(" mA");
//  saveCorrentePicoToSPIFFS();


// Energia semanal

   

  corrente_pico_semanal = ZERO_SENSOR - menor_valor; 
  corrente_pico_semanal = corrente_pico*0.805; 
  corrente_pico_semanal = corrente_pico/185;

  potencia_semanal = abs(corrente_eficaz_semanal * tensaoAC);
  energia_semanal+=(potencia_semanal*1.2/1000);
  energiaSemanal = (energia_semanal / 3600);

  Serial.print(energiaSemanal);



  //energiaSemanal = kwh;
  Firebase.setFloat(minhaBase, "/energia/consumo_semanal", energiaSemanal);




 // Salva o valor de corrente_pico no SPIFFS
  File fileEnergia = SPIFFS.open(filePathEnergia, "w");
  if (fileEnergia) {
    fileEnergia.print(corrente_pico);
    fileEnergia.close();
  } else {
    Serial.println("Erro ao abrir o arquivo no SPIFFS para escrita.");
  }


// Energia Semanal

 File fileEnergiaSemanal = SPIFFS.open(filePathEnergiaSemanal, "w");
  if (fileEnergiaSemanal) {
    fileEnergiaSemanal.print(corrente_pico_semanal);
    fileEnergiaSemanal.close();
  } else {
    Serial.println("Erro ao abrir o arquivo no SPIFFS para escrita.");
  }
  
  }
 

  
}

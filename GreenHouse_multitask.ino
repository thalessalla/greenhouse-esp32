
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Adafruit_BMP085.h>

#include "FS.h"
#include "SPIFFS.h"


#define BMP_SDA 21
#define BMP_SCL 22
#define releAgua 2
#define releVent 19
#define releSupli 18

#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP);



TaskHandle_t Task1;




//Agua
int sensorPin = 5;
const char *filePath = "/pulseValue.txt"; // Caminho do arquivo no SPIFFS
const char *filePathAguaSemanal = "/pulseValueSemanal.txt";
volatile long pulse;
volatile long pulseSemanal;



// Energia semanal
float corrente_pico_semanal;
float potencia_semanal; 
float energia_semanal = 0;
float corrente_eficaz_semanal;




//Energia
int pino_sensor = 36;
int menor_valor;
int valor_lido;
int menor_valor_acumulado = 0;
int ZERO_SENSOR = 0;
float corrente_pico;

float corrente_eficaz;
double maior_valor=0;
double corrente_valor=0;



float tensaoAC = 127;
float potencia; 
float energia = 0;
float kwh;

const char *filePathEnergia = "/correntePico.txt";
const char *filePathEnergiaSemanal = "/correntePicoSemanal.txt";
////


const int sensorHumidade = 34;

Adafruit_BMP085 bmp;

const char* usuario = "esp32";
const char* senha = "rocambole";
bool statusConexao = false;

const char* host = "https://greenhousecontrol-f5e05-default-rtdb.firebaseio.com/";
const char* token = "ZqKxfNRyBmYz3kT0yqgmsEYIKnapG7oY3vpSyNIG";

FirebaseData minhaBase;



// Data
  

void setup() {
   
  Serial.begin(9600);

  
  
   pinMode(15, OUTPUT); 
   digitalWrite(15, HIGH); 
   pinMode(4, OUTPUT);
   pinMode(18, OUTPUT);
   pinMode(releAgua, OUTPUT);
   pinMode(releVent, OUTPUT);
   pinMode(releSupli, OUTPUT);

   WiFi.begin(usuario, senha);
  
   statusConexao = true;
   Firebase.begin(host, token);


   Wire.begin(BMP_SDA, BMP_SCL);

   if (!bmp.begin()) {
      Serial.println("Falha ao iniciar o BMP180. Verifique as conexões ou a biblioteca.");
      while (1);
    }

   

   //Agua
    pinMode(sensorPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
   
    if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar o sistema de arquivos SPIFFS.");
  }
  
  // Carrega o valor armazenado no SPIFFS, se existir.
  if (SPIFFS.exists(filePath)) {
    File file = SPIFFS.open(filePath, "r");
    if (file) {
      pulse = file.parseInt();
      file.close();
    } else {
      Serial.println("Erro ao abrir o arquivo no SPIFFS para leitura.");
    }
  }

  // Carrega o valor armazenado no SPIFFS do valor SEMANAL.
  if (SPIFFS.exists(filePathAguaSemanal)) {
    File fileAguaSemanal = SPIFFS.open(filePathAguaSemanal, "r");
    if (fileAguaSemanal) {
      pulseSemanal = fileAguaSemanal.parseInt();
      fileAguaSemanal.close();
    } else {
      Serial.println("Erro ao abrir o arquivo no SPIFFS para leitura.");
    }
  }
  
  


//Energia

  pinMode(pino_sensor,INPUT);
  delay(3000);
  //Fazer o AUTO-ZERO do sensor
  Serial.println("Fazendo o Auto ZERO do Sensor...");

  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar o sistema de arquivos SPIFFS.");
  }

  if (SPIFFS.exists(filePathEnergia)) {
    File fileEnergia = SPIFFS.open(filePathEnergia, "r");
    if (fileEnergia) {
      corrente_pico = fileEnergia.parseFloat();
      fileEnergia.close();
    } else {
      Serial.println("Erro ao abrir o arquivo no SPIFFS para leitura.");
    }
  }

  // Semanal
   if (SPIFFS.exists(filePathEnergiaSemanal)) {
    File fileEnergiaSemanal = SPIFFS.open(filePathEnergiaSemanal, "r");
    if (fileEnergiaSemanal) {
      corrente_pico = fileEnergiaSemanal.parseFloat();
      fileEnergiaSemanal.close();
    } else {
      Serial.println("Erro ao abrir o arquivo no SPIFFS para leitura.");
    }
  }


menor_valor = 4095;
 
  for(int i = 0; i < 10000 ; i++){
  valor_lido = analogRead(pino_sensor);
  if(valor_lido < menor_valor){
  menor_valor = valor_lido;    
  }
  delayMicroseconds(1);  
  }
  ZERO_SENSOR = menor_valor;
  Serial.print("Zero do Sensor:");
  Serial.println(ZERO_SENSOR);
  delay(3000);




 
  xTaskCreate(hisAgua, "Historico agua", 10000, NULL, 1, NULL);
  xTaskCreate(hisEnergia, "Historico-energia", 10000, NULL, 1, NULL);
  xTaskCreate(supli, "suplementacao", 10000, NULL, 1, NULL);
  //xTaskCreate(zerar, "zerar valores", 10000, NULL, 1, NULL);

  
  // Data

    ntp.begin();

//-10800 = GMT Brasil
  ntp.setTimeOffset(-10800);


}



 void loop() {

 higrometro(); 
 temp();
 verifica();
 energiaKw();
 agua();
 zerar();


  
}


void zerar() {
 Firebase.get(minhaBase, "historicos/zerar");

 int zerar = minhaBase.intData();
 
  //Serial.println(zerar);
  if(zerar == 1){
      pulseSemanal = 0;
      pulse = 0;
      corrente_pico = 0;
      Serial.println("Testeeeeeeeeeeee");
      Serial.println(zerar);
       }
        delay(1000);
  }

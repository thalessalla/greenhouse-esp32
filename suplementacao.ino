


void supli(void *parameter) {

  for(;;){



float domingo = Firebase.get(minhaBase, "diasSuplementacao/dom");
 float segunda = Firebase.get(minhaBase, "diasSuplementacao/seg");
 float terca = Firebase.get(minhaBase, "diasSuplementacao/ter");
 float quarta = Firebase.get(minhaBase, "diasSuplementacao/qua");
 float quinta = Firebase.get(minhaBase, "diasSuplementacao/qui");
 float sexta = Firebase.get(minhaBase, "diasSuplementacao/sex");
 float sabado = Firebase.get(minhaBase, "diasSuplementacao/sab");

 int tempoSupli = Firebase.get(minhaBase, "diasSuplementacao/tempo");

 if (ntp.update()) {
          if (ntp.getDay() == domingo){
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == segunda){
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == terca){
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == quarta){
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == quinta) {
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == sexta) {
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } else if(ntp.getDay() == sabado) {
            digitalWrite(releSupli, LOW);
            delay(tempoSupli);
            digitalWrite(releSupli, HIGH);
          } 

    }
    delay(86400000);

  }
}

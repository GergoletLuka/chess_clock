#include<LiquidCrystal.h>
#include <Arduino.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
/*
  za dodat:

  -konec igre (se pokazejo rdece led)
  (-rocno nastavljanje tudi 2. casa)
  -dodatek za cas pri rocnem nastavljanju + na izbranih casih

*/
enum stanje {izbira_igre, rocno_nastavljanje_casa, potek_igre, konec_igre};
int korak = 0;
int OK = 4;
int plus = 5;
int buttonState1, buttonState2;
int lastbuttonState1 = 0;
int lastbuttonState2 = 0;
long int passedTime1 = 0;
long int passedTime2 = 0;
long int currentTime = 0;
long int previousTime1 = 0;
long int previousTime2 = 0;
long int cas1;
long int cas2;
long int prejsnji_cas1;
long int prejsnji_cas2;
long int lastTime = 0;
long int dodatek = 3000;
int minutaza = 0;
int sekunde = 0;
int ure = 0;
int stetje = 0;
int igralni_cas;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode (2, OUTPUT);//zelena led
  pinMode (13, OUTPUT);//zelena led
  pinMode (A4, OUTPUT);//rdeca led
  pinMode (A5, OUTPUT);//rdeca led
  pinMode (3, INPUT_PULLUP);//button
  pinMode (12, INPUT_PULLUP);//button
  pinMode(OK, INPUT);  //gumb ok
  pinMode(plus, INPUT);//gumb_zvisaj
}
void izpis() {
  lcd.setCursor(0, 0);
  lcd.print("Player1  Player2");
  if ((cas1 >= 0) && (cas2 >= 0)) {
    //cas1
    lcd.setCursor(0, 1);
    if ( cas1 >= 3600000) {
      //Serial.print("igralec 1: ");
      lcd.print(" ");
      lcd.print(cas1 / 3600000);
      //Serial.print(cas1/3600000UL);
      lcd.print("h ");
      //Serial.print("h ");
      if (((cas1 % 3600000) / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print((cas1 % 3600000) / 60000);
      //Serial.print((cas1%3600000UL)/1000UL);
      lcd.print("'");
      //Serial.print("'    ");
    }

    if ( cas1 < 3600000) {
      //Serial.print("igralec 1: ");
      if ((cas1 / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print(cas1 / 60000);
      //Serial.print(cas1/60000UL);
      lcd.print("' ");
      //Serial.print("' ");
      if (((cas1 % 60000) / 1000) < 10) {
        lcd.print(" ");
      }
      lcd.print((cas1 % 60000) / 1000);
      //Serial.print((cas1%60000UL)/1000UL);
      lcd.print("\"");
      //Serial.print("\"  ");
    }
    //cas2
    lcd.setCursor(9, 1);
    if ( cas2 >= 3600000) {
      //Serial.print("igralec 2: ");
      lcd.print(" ");
      lcd.print(cas2 / 3600000);
      //Serial.print(cas2/3600000UL);
      lcd.print("h ");
      //Serial.print("h ");
      if (((cas2 % 3600000) / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print((cas2 % 3600000) / 60000);
      //Serial.print((cas2%3600000UL)/1000UL);
      lcd.print("'");
      //Serial.print("'    ");
    }

    if ( cas2 < 3600000) {
      //Serial.print("igralec 2: ");
      if ((cas2 / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print(cas2 / 60000);
      //Serial.print(cas2/60000UL);
      lcd.print("' ");
      //Serial.print("' ");
      if (((cas2 % 60000) / 1000) < 10) {
        lcd.print(" ");
      }
      lcd.print((cas2 % 60000) / 1000);
      //Serial.print((cas2%60000UL)/1000UL);
      lcd.print("\"");
      //Serial.print("\"  ");
    }


    //Serial.print("igralec 1: ");
    //Serial.print(cas1/1000UL);
    //Serial.print("     igralec 2: ");
    //Serial.print(cas2/1000UL);
    //Serial.print("\n");
  }
}

void loop() {

  switch (korak) {
    case izbira_igre:

      if (digitalRead(plus) == HIGH) {
        igralni_cas = igralni_cas + 1;
        if (igralni_cas > 7) {
          igralni_cas = 0;
          lcd.clear();
          lcd.setCursor(2, 0);
        }
      }

      lcd.setCursor(2, 0);
      switch (igralni_cas) {
        case 0:

          lcd.print("manual");
          Serial.println("rocno nastavljanje");
          break;
        case 1:
          cas1 = 60000;
          lcd.print("1' + 0\"");
          Serial.println("1' + 0\"");
          break;

        case 2:
          cas1 = 120000;
          lcd.print("2' + 0\"");
          Serial.println("2' + 0\"");
          break;

        case 3:
          cas1 = 300000;
          lcd.print("5' + 0\"");
          Serial.println("5' + 0\"");
          break;

        case 4:
          cas1 = 600000;
          lcd.print("10' + 0\"");
          Serial.println("10' + 0\"");
          break;

        case 5:
          cas1 = 900000;
          lcd.print("15' + 0\"");
          Serial.println("15' + 0\"");
          break;

        case 6:
          cas1 = 1800000;
          lcd.print("30' + 0\"");
          Serial.println("30' + 0\"");
          break;

        case 7:
          cas1 = 3600000;
          lcd.print("60' + 0\"");
          Serial.println("60' + 0\"");
          break;
      }
      delay(200);
      cas2 = cas1;

      if (digitalRead (OK) == HIGH) {
        if (igralni_cas == 0) {
          korak = rocno_nastavljanje_casa;
        }
        else {
          korak = potek_igre;
        }
      }
      break;
    case rocno_nastavljanje_casa:

      //_____________konec 1. zanke____________________________________
      while (digitalRead (OK) == HIGH) {}

      lcd.setCursor(0, 0);
      lcd.print("        ");
      //stevilo ur
      stetje = 0;
      while (digitalRead (OK) == LOW) {
        Serial.println();
        lcd.setCursor(0, 0);
        lcd.print(stetje);
        Serial.print(stetje);
        lcd.print(" h");
        Serial.print(" h");
        if (digitalRead (plus) == HIGH) {

          stetje += 1;
          if (stetje == 10) {
            lcd.clear();
            stetje = 0;

          }
        }
        delay(200);
      }
      ure =  stetje;
      while (digitalRead (OK) == HIGH) {
      }

      //stevilo minut
      stetje = 0;
      while (digitalRead (OK) == LOW) {
        if (stetje < 10) {
          lcd.setCursor(0, 0);
          lcd.print(" ");
          lcd.print(stetje);
        }

        else {
          lcd.setCursor(0, 0);
          lcd.print(stetje);
        }

        Serial.println();
        Serial.print(stetje);
        lcd.setCursor(2, 0);
        lcd.print(" min");
        Serial.print(" min");
        if (digitalRead (plus) == HIGH) {

          stetje += 1;
          if (stetje == 60) {

            stetje = 0;
          }

        }

        delay(200);
      }
      minutaza = stetje;
      while (digitalRead (OK) == HIGH) {};
      //stevilo sekund
      stetje = 0;
      lcd.setCursor(0, 0);
      lcd.print("             ");
      while (digitalRead (OK) == LOW) {
        if (stetje < 10) {
          lcd.setCursor(0, 0);
          lcd.print(" ");
          lcd.print(stetje);
        }

        else {
          lcd.setCursor(0, 0);
          lcd.print(stetje);
        }
        Serial.println();
        Serial.print(stetje);
        lcd.setCursor(2, 0);
        lcd.print(" s");
        Serial.print(" s");
        if (digitalRead (plus) == HIGH) {

          stetje += 1;
          if (stetje == 60) {
            stetje = 0;
          }
        }

        delay(200);
      }
      sekunde = stetje;
      if (digitalRead (OK) == HIGH) {
        cas1 = (ure * 3600000 + minutaza * 60000 + sekunde * 1000);
        cas2 = cas1;
        korak = potek_igre;
      }
      break;

    //__________________________________________________

    case potek_igre:
      /*//dodatek
        if (digitalRead(3)==LOW){
        buttonState1=1;
        }
        else{buttonState1=0;}



        if (digitalRead(12)==LOW){
        buttonState2=1;
        }
        else{buttonState2=0;}
        if ((buttonState1-lastbuttonState1)==1){
        cas1=cas1+dodatek;}
        if ((buttonState2-lastbuttonState2)==1){
        cas2=cas2+dodatek;}
      */

      //1. primer
      //______________________________________________________________
      if (digitalRead(12) == HIGH) {
        currentTime = millis();
        passedTime2 = currentTime - previousTime2;
        cas2 = cas2 - passedTime2;//............................+dodatek na potezo
        previousTime2 = currentTime;
        digitalWrite(2, HIGH);
      }
      else {
        digitalWrite(2, LOW);
        previousTime2 = millis();
      }

      //2. primer
      //______________________________________________________________
      if (digitalRead(3) == HIGH) {
        currentTime = millis();
        passedTime1 = currentTime - previousTime1;
        cas1 = cas1 - passedTime1;//...........................+dodatek na potezo
        previousTime1 = currentTime;
        digitalWrite(13, HIGH);
      }
      else {
        digitalWrite(13, LOW);
        previousTime1 = millis();
      }
      lastbuttonState1 = buttonState1;
      lastbuttonState2 = buttonState2;

      izpis();

      if (cas1 <= 0 || cas2 <= 0) {
        korak = konec_igre;
      }
      delay(100); //za boljse delovanje programa
      break;
    case konec_igre:
      //Serial.print(sekunde);
      //Serial.print("\t");
      //Serial.println(minutaza);
      digitalWrite(2, LOW);
      digitalWrite(13, LOW);
      if (cas1 < 0)
        digitalWrite(A4, HIGH);
      if (cas2 < 0)
        digitalWrite(A5, HIGH);
      lcd.setCursor(0, 1);
      lcd.println("   KONEC IGRE      ");
      //Serial.println("konec igre");
      delay(1);
      break;
  }
}
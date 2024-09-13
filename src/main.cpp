#include<LiquidCrystal.h>
#include <Arduino.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

enum stanje {select_mode, manual_time_set, game_phase, end_phase};
int step = 0;
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
long int time_p1;
long int time_p2;
long int previous_time_p1;
long int previous_time_p2;
long int lastTime = 0;
long int increment = 3000;
int time_minutes = 0;
int time_seconds = 0;
int time_hours = 0;
int counting = 0;
int playing_time;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode (2, OUTPUT);//green led
  pinMode (13, OUTPUT);//green led
  pinMode (A4, OUTPUT);//red led
  pinMode (A5, OUTPUT);//red led
  pinMode (3, INPUT_PULLUP);//button
  pinMode (12, INPUT_PULLUP);//button
  pinMode(OK, INPUT);  //confirm button
  pinMode(plus, INPUT);//increment button
}
void izpis() {
  lcd.setCursor(0, 0);
  lcd.print("Player1  Player2");
  if ((time_p1 >= 0) && (time_p2 >= 0)) {
    //time_p1
    lcd.setCursor(0, 1);
    if ( time_p1 >= 3600000) {
      lcd.print(" ");
      lcd.print(time_p1 / 3600000);
      lcd.print("h ");
      if (((time_p1 % 3600000) / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print((time_p1 % 3600000) / 60000);
      lcd.print("'");
    }

    if ( time_p1 < 3600000) {
      if ((time_p1 / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print(time_p1 / 60000);
      lcd.print("' ");
      if (((time_p1 % 60000) / 1000) < 10) {
        lcd.print(" ");
      }
      lcd.print((time_p1 % 60000) / 1000);
      lcd.print("\"");
    }
    //time_p2
    lcd.setCursor(9, 1);
    if ( time_p2 >= 3600000) {
      lcd.print(" ");
      lcd.print(time_p2 / 3600000);
      lcd.print("h ");
      if (((time_p2 % 3600000) / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print((time_p2 % 3600000) / 60000);
      lcd.print("'");
    }

    if ( time_p2 < 3600000) {
      if ((time_p2 / 60000) < 10) {
        lcd.print(" ");
      }
      lcd.print(time_p2 / 60000);
      lcd.print("' ");
      if (((time_p2 % 60000) / 1000) < 10) {
        lcd.print(" ");
      }
      lcd.print((time_p2 % 60000) / 1000);
      lcd.print("\"");
    }


    //Serial.print("Player 1: ");
    //Serial.print(time_p1/1000UL);
    //Serial.print("     player 2: ");
    //Serial.print(time_p2/1000UL);
    //Serial.print("\n");
  }
}

void loop() {

  switch (step) {
    case select_mode:

      if (digitalRead(plus) == HIGH) {
        playing_time = playing_time + 1;
        if (playing_time > 7) {
          playing_time = 0;
          lcd.clear();
          lcd.setCursor(2, 0);
        }
      }

      lcd.setCursor(2, 0);
      switch (playing_time) {
        case 0:

          lcd.print("manual");
          Serial.println("manual");
          break;
        case 1:
          time_p1 = 60000;
          lcd.print("1' + 0\"");
          Serial.println("1' + 0\"");
          break;

        case 2:
          time_p1 = 120000;
          lcd.print("2' + 0\"");
          Serial.println("2' + 0\"");
          break;

        case 3:
          time_p1 = 300000;
          lcd.print("5' + 0\"");
          Serial.println("5' + 0\"");
          break;

        case 4:
          time_p1 = 600000;
          lcd.print("10' + 0\"");
          Serial.println("10' + 0\"");
          break;

        case 5:
          time_p1 = 900000;
          lcd.print("15' + 0\"");
          Serial.println("15' + 0\"");
          break;

        case 6:
          time_p1 = 1800000;
          lcd.print("30' + 0\"");
          Serial.println("30' + 0\"");
          break;

        case 7:
          time_p1 = 3600000;
          lcd.print("60' + 0\"");
          Serial.println("60' + 0\"");
          break;
      }
      delay(200);
      time_p2 = time_p1;

      if (digitalRead (OK) == HIGH) {
        if (playing_time == 0) {
          step = manual_time_set;
        }
        else {
          step = game_phase;
        }
      }
      break;
    case manual_time_set:

      //_____________end of 1st loop____________________________________
      while (digitalRead (OK) == HIGH) {}

      lcd.setCursor(0, 0);
      lcd.print("        ");
      //number of hours
      counting = 0;
      while (digitalRead (OK) == LOW) {
        Serial.println();
        lcd.setCursor(0, 0);
        lcd.print(counting);
        Serial.print(counting);
        lcd.print(" h");
        Serial.print(" h");
        if (digitalRead (plus) == HIGH) {

          counting += 1;
          if (counting == 10) {
            lcd.clear();
            counting = 0;

          }
        }
        delay(200);
      }
      time_hours =  counting;
      while (digitalRead (OK) == HIGH) {
      }

      //number of minutes
      counting = 0;
      while (digitalRead (OK) == LOW) {
        if (counting < 10) {
          lcd.setCursor(0, 0);
          lcd.print(" ");
          lcd.print(counting);
        }

        else {
          lcd.setCursor(0, 0);
          lcd.print(counting);
        }

        Serial.println();
        Serial.print(counting);
        lcd.setCursor(2, 0);
        lcd.print(" min");
        Serial.print(" min");
        if (digitalRead (plus) == HIGH) {

          counting += 1;
          if (counting == 60) {

            counting = 0;
          }

        }

        delay(200);
      }
      time_minutes = counting;
      while (digitalRead (OK) == HIGH) {};
      //number of seconds
      counting = 0;
      lcd.setCursor(0, 0);
      lcd.print("             ");
      while (digitalRead (OK) == LOW) {
        if (counting < 10) {
          lcd.setCursor(0, 0);
          lcd.print(" ");
          lcd.print(counting);
        }

        else {
          lcd.setCursor(0, 0);
          lcd.print(counting);
        }
        Serial.println();
        Serial.print(counting);
        lcd.setCursor(2, 0);
        lcd.print(" s");
        Serial.print(" s");
        if (digitalRead (plus) == HIGH) {

          counting += 1;
          if (counting == 60) {
            counting = 0;
          }
        }

        delay(200);
      }
      time_seconds = counting;
      if (digitalRead (OK) == HIGH) {
        time_p1 = (time_hours * 3600000 + time_minutes * 60000 + time_seconds * 1000);
        time_p2 = time_p1;
        step = game_phase;
      }
      break;

    //__________________________________________________

    case game_phase:
      /*//increment
        if (digitalRead(3)==LOW){
        buttonState1=1;
        }
        else{buttonState1=0;}



        if (digitalRead(12)==LOW){
        buttonState2=1;
        }
        else{buttonState2=0;}
        if ((buttonState1-lastbuttonState1)==1){
        time_p1=time_p1+increment;}
        if ((buttonState2-lastbuttonState2)==1){
        time_p2=time_p2+increment;}
      */

      //1. case
      //______________________________________________________________
      if (digitalRead(12) == HIGH) {
        currentTime = millis();
        passedTime2 = currentTime - previousTime2;
        time_p2 = time_p2 - passedTime2;//............................+increment per move
        previousTime2 = currentTime;
        digitalWrite(2, HIGH);
      }
      else {
        digitalWrite(2, LOW);
        previousTime2 = millis();
      }

      //2. case
      //______________________________________________________________
      if (digitalRead(3) == HIGH) {
        currentTime = millis();
        passedTime1 = currentTime - previousTime1;
        time_p1 = time_p1 - passedTime1;//...........................+increment per move
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

      if (time_p1 <= 0 || time_p2 <= 0) {
        step = end_phase;
      }
      delay(100); //za boljse delovanje programa
      break;
    case end_phase:
      //Serial.print(time_seconds);
      //Serial.print("\t");
      //Serial.println(time_minutes);
      digitalWrite(2, LOW);
      digitalWrite(13, LOW);
      if (time_p1 < 0)
        digitalWrite(A4, HIGH);
      if (time_p2 < 0)
        digitalWrite(A5, HIGH);
      lcd.setCursor(0, 1);
      lcd.println("   GAME OVER    ");
      delay(1);
      break;
  }
}
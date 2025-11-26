#include <Arduino.h>
#include "mfs.h"


int main() {
  init();
  initMFS();
  Serial.begin(9600);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  enum states {FIRST_DIGIT, SECOND_DIGIT, THIRD_DIGIT, FOURTH_DIGIT, INPUT_FINISHED};   //enum/enumeration verwendet, um das Programmzustand darzustellen
  //FIRST_DIGIT = 0, SECOND_DIGIT = 1, THIRD_DIGIT = 2, FOURTH_DIGIT = 3, INPUT_FINISHED = 4

  int incremented_value(int value);
  int decremented_value(int value);
  int state = FIRST_DIGIT;    //bedeutet, dass zu Beginn mit FIRST_DIGIT ist
  uint8_t digit1=0, digit2=SEGMENT_CLEAR, digit3=SEGMENT_CLEAR, digit4=SEGMENT_CLEAR;   //SEGMENT_CLEAR definiert in MFS.H Bibliothek
  uint8_t buttonA1, buttonA2, buttonA3;
  uint8_t buttonA1_old = digitalRead(A1);
  uint8_t buttonA2_old = digitalRead(A2);
  uint8_t buttonA3_old = digitalRead(A3);
  unsigned long value=0;    //unsigned int ist auch ok

  while(1) {
    buttonA1 = digitalRead(A1);
    buttonA2 = digitalRead(A2);
    buttonA3 = digitalRead(A3);

    writeCharToSegment(0, digit1, 0);   //0 am Ende = ohne Dezimalzeichen, 1 = mit dezimalzeichen
    writeCharToSegment(1, digit2, 0);
    writeCharToSegment(2, digit3, 0);
    writeCharToSegment(3, digit4, 0);

    switch (state) {
      case FIRST_DIGIT:
        if (buttonA1 < buttonA1_old) {           
          digit1=incremented_value(digit1);
        }
        if (buttonA2 < buttonA2_old) {
          digit1=decremented_value(digit1);
        }
        if (buttonA3 > buttonA3_old) {       
          state = SECOND_DIGIT; 
          digit2=0;
        } 
        break;
      case SECOND_DIGIT:
        if (buttonA1 < buttonA1_old) {           
          digit2=incremented_value(digit2);
        }
        if (buttonA2 < buttonA2_old) {
          digit2=decremented_value(digit2);
        }
        if (buttonA3 > buttonA3_old) {       
          state = THIRD_DIGIT;
          digit3=0;
        }
        break;
      case THIRD_DIGIT:
        if (buttonA1 < buttonA1_old) {            
          digit3=incremented_value(digit3);
        }
        if (buttonA2 < buttonA2_old) {
          digit3=decremented_value(digit3);
        }
        if (buttonA3 > buttonA3_old) {       
          state = FOURTH_DIGIT;
          digit4=0;           
        }
        break;
      case FOURTH_DIGIT:
        if (buttonA1 < buttonA1_old) {            
          digit4=incremented_value(digit4);  
        }
        if (buttonA2 < buttonA2_old) {
          digit4=decremented_value(digit4);
        }
        if (buttonA3 > buttonA3_old) {         
          state = INPUT_FINISHED;  
          value=digit1*1000 + digit2*100 + digit3*10 + digit4;
          Serial.print("Wert: "); Serial.println(value);
        }                      
        break;
      case INPUT_FINISHED:
        break;
    }

    buttonA1_old = buttonA1;
    buttonA2_old = buttonA2;
    buttonA3_old = buttonA3;
  }

  return 0;
}

int incremented_value(int value) {
  value++;         
  if (value>9) {      
    value=0;      
  }
  return value;     // Gib den aktualisierten Wert an den Aufrufer zurück
}

int decremented_value(int value) {
  value--;
  if (value < 0) {
    value = 9;
  }
  return value;
}
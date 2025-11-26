#include <arduino.h>
#include "keypad.h"
#define CODE1 1
#define CODE2 3
#define CODE3 5

int main(){
  init();
  initKEYPAD();
  Serial.begin(9600);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  enum states {IDLE, Counter1, Counter2};
  uint8_t state = IDLE;
  uint8_t act_key;
  uint8_t old_key = readKey();
  uint8_t Input1, Input2, Input3;

  while(1){
    act_key = readKey();

    switch (state){
      case IDLE:
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        if(act_key > old_key){
          Input1 = act_key;
          state = Counter1;
        }
        break;
      case Counter1:
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        if(act_key > old_key){
          Input2 = act_key;
          state = Counter2;
        }
        break;
      case Counter2:
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        if(act_key > old_key){
          Input3 = act_key;
        }

        if((Input1 == CODE1) && (Input2 == CODE2) && (Input3 == CODE3)){
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          delay(2000);
          state = IDLE;
        } else {
          digitalWrite(6, HIGH);
          digitalWrite(5, LOW);
          delay(1000);
          state = IDLE;
        }
        break;
    }

    old_key = act_key;
  }
}

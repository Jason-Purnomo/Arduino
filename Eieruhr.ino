#include <arduino.h>
#include "mfs.h"
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3
#define INPUT_FINISHED 4
#define START_TIMER 5
#define ALARM 6

int main(){
  init();
  initMFS();
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);

  uint8_t buttonA1, buttonA2, buttonA3;
  uint8_t buttonA1_old = digitalRead(A1);
  uint8_t buttonA2_old = digitalRead(A2);
  uint8_t buttonA3_old = digitalRead(A3);
  uint8_t digit1 = 0, digit2 = SEGMENT_CLEAR, digit3 = SEGMENT_CLEAR, digit4 = SEGMENT_CLEAR;
  uint8_t state = FIRST;
  int num = 0;
  bool last_dot = false;
  unsigned long value;
  uint32_t timer = 0;
  uint32_t blinktime = 0;
  uint8_t led = 0;

  while(1){
    buttonA1 = digitalRead(A1);
    buttonA2 = digitalRead(A2);
    buttonA3 = digitalRead(A3);

    writeCharToSegment(0, digit1, 0);
    writeCharToSegment(1, digit2, 0);
    writeCharToSegment(2, digit3, 0);
    writeCharToSegment(3, digit4, last_dot);

    switch (state) {
      case FIRST:
        if(buttonA1 < buttonA1_old){
          num++;
          if(num > 9){
            num = 0;
          }
        }
        if(buttonA2 < buttonA2_old){
          num--;
          if(num < 0){
            num = 9;
          }
        }
        digit1 = num;
        if(buttonA3 > buttonA3_old){
          state = SECOND;
          num = 0;
        }
        break;
      case SECOND:
        if(buttonA1 < buttonA1_old){
          num++;
          if(num > 9){
            num = 0;
          }
        }
        if(buttonA2 < buttonA2_old){
          num--;
          if(num < 0){
            num = 9;
          }
        }
        digit2 = num;
        if(buttonA3 > buttonA3_old){
          state = THIRD;
          num = 0;
        }
        break;
      case THIRD:
        if(buttonA1 < buttonA1_old){
          num++;
          if(num > 9){
            num = 0;
          }
        }
        if(buttonA2 < buttonA2_old){
          num--;
          if(num < 0){
            num = 9;
          }
        }
        digit3 = num;
        if(buttonA3 > buttonA3_old){
          state = FOURTH;
          num = 0;
        }
        break;
      case FOURTH:
        if(buttonA1 < buttonA1_old){
          num++;
          if(num > 9){
            num = 0;
          }
        }
        if(buttonA2 < buttonA2_old){
          num--;
          if(num < 0){
            num = 9;
          }
        }
        digit4 = num;
        if(buttonA3 > buttonA3_old){
          last_dot = true;
          value = digit1*1000 + digit2*100 + digit3*10 + digit4;
          Serial.print("Result= ");
          Serial.println(value);
          state = INPUT_FINISHED;
        }
        break;
      case INPUT_FINISHED:
        if((buttonA1 < buttonA1_old) || (buttonA2 < buttonA2_old) || (buttonA3 < buttonA3_old)){
          last_dot = false;
          state = START_TIMER;
        }
        break;
      case START_TIMER:
        digit1 = value/1000;
        digit2 = (value/100)%10;
        digit3 = (value/10)%10;
        digit4 = value%10;
        if(value == 0){
          state = ALARM;
        } else {
          if(millis() > timer + 1000){
            value--;
            timer = millis();
          }
        }
        break;
      case ALARM:
        if(millis() > blinktime + 500){
          blinktime = millis();
          led = !led;
          digitalWrite(LED1, led);
        }
        break;
    }

    buttonA1_old = buttonA1;
    buttonA2_old = buttonA2;
    buttonA3_old = buttonA3;
  }
}
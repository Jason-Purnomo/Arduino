#include <arduino.h>
#include "mfs.h"
#define Red 0
#define Yellow 1
#define Green 2
#define Yellow2 3
#define red_light 10000
#define yellow_light 5000
#define green_light 10000

int main(void){
  init();
  initMFS();
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  uint8_t Ampel = Red;
  uint32_t start_time = millis();
  uint32_t blinktime = 0;
  uint8_t ledstate = 0;   //aus
  int8_t a = 10;
  int8_t b = 5;
  int8_t c = 10;
  int8_t d = 5;
  uint32_t countdown = 0;

  while(1){
    switch (Ampel){
      case Red:
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);

        if(millis() - countdown > 1000){
          a--;
          countdown = millis();
        }
        if(a < 0){
          a = 10;      
        }
        writeDecToSegment(a);

        if(millis() > start_time + red_light){
          digitalWrite(LED1, HIGH);
          Ampel = Yellow;
          start_time = millis();
          b = 5;
        }
        break;
      case Yellow:
        if(millis() - blinktime > 500){
          ledstate = !ledstate;
          blinktime = millis();

          if (ledstate == 1){
            digitalWrite(LED2, LOW);
          } else {
            digitalWrite(LED2, HIGH);
          }
        }

        if(millis() - countdown > 1000){
          b--;
          countdown = millis();
        }
        if(b < 0){
          b = 5;
        }
        writeDecToSegment(b);
        
        if(millis() > start_time + yellow_light){
          digitalWrite(LED2, HIGH);
          Ampel = Green;
          start_time = millis();
          c = 10;
        }
        break;
      case Green:
        digitalWrite(LED3, LOW);
        
        if(millis() - countdown > 1000){
          c--;
          countdown = millis();
        }
        if(c < 0){
          c = 10;
        }
        writeDecToSegment(c);
        
        if(millis() > start_time + green_light){
          digitalWrite(LED3, HIGH);
          Ampel = Yellow2;
          start_time = millis(); 
          d = 5;       
        }
        break;
      case Yellow2:
        if(millis() - blinktime > 500){
          ledstate = !ledstate;
          blinktime = millis();

          if (ledstate == 1){
            digitalWrite(LED2, LOW);
          } else {
            digitalWrite(LED2, HIGH);
          }
        }

        if(millis() - countdown > 1000){
          d--;
          countdown = millis();
        }
        if(d < 0){
          d = 5;
        }
        writeDecToSegment(d);

        if(millis() > start_time + yellow_light){
          digitalWrite(LED2, HIGH);
          Ampel = Red;
          start_time = millis();
          a = 10;
        }
        break;
    }
  }
}

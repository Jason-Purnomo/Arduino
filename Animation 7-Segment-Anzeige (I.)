#include <arduino.h>
#include "mfs.h"

int main() {
  init();
  initMFS();
  uint8_t v[6] = {0b11111100, 0b11111001, 0b11110011, 0b11100111, 0b11001111, 0b11011110};		//Laut der Aufgabe, 0 = leuchten, 1 = aus
  //Hier bedeutet, dass für v[1]: ab, v[2]: bc, v[3]: cd, v[4]: de, v[5]: ef und v[6]: af leuchtet
  uint8_t i = 0;

  while (1){
    i++;
    if (i>5) {
      i = 0;
    }
    digitalWrite(LATCH_DIO, LOW);       //LOW = neue Daten können Seriell in das Register geschrieben werden (Eingabemodus des Schieberegisters aktiviert), ohne die Ausgänge (Anzeige) zu beeinflussen & die neue Daten per ShiftOut eingetragen werden
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, v[i]); 
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, 0x08);		//0x08 = 0b00001000
    digitalWrite(LATCH_DIO, HIGH);      //HIGH = die im Register gespeicherte Daten werden auf die Ausgänge freigeschaltet (aktualisiert die Ausgänge des Schieberegisters)
    delay(120);
  }
}

#include "rims.h"

volatile unsigned char TimerFlag = 0;
unsigned char soundCount = 0;
unsigned char lightCount = 0;

void TimerISR() {
  TimerFlag = 1;
  ++soundCount;
  ++lightCount;
}

void main() {
  B = 0;

  TimerSet(50);
  TimerOn();

  while (1) {
    if (!(soundCount < 3)) {
      B0 = !B0;
      soundCount = 0;
    }
    
    if (!(lightCount < 5)) {
      B1 = !B1;
      lightCount = 0;
    }

    while (!TimerFlag) {}
    TimerFlag = 0;
  }
}

/*

Does the sound work? Yes
Does the light flash? Yes

*/

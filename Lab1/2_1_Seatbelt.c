#include "RIMS.h"

int main() {
   while(1) {
      B0 = A0 && A1 && !A2;
   }
   return 0;
}

/*

When the car is on, A0 = 1
When a driver is seated, A1 = 1
When the seatbelt is not fastened, !A2 = 1
A0 && A1 && !A2;

*/

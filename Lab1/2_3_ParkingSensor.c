#include "RIMS.h"
unsigned char Getbit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}
int main() {
  unsigned char i = 0;
  unsigned char count = 0;
   while(1) {
     count = 0;
      for (i = 0; i < 6; i++) {
        count += GetBit(A, i);
      }
      B = ((6 - count) << 5) + (A7 && A6);
   }
   return 0;
}

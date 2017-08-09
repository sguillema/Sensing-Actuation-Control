#include "RIMS.h"

unsigned char GetBit(unsigned char x, unsigned char k)
{
  return ((x & (0x01 << k)) != 0);
}

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
  return (b ? (x | (0x01 << k)) : (x & ~(0x01 << k)));
}

int main() {
  unsigned char count = 0;
  unsigned char i = 0;
  unsigned char temp = 0;
  unsigned char prevA = 0;

  while (1) {
    count = 0;
    for (i = 0; i < 8; i++) {
      count += GetBit(A, i);
    }

    for (i = 0; i < 8; i++) {
      if (i < count){
        B = SetBit(B, i, 1);
      }
      else{
        B = SetBit(B, i, 0);
      }
    }

    prevA = A;
    while (prevA == A) {
      if (B7) {
        temp = B7;
        B = (B << 1) + temp;
      }
      else {
        B = B << 1;
      }
    }
  }
}

/*

A = 0011 0000 ?   2 lights shifting
A = 1111 1111 ?   8 lights shifting
A = 1000 1111 ?   5 lights shifting
A = 1000 1101 ?   4 lights shifting

*/

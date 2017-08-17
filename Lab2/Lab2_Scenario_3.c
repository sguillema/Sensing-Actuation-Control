/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/16/2017 12:30:4 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char cnt = 0;

unsigned char SM3_Clk;
void TimerISR() {
   SM3_Clk = 1;
}

enum SM3_States { SM3_Init, SM3_WaitA0, SM3_WaitA1, SM3_DisplaySpeed } SM3_State;

TickFct_State_machine_3() {
   switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_Init;
         break;
         case SM3_Init: 
         if (1) {
            SM3_State = SM3_WaitA0;
         }
         break;
      case SM3_WaitA0: 
         if (A0) {
            SM3_State = SM3_WaitA1;
            cnt = 0;
         }
         else if (!A0) {
            SM3_State = SM3_WaitA0;
         }
         break;
      case SM3_WaitA1: 
         if (!A1) {
            SM3_State = SM3_WaitA1;
         }
         else if (A1) {
            SM3_State = SM3_DisplaySpeed;
         }
         break;
      case SM3_DisplaySpeed: 
         if (1) {
            SM3_State = SM3_WaitA0;
         }
         break;
      default:
         SM3_State = SM3_Init;
   } // Transitions

   switch(SM3_State) { // State actions
      case SM3_Init:
         B = 0;
         break;
      case SM3_WaitA0:
         break;
      case SM3_WaitA1:
         cnt++;
         break;
      case SM3_DisplaySpeed:
         B = (short)(360*3/cnt);
         printf("the speed is: %d\n", B);
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_3 = 100;
   TimerSet(periodState_machine_3);
   TimerOn();
   
   SM3_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_3();
      while(!SM3_Clk);
      SM3_Clk = 0;
   } // while (1)
} // Main
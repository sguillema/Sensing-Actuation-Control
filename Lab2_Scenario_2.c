/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/16/2017 11:59:18 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char SM2_Clk;
void TimerISR() {
   SM2_Clk = 1;
}

enum SM2_States { SM2_Init, SM2_WaitPerson, SM2_Open } SM2_State;

TickFct_State_machine_2() {
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_Init;
         break;
         case SM2_Init: 
         if (1) {
            SM2_State = SM2_WaitPerson;
         }
         break;
      case SM2_WaitPerson: 
         if (A0 && !A1) {
            SM2_State = SM2_Open;
         }
         else {
            SM2_State = SM2_WaitPerson;
         }
         break;
      case SM2_Open: 
         if (A0 || A1) {
            SM2_State = SM2_Open;
         }
         else {
            SM2_State = SM2_WaitPerson;
         }
         break;
      default:
         SM2_State = SM2_Init;
   } // Transitions

   switch(SM2_State) { // State actions
      case SM2_Init:
         B0 = 0;
         break;
      case SM2_WaitPerson:
         B0 = 0;
         break;
      case SM2_Open:
         B0 = 1;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_2 = 1000; // 1000 ms default
   TimerSet(periodState_machine_2);
   TimerOn();
   
   SM2_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_2();
      while(!SM2_Clk);
      SM2_Clk = 0;
   } // while (1)
} // Main
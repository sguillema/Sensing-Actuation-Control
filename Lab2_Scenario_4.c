/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/16/2017 12:52:22 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char cnt = 0;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_DontWalk, SM1_WaitBut, SM1_Walk } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_WaitBut;
         break;
         case SM1_DontWalk: 
         if (cnt < 20;) {
            SM1_State = SM1_WaitBut;
         }
         break;
      case SM1_WaitBut: 
         if (!A0) {
            SM1_State = SM1_WaitBut;
         }
         else if (A0) {
            SM1_State = SM1_Walk;
            cnt = 0;
         }
         break;
      case SM1_Walk: 
         if (cnt < 20) {
            SM1_State = SM1_Walk;
            cnt++;
         }
         else {
            SM1_State = SM1_DontWalk;
            cnt = 0;
         }
         break;
      default:
         SM1_State = SM1_WaitBut;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_DontWalk:
         B0 = 1;
         B1 = 0;
         cnt++;
         break;
      case SM1_WaitBut:
         break;
      case SM1_Walk:
         B0 = 0;
         B1 = 1;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 500;
   TimerSet(periodState_machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main
/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/30/2017 12:48:0 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char mtn = 0;

unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_DM0, SM1_DM1, SM1_DM2 } SM1_State;

TickFct_State_machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/

   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_DM0;
         break;
      case SM1_DM0:
         if (!A0) {
            SM1_State = SM1_DM0;
         }
         else if (A0) {
            SM1_State = SM1_DM1;
         }
         break;
      case SM1_DM1:
         if (!A0) {
            SM1_State = SM1_DM0;
         }
         else if (A0) {
            SM1_State = SM1_DM2;
         }
         break;
      case SM1_DM2:
         if (A0) {
            SM1_State = SM1_DM2;
         }
         else if (!A0) {
            SM1_State = SM1_DM0;
         }
         break;
      default:
         SM1_State = SM1_DM0;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_DM0:
         mtn = 0;
         break;
      case SM1_DM1:
         break;
      case SM1_DM2:
         mtn = 1;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_IL0, SM2_IL1, SM2_IL2 } SM2_State;

TickFct_State_machine_2() {
   static unsigned cnt = 0;
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_IL0;
         break;
      case SM2_IL0:
         if (mtn) {
            SM2_State = SM2_IL1;
         }
         else if (!mtn) {
            SM2_State = SM2_IL0;
         }
         break;
      case SM2_IL1:
         if (!mtn) {
            SM2_State = SM2_IL2;
            cnt = 0;
         }
         else if (mtn) {
            SM2_State = SM2_IL1;
         }
         break;
      case SM2_IL2:
         if ((!mtn && cnt < 50)) {
            SM2_State = SM2_IL2;
         }
         else if (mtn) {
            SM2_State = SM2_IL1;
         }
         else if ((!mtn && !(cnt < 50))) {
            SM2_State = SM2_IL0;
         }
         break;
      default:
         SM2_State = SM2_IL0;
      } // Transitions

   switch(SM2_State) { // State actions
      case SM2_IL0:
         B1 = 0;
         break;
      case SM2_IL1:
         B1 = 1;
         break;
      case SM2_IL2:
         cnt++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM3_States { SM3_BL0, SM3_BL1 } SM3_State;

TickFct_State_machine_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_BL0;
         break;
      case SM3_BL0:
         if (mtn) {
            SM3_State = SM3_BL1;
         }
         else if (!mtn) {
            SM3_State = SM3_BL0;
         }
         break;
      case SM3_BL1:
         if (1) {
            SM3_State = SM3_BL0;
         }
         break;
      default:
         SM3_State = SM3_BL0;
      } // Transitions

   switch(SM3_State) { // State actions
      case SM3_BL0:
         B0 = 0;
         break;
      case SM3_BL1:
         B0 = 1;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(200);
   TimerOn();
   SM1_State = -1;
   SM2_State = -1;
   SM3_State = -1;
   while(1) {
      TickFct_State_machine_1();
      TickFct_State_machine_2();
      TickFct_State_machine_3();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}
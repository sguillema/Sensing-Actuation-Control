/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/16/2017 11:32:38 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char Lights_Clk;
void TimerISR() {
   Lights_Clk = 1;
}

enum Lights_States { Lights_LightOff, Lights_LightOn } Lights_State;

TickFct_Light_Off() {
   switch(Lights_State) { // Transitions
      case -1:
         Lights_State = Lights_LightOff;
         break;
         case Lights_LightOff: 
         if (A0) {
            Lights_State = Lights_LightOn;
         }
         else if (!A0) {
            Lights_State = Lights_LightOff;
         }
         break;
      case Lights_LightOn: 
         if (A1) {
            Lights_State = Lights_LightOff;
         }
         else if (!A1) {
            Lights_State = Lights_LightOn;
         }
         break;
      default:
         Lights_State = Lights_LightOff;
   } // Transitions

   switch(Lights_State) { // State actions
      case Lights_LightOff:
         B = 0x00;
         break;
      case Lights_LightOn:
         B = 0xFF;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodLight_Off = 1000; // 1000 ms default
   TimerSet(periodLight_Off);
   TimerOn();
   
   Lights_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_Light_Off();
      while(!Lights_Clk);
      Lights_Clk = 0;
   } // while (1)
} // Main
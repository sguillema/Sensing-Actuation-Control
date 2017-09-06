/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/6/2017 12:31:57 PST
*/

#include "rims.h"


typedef struct _Q3uc {
	unsigned char buf[3];
	unsigned char cnt;
} Q3uc;

void Q3ucInit(Q3uc *Q) {
	(*Q).cnt = 0;
}

unsigned char Q3ucFull(Q3uc Q) {
	return (Q.cnt == 3);
}

unsigned char Q3ucEmpty(Q3uc Q) {
	return (Q.cnt == 0);
}

void Q3ucPush(Q3uc *Q, unsigned char item) {
	if (!Q3ucFull(*Q)) {
		DisableInterrupts();
		(*Q).buf[(*Q).cnt] = item;
		(*Q).cnt++;
		EnableInterrupts();
	}
}

unsigned char Q3ucPop(Q3uc *Q) {
	int i;
	unsigned char item = 0;
	if (!Q3ucEmpty(*Q)) {
		DisableInterrupts();
		item = (*Q).buf[0];
		(*Q).cnt--;
		for (i=0; i<(*Q).cnt; i++) {
			//shift fwd
			(*Q).buf[i] = (*Q).buf[i+1];
		}
		EnableInterrupts();
	}
	return item;
}

void Q3ucPrint(Q3uc Q) {
	int j;
	printf("Q3uc contents: \r\n");
	for (j=0; j<4; j++) {
		printf("Item %d", j);
		printf(": %d\r\n", Q.buf[j]);
	}
}
unsigned char DB_GetBtn() {
	unsigned char btn;
	switch((A&0x3E)>>1) {
		case 0x00: btn = 0; break;
		case 0x01: btn = 1; break;
		case 0x02: btn = 2; break;
		case 0x04: btn = 3; break;
		case 0x08: btn = 4; break;
		case 0x10: btn = 5; break;
		default: btn = 0; break;
	}
	return btn;
}

unsigned char b;
Q3uc Q;
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long periodState_machine_1 = 100;
const unsigned long periodState_machine_2 = 200;

const unsigned long tasksPeriodGCD = 100;

int TickFct_State_machine_1(int state);
int TickFct_State_machine_2(int state);

unsigned char processingRdyTasks = 0;
void TimerISR() {
   unsigned char i;
   if (processingRdyTasks) {
      printf("Period too short to complete tasks\n");
   }
   processingRdyTasks = 1;
   for (i = 0; i < tasksNum; ++i) { // Heart of scheduler code
      if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
         tasks[i].state = tasks[i].TickFct(tasks[i].state);
         tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += tasksPeriodGCD;
   }
   processingRdyTasks = 0;
}
int main() {
   // Priority assigned to lower position tasks in array
   unsigned char i=0;
   tasks[i].state = -1;
   tasks[i].period = periodState_machine_1;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_State_machine_1;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodState_machine_2;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_State_machine_2;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_s1, SM1_s2 } SM1_State;
int TickFct_State_machine_1(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/



   switch(state) { // Transitions
      case -1:
         state = SM1_s1;
         break;
      case SM1_s1:
         if (!(b==0)) {
            state = SM1_s2;
            Q3ucPush(&Q, b);
         }
         else if (b==0) {
            state = SM1_s1;
         }
         break;
      case SM1_s2:
         if (b==0) {
            state = SM1_s1;
         }
         else if (!(b==0)) {
            state = SM1_s2;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_s1:
         b = DB_GetBtn();
         break;
      case SM1_s2:
         b = DB_GetBtn();
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_Init, SM2_Start, SM2_Wait, SM2_Match, SM2_Check } SM2_State;
int TickFct_State_machine_2(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static const unsigned char seq[3] = {5,2,3};
static unsigned char c;
static unsigned char i;
   switch(state) { // Transitions
      case -1:
         state = SM2_Init;
         break;
      case SM2_Init:
         if (1) {
            state = SM2_Start;
         }
         break;
      case SM2_Start:
         if (1) {
            state = SM2_Wait;
         }
         break;
      case SM2_Wait:
         if (Q3ucEmpty(Q)) {
            state = SM2_Wait;
         }
         else if (!Q3ucEmpty(Q)) {
            state = SM2_Check;
            c = Q3ucPop(&Q);
         }
         break;
      case SM2_Match:
         if (!(i==2)) {
            state = SM2_Wait;
            i++;
         }
         else if ((b==0)&&(i==2)) {
            state = SM2_Start;
            B1=!B1;
         }
         break;
      case SM2_Check:
         if (c == seq[i]) {
            state = SM2_Match;
         }
         else {
            state = SM2_Start;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_Init:
         B1 = 0;
         break;
      case SM2_Start:
         i = 0;
         
         break;
      case SM2_Wait:
         break;
      case SM2_Match:
         break;
      case SM2_Check:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}


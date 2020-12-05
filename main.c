#include <stdio.h>
#include <stdbool.h>


int ip = 0;
int sp = -1;
bool running = true;
int stack[256];


typedef enum {
     PSH,
     ADD,
     POP,
     SET,
     HLT
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int fetch()
{
     return program[ip];
}

void eval(int instr)
{
     switch(instr)
     {
	  case HLT:{
	       running = false;
	       break;
	  }
	  case PSH:{
	       sp++;
	       stack[sp] = program[++ip];
	       break;
	  }
	  case POP:{
	       int val_popped = stack[sp--];
	       printf("popped off %d\n",val_popped);
	       break;
	  }
	  case ADD:{
	       int a = stack[sp--];
	       printf("a = %d\n",a);
	       int b = stack[sp];
	       printf("b = %d\n",b);


	       int result = a + b;
	       sp++;
	       stack[sp] = result;

	       break;
	  }
     }
}

int main()
{
     while(running) 
     {
	  eval(fetch());
	  ip++;
     }
     return 0;
}


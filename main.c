#include <stdio.h>
#include <stdbool.h>

/** 
 * Here, we have the: 
 * instruction pointer (ip)
 * stack pointer (sp) 
 * global variable to start/stop the "machine" (running)
 * the stack (stack[256])
 *
 * The instruction pointer is used to keep track of the current instruction,
 * and the stack pointer is used to keep track of the current stack frame.
 */

int ip = 0;
int sp = -1;
bool running = true;
int stack[256];

/** 
 * These are the instructions used to perform operations
 * They are meant to resemble general assembly language
 * stack pointer (sp) 
 * global variable to start/stop the "machine" (running)
 * the stack (stack[256])
 *
 * The instruction pointer is used to keep track of the current instruction,
 * and the stack pointer is used to keep track of the current stack frame.
 */

typedef enum {
     PSH,
     ADD,
     POP,
     SET,
     HLT
} InstructionSet;

/** 
 * Here is the program itself.
 * This can be thought of as a really dumbed-down abstraction of a source code file.
 */

const int program[] = {
    PSH, 5, // push 5 onto the stack
    PSH, 6, // push 6 onto the stack
    ADD,    // add them, result is stored on stack
    POP,    // pop result off stack
    HLT     // program is done
};

/** 
 * The instruction pointer is essntially used to index the program (source code abstraction above)
 * So either an "opcode" or "operand" will be returned from the fetch
 */

int fetch()
{
     return program[ip];
}

/** 
 * This function evaluates our "source file"
 * It can be thought of as an extremely, mind numbingly, dumbed down version of an interpreter (if you even want to call it that)
 * We read the current instruction, and perform the necessary action based on that instruction and its operands.
 */

void eval(int instr)
{
     switch(instr)
     {
	  case HLT:{
	       // Houston, we have a problem
	       running = false; 
	       break;
	  }
	  case PSH:{
	       // push something onto the stack
	       sp++;
	       stack[sp] = program[++ip];
	       break;
	  }
	  case POP:{
	       // pop, lock, and drop it
	       int val_popped = stack[sp--];
	       printf("popped off %d\n",val_popped);
	       break;
	  }
	  case ADD:{
	       // bit more complex than the others (not really tho)
	       // we get the first argument (a)
	       // we get the second argument (b)
	       // we add them, and push that result onto the stack!
	       int a = stack[sp--];
	       printf("a = %d\n",a);
	       int b = stack[sp];
	       printf("b = %d\n",b);

	       int result = a + b;
	       sp++;               // increment stack pointer 
	       stack[sp] = result; // push result onto stack
	       break;
	  }
     }
}

int main()
{
     while(running)
     {
	  // while the machine is on,
	  // evaluate the current instruction,
	  // and get the next instruction
	  eval(fetch());
	  ip++;
     }
     return 0;
}


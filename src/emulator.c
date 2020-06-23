/**
 * @file															                         
 * @author  Ben Goldsworthy (rumps) <me+scc150@bengoldsworthy.net>              
 * @version 1.0	                                                          
 *                                                                          
 * @section LICENSE                                                         
 *                                                                          
 * This file is free software: you can redistribute it and/or modify        
 * it under the terms of the GNU General Public License as published by     
 * the Free Software Foundation, either version 3 of the License,           
 * or (at your option) any later version.                                   
 *                                                                          
 * This file is distributed in the hope that it will be useful,             
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            
 * GNU General Public License for more details.                             
 *                                                                          
 * You should have received a copy of the GNU General Public License        
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.    
 *                                                                          
 * @section DESCRIPTION                                                     
 *                                                                          
 * This program emulates programs written in the SCC.150 Assembler language.
 * The language is a very simple assembly language that comprises of only ten
 * opcodes:                                                                 
 *                                                                          
 * `NOP` or 'No OPeration', which performs no task   
 *                        
 * `SET ARG1 ARG2`, which puts the value in `ARG2` into the register        
 * indicated in `ARG1`                  
 *                                     
 * `AND ARG1 ARG2`, which performs a bitwise AND operation on the values in 
 * `ARG1` and `ARG2`           
 *                                              
 * `OR ARG1 ARG2`, which performs a bitwise OR operation on the values in   
 * `ARG1` and `ARG2`                  
 *                                       
 * `ADD ARG1 ARG2`, which performs an addition operation on the values in   
 * `ARG1` and `ARG2`             
 *                                            
 * `SUB ARG1 ARG2`, which performs a subtraction operation on the values in 
 * `ARG1` and `ARG2`          
 *                                               
 * `SHL ARG1 ARG2`, which performs a bitwise shift left on the value in     
 * `ARG1`, to the number indicated in `ARG2`  
 *                               
 * `SHR ARG1 ARG2`, which performs a bitwise shift right on the value in    
 * `ARG1`, to the number indicated in `ARG2`    
 *                             
 * `JMP ARG1`, which jumps to the line indicated by `ARG1` if the value in  
 * `REGX` is 0                             
 *                                  
 * `PRT ARG1`, which prints the value in `ARG1`                             
 *                                                                          
 * Five registers are used: `REGA`, `REGB`, `REGC`, `REGX` and `INSP`, or   
 * 'INStruction Pointer'.                                                   
 *                                                                          
 * Comments in the language are indicated by the line beginning with a '#'. 
 */

#include "emulator.h"
#include "mystring.h"

// Function pointer definition for opcodes
typedef int (*opcode_function)(char*, char*, char*);

// Contains the program after reading it from the file
char prog[MAX_PROG_LEN][MAX_LINE_LEN];
// The length of the loaded program in lines
int progLen = 0;

// Used to detect if a program is stuck in an infinite loop
unsigned int programRuns = 0;

// The three general purpose registers
unsigned int REGA = 0;
unsigned int REGB = 0;
unsigned int REGC = 0;
// A special register, used by JMP
unsigned int REGX = 0;
// A special register; the instruction pointer pointing to the next
// program line to be executed
unsigned int INSP = 0;

// Arrays to allow generic access to registers (not actually used in the end)
const char* register_str[] = {"REGA", "REGB", "REGC", "REGX"};
//int *register_ptr[]={&REGA, &REGB, &REGC, &REGX};


// Arrays to allow generic access to functions for opcode execution
const char* opcodeStr[] = {"NOP", "SET", "AND", "OR", "ADD",
                            "SUB", "SHL", "SHR", "JMP", "PRT"};
opcode_function opcodeFunc[] = {&opcodeNOP, &opcodeSET, &opcodeAND, &opcodeOR,
                                 &opcodeADD, &opcodeSUB, &opcodeSHL, &opcodeSHR,
                                 &opcodeJMP, &opcodePRT};

/**
 * A function to handle the `NOP` opcode
 * 
 * Increments the instruction pointer `INSP`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument (not applicable for `NOP`)
 * @param arg2 the second argument (not applicable for `NOP`)
 * @return 0 on success
 */
int opcodeNOP(char* opcode, char* arg1, char* arg2) {
	INSP++;

   return 0;
}

/**
 * A function to handle the `SET` opcode
 * 
 * Gets the value of either the register or integer set in `arg2` and places it
 * in the register indicated by `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeSET(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `AND` opcode
 * 
 * Performs a bitwise AND on the values in `arg1` and `arg2`, storing
 * the result in `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeAND(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA & val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB & val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC & val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX & val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `OR` opcode
 * 
 * Performs a bitwise OR on the values in `arg1` and `arg2`, storing
 * the result in `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeOR(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA | val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB | val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC | val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX | val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `ADD` opcode
 * 
 * Performs addition on the values in `arg1` and `arg2`, storing
 * the result in `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeADD(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA + val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB + val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC + val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX + val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `SUB` opcode
 * 
 * Subtracts the value in `arg2` from the value in `arg1`, storing
 * the result in `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeSUB(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA - val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB - val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC - val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX - val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `SHL` opcode
 * 
 * Performs a bitwise shift left on the value in `arg1`, storing
 * the result in `arg1`. The number of shifts is specified in `arg2`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeSHL(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA << val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB << val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC << val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX << val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `SHR` opcode
 * 
 * Performs a bitwise shift right on the value in `arg1`, storing
 * the result in `arg1`. The number of shifts is specified in `arg2`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument
 * @return 0 on success
 */
int opcodeSHR(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg2);
   
   if (!mystrncmp(arg1, "REGA", ARG_LENGTH)) REGA = REGA >> val;
   else if (!mystrncmp(arg1, "REGB", ARG_LENGTH)) REGB = REGB >> val;
   else if (!mystrncmp(arg1, "REGC", ARG_LENGTH)) REGC = REGC >> val;
   else if (!mystrncmp(arg1, "REGX", ARG_LENGTH)) REGX = REGX >> val;
   
	INSP++;
   
	return 0;
}

/**
 * A function to handle the `JMP` opcode
 * 
 * If `REGX` contains 0, jumps to the line indicated by `arg1`.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument (not applicable for `JMP`)
 * @return 0 on success
 */
int opcodeJMP(char* opcode, char* arg1, char* arg2) {
   int val = getArg2(arg1);
   
   if (REGX == 0) INSP = val;
   else INSP++;
   
	return 0;
}

/**
 * A function to handle the `PRT` opcode
 * 
 * Prints the value in the register indicated in `arg1`, or the integer value
 * specified.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument (not applicable for `PRT`)
 * @return 0 on success
 */
int opcodePRT(char* opcode, char* arg1, char* arg2) {
	if(!mystrncmp(arg1, "REGA", ARG_LENGTH)) printf("REGA = %d\n", REGA);
	else if(!mystrncmp(arg1, "REGB", ARG_LENGTH)) printf("REGB = %d\n", REGB);
	else if(!mystrncmp(arg1, "REGC", ARG_LENGTH)) printf("REGC = %d\n", REGC);
	else if(!mystrncmp(arg1, "REGX", ARG_LENGTH)) printf("REGX = %d\n", REGX);
	else printf("     = %d\n", atoi(arg1));
   
	INSP++;
   
	return 0;
}

/**
 * A function to return the value in the second argument of an instruction.
 * 
 * Returns either the value in the indicated register or, as the instruction
 * is parsed as a string, the integer value given. `mystrncmp()` is used
 * over `mystrcmp()` because there tends to be dodgy C string magic tacked on
 * to the end of the args. 
 * 
 * @param arg2 the value to parse
 * @return an integer
 */
int getArg2(char* arg2) {   
   if (!mystrncmp(arg2, "REGA", ARG_LENGTH)) return REGA;
   else if (!mystrncmp(arg2, "REGB", ARG_LENGTH)) return REGB;
   else if (!mystrncmp(arg2, "REGC", ARG_LENGTH)) return REGC;
   else if (!mystrncmp(arg2, "REGX", ARG_LENGTH)) return REGX;
   else return atoi(arg2);
}

/**
 * Tests if an instruction is valid.
 * 
 * Tests that the opcode is valid and that the registers are also.
 * 
 * @param opcode the opcode
 * @param arg1 the first argument
 * @param arg2 the second argument (not applicable for `PRT`)
 * @return `true` if the string is valid, `false` if it is not
 */
bool isValid(char* opcode, char* arg1, char* arg2) { 
   bool validOpcode = false, validArg1 = false, validArg2 = false;
   
   for (size_t i = 0; (i < MAX_OPCODE) && (!validOpcode); i++)
      if (!mystrncmp(opcode, opcodeStr[i], OPCODE_LENGTH))
         validOpcode = true;
      
   if (mystrncmp(opcode, "NOP", OPCODE_LENGTH)) {
      if ((!mystrncmp(arg1, "REGA", 3)) || 
          (!mystrncmp(arg1, "REGB", ARG_LENGTH)) ||
          (!mystrncmp(arg1, "REGC", ARG_LENGTH)) ||
          (!mystrncmp(arg1, "REGX", ARG_LENGTH)) ||
          (atoi(arg1) > 0)) validArg1 = true;
      
      if ((mystrncmp(opcode, "JMP", OPCODE_LENGTH)) ||
          (mystrncmp(opcode, "PRT", OPCODE_LENGTH))) {
         if ((!mystrncmp(arg2, "REGA", ARG_LENGTH)) || 
            (!mystrncmp(arg2, "REGB", ARG_LENGTH)) ||
            (!mystrncmp(arg2, "REGC", ARG_LENGTH)) ||
            (!mystrncmp(arg2, "REGX", ARG_LENGTH)) ||
            ((atoi(arg2) > 0) || (!mystrncmp(arg2, "0", 1)))) validArg2 = true;
      } else validArg2 = true;
   } else { validArg1 = true; validArg2 = true; }
   
   return (validOpcode && validArg1 && validArg2) ? true : false;
}

/**
 * Executes an instruction.
 * 
 * Tests the validity of an instruction (and whether or not it's a comment), 
 * and if the line passes, calls the appropriate function.
 * 
 * @param instruction the instruction to test
 * @return 0 on success, -1 on failure
 */
int execInstruction(char* instruction) {
// DEBUGGING: prints the current instruction
//printf("executing line: %s", instruction);

   // Skips the line if it begins with the comment symbol '#'
   if (instruction[0] != '#') {
      // Three arrays to hold the parsed sections of the instruction
      char opcode[OPCODE_LENGTH];
      char arg1[ARG_LENGTH];
      char arg2[ARG_LENGTH];
      size_t i = 0;
      int instrSection = OPCODE;
      
      // Reads the instruction to the end, parsing out the opcode and,
      // where applicable, arg(s)
      // Note: I am thick for not using fscanf() and saving 18 lines
      // (I should probably stop looking at so many SO code golfs)
      while (*instruction != '\0') {
         if (*instruction == ' ') {
            instrSection++;
            i = 0;
            instruction++;
         }
         
         switch (instrSection) {
         case OPCODE:
            opcode[i++] = *instruction++;
            break;
         case ARG1:
            arg1[i++] = *instruction++;
            break;
         case ARG2:
            arg2[i++] = *instruction++;
         }
      }
      if (isValid(opcode, arg1, arg2)) {
         // Calls the appropriate function for the instruction
         for (size_t j = 0; j < MAX_OPCODE; j++)
            if (!mystrncmp(opcode, opcodeStr[j], OPCODE_LENGTH))
               (*opcodeFunc[j])(opcode, arg1, arg2);
      } else return -1;
   } else INSP++;
   
   programRuns++;
   if (programRuns > 150) return -1;
   
	return 0;
}

/**
 * Executes an the program.
 * 
 * Runs `execInstruction` on each line of the program in turn.
 * 
 * @return 0 on success, -1 on failure
 */
int execProgram() {
   INSP = 0;
   printf("RUNNING PROGRAM...\n");
   while (INSP < progLen) {
      if (execInstruction(&prog[INSP][0]) < 0) {
         printf("EXECUTION ERROR\n");
         return -1;
      }
// DEBUGGING: displays register contents
//printf("REGS: %d %d %d %d %d\n", REGA, REGB, REGC, REGX, INSP);
   }
   printf("... DONE!\n");
   return 0;
}

/**
 * Loads a program.
 * 
 * Loads the program file and reads each line into an array.
 * 
 * @return 0 on success, -1 on failure
 */
int loadProgram() {
   FILE *f;
       
   // Reads in the program file (the .scc filetype is just for kicks;
   // the program just reads text files)
   f = fopen("../programs/prog.scc", "r");
   if (f == NULL) {
      printf("FILE OPEN ERROR\n");
      return -1;
   }
   while(fgets(&prog[progLen][0], MAX_LINE_LEN, f) != NULL) {
      progLen++;
   }

// DEBUGGING: print the program out
/* 
printf("PROGRAM:\n");
for (int j = 0; j < progLen; j++) {
   printf("%d: %s", j, &prog[j][0]);
}
*/

   return 0;
}

/**
 * Runs the program.
 * 
 * @return 0 on success, -1 on failure
 */
int main() {
   if (loadProgram() < 0) return -1;
   if (execProgram() < 0) return -1;
   
   return 0;
}

#ifndef EMULATOR_H_
#define EMULATOR_H_

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
 * Header file for `emulator.c`.                                            
 */

#include <stdio.h> // used for printf()
#include <stdlib.h> // used for atoi()
#include <stdbool.h> // used for bool data type

#define MAX_PROG_LEN 99 // The maximum length (in lines) a program can have
#define MAX_LINE_LEN 80 // The maximum length of a program line (in characters)
#define MAX_OPCODE   10 // The maximum number of opcodes that are supported
#define MAX_REGISTER 4  // The maximum number of registers (minus INSP)
#define OPCODE_LENGTH 3 // The maximum length of an opcode
#define ARG_LENGTH 4    // The maximum length of an arg
#define OPCODE 0        // Used for parsing instruction segments
#define ARG1 1
#define ARG2 2

// Opcode handling functions
int opcodeNOP(char* opcode, char* arg1, char* arg2);
int opcodeSET(char* opcode, char* arg1, char* arg2);
int opcodeAND(char* opcode, char* arg1, char* arg2);
int opcodeOR(char* opcode, char* arg1, char* arg2);
int opcodeADD(char* opcode, char* arg1, char* arg2);
int opcodeSUB(char* opcode, char* arg1, char* arg2);
int opcodeSHL(char* opcode, char* arg1, char* arg2);
int opcodeSHR(char* opcode, char* arg1, char* arg2);
int opcodeJMP(char* opcode, char* arg1, char* arg2);
int opcodePRT(char* opcode, char* arg1, char* arg2);

// Argument extraction function
int getArg2(char* arg2);

// Command validator function
bool isValid(char* opcode, char* arg1, char* arg2);

// Emulator run functions
int execInstruction(char* instruction);
int execProgram();
int loadProgram();

#endif /* EMULATOR_H_ */

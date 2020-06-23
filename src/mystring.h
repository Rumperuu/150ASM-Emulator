#ifndef MYSTRING_H_
#define MYSTRING_H_

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
 * Header file for `mystring.c`.                                            
 */

#include <stddef.h> // used for size_t

size_t mystrlen(const char* s);
int mystrcmp(const char* s1, const char* s2);
int mystrncmp(const char* s1, const char* s2, int n);
char* mystrchr(char* haystack, const char needle);
char* mystrstr(char* haystack, const char* needle);

#endif /* MYSTRING_H_ */

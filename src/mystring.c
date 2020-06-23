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
 * The `mystring.h` library serves as a fairly pointless replacement        
 * for the perfectly good (better, even) `string.h`.                        
 */

#include <stddef.h> // used for size_t

#include "mystring.h"

// I prefer <type>* <name> to <type> *<name>, for the reasons laid out
// by Bjarne Stroustrup at <http://www.stroustrup.com/bs_faq2.html#whitespace>

/**
 * A function to measure the length of a valid C string.
 * 
 * Goes through the null-terminated (i.e. valid C) string `s` 
 * character-by-character, returning the length of the string (sans the 
 * null terminator).
 * 
 * @param s the string to measure
 * @return the length of the string as an `unsigned int` (`size_t` because
 *         apparently that's the done thing as of C99, which I'm using
 *         because I love for loop initial declarations to bits)
 */
size_t mystrlen(const char* s) {
   int length = 0;
	
   while (*s != '\0') {
      s++;
      length++;
   }
	
   return length;
}

/**
 * A function to compare two strings.
 * 
 * Compares two strings, returning -1 if `s1` < `s2`, 1 if `s1` > `s2`
 * and 0 if `s1` == `s2`.
 * 
 * @param s1 the string to compare
 * @param s2 the string to compare `s1` to
 * @return -1 if the `s1` < `s2`; 1 if `s1` > `s2`; 0 if `s1` == `s2`
 */
int mystrcmp(const char* s1, const char* s2) {
   while (*s1 != '\0') {
      if (*s2 == '\0') return  1;
      if (*s1 < *s2)   return -1;
      if (*s1 > *s2)   return  1;

      s1++;
      s2++;
   }

   if (*s2 != '\0') return -1;

   return 0;
}

/**
 * A function to compare two strings up to a certain point.
 * 
 * Goes through `n` characters of `s1`, comparing them to the
 * matching characters of `s2`. If the characters are different,
 * it returns -1 if `s1` < `s2` and 1 if `s1` > `s2`. 
 * 
 * If they're the same, it returns 0 if `s1` is the same length as `s2`
 * (i.e. the same characters are both `NUL`). If the function reaches
 * the `n`th character of `s1` and it remains the same as `s2`, it 
 * returns 0 also.
 * 
 * @param s1 the string to compare
 * @param s2 the string to compare `s1` to
 * @param n the length of `s1` to compare
 * @return -1/1 if the strings don't match, 0 if they do
 */
int mystrncmp(const char* s1, const char* s2, int n) {
   for (; n > 0; s1++, s2++, --n) {
      if (*s1 != *s2)
         return (*s1 < *s2) ? -1 : 1;
      else if (*s1 == '\0')
         return 0;
   }
   
   return 0;
}

/**
 * A function to find if a character exists in a string.
 * 
 * Goes through the string `haystack` looking for the character `needle`.
 * 
 * @param haystack the string to search
 * @param needle the character to search for
 * @return `haystack` if successful, 0 if not
 */
char* mystrchr(char* haystack, const char needle) {
    while (*haystack != needle) {
        if (!*haystack++) {
            return NULL;
        }
    }
    return haystack;
}

/**
 * A function to find if a string exists as a subset or totality of another.
 * 
 * Goes through the string `haystack` looking for the string `needle` by
 * executing `mystrchr` on each character in turn.
 * 
 * @param haystack the string to search
 * @param needle the (sub)string to search for
 * @return `haystack` if successful, 0 if not
 */
char* mystrstr(char* haystack, const char* needle) {
   const size_t len = mystrlen(needle);

   while ((haystack = mystrchr(haystack, *needle)) != 0) {
      if (mystrncmp(haystack, needle, len) == 0)
         return haystack;
   }
  
  return 0;
}

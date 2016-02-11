/* PROGRAM: Cipher Header
   AUTHOR:  Tryton Van Meer
   DATE:    November 2015
   PURPOSE: CST8234 Assignment 3
*/

#ifndef VAN_A3_H
#define VAN_A3_H

/**************************************************************************/
/* Declare include files
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**************************************************************************/
/* Macro Defines
**************************************************************************/

/**************************************************************************/
/* Global Variables
**************************************************************************/

/* Make the program name accessable from anywhere */
char *prog;


/**************************************************************************/
/* Function prototypes
**************************************************************************/
int usage();
int a3_crypt(int KEY, char *SRC, char *DEST);
int transpo(int KEY, char *SRC, char *DEST, char de);


#endif /* VAN_A3_H */

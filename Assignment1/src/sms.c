/* PROGRAM: sms.c
   AUTHOR: Tryton Van Meer | Sheldon McGrath
   DATE:  October 2015
   PURPOSE: CST8234 C Lang - Assigment 1

*/

/**************************************************************************/
/* Declare include files
**************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**************************************************************************/
/* Macro Defines
**************************************************************************/
#define MEM_SIZE 1000
#define INIT_MEM 50505
#define END -999999

/* OPERATIONS */
#define READ 10
#define SAVE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBSTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

/* ERRORS */
#define TOO_BIG -10
#define INVALID_WORD -20
#define OPERATION_CODE_ERROR -21
#define OVERFLOW -30
#define ADD_OVERFLOW -31
#define SUB_OVERFLOW -32
#define MUL_OVERFLOW -33
#define UNDERFLOW -40
#define ADD_UNDERFLOW -41
#define SUB_UNDERFLOW -42
#define MUL_UNDERFLOW -43
#define DIV_BY_0 -51
#define MULL_INVALID -52
#define DIV_INVALID -53

/* FORMATTING */
#define DASHES "------------------------------------------------------------"
#define STARS "********************"

/**************************************************************************/
/* Function prototypes
**************************************************************************/
int main( void );
void dump( int[], int, int, int, int, int );
void dump_mem( int[], int );
void init_mem( int[] );
int load( int[] );
void execute( int, int, int, int, int, int, int[] );
void error_message( int);
int get_int_len( int );

/**************************************************************************/
/* Global variables
**************************************************************************/


/**************************************************************************/
/* Main
**************************************************************************/
int main()
{
  int memory[MEM_SIZE];

  int accumulator = 0;
  int instcounter = 0;
  int instregister = 0;
  int operationcode = 0;
  int operand = 0;
  int validinstruction = 0;

  int load_result;
  int error = 0;

  int done = 0;

  init_mem(memory);

  load_result = load(memory);
  if(load_result != 0)
  {
    printf("\n");
    dump(memory, accumulator, instcounter, instregister, operationcode, operand);
    return EXIT_FAILURE;
  }

  /* EXECUTION */
  printf("%sSTART EXECUTION%s\n\n", STARS, STARS);

  while(!done)
  {
    /* SET OPERATION REGISTERS */
    instregister = memory[instcounter];
    operationcode = instregister / 1000;
    operand = instregister % 1000;

    /* PROCESS OPERAND */
    switch(operationcode)
    {

      case READ:
        fscanf(stdin, "%d\n", &memory[operand]);
        printf("READ: %+06i\n", memory[operand]);
        break;

      case SAVE:
        printf("%+06i\n", memory[operand]);
        break;

      case LOAD:
        accumulator = memory[operand];
        break;


      case STORE:
        memory[operand] = accumulator;
        break;

      case ADD:
        accumulator += memory[operand];
        if(get_int_len(accumulator) > 5)
        {
          if(accumulator < 0)
          {
            error = ADD_UNDERFLOW;
          }
          else
          {
            error = ADD_OVERFLOW;
          }
          error_message(error);
          done = 1;
          break;
        }
        break;

      case SUBSTRACT:
        accumulator -= memory[operand];
        if(get_int_len(accumulator) > 5)
        {
          if(accumulator < 0)
          {
            error = SUB_UNDERFLOW;
          }
          else
          {
            error = SUB_OVERFLOW;
          }
          error_message(error);
          done = 1;
          break;
        }
        break;

      case DIVIDE:
        if(memory[operand] == 0)
        {
          error = DIV_BY_0;
          error_message(error);
          done = 1;
          break;
        }
        else if(get_int_len(memory[operand]) > 5 || get_int_len(accumulator) > 5)
        {
          error = DIV_INVALID;
          error_message(error);
          done = 1;
          break;
        }
        accumulator /= memory[operand];
        break;

      case MULTIPLY:
        if(get_int_len(memory[operand]) > 5 || get_int_len(accumulator) > 5)
        {
          error = MULL_INVALID;
          error_message(error);
          done = 1;
          break;
        }
        accumulator *= memory[operand];
        if(get_int_len(accumulator) > 5)
        {
          if(accumulator < 0)
          {
            error = MUL_UNDERFLOW;
          }
          else
          {
            error = MUL_OVERFLOW;
          }
          error_message(error);
          done = 1;
          break;
        }
        break;

      case HALT:
        done = 1;
        break;

      default:
        error = OPERATION_CODE_ERROR;
        error_message(error);
        done = 1;
        break;
    }

    /* ADVANCE INSTRUCTION REGISTER AND VALID INSTRUCTION COUNT */
    instcounter++;
    validinstruction++;
  }

  printf("\n%sEND EXECUTION%s\n\n", STARS, STARS);
  /* END EXECUTION
     DUMP REGISTERS/MEMORY
     EXIT MAIN */
  dump(memory, accumulator, instcounter, instregister, operationcode, operand);
  if(error == 0)
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }
}

/**************************************************************************/
/* error_message
 * Initializes all the memory positions to INIT_MEM
**************************************************************************/
void error_message(int error_code)
{
  printf("\n");
  switch(error_code)
  {
    case OPERATION_CODE_ERROR:
      printf("ABEND: invalid operation");
      break;
    case TOO_BIG:
      printf("ABEND: out of memory; program too big");
      break;
    case INVALID_WORD:
      printf("ABEND: invalid word in program");
      break;
    case OVERFLOW:
      printf("ABEND: memory overflow");
      break;
    case ADD_OVERFLOW:
      printf("ABEND: memory overflow while doing addition");
      break;
    case SUB_OVERFLOW:
    printf("ABEND: memory overflow while doing subtraction");
    break;
    case MUL_OVERFLOW:
    printf("ABEND: memory overflow while doing multiplication");
    break;
    case ADD_UNDERFLOW:
      printf("ABEND: memory underflow while doing addition");
      break;
    case SUB_UNDERFLOW:
      printf("ABEND: memory underflow while doing subtraction");
      break;
    case MUL_UNDERFLOW:
      printf("ABEND: memory underflow while doing multiplication");
      break;
    case DIV_BY_0:
    printf("ABEND: division by 0");
    break;
    case MULL_INVALID:
      printf("ABEND: invalid operation for multiplication");
      break;
    case DIV_INVALID:
      printf("ABEND: invalid operation for division");
      break;
  }
  printf("\n");
}

/**************************************************************************/
/* init_mem
 * Initializes all the memory positions to INIT_MEM
**************************************************************************/
void init_mem(int a[])
{
  int *p = &a[0];
  int i;

  for(i=0; i<MEM_SIZE; i++)
  {
    *p++ = INIT_MEM;
  }
}

/**************************************************************************/
/* dump
 * Dumps all the values to stdout
**************************************************************************/
void dump(int memory[], int accumulator,
  int instcounter, int instregister, int operationcode, int operand)
{
  printf("REGISTERS: \n");
  printf("accumulator %+04d\n", accumulator);
  printf("instruction counter %d\n", instcounter);
  printf("instruction register %+04d\n", instregister);
  printf("operation code %d\n", operationcode);
  printf("operand %d\n", operand);
  printf("\nMEMORY: \n\n");
  dump_mem(memory, instcounter);
}

/**************************************************************************/
/* dump_mem
 * Dumps memory values to stdout
**************************************************************************/
void dump_mem(int memory[], int max)
{
  int j = 0;
  int i;


  while(j<max)
  {
    printf("x%02i", j);
    for(i=0; i<10; i++)
    {
      printf("%*.s%+i ", 3, " ", memory[i+j]);
    }
    printf("\n");
    j += 10;
  }
}

/**************************************************************************/
/* load
 * Load sml commands into memory
**************************************************************************/
int load(int mem[])
{
  int *p = &mem[0];
  int line_result;
  int end_flag = 0;
  int count = 0;
  int error = 0;

	while(!end_flag)
  {
		fscanf(stdin, "%d\n", &line_result);

    if(line_result != END)
    {
      if(get_int_len(line_result) != 5)
      {
        error = INVALID_WORD;
        end_flag = 1;
      }

      *p++ = line_result;
      count++;

      if(count == MEM_SIZE)
      {
        error = TOO_BIG;
        end_flag = 1;
      }
    }
    else
    {
      end_flag = 1;
    }
	}

  if(error == 0)
  {
    return EXIT_SUCCESS;
  }
  else
  {
    error_message(error);
    return error;
  }
}

/**************************************************************************/
/* get_int_len
 * Retrun the length of an integer
**************************************************************************/
int get_int_len(int integer)
{
  int int_len = floor(log10(abs(integer))) + 1;
  return int_len;
}

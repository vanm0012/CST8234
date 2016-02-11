/* PROGRAM: Transpo
   AUTHOR:  Tryton Van Meer
   DATE:    November 2015
   PURPOSE: CST8234 Assignment 3
*/

/**************************************************************************/
/* Declare include files
**************************************************************************/
#include "van_a3.h"


/**************************************************************************
 * Main
 *
**************************************************************************/
int main(int argc, char** argv)
{
  int opt;

  int key = 0;
  char *src_file = NULL;
  char *dst_file = NULL;

  /* Flags for options */
  int h_flag = 0;
  int d_flag = 0;
  int e_flag = 0;

  while ((opt = getopt(argc, argv, "hd:e:")) != -1)
  {
    switch(opt)
    {
      case 'h':
       h_flag = 1;
       break;
      case 'd':
       d_flag = 1;
       key = atoi(optarg);
       break;
      case 'e':
       e_flag = 1;
       key = atoi(optarg);
       break;
    }
  }

  /* set the prog name */
  prog = argv[0];

  /* Checks if key is integer */
  if (key == 0)
  {
    printf("Key must be a sequence of decimal integers\n");
    usage();
    return EXIT_FAILURE;
  }

  /* Checks for source and destination arguments */
  if (argv[optind] != NULL)
  {
    src_file = argv[optind];
    if (argv[optind+1] != NULL)
    {
      dst_file = argv[optind+1];
    }
  }
  /* Args not found */
  if (src_file == NULL || dst_file == NULL)
  {
    fprintf(stderr, "%s: SOURCE and DESTINATION args must be given\n", argv[0]);
  }

  /* Check flags and run encrypt/decrypt functions */
  if (h_flag == 0 && d_flag == 0 && e_flag == 0)
  {
    usage();
    return EXIT_FAILURE;
  }
  else if (e_flag == 1 && d_flag == 1)
  {
    fprintf(stderr, "%s: d and e flag may not be used together\n", argv[0]);
    return EXIT_FAILURE;
  }
  else if (h_flag == 1)
  {
    usage();
    return EXIT_SUCCESS;
  }
  else if(d_flag == 1)
  {
    printf("decrypting %s...\n", src_file);
    transpo(key, src_file, dst_file, 'd');
    return EXIT_SUCCESS;
  }
  else if(e_flag == 1)
  {
    printf("encrypting %s...\n", src_file);
    transpo(key, src_file, dst_file, 'e');
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}


/**************************************************************************
 * usage
 * prints help
**************************************************************************/
int usage()
{
  printf("usage: %s [OPTIONS] [SOURCE] [DESTINATION]\n\n", prog);
  printf("options:\n");
  printf("-d KEY    %s\n", "decrypt the file SOURCE using KEY and writes back into DESTINATION");
  printf("-e KEY    %s\n", "encrypt the file SOURCE using KEY and writes back into DESTINATION");
  printf("-h       %s\n", " prints help");
  return EXIT_SUCCESS;
}

/**************************************************************************
 * transpo
 * (En|De)crypts SRC file to a DST file using a KEY and the Transposition Algorithm
 * SRC is the source file to encrypt
 * DST is the file to write to
 * KEY is the decimal integer to use for decryption/encryption
 *
 * Returns EXIT_FAILURE if the files could not be opened for any reason
 * Else EXIT_SUCCESS is returned
**************************************************************************/
int transpo(int KEY, char *SRC, char *DEST, char de)
{
  FILE *src_fp;
  FILE *dest_fp;
  int nextchar;
  int src_size;
  int i;
  int j;
  int k = 0;

  /*
   Opens the SRC and DEST file and checks for errors along the way
   SRC opened with read permisions
   DEST opened with read and write permisions
   */
  src_fp = fopen(SRC, "r");
  dest_fp = fopen(DEST, "w");

  if (src_fp == NULL)
  {
    fprintf(stderr, "%s: [%s] could not be opened.\n", prog, SRC);
    return EXIT_FAILURE;
  }
  else if (dest_fp == NULL)
  {
    fprintf(stderr, "%s: [%s] could not be opened.\n", prog, DEST);
    return EXIT_FAILURE;
  }

  /* Files opened correctly.  Now get file size, and move back to beginning */

  fseek(src_fp, 0, SEEK_END);
  src_size = ftell(src_fp);
  rewind(src_fp);

  if (de == 'e')
  {
    /* Now encrypt the source file */
    for (i=0; i<KEY; i++)
    {
      for (j=k; j<src_size; j+=KEY)
      {
        fseek(src_fp, j, 0);
        nextchar = fgetc(src_fp);
        fprintf(dest_fp, "%c", nextchar);
      }
      k++;
    }
  }
  else if (de == 'd')
  {
    j = 0;
    /* Now decrypt the source file */
    for (i=0; i<src_size; i++)
    {
      nextchar = fgetc(src_fp);
      fseek(dest_fp, j, 0);
      fprintf(dest_fp, "%c", nextchar);

      /* Increment j by Key values and check if j has to start back at begining */
      j += KEY;
      if (j >= src_size)
      {
        k++;
        j = k;
      }
    }
  }

  /* Done encrypting. Now close the files */
  fclose(src_fp);
  fclose(dest_fp);

  return EXIT_SUCCESS;
}

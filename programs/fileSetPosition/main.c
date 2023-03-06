/* 
 * File:   main.c
 * Author: Lefeldiman
 *
 * Created on November 1, 2013, 2:04 AM
 */

/* fsetpos example */
#include <stdio.h>

int main ()
{
  FILE * pFile;
  fpos_t position;

  pFile = fopen ("myfile.txt","w");
  fgetpos (pFile, &position);
  fputs ("That is a sample",pFile);
  fsetpos (pFile, &position);
  printf("%jd",(intmax_t)position);
  fputs ("This",pFile);
  fclose (pFile);
  return 0;
}
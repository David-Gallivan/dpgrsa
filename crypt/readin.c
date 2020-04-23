//JMJ

// readin.c
// by David Gallivan

// support functions for reading in keys and messages
// TODO document better!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// all input values must be made up of ASCII decimal digits only;
// any non-digit character will denote the end of an input value
#define IS_DIGIT (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
#define MAX_LENGTH 1024 

int readPublicKey(char *filename, char **e, char **n)
{
  int i;
  char c, *eBuffer, *nBuffer;
  eBuffer = malloc(MAX_LENGTH);
  nBuffer = malloc(MAX_LENGTH);
  FILE *fp;
  fp = fopen(filename, "r");
  
  // read in e
  c = (char) fgetc(fp);
  i = 0;
  while (IS_DIGIT)
  {
    eBuffer[i] = c;
    c = (char) fgetc(fp);
    i += 1;
  }
  eBuffer[i] = 0x00;
  *e = eBuffer;

  // read in n
  c = (char) fgetc(fp);
  i = 0;
  while (IS_DIGIT)
  {
    nBuffer[i] = c;
    c = (char) fgetc(fp);
    i += 1;
  }
  nBuffer[i] = 0x00;
  *n = nBuffer;

  return 0;
}

int readMessage(char *filename, char **m)
{
  int i;
  char c, *buffer;
  buffer = malloc(MAX_LENGTH);
  memset(buffer, 0x00, MAX_LENGTH);
  FILE *fp;
  fp = fopen(filename, "r");
  c = (char) fgetc(fp);
  i = 0;
  while (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
  {
    buffer[i] = c;
    c = (char) fgetc(fp);
    i += 1;
  }
  //buffer[i] = 0x00;
  *m = buffer;

  return 0;
}

int readPrivateKey(char *filename, char **d)
{
  int i;
  char c, *buffer;
  buffer = malloc(MAX_LENGTH);
  FILE *fp;
  fp = fopen(filename, "r");
  c = (char) fgetc(fp);
  i = 0;
  while (IS_DIGIT)
  {
    buffer[i] = c;
    c = (char) fgetc(fp);
    i += 1;
  }
  buffer[i] = 0x00;
  *d = buffer;

  return 0;
}

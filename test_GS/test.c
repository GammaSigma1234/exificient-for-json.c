#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EXIforJSONEncoder.h"
#include "EXIforJSONDecoder.h"

#define BUFFER_SIZE 128

int main(int argc, char *argv[])
{
  int errn = 0;
  char JSON_STRING_OUT[BUFFER_SIZE];
  uint8_t buffer[BUFFER_SIZE];
  size_t posEncode = 0;
  size_t posDecode = 0;
  unsigned char ch; // Use `unsigned char` (i.e. byte) to avoid interpreting bytes as negative numbers

  // Open EXI file in binary mode

  const char *fileName = argv[1];
  FILE *EXI_file = fopen(fileName, "rb");

  if (EXI_file == NULL)
  {
    printf("Error opening '%s'\n", fileName);
    return -1;
  }

  // Print binary content of EXI file

  printf("Content of EXI file:\n");
  unsigned int columnCounter = 0;
  while (fread(&ch, sizeof(unsigned char), 1, EXI_file) == 1) // Read one byte from `EXI_file` into `ch`. Fails when 0 bytes are read (EOF reached)
  {
    fprintf(stdout, "%02X ", ch); // Print the byte as a two-digit hexadecimal number
    ++columnCounter;
    if (columnCounter == 16)
    {
      putchar('\n');
      columnCounter = 0;
    }
  }

  printf("\n\n");

  // Read EXI file to `uint8_t` buffer

	unsigned long fileLen;

	// Get EXI_file length
	fseek(EXI_file, 0, SEEK_END);
	fileLen = ftell(EXI_file);
	fseek(EXI_file, 0, SEEK_SET);

	// Read EXI_file contents into buffer
	fread(buffer, fileLen, 1, EXI_file);  // Read into `buffer` `fileLen` bytes from `EXI_file`. Fails when 0 bytes are read (EOF reached)
	fclose(EXI_file);

  // Print again binary content of EXI file, but reading from buffer this time

  printf("Content of EXI file (from buffer):\n");
  columnCounter = 0;
  for (unsigned long i = 0; i != fileLen; ++i)
  {
    fprintf(stdout, "%02X ", buffer[i]); // Print the byte as a two-digit hexadecimal number
    ++columnCounter;
    if (columnCounter == 16)
    {
      putchar('\n');
      columnCounter = 0;
    }
  }

  printf("\n\n");

  /* Try to transform EXI to JSON */

  errn = decodeEXIforJSON(buffer, BUFFER_SIZE, &posDecode, JSON_STRING_OUT, BUFFER_SIZE);

  if( errn == 0 )
  {
    /* OK */
    printf("Decoding EXIforJSON (len=%lu) to JSON (len=%lu) was successful \n", posDecode, strlen(JSON_STRING_OUT));
    printf("TO: \n%s \n", JSON_STRING_OUT);
  } else
  {
    /* ERROR */
    printf("Decoding EXIforJSON to JSON failed due to error %d \n", errn);
  }

  return errn;
}
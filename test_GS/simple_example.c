#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EXIforJSONEncoder.h"
#include "EXIforJSONDecoder.h"

#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
  int errn = 0;

  // char *JSON_STRING_IN = "{\"keyNumber\":           123, \"keyArrayStrings\":  [     \"s1\",    \"s2\"   ]       }"; // (GS) Irregular number of spaces just to test whether they are correctly ignored by the encoder
  char *JSON_STRING_IN = // Copy-pasted and adapted from `EXI_sample_2.json`
  "{"
  "    \"V2G_Message\": {"
  "        \"Header\": {"
  "            \"SessionID\": \"D481F3E6AF8B227A\","
  "            \"Notification\": {"
  "                \"FaultCode\": \"ParsingError\","
  "                \"FaultMsg\": \"WeldingDetectionReq' not accepted in state <iso15118.secc.stat..\""
  "            }"
  "        },"
  "        \"Body\": {"
  "            \"WeldingDetectionRes\": {"
  "                \"ResponseCode\": \"FAILED_SequenceError\","
  "                \"DC_EVSEStatus\": {"
  "                    \"NotificationMaxDelay\": 0,"
  "                    \"EVSENotification\": \"None\","
  "                    \"EVSEIsolationStatus\": \"Valid\","
  "                    \"EVSEStatusCode\": \"EVSE_Ready\""
  "                },"
  "                \"EVSEPresentVoltage\": {"
  "                    \"Value\": 230,"
  "                    \"Multiplier\": 0,"
  "                    \"Unit\": \"V\""
  "                }"
  "            }"
  "        }"
  "    }"
  "}";

  const size_t lenOut = strlen(JSON_STRING_IN) + 100; /* some extra space for decoding differences e.g, number 1 -> 1E0 etc */
  char JSON_STRING_OUT[lenOut];

  uint8_t buffer[BUFFER_SIZE];
  size_t posEncode = 0;
  size_t posDecode = 0;

  printf("FROM: \n%s \n", JSON_STRING_IN);

  errn = encodeEXIforJSON(JSON_STRING_IN, strlen(JSON_STRING_IN), buffer, BUFFER_SIZE, &posEncode);
  if( errn == 0 )
  {
    /* OK so far */
    printf("Encoding JSON (len=%d) to EXIforJSON (len=%d) was successful \n", strlen(JSON_STRING_IN), posEncode);

    // (GS) print raw bytes to terminal

    unsigned char ch; // Use 'unsigned char' (i.e. byte) to avoid interpreting bytes as negative numbers

    printf("Content of buffer containing EXI file:\n");
    unsigned int columnCounter = 0;
    for (int i = 0; i != posEncode; ++i)
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

    /* Try to transform it back to JSON again */
    errn = decodeEXIforJSON(buffer, BUFFER_SIZE, &posDecode, JSON_STRING_OUT, lenOut);

    if( errn == 0 )
    {
      /* OK */
      printf("Decoding EXIforJSON (len=%d) to JSON (len=%d) was successful \n", posEncode, strlen(JSON_STRING_OUT));
      printf("TO: \n%s \n", JSON_STRING_OUT);
    } else
    {
      /* ERROR */
      printf("Decoding EXIforJSON to JSON failed due to error %d \n", errn);
    }
  } else
  {
    /* ERROR */
    printf("Encoding JSON to EXIforJSON failed due to error %d \n", errn);
  }

  return errn;
}
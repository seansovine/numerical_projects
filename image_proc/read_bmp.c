#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE.

#include "bmp.h"

/* Main. */

const char *FILENAME = "sample.bmp";

int main(void) {

  FILE *fp;
  BMPHeader *bmpHeader = NULL;
  BMPInfoHeader *infoHeader = NULL;

  if ((fp = fopen(FILENAME, "rb")) == NULL) {
    printf("Cannot open file: %s\n\n", FILENAME);
    exit(EXIT_FAILURE);
  }

  // Read headers and display info.
  bmpHeader = readHeader(fp);
  infoHeader = readInfoHeader(fp);
  printHeaderInfo(bmpHeader, infoHeader);

  // For now we only support 24-bit pixels.
  assert(infoHeader->bitcount == 24);

  // Read pixel data.
  Pixel *pixels = readPixels(bmpHeader, infoHeader, fp);

  // Clean-up.
  free(bmpHeader);
  fclose(fp);

  return EXIT_SUCCESS;
}

//  c && gcc -Wall read_bmp.c bmp.c -o read_bmp && echo "---" && ./read_bmp

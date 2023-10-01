#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE.
#include <string.h> // For strlen.

#include "bmp.h"

/* Main. */

// Expected to end with "".bmp";
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

  // Read pixel data and convert to grayscale.
  PixelData *pixData = readPixels(bmpHeader, infoHeader, fp);
  PixelData *gsPixData = convertToGrayscale(pixData);

  // Write result to "<FILENAME_NO_EXT>_grayscale.bmp";
  writeImageFile(fp, bmpHeader, infoHeader, gsPixData, FILENAME,
                 strlen(FILENAME));

  // Clean-up.
  free(pixData->pixels);
  free(pixData);
  free(gsPixData->pixels);
  free(gsPixData);
  free(bmpHeader);
  fclose(fp);

  return EXIT_SUCCESS;
}

//  c && gcc -Wall convert_gs.c bmp.c -o build/convert_gs && echo "---"
//    && ./build/convert_gs
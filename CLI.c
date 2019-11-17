#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

char* IMAGE_FILENAME = "bee.bmp";
char* TEXT_FILENAME = "beemoviescript.txt";
char* OUTPUT_FILENAME = "beeStegged.bmp";

int main(int argc, char *argv[])
{
  if(argc != 1 && argc != 4) {
		printf("ERROR: Run with no arguments or with 3 arguments: %s IMAGE_FILENAME TEXT_FILENAME OUTPUT_FILENAME", argv[0]);
		return -1;
	}
	if(argc == 4) {
		IMAGE_FILENAME = argv[1];
		TEXT_FILENAME = argv[2];
		OUTPUT_FILENAME = argv[3];
	}

  //openImageAsArray();
  openTextAsArray();
  return 0;
}

char* getImageName(){return IMAGE_FILENAME;}
char* getTextFileName(){return TEXT_FILENAME;}
char* getOutputName(){return OUTPUT_FILENAME;}

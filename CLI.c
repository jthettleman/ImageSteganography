#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

char* IMAGE_FILENAME = "bee.bmp";
char* TEXT_FILENAME = "beemoviescript.txt";
char* OUTPUT_FILENAME = "beeStegged.bmp";
char* OUTPUT_TEXT_FILENAME = "beeSteggedTextOutput.txt";

int main(int argc, char *argv[])
{
  if(argc != 1 && argc != 4 && argc!= 5) 
  {
		printf("ERROR: Please do the following:\n"
           "Run with no arguments to use the default image and text file"
           "To create a stegged image: %s -c IMAGE_FILENAME TEXT_FILENAME OUTPUT_BMP_FILENAME\n"
           "To read a stegged image: %s -r IMAGE_FILENAME OUTPUT_TEXT_FILENAME\n", argv[0], argv[0]);
		return -1;
	}
 
  if(argc == 1)
  {
    openImageAsArray();
    openTextAsArray();
    hackifyImage();
    rebuildImage();
    
    free(text_data);
  }
  
	else if(argc == 5) 
  {
		IMAGE_FILENAME = argv[2];
		TEXT_FILENAME = argv[3];
		OUTPUT_FILENAME = argv[4];
   
    openImageAsArray();
    openTextAsArray();
    hackifyImage();
    rebuildImage();
    
    free(text_data);
	}
  
  else
  {
    IMAGE_FILENAME = argv[2];
    OUTPUT_TEXT_FILENAME = argv[3];
    
    openImageAsArray();
    readHiddenData();
  }

  free(image_data);
  return 0;
}

//Totally not getters, don't let Binkley see this please :)
char* getImageName(){return IMAGE_FILENAME;}
char* getTextFileName(){return TEXT_FILENAME;}
char* getOutputName(){return OUTPUT_FILENAME;}
char* getOutputTextFileName(){return OUTPUT_TEXT_FILENAME;}

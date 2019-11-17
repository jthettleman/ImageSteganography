#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

int width;
int height;
int row_padding;
unsigned char image_info[54];

void openImageAsArray()
{
  FILE *fp;

  //Open Image
  if((fp = fopen(getImageName(), "rb")) == NULL)
  {
    printf("Error opening image\n");
    exit(1);
  }

  //Get bmp header information
  int success = fread(image_info, sizeof(unsigned char), 54, fp);
  if(success <= 1)
  {
    printf("Not a bmp file\n");
    exit(1);
  }

  //Get width and height of image
  width = *(int*)&image_info[18];
  height = *(int*)&image_info[22];
  row_padding = (width * 3 + 3) & (~3);
  printf("Height: %d", height);
  printf("Width: %d", width);
  printf("Row padding: %d", row_padding);
  //Allocate size
  image_data = (unsigned char*) malloc(row_padding*height);
  //int counter = 0;

  //Read pixel information

  success = fread(image_data, sizeof(unsigned char), row_padding*height, fp);
  if(success <= 1)
  {
    printf("Not a bmp file\n");
    exit(1);
  }

  //printf("Number of pixels: %d", counter);
  fclose(fp);
  return;
}

void hackifyImage()
{
  for(int j = 0; j < getTextFileSize(); j++)
  {
    const char* binary = byte_to_binary(image_data[j]);
    //printf("Binary: %s\n", binary);
    bool last_digit = (binary[7]==49 ? 1 : 0);
    //printf("Last: %d\n", last_digit);
    if(last_digit == text_data[j])
    {
      //Nothin
    }
    else
    {
      //printf("%d\n", last_digit);
      if(last_digit == 1)
      {
        //image_data[j] = image_data[j] & 254;
        image_data[j] = image_data[j] & 254;
      }
      else
      {
        image_data[j] = image_data[j] | 1;
      }
    }
  }
}

void rebuildImage()
{
  FILE* fp;
  if((fp = fopen(getOutputName(), "wb")) == NULL)
  {
    printf("Error creating image\n");
    exit(1);
  }

  fwrite(image_info, sizeof(unsigned char), 54, fp);
  fwrite(image_data, sizeof(unsigned char), row_padding*height, fp);

  printf("Made Image!\n");
}

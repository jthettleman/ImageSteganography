#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

int width;
int height;
int row_padding;

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
  unsigned char image_info[54];
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

  //Allocate size
  image_data = (unsigned char*) malloc(row_padding);
  int counter = 0;

  //Read pixel information
  for(int i = 0; i < height; i++)
  {
    success = fread(image_data, sizeof(unsigned char), row_padding, fp);
    if(success <= 1)
    {
      printf("Not a bmp file\n");
      exit(1);
    }

    for(int j = 0; j < width*3; j+=3)
    {
      unsigned char tmp = image_data[j];
      image_data[j] = image_data[j+2];
      image_data[j+2] = tmp;
      //printf("%x%x%x\n", (int)image_data[j], (int)image_data[j+1], (int)image_data[j+2]);
      //printf("%s\n%s\n%s\n", byte_to_binary(image_data[j]), byte_to_binary(image_data[j+1]), byte_to_binary(image_data[j+2]));
      counter++;
    }
  }

  printf("Number of pixels: %d", counter);
  fclose(fp);
  return;
}

void hackifyImage()
{
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width*3; j+=3)
    {
      const char* binary = byte_to_binary(image_data[j]);
      printf("%s\n", binary);
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

int width;
int height;
int row_padding;
unsigned char image_info[54];

//Opens a desired bmp image file as an array of B,G,R color values
//I.E. image_data[0-2] would have the B, G, and R pixel values and 
//then image_data[3-5] would have the second pixel color values
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
    printf("ERROR: Not a bmp file\n");
    exit(1);
  }

  //Get width and height of image and allocate for padding
  width = *(int*)&image_info[18];
  height = *(int*)&image_info[22];
  row_padding = (width * 3 + 3) & (~3);
  
  printf("%d --- %d", width, height);

  //Allocate size
  image_data = (unsigned char*) malloc(row_padding*height);
  //int counter = 0;

  //Read pixel information
  success = fread(image_data, sizeof(unsigned char), row_padding*height, fp);
  if(success <= 1)
  {
    printf("ERROR: Not a bmp file\n");
    exit(1);
  }

  fclose(fp);
  return;
}

//Modifies pixel values last bits to match those of the text_data bits
//to store text inside the image
void hackifyImage()
{
  if(row_padding*height < getTextFileSize())
  {
    printf("ERROR: Image is not large enough to store the text file provided\n");
    exit(1);
  }
  else
  {
    for(int j = 0; j < getTextFileSize(); j++)
    {
      //Stores single pixel value as a string
      const char* binary = byte_to_binary(image_data[j]);
      //Converts boolean to integer 1 or 0
      bool last_digit = (binary[7]==49 ? 1 : 0);
      
      if(last_digit == text_data[j])
      {
        //Pixel last bit already matches text file bit
      }
      else
      {
        if(last_digit == 1)
        {
          //Flips last bit from 1 to 0
          image_data[j] = image_data[j] & 254;
        }
        else
        {
          //Flips last bit from 0 to 1
          image_data[j] = image_data[j] | 1;
        }
      }
    }
  }
}

//Writes new pixel data to a new image file specified by the user
void rebuildImage()
{
  FILE* fp;
  if((fp = fopen(getOutputName(), "wb")) == NULL)
  {
    printf("Error creating image\n");
    exit(1);
  }

  //Writes bmp header and new data
  fwrite(image_info, sizeof(unsigned char), 54, fp);
  fwrite(image_data, sizeof(unsigned char), row_padding*height, fp);

  printf("SUCCESS: Image Created\n");
}

//Reads the hidden data inside of the image
void readHiddenData()
{
  FILE* fp;
  if((fp = fopen(getOutputTextFileName(), "wb")) == NULL)
  {
    printf("Error creating text file\n");
    exit(1);
  }

  unsigned char byte_buffer = ' ';
  byte_buffer = byte_buffer & 0;
  int byte_counter = 0;
  
  for(int i = 0; i < row_padding*height; i++)
    {
      //Stores single pixel value as a string
      const char* binary = byte_to_binary(image_data[i]);
      //Converts boolean to integer 1 or 0
      bool last_digit = (binary[7]==49 ? 1 : 0);
      
      if(byte_counter%8 == 0)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|128;
      }
      else if(byte_counter%8 == 1)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|64;
      }
      else if (byte_counter%8 == 2)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|32;
      }
      
      else if (byte_counter%8 == 3)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|16;
      }
      
      else if (byte_counter%8 == 4)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|8;
      }
      
      else if (byte_counter%8 == 5)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|4;
      }
      
      else if (byte_counter%8 == 6)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|2;
      }
      
      else if(byte_counter%8 == 7)
      {
        if(last_digit == 1)byte_buffer = byte_buffer|1;
        fwrite(&byte_buffer, 1, 1, fp);
        byte_buffer = byte_buffer & 0;
      }
    }
    fclose(fp);
}

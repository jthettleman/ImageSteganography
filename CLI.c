#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char input_image[] = "bee.bmp";
unsigned char* image_data;

unsigned char* openImageAsArray()
{
  FILE *fp;
  if((fp = fopen("bee.bmp", "rb")) == NULL)
  {
    printf("Error opening image\n");
    exit(1);
  }

  unsigned char image_info[54];
  int success = fread(image_info, sizeof(unsigned char), 54, fp);
  if(success <= 1)
  {
    printf("Not a bmp file\n");
    exit(1);
  }

  int width = *(int*)&image_info[18];
  int height = *(int*)&image_info[22];
  int row_padding = (width * 3 + 3) & (~3);

  image_data = (unsigned char*) malloc(row_padding);

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
      printf("%x%x%x\n", (int)image_data[j], (int)image_data[j+1], (int)image_data[j+2]);
    }
  }

  return image_data;
}

int main()
{
  openImageAsArray();
  return 0;
}

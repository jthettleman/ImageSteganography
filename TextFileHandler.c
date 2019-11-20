#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"


int SIZE;

char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void openTextAsArray()
{
    int placementCounter =0;
    FILE *sourceFile;
    char ch;


    //open the source file in read mode
    sourceFile = fopen(getTextFileName(), "r");
    size_t pos = ftell(sourceFile);
    fseek(sourceFile, 0, SEEK_END);
    size_t file_size = ftell(sourceFile);
    fseek(sourceFile, pos, SEEK_SET);
    SIZE = file_size*8;
    text_data = (bool*) malloc(SIZE);

    //error handling
    if (!sourceFile)
    {
            printf("Unable to open the input file!!\n");
            exit(1);
    }


    //read text from sourceFile, output to the targetFile as binary
    while (!feof(sourceFile))
    {
            //reading one byte of data
            int success = fread(&ch, sizeof(char), 1, sourceFile);
            if(success < 0)
            {
              printf("Read error\n");
              exit(1);
            }
            char* num = byte_to_binary(ch);
            for(int i=0;i<8;i++)
            {
              if ((int)num[i] == 49) //checking for a 1 in ASCII since reading from char*
              {
                text_data[placementCounter] = 1;
              }
              else
              {
                text_data[placementCounter] = 0;
              }
              placementCounter++;
            }
    }

    // close files
    fclose(sourceFile);
    //fclose(targetFile);
    return;
}

int getTextFileSize()
{
  return SIZE;
}

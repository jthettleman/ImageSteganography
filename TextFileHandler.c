#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"




const char *byte_to_binary(int x)
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

    int counter = 0;
    //int num;
    FILE *sourceFile;//, *targetFile;
    char ch;//, source[MAX_FILENAME], target[MAX_FILENAME];


    //open the source file in read mode
    sourceFile = fopen(getTextFileName(), "r");
    size_t pos = ftell(sourceFile);
    fseek(sourceFile, 0, SEEK_END);
    size_t file_size = ftell(sourceFile);
    fseek(sourceFile, pos, SEEK_SET);

    text_data = (bool*) malloc(file_size*8);

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
            //prints out hex
            //printf("%x\n", ch);

            text_data[counter] = ch;
            //byte to binary implemantation
            //printf("%s\n", byte_to_binary(ch));
            printf("%s\n", byte_to_binary(text_data[counter++]));

            // saving as a char as an int, turns it into an ascii value
            //converting the character to ascii integer value
            //num = ch;
            //writing 4 byte of data to the output file
            //fwrite(&num, sizeof(int), 1, targetFile);
    }

    printf("Number of characters: %d", counter);

    // close files
    fclose(sourceFile);
    //fclose(targetFile);
    return;
}
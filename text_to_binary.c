

  #include <stdio.h>
  #include <string.h>
  #define MAX 256

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



  int main() {
        int num;
        FILE *sourceFile, *targetFile;
        char ch, source[MAX], target[MAX];

        //get the input file name from the user
        printf("Enter your input file name:");
        scanf("%s", source);

        //get the output filename from the user
        printf("Enter your output file name:");
        scanf("%s", target);

        //open the source file in read mode
        sourceFile = fopen(source, "r");

        //error handling
        if (!sourceFile)
        {
                printf("Unable to open the input file!!\n");
                return 0;
        }

        // open the target file in binary write mode
        targetFile = fopen(target, "wb");

        // error handling
        if (!targetFile)
        {
                printf("Unable to open the output file!!\n");
                return 0;
        }


        //read text from sourceFile, output to the targetFile as binary
        while (!feof(sourceFile))
        {
                //reading one byte of data
                fread(&ch, sizeof(char), 1, sourceFile);

                 // prints out hex
              //  printf("%x\n", ch);

                //byte to binary implemantation
                printf("%s\n", byte_to_binary(ch));

                // saving as a char as an int, turns it into an ascii value
                //converting the character to ascii integer value
                num = ch;
                //writing 4 byte of data to the output file
                fwrite(&num, sizeof(int), 1, targetFile);
        }

        // close files
        fclose(sourceFile);
        fclose(targetFile);

        return 0;
  }



  #include <stdio.h>
  #include <string.h>
  #define MAX 256

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
                fread(&num, sizeof(int), 1, sourceFile);

                //converting the character to ascii integer value
                ch = num;

                //writing 4 byte of data to the output file
                fwrite(&ch, sizeof(char), 1, targetFile);
        }

        // close files
        fclose(sourceFile);
        fclose(targetFile);

        return 0;
  }

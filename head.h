#include <stdbool.h>
#define MAX_FILENAME 256

unsigned char* image_data;
bool* text_data;

void openImageAsArray();
void openTextAsArray();
void hackifyImage();
void rebuildImage();
void readHiddenData();

int getTextFileSize();

char* getImageName();
char* getTextFileName();
char* getOutputName();
char* getOutputTextFileName();
char* byte_to_binary(int x);
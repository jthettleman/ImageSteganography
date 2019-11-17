#include <stdbool.h>
#define MAX_FILENAME 256

unsigned char* image_data;
bool* text_data;
void openImageAsArray();
void openTextAsArray();
char* getImageName();
char* getTextFileName();
char* getOutputName();

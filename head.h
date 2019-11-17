#include <stdbool.h>
#define MAX_FILENAME 256

unsigned char* image_data;
bool* text_data;
void openImageAsArray();
void openTextAsArray();
void hackifyImage();
char* getImageName();
char* getTextFileName();
char* getOutputName();
const char *byte_to_binary(int x);

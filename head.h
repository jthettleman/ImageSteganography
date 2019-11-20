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

typedef struct                        // Total: 54 bytes
{              
  unsigned short int type;            // File type
  unsigned int size;                  // File size in bytes
  unsigned short int reserved1;       // Not used
  unsigned short int reserved2;       // Not used
  unsigned int offset;                // Offset to image data in bytes from beginning of file (54 bytes)
  unsigned int dib_header_size;       // DIB Header size in bytes (40 bytes)
  int width;                          // Width of the image
  int height;                         // Height of image
  unsigned short int num_planes;      // Number of color planes
  unsigned short int bits_per_pixel;  // Bits per pixel
  unsigned int compression;           // Compression type
  unsigned int image_size_bytes;      // Image size in bytes
  int x_resolution_ppm;               // Pixels per meter
  int y_resolution_ppm;               // Pixels per meter
  unsigned int num_colors;            // Number of colors  
  unsigned int important_colors;      // Important colors 
} BMPHeader;
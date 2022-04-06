#include <png.h>
#include <errno.h>
#include <stdbool.h>
#include "encoder.h"


struct _PngData
{
    png_structp png_p;
    png_infop info_p;
};


bool is_png(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("An error occured while opening the file");
        return false;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);
    fclose(fp);

    return png_sig_cmp(header, 0, 8) == 0;
}


bool encode_into(const char *filename, const char *string) {
    return false;
}


const char* decode_from(const char *filename) {
    
    return "";
}
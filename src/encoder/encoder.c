#include <png.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include "encoder.h"

const char* _FILENAME_SUFFIX = "_encoded";

struct _PngData
{
    png_structp png_p;
    png_infop info_p;
};


char* _addSuffixToFileName(const char* fileName, const char *suffix) {
    const int FILE_NAME_LENGTH = strlen(fileName);
    const int SUFFIX_LENGTH = strlen(suffix);

    const int NEW_FILE_NAME_LENGTH = FILE_NAME_LENGTH + SUFFIX_LENGTH;
    char *newFileName = malloc(sizeof(char) * (NEW_FILE_NAME_LENGTH + 1));

    char *lastDotInFileName = strrchr(fileName, '.');
    if(!lastDotInFileName)
    {
        strncpy(newFileName, fileName, FILE_NAME_LENGTH);
        strncpy(newFileName+FILE_NAME_LENGTH, suffix, SUFFIX_LENGTH);
    }

    return newFileName;
}


bool isPng(const char *fileName) {
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        perror("An error occured while opening the file");
        return false;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);
    fclose(fp);

    return png_sig_cmp(header, 0, 8) == 0;
}


bool encodeInto(const char *fileName, const char *string) {
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    png_image_begin_read_from_file(&image, fileName);
    image.format = PNG_FORMAT_ARGB;

    const int IMAGE_BUFFER_SIZE = image.height * image.width * 4;
    png_bytep imageBuffer = malloc(IMAGE_BUFFER_SIZE);
    png_image_finish_read(&image, NULL, imageBuffer, 0, NULL);

    //TODO: manipulate image here!

    char* newFileName = _addSuffixToFileName(fileName, _FILENAME_SUFFIX);
    png_image_write_to_file(&image, newFileName, 0, imageBuffer, 0, NULL);

    free(newFileName);
    free(imageBuffer);

    return false;
}


const char* decodeFrom(const char *fileName) {
    
    return "";
}
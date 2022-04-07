#include <png.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <zlib.h>
#include "encoder.h"

const char* _FILENAME_SUFFIX = "_encoded";

struct _PngData
{
    png_structp png_p;
    png_infop info_p;
};


void addSuffixToFileName(const char* fileName, const char *suffix, char *buffer, const int bufferSize) {
    const int FILE_NAME_LENGTH = strlen(fileName);
    const int SUFFIX_LENGTH = strlen(suffix);

    char *lastDotInFileName = strrchr(fileName, '.');
    if(!lastDotInFileName)
    {
        // Just copy the suffix to the end of the string
        strncpy(buffer, fileName, bufferSize);
        strncpy((buffer+FILE_NAME_LENGTH), suffix, (bufferSize-FILE_NAME_LENGTH));
    } else {
        // Copy the suffix before the last dot
        const int CHARS_TO_DOT = (intptr_t)lastDotInFileName - (intptr_t)fileName;
        strncpy(buffer, fileName, CHARS_TO_DOT);
        strncpy((buffer+CHARS_TO_DOT), suffix, (bufferSize-CHARS_TO_DOT));
        strncpy((buffer+CHARS_TO_DOT+SUFFIX_LENGTH), lastDotInFileName, (bufferSize-CHARS_TO_DOT-SUFFIX_LENGTH));
    }
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


bool encodeIntoFile(const char *fileName, const char *string) {
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    png_image_begin_read_from_file(&image, fileName);
    image.format = PNG_FORMAT_RGBA;

    const int IMAGE_PIXEL_COUNT = image.height * image.width;
    const int IMAGE_BUFFER_SIZE = IMAGE_PIXEL_COUNT * 4; // +4 values for every pixel (Because of RGBA)
    png_bytep imageBuffer = malloc(IMAGE_BUFFER_SIZE);
    png_image_finish_read(&image, NULL, imageBuffer, 0, NULL);
    // png_image_free(&image); // Not necessary because png_image_finish_read does this automatically

    png_bytep pBuf = imageBuffer;
    const char *chr = string;
    for (uint64_t i = 0; i < IMAGE_PIXEL_COUNT; ++i)
    {
        pBuf[0] = (pBuf[0] & ~0x3) | ((*chr) & 0x3);
        pBuf[1] = (pBuf[1] & ~0x3) | (((*chr) >> 2) & (0x3));
        pBuf[2] = (pBuf[2] & ~0x3) | (((*chr) >> 4) & (0x3));
        pBuf[3] = (pBuf[3] & ~0x3) | (((*chr) >> 6) & (0x3));

        if(*chr == 0)
            break;

        pBuf += 4;
        ++chr;
    }

    const int FILE_NAME_LENGTH = strlen(fileName);
    const int SUFFIX_LENGTH = strlen(_FILENAME_SUFFIX);
    const int NEW_FILE_NAME_LENGTH = (FILE_NAME_LENGTH+SUFFIX_LENGTH+1);
    char* newFileName = malloc(sizeof(char) * NEW_FILE_NAME_LENGTH);
    addSuffixToFileName(fileName, _FILENAME_SUFFIX, newFileName, NEW_FILE_NAME_LENGTH);
    
    png_image_write_to_file(&image, newFileName, 0, imageBuffer, 0, NULL);
    //png_image_free(&image); // Not necessary because png_image_write_to_file does this automatically

    free(newFileName);
    free(imageBuffer);

    return false;
}


const char* decodeFromFile(const char *fileName) {
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    png_image_begin_read_from_file(&image, fileName);
    image.format = PNG_FORMAT_RGBA;

    const int IMAGE_PIXEL_COUNT = image.height * image.width;
    const int IMAGE_BUFFER_SIZE = IMAGE_PIXEL_COUNT * 4; // +4 values for every pixel (Because of RGBA)
    png_bytep imageBuffer = malloc(IMAGE_BUFFER_SIZE);
    png_image_finish_read(&image, NULL, imageBuffer, 0, NULL);
    //png_image_free(&image); // Not necessary because png_image_finish_read does this automatically

    const int MSG_BUFFER_SIZE = sizeof(char) * IMAGE_PIXEL_COUNT;
    char *messageBuffer = malloc(MSG_BUFFER_SIZE);
    memset(messageBuffer, 0, MSG_BUFFER_SIZE);

    png_bytep pBuf = imageBuffer;
    char *msgBuf = messageBuffer;
    for (uint64_t i = 0; i < IMAGE_PIXEL_COUNT; ++i)
    {
       (*msgBuf) = (pBuf[0] & 0x3)
                 | ((pBuf[1] & 0x3) << 2)
                 | ((pBuf[2] & 0x3) << 4)
                 | ((pBuf[3] & 0x3) << 6);
        
        if(*msgBuf == 0)
            break;

        ++msgBuf;
        pBuf += 4;
    }

    free(imageBuffer);
    return messageBuffer;
}
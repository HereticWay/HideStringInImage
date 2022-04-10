#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <png.h>
#include "message_hider.h"

#define FILENAME_SUFFIX "_with_hidden_msg"


char *addSuffixToFileName(const char *fileName, const char *suffix)
{
    const unsigned int fileNameLength = strlen(fileName);
    const unsigned int suffixLength = strlen(suffix);

    const unsigned int bufferSize = (fileNameLength + suffixLength + 1);
    char *buffer = malloc(sizeof(char) * bufferSize);

    char *lastDotInFileName = strrchr(fileName, '.');
    if (!lastDotInFileName)
    {
        // Just copy the suffix to the end of the string
        strcpy(buffer, fileName);
        strcpy((buffer + fileNameLength), suffix);
    } else
    {
        // Copy the suffix before the last dot
        const unsigned int charsCountToFirstDot = lastDotInFileName - fileName;
        strncpy(buffer, fileName, charsCountToFirstDot);
        strcpy((buffer + charsCountToFirstDot), suffix);
        strcpy((buffer + charsCountToFirstDot + suffixLength), lastDotInFileName);
    }

    return buffer;
}


bool isPng(const char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if (file == NULL)
    {
        perror("An error occurred while opening the file");
        return false;
    }

    png_byte header[8];
    fread(header, 1, 8, file);
    fclose(file);

    return png_sig_cmp(header, 0, 8) == 0;
}


void codeMessageIntoImage(const char *fileName, const char *message)
{
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    png_image_begin_read_from_file(&image, fileName);
    image.format = PNG_FORMAT_RGBA;

    const uint64_t imagePixelCount = image.height * image.width;
    const uint64_t imageBufferSize = imagePixelCount * 4; // +4 values for every pixel (Because of RGBA)
    png_bytep imageBuffer = malloc(imageBufferSize);
    png_image_finish_read(&image, NULL, imageBuffer, 0, NULL);
    // png_image_free(&image); // Not necessary because png_image_finish_read does this automatically

    png_bytep imgBuf = imageBuffer;
    const char *msgChar = message;
    for (uint64_t i = 0; i < imagePixelCount; ++i)
    {
        imgBuf[0] = (imgBuf[0] & ~0x3) | ((*msgChar) & 0x3);
        imgBuf[1] = (imgBuf[1] & ~0x3) | (((*msgChar) >> 2) & (0x3));
        imgBuf[2] = (imgBuf[2] & ~0x3) | (((*msgChar) >> 4) & (0x3));
        imgBuf[3] = (imgBuf[3] & ~0x3) | (((*msgChar) >> 6) & (0x3));

        if (*msgChar == 0)
            break;

        imgBuf += 4;
        ++msgChar;
    }

    char *newFileName = addSuffixToFileName(fileName, FILENAME_SUFFIX);
    png_image_write_to_file(&image, newFileName, 0, imageBuffer, 0, NULL);
    //png_image_free(&image); // Not necessary because png_image_write_to_file does this automatically

    free(newFileName);
    free(imageBuffer);
}


char *decodeMessageFromImage(const char *fileName)
{
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    png_image_begin_read_from_file(&image, fileName);
    image.format = PNG_FORMAT_RGBA;

    const uint64_t imagePixelCount = image.height * image.width;
    const uint64_t imageBufferSize = imagePixelCount * 4; // +4 values for every pixel (Because of RGBA)
    png_bytep imageBuffer = malloc(imageBufferSize);
    png_image_finish_read(&image, NULL, imageBuffer, 0, NULL);
    //png_image_free(&image); // Not necessary because png_image_finish_read does this automatically

    const uint64_t messageBufferSize = sizeof(char) * imagePixelCount;
    unsigned char *messageBuffer = malloc(messageBufferSize);
    memset(messageBuffer, 0, messageBufferSize);

    png_bytep imgBuf = imageBuffer;
    unsigned char *msgBuf = messageBuffer;
    for (uint64_t i = 0; i < imagePixelCount; ++i)
    {
        (*msgBuf) = (imgBuf[0] & 0x3)
                    | ((imgBuf[1] & 0x3) << 2)
                    | ((imgBuf[2] & 0x3) << 4)
                    | ((imgBuf[3] & 0x3) << 6);

        if (*msgBuf == 0)
            break;

        ++msgBuf;
        imgBuf += 4;
    }

    free(imageBuffer);
    return messageBuffer;
}
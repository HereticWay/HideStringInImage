#ifndef MESSAGE_HIDER_H
#define MESSAGE_HIDER_H

#include <stdbool.h>


bool isPng(const char *filename);

void codeMessageIntoImage(const char *fileName, const char *message);

char *decodeMessageFromImage(const char *fileName);

#endif
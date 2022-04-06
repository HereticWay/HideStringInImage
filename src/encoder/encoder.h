#ifndef ENCODER_H
#define ENCODER_H

bool isPng(const char *filename);
bool encodeIntoFile(const char *filename, const char *string);
const char* decodeFromFile(const char *filename);

#endif
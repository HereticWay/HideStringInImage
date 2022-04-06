#ifndef ENCODER_H
#define ENCODER_H

bool isPng(const char *filename);
bool encodeInto(const char *filename, const char *string);
const char* decodeFrom(const char *filename);

#endif
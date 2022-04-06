#ifndef ENCODER_H
#define ENCODER_H

bool is_png(const char *filename);
bool encode_into(const char *filename, const char *string);
const char* decode_from(const char *filename);

#endif
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "encoder/encoder.h"


int main(int argc, char**argv) {
    const char* FILE_PATH = "./test.png";
    printf("The provided file %s a png.\n", isPng(FILE_PATH) ? "IS" : "IS NOT");

    return 0;
}

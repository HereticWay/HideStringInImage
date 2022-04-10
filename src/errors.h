#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>


#define INFO_TO_LOG(...) \
    printf(__VA_ARGS__)

#define ERROR_TO_LOG(...) \
    fprintf(stderr, __VA_ARGS__)

#ifdef DEBUG
#define DEBUG_TO_LOG(...) \
    printf(__VA_ARGS__)
#else
#define DEBUG_TO_LOG(...) ;
#endif //DEBUG


#endif //ERRORS_H

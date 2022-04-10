#include <stdio.h>
#include <stdlib.h>
#include "message_hider/message_hider.h"


int main(int argc, char **argv)
{
    const char *FILE_PATH = "./test.png";
    if(!isPng(FILE_PATH))
    {
        printf("The provided file is not a png!\n");
        return 1;
    }

    codeMessageIntoImage(FILE_PATH, "Test message hidden in a png image.");

    char *decodedMessage = decodeMessageFromImage("./test_with_hidden_msg.png");
    printf("Message: %s\n", decodedMessage);
    free(decodedMessage);

    return 0;
}

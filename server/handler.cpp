#include "./defaultIncludes.h"

char *handleConnection(const char *message) {
    char *response = (char*)malloc(255*sizeof(char));
    sprintf(response, message, 255);

    return response;
}

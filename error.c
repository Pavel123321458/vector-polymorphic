#include "error.h"
#include <string.h>

static Error error = {ERROR_NONE, NULL};

void set_error(ErrorCode code, const char* message){
    error.code = code;
    error.message = message;
}

Error get_error(void){
    Error err = error;
    error.code = ERROR_NONE;
    error.message = NULL;
    return err;
}

int has_error(void){
    return error.code != ERROR_NONE;
}
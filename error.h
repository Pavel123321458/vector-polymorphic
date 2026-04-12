#ifdef __cplusplus
extern "C" {
#endif

#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_NONE,
    ERROR_NULL_VECTOR,
    ERROR_NULL_ELEMENT,
    ERROR_DIFFERENT_TYPES,
    ERROR_DIFFERENT_SIZES,
    ERROR_OUT_OF_BOUNDS
} ErrorCode;

typedef struct {
    ErrorCode code;
    const char* message;
} Error;

void set_error(ErrorCode code, const char* message);
Error get_error(void);
int has_error(void);

#endif

#ifdef __cplusplus
}
#endif
#ifndef IMAGE_TRANSFORMER_FILE_HANDLER_H
#define IMAGE_TRANSFORMER_FILE_HANDLER_H

#include "image.h"
#include <stdio.h>


/*  deserializer   */
enum read_status {
    READ_OK = 0,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* коды других ошибок  */
};

/*  serializer   */
enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

#endif //IMAGE_TRANSFORMER_FILE_HANDLER_H

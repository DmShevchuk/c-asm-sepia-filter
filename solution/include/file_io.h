#ifndef IMAGE_TRANSFORMER_FILE_IO_H
#define IMAGE_TRANSFORMER_FILE_IO_H

#include <stdbool.h>
#include <stdio.h>

bool open_file(FILE** const file, char* const name, char* const mode);

bool close_file(FILE** const file);

#endif //IMAGE_TRANSFORMER_FILE_IO_H

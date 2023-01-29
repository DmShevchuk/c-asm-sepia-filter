#ifndef IMAGE_TRANSFORMER_BMP_HANDLER_H
#define IMAGE_TRANSFORMER_BMP_HANDLER_H

#include "bmp.h"
#include "file_handler.h"
#include "image.h"
#include <stdbool.h>
#include <stdio.h>

enum write_status to_bmp(FILE *const output_image, struct image const *img);

bool read_pixels(FILE *const input_file, struct image *struct_image, struct bmp_header header);

enum read_status from_bmp(FILE *const input_file, struct image *struct_image);

bool write_pixels(FILE *const output_image, struct image const *struct_image);

#endif //IMAGE_TRANSFORMER_BMP_HANDLER_H

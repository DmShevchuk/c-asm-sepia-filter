#include "../include/bmp.h"
#include "../include/file_handler.h"
#include "../include/image_handler.h"
#include <stdbool.h>
#include <stdio.h>


size_t get_padding(const uint32_t width);


bool read_pixels(FILE *const input_file, struct image *struct_image, struct bmp_header header) {

    size_t padding = get_padding(header.biWidth);
    for (size_t i = 0; i < (*struct_image).height; ++i) {
        if (fread((*struct_image).data + (i * (*struct_image).width),
                  sizeof(struct pixel), (*struct_image).width, input_file) != (*struct_image).width) {
            destroy_image(struct_image);
            return false;
        }

        if (fseek(input_file, (long) padding, SEEK_CUR) != 0) {
            destroy_image(struct_image);
            return false;
        }
    }
    return true;
}

enum read_status from_bmp(FILE *const input_file, struct image *struct_image) {
    size_t COUNT = 1;
    struct bmp_header header = {0};

    size_t count = fread(&header, sizeof(struct bmp_header), COUNT, input_file);
    if (count != 1) {
        return READ_INVALID_HEADER;
    }

    *struct_image = get_image(header.biWidth, header.biHeight);

    return read_pixels(input_file, struct_image, header) ? READ_OK : READ_INVALID_BITS;
}

#include "../include/bmp.h"
#include "../include/file_handler.h"
#include "../include/header_creator.h"
#include <stdbool.h>
#include <stdio.h>

size_t get_padding(const uint32_t width);

bool write_pixels(FILE *const output_image, struct image const *struct_image) {
    size_t COUNT = 1;
    uint64_t new_padding = 0;

    size_t padding = get_padding((*struct_image).width);
    for (size_t i = 0; i < (*struct_image).height; i++) {
        if (fwrite((*struct_image).data + (i * (*struct_image).width),
                   sizeof(struct pixel), (*struct_image).width, output_image) != (*struct_image).width) {
            return false;
        }

        for (size_t j = 0; j < padding; j++) {
            if (!fwrite(&new_padding, sizeof(uint8_t), COUNT, output_image)) {
                return false;
            }
        }
    }

    return true;
}

enum write_status to_bmp(FILE *const output_image, struct image const *struct_image) {
    size_t COUNT = 1;
    struct bmp_header header = create_header(struct_image);

    if (!fwrite(&header, sizeof(struct bmp_header), COUNT, output_image)) {
        return WRITE_ERROR;
    }
    return write_pixels(output_image, struct_image) ? WRITE_OK : WRITE_ERROR;
}



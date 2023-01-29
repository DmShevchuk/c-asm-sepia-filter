#include "../include/image.h"

#include "malloc.h"
#include "stdint.h"

struct image get_image(const uint64_t width, const uint64_t height) {
    struct image image = {
            .width = width,
            .height = height,
            .data = malloc(width * height * sizeof(struct pixel))
    };
    return image;
}

void destroy_image(struct image *image) {
    free((*image).data);
}

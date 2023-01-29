#include "../include/image.h"
#include "../include/image_handler.h"
#include "../include/rotate.h"
#include "stdio.h"

void set_pixel(const struct image *image, uint64_t x, uint64_t y, const struct pixel new_pixel) {
    if ((*image).data == NULL) {
        return;
    }
    (*image).data[y * (*image).width + x] = new_pixel;
}


struct image rotate(const struct image *source_image) {

    struct image image = get_image((*source_image).height, (*source_image).width);

    for (size_t height_counter = 0; height_counter < (*source_image).height; height_counter++) {
        for (size_t width_counter = 0; width_counter < (*source_image).width; width_counter++) {
            set_pixel(&image,
                      (*source_image).height - 1 - height_counter,
                      width_counter,
                      (*source_image).data[height_counter * (*source_image).width + width_counter]
            );
        }
    }

    return image;
}

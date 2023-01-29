//
// Created by dmitr on 21.01.2023.
//
#include "../include/image.h"
#include "../include/image_handler.h"
#include "../include/sepia.h"
#include <stdio.h>

void insert_pixel(const struct image *image, uint64_t x, uint64_t y, const struct pixel new_pixel) {
    if ((*image).data == NULL) {
        return;
    }
    (*image).data[x * (*image).width + y] = new_pixel;
}

static unsigned char count_color(uint64_t x) {
    if (x < 256)
        return x;
    return 255;
}

static struct pixel apply_sepia(struct pixel pixel) {
    /**
     * Массив для расчета по формуле
     *
     * r = (0.393 * old_r + 0.769 * old_g + 0.189 * old_b);
     * g = (0.349 * old_r + 0.686 * old_g + 0.168 * old_b);
     * b = (0.272 * old_r + 0.534 * old_g + 0.131 * old_b);
     *
     * */
    const float f[3][3] = {
            {0.393, 0.769, 0.189},
            {0.349, 0.686, 0.168},
            {0.272, 0.534, 0.131}
    };

    float r = count_color(f[0][0] * pixel.r + f[0][1] * pixel.g + f[0][2] * pixel.b);
    float g = count_color(f[1][0] * pixel.r + f[1][1] * pixel.g + f[1][2] * pixel.b);
    float b = count_color(f[2][0] * pixel.r + f[2][1] * pixel.g + f[2][2] * pixel.b);

    struct pixel result = {0};

    result.r = r;
    result.g = g;
    result.b = b;

    return result;
}


extern struct pixel *get_pixel(const struct image *img, const size_t x, const size_t y) {
    return &img->data[x * img->width + y];
}

struct image sepia_filter(const struct image *source_image) {
    struct image image = get_image((*source_image).width, (*source_image).height);

    for (size_t height_counter = 0; height_counter < (*source_image).height; height_counter++) {
        for (size_t width_counter = 0; width_counter < (*source_image).width; width_counter++) {
            insert_pixel(&image,
                         height_counter,
                         width_counter,
                         apply_sepia(*get_pixel(source_image, height_counter, width_counter))
            );
        }
    }
    return image;
}

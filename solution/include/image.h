#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H

#include  <stdint.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};


#endif //IMAGE_TRANSFORMER_IMAGE_H

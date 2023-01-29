#ifndef IMAGE_TRANSFORMER_IMAGE_HANDLER_H
#define IMAGE_TRANSFORMER_IMAGE_HANDLER_H

#include  <stdint.h>

struct image get_image(const uint64_t width, const uint64_t height);

void destroy_image(struct image *image);

#endif //IMAGE_TRANSFORMER_IMAGE_HANDLER_H

#include "../include/bmp.h"
#include "../include/header_creator.h"
#include <stdio.h>

#define BMP_HEADER_TYPE 0x4D42
#define BMP_HEADER_PLANES 1
#define BMP_HEADER_INFO_SIZE 40
#define BMP_HEADER_RESERVED 0
#define BMP_BIT_COUNT 24
#define BMP_COMPRESSION 0
#define BMP_XY_PER_METER 0
#define BMP_USED 0
#define BMP_IMPORTANT 0


size_t get_padding(const size_t width) {
    if (width % 4 == 0) return 0;
    return ((width * 3 / 4) + 1) * 4 - width * 3;
}

struct bmp_header create_header(const struct image *image) {
    uint64_t pixel_size = sizeof(struct pixel);
    uint64_t header_size = sizeof(struct bmp_header);

    size_t size = ((*image).width + get_padding((*image).width)) * (*image).height * pixel_size;
    uint64_t bfileSize = size + header_size;

    struct bmp_header bmp_header = {
            .bfType = BMP_HEADER_TYPE,
            .bfileSize = bfileSize,
            .bfReserved = BMP_HEADER_RESERVED,
            .bOffBits = header_size,
            .biSize = BMP_HEADER_INFO_SIZE,
            .biWidth = (*image).width,
            .biHeight = (*image).height,
            .biPlanes = BMP_HEADER_PLANES,
            .biBitCount = BMP_BIT_COUNT,
            .biCompression = BMP_COMPRESSION,
            .biSizeImage = size,
            .biXPelsPerMeter = BMP_XY_PER_METER,
            .biYPelsPerMeter = BMP_XY_PER_METER,
            .biClrUsed = BMP_USED,
            .biClrImportant = BMP_IMPORTANT,
    };

    return bmp_header;
}

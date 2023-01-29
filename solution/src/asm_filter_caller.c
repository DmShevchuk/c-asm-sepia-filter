//
// Created by dmitr on 22.01.2023.
//
#include "../include/image.h"
#include "../include/asm_filter_caller.h"
#include <stdio.h>

/**
 * Функция определена в файле sepia_filter.asm
 * */
extern void sepia_fast(float buff[12]);


static unsigned char count_color(uint64_t x) {
    if (x < 256)
        return x;
    return 255;
}


static void create_buffer(const struct pixel *p, float buff[12]) {
    for (size_t i = 0; i < 4; i++) {
        buff[i] = p->r;
        buff[i + 4] = p->g;
        buff[i + 8] = p->b;
    }
}

static void apply_filter_to_pixel(struct pixel *const p, const float buff[12]) {
    p->r = count_color(buff[0]);
    p->g = count_color(buff[1]);
    p->b = count_color(buff[2]);
}

static void generate_new_pixel(struct pixel *const p) {
    float buff[12];
    create_buffer(p, buff);
    sepia_fast(buff);
    apply_filter_to_pixel(p, buff);
}


struct image call_asm_filter(struct image img) {

    for (size_t x = 0; x < img.height; x++) {
        for (size_t y = 0; y < img.width; y+=4) {
            generate_new_pixel(&img.data[x * img.width + y + 0]);
            generate_new_pixel(&img.data[x * img.width + y + 1]);
            generate_new_pixel(&img.data[x * img.width + y + 2]);
            generate_new_pixel(&img.data[x * img.width + y + 3]);
        }
    }

    return img;
}

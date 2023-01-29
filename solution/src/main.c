#include "../include/bmp_handler.h"
#include "../include/file_io.h"
#include "../include/image_handler.h"
#include "../include/rotate.h"
#include "../include/sepia.h"
#include "../include/asm_filter_caller.h"

#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    FILE *input = NULL;
    FILE *output = NULL;

    char *run_mode = NULL;

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    if (argc == 4){
        run_mode = argv[3];
    }else{
        run_mode = "t";
    }

    if (!open_file(&input, input_file_name, "rb")) {
        return 1;
    }

    struct image img = {0};

    enum read_status status = from_bmp(input, &img);
    if (status != READ_OK) {
        destroy_image(&img);
        return 1;
    }

    if (!close_file(&input)) {
        destroy_image(&img);
        return 1;
    }

    if (*run_mode == 'c'){

        img = sepia_filter(&img);
        printf("The filter on C has been applied!\n");

    } else if(*run_mode == 'a'){

        img = call_asm_filter(img);
        printf("The filter on ASM has been applied!\n");

    }else{

        double asm_time_counter = 0;

        for (uint8_t i = 0; i < 10; i++) {
            clock_t begin = clock();

            img = call_asm_filter(img);

            clock_t end = clock();
            asm_time_counter += (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC;
        }

        printf("Average ASM execution time (ms): %f\n", asm_time_counter / 5);

        double c_time_counter = 0;

        for (uint8_t i = 0; i < 10; i++) {
            clock_t begin = clock();

            img = sepia_filter(&img);

            clock_t end = clock();
            c_time_counter += (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC;
        }

        printf("Average C execution time (ms): %f\n", c_time_counter / 5);


        printf("-------------------------------------\n");
        printf("The resulting acceleration %f\n", c_time_counter / asm_time_counter);

    }


    if (!open_file(&output, output_file_name, "wb")) {
        destroy_image(&img);
        return 1;
    }

    enum write_status write_status = to_bmp(output, &img);
    if (write_status != WRITE_OK) {
        destroy_image(&img);
        return 1;
    }

    if (!close_file(&output)) {
        destroy_image(&img);
        return 1;
    }

    destroy_image(&img);
    return 0;
}

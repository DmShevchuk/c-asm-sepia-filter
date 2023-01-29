#include "../include/file_io.h"


bool open_file(FILE** const file, char* const name, char* const mode){
    *file = fopen(name, mode);
    return (*file == NULL) ? false : true;
}

bool close_file(FILE** const file){
    return (fclose(*file) == 0) ? true : false;
}


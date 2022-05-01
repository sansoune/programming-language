#include "../includes/util.h"

char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        printf("file not found\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*) malloc(sizeof(char) * (size + 1));
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);

    return buffer;
}
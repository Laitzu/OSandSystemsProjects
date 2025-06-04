#include <stdio.h>
#include <stdlib.h>

FILE* openFile(char *fileName, char *mode);
void decompressFile(FILE* file);

int main(int argc, char* argv[]) {

    FILE* file = NULL;

    // Check that parameters (files are given)
    if(argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    // For loop to open and decompress multiple files (if given)
    for(int i = 1; i < argc; i++) {
        // Open the file for reading
        file = openFile(argv[i], "r");
        // Decompress the current file
        decompressFile(file);
        // Close file
        fclose(file);
    }

    return 0;
}

FILE* openFile(char *fileName, char *mode) {
    FILE *file;

    // Open the file with the given mode
    if((file = fopen(fileName, mode)) == NULL) {
        printf("my-unzip: cannot open file\n");
        exit(1);
    }
    return file;
}


void decompressFile(FILE* file) {

    // To keep track of how many of the current char there are
    int count = 0;
    // Current char
    char c;

    // Keep looping while fread can read an integer AND a character from the file
    while(fread(&count, sizeof(int), 1, file) == 1 && fread(&c, sizeof(char), 1, file) == 1) {

        // Print the given character as many times as count implies
        for(int i = 0; i < count; i++) {
            printf("%c", c);
        }
    }

    return;
}
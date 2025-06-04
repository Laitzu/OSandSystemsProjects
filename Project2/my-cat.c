#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char *fileName, char *mode);
void readAndPrintLines(FILE* file);


int main(int argc, char* argv[]) {
    FILE* file = NULL;

    // Check that a file or file(s) were given
    if(argc < 2) {
        exit(0);
    }

    // For loop to open and print multiple files
    for(int i = 1; i < argc; i++) {
        // Open the file for reading
        file = openFile(argv[i], "r");
        // Print the lines inside the file
        readAndPrintLines(file);
        // Close file
        fclose(file);
    }

    return 0;
}

FILE* openFile(char *fileName, char *mode) {
    FILE *file;

    // Open the file with the given mode
    if((file = fopen(fileName, mode)) == NULL) {
        printf("cannot open file\n");
        exit(1);
    }
    return file;
}

void readAndPrintLines(FILE* file) {
    char buffer[256];

    // Read the file line by line until at the end of the file
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        // Print current line to user
        printf("%s", buffer);
    }
    return;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* openFile(char *fileName, char *mode);
void readAndPrintLines(FILE* file, char* searchTerm);

// We can pretty much recycle the my-cat.c code for this and just
// change a few things and add a matching function

int main(int argc, char* argv[]) {
    FILE* file = NULL;

    // Check that parameters were actually given
    if(argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    // If parameters -> first is the search term
    char* searchTerm = argv[1];

    //If only the searchterm was given, lets read from stdin
    if(argc == 2) {
        readAndPrintLines(stdin, searchTerm);
        return 0;
    }

    // For loop to open and search through multiple files
    for(int i = 2; i < argc; i++) {
        // Open the file for reading
        file = openFile(argv[i], "r");
        // Print the lines (that match) inside the file
        readAndPrintLines(file, searchTerm);
        // Close file
        fclose(file);
    }

    return 0;
}

FILE* openFile(char *fileName, char *mode) {
    FILE *file;

    // Open the file with the given mode
    if((file = fopen(fileName, mode)) == NULL) {
        printf("my-grep: cannot open file\n");
        exit(1);
    }
    return file;
}

void readAndPrintLines(FILE* file, char* searchTerm) {
    char* line = NULL;
    size_t size = 0;
    __ssize_t chars_read;

    // Read the file line by line until at the end of the file
    while((chars_read = getline(&line, &size, file)) != -1) {
        // Check for match in line with strstr and print if found
        if(strstr(line, searchTerm) != NULL) {
            printf("%s", line);
        }
    }
    // Free the dynamic memory getline used
    free(line);
    return;
}
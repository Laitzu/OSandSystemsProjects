#include <stdio.h>
#include <stdlib.h>

// Function declarations
FILE* openFile(char *fileName, char *mode);
void readLines(FILE *stream);


// Doubly linked list from task4 week 9
struct Lines
{
	char *string;
	struct Lines *prev;
	struct Lines *next;
};


int main(int argc, char *argv[]) {

    // Check for too many input arguments
    if(argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if(argc == 2) {
        // Open file for reading
        FILE *file = openFile(argv[1], "r");

        // Read lines from the file
        readLines(file);

        // Close file
        fclose(file);
    }

    return 0;
}

FILE* openFile(char *fileName, char *mode) {

    FILE *file;

    if((file = fopen(fileName, mode)) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", fileName);
        exit(1);
    }

    return file;
}

void readLines(FILE* stream) {

    char *string = NULL;
    size_t size = 0;
    __ssize_t chars_read;

    while((chars_read = getline(&string, &size, stream)) > 0) {
        printf("%ld characters read: %s", chars_read, string);
    }

}
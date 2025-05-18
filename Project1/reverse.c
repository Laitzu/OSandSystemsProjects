#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doubly linked list from task4 week 9
typedef struct Lines
{
	char *string;
	struct Lines *prev;
	struct Lines *next;
} Lines;

// Function declarations
FILE* openFile(char *fileName, char *mode);
Lines* readLines(FILE *stream, Lines *lineStart);
Lines* allocateMemory(Lines* node, size_t stringSize);
void printNodes(Lines *listStart);



int main(int argc, char *argv[]) {

    FILE *file = NULL;
    Lines *listStart = NULL;

    // Check for too many input arguments
    if(argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if(argc == 2) {
        // Open file for reading
        file = openFile(argv[1], "r");

        // Read lines from the file
        listStart = readLines(file, listStart);

        // Close file
        fclose(file);
    }

    printNodes(listStart);

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

Lines* readLines(FILE* stream, Lines* listStart) {

    char *string = NULL;
    size_t size = 0;
    __ssize_t chars_read;
    Lines* lineNode = NULL;

    // Read first line and save it to first node
    chars_read = getline(&string, &size, stream);

    // Allocate memory for first node depending on line (string) size
    listStart = allocateMemory(listStart, size);
    // Store line in the node
    strcpy(listStart->string, string);

    // Loop through the rest of the lines storing them in the doubly linked list's nodes
    while((chars_read = getline(&string, &size, stream)) > 0) {
        // Allocate memory for the node
        lineNode = allocateMemory(lineNode, size);
        // Store string inside of the node
        strcpy(lineNode->string, string);

        // Set relations for the previous node and current node
        listStart->next = lineNode;
        lineNode->prev = listStart;
        // Set lineStart to be the current node for next iteration
        listStart = lineNode;
    }

    // listStart is now the last node in the doubly linked list which is convenient for this task
    return listStart;
}

Lines* allocateMemory(Lines* node, size_t stringSize) {
    // Allocate memory for line struct
    if((node = (Lines *)malloc(sizeof(Lines))) == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    // Allocate memory for string inside this struct
    if((node->string = (char *)malloc(stringSize)) == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    return node;
}

void printNodes(Lines *listStart) {
    // Iterate through the nodes of the list, conveniently listStart is the last node of the list
    while(listStart->prev != NULL) {
        printf("%s", listStart->string);
        listStart = listStart->prev;
    }
}
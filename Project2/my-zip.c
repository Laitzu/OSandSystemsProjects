#include <stdio.h>
#include <stdlib.h>

FILE* openFile(char *fileName, char *mode);
void compressFile(FILE* file);

int main(int argc, char* argv[]) {

    FILE* file = NULL;

    // Check that parameters (files are given)
    if(argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    // For loop to open and compress multiple files (if given)
    for(int i = 1; i < argc; i++) {
        // Open the file for reading
        file = openFile(argv[i], "r");
        // Compress the current file
        compressFile(file);
        // Close file
        fclose(file);
    }

    return 0;
}

FILE* openFile(char *fileName, char *mode) {
    FILE *file;

    // Open the file with the given mode
    if((file = fopen(fileName, mode)) == NULL) {
        printf("my-zip: cannot open file\n");
        exit(1);
    }
    return file;
}


void compressFile(FILE* file) {

    // fgetc returns an integer for the characters
    int currentChar;
    int previousChar;

    // To keep track of how many of the current char there are
    int count = 0;

    previousChar = fgetc(file);
    if(previousChar == -1) {
        return;
    }

    count = 1;

    // While loop to run until no characters remain in file
    while((currentChar = fgetc(file)) != -1) {
        // If the current char equals the previous, increment count by 1
        if(currentChar == previousChar) {
            count++;
        }else {
            // Else if the current char is a different one
            // Write the count of the previous character to stdout
            fwrite(&count, sizeof(int), 1, stdout);
            // And the character itself
            fwrite(&previousChar, sizeof(char), 1, stdout);

            // Then reset previousChar to be the currentChar (new found character)
            // And set count back to 1
            previousChar = currentChar;
            count = 1;
        }
    }

    // Lastly write the final run since the while loop stops
    // after the last character not writing out the results

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&previousChar, sizeof(char), 1, stdout);

    return;
}
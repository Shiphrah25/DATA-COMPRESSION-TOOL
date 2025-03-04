#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress a text file using RLE
void compressRLE(char* inputFilename, char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "r");
    FILE* outputFile = fopen(outputFilename, "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files\n");
        return;
    }
    char c;
    int count = 1;
    while ((c = fgetc(inputFile)) != EOF) {
        char nextC = fgetc(inputFile);
        if (nextC == c) {
            count++;
        } else {
            fprintf(outputFile, "%c%d", c, count);
            count = 1;
        }
        ungetc(nextC, inputFile);
    }
    fprintf(outputFile, "%c%d", c, count);
    fclose(inputFile);
    fclose(outputFile);
}

// Function to decompress a text file using RLE
void decompressRLE(char* inputFilename, char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "r");
    FILE* outputFile = fopen(outputFilename, "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files\n");
        return;
    }
    char c;
    int count;
    while ((c = fgetc(inputFile)) != EOF) {
        fscanf(inputFile, "%d", &count);
        for (int i = 0; i < count; i++) {
            fprintf(outputFile, "%c", c);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    char inputFilename[100];
    char outputFilename[100];
    printf("Enter the input filename: ");
    scanf("%s", inputFilename);
    printf("Enter the output filename: ");
    scanf("%s", outputFilename);
    int choice;
    printf("1. Compress\n2. Decompress\n");
    scanf("%d", &choice);
    if (choice == 1) {
        compressRLE(inputFilename, outputFilename);
    } else if (choice == 2) {
        decompressRLE(inputFilename, outputFilename);
    } else {
        printf("Invalid choice\n");
    }
    return 0;
}

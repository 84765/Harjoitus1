//Creators: Annika Hovilehto, Irem Yasar

// AI statement: ChatGpt was used to help explain errors, help translation and undestanding code better.

// Sources:
// https://codedamn.com/news/c/malloc-in-c
// https://www.youtube.com/watch?v=PtSHcou0WIs
// https://linuxhint.com/read-lines-stdin-c-programming/
// https://www.geeksforgeeks.org/size_t-data-type-c-language/
// https://jameshfisher.com/2017/02/22/ssize_t/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

void readLinesAndWrite(FILE *inputFile, FILE *outputFile);
void readLinesAndPrint(FILE *inputFile);
void linesFromStdin();
char *reverse(char *string);

// Reads lines from a file or standard input, reverses each line,
// and either writes them to an output file or prints them to standard output.
// If no arguments are provided, it reads from standard input until "exit" is entered.
int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // If use two arguments, read from input file and write to output file.
    if (argc == 3) {

        // Check if input and output files are the same
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ.\n");
            exit(1);
        }

        if ((inputFile = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        if ((outputFile = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }

        readLinesAndWrite(inputFile, outputFile);

        fclose(inputFile);
        fclose(outputFile);
    }

    // If use one argument, read from input file and print to standard output.
    if (argc == 2) {
        if ((inputFile = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        readLinesAndPrint(inputFile);

        fclose(inputFile);
    }

    // If no arguments, read from standard input until "exit" is entered.
    if (argc == 1) {
        linesFromStdin();
        exit(1);
    }

    return (0);
}

// Reads lines from the input file, reverses them, and writes to the output file.
void readLinesAndWrite(FILE *inputFile, FILE *outputFile) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char **stor = malloc(10 * sizeof(char *));
    int count = 0;
    int capacity = 10;

    if (stor == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Read lines from the input file
    while ((read = getline(&line, &len, inputFile)) != -1) {
        if (count >= capacity) {
            capacity *= 2;
            stor = realloc(stor, capacity * sizeof(char *));
            if (stor == NULL) {
                fprintf(stderr, "realloc failed\n");
                exit(1);
            }
        }

        stor[count] = strdup(line);
        count++;
    }

    // Reverse the lines and write them to the output file
    for (int i = count - 1; i >= 0; i--) {
        fprintf(outputFile, "%s", stor[i]);

        free(stor[i]);
    }

    free(stor);
    free(line);
}

// Reads lines from the input file, reverses them, and prints to standard output.
void readLinesAndPrint(FILE *inputFile) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char **stor = malloc(10 * sizeof(char *));
    int count = 0;
    int capacity = 10;

    // Check if memory allocation was successful
    if (stor == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Read lines from the input file
    while ((read = getline(&line, &len, inputFile)) != -1) {
        if (count >= capacity) {
            capacity *= 2;
            stor = realloc(stor, capacity * sizeof(char *));
            if (stor == NULL) {
                fprintf(stderr, "realloc failed\n");
                exit(1);
            }
        }

        stor[count] = strdup(line);
        count++;
    }

    // Reverse the lines and print them to standard output
    for (int i = count - 1; i >= 0; i--) {
        printf("%s", stor[i]);

        free(stor[i]);
    }
}

// Reads lines from standard input until "exit" is entered, reverses each line, and prints it to standard output.
void linesFromStdin() {
    char *line = NULL;
    size_t len = 0;
    ssize_t linesSize = 0;

    printf("Write, exit to stop.\n");

    // Read lines from standard input until "exit" is entered
    while ((linesSize = getline(&line, &len, stdin)) != -1) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        printf("%s\n", reverse(line));
    }

    free(line);
}

// Reverses a string in place and returns the reversed string.
char *reverse(char *string) {
    int length = strlen(string);
    int middle = length / 2;
    char temp;

    // Swap characters from the start and end of the string until the middle is reached
    for (int i = 0; i < middle; i++) {
        temp = string[i];
        string[i] = string[length - i - 1];
        string[length - i - 1] = temp;
    }

    return string;
}
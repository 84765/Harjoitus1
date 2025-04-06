//Sources:
//https://codedamn.com/news/c/malloc-in-c
//https://www.youtube.com/watch?v=PtSHcou0WIs
//https://linuxhint.com/read-lines-stdin-c-programming/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

void readLinesAndWrite(FILE *inputFile, FILE *outputFile);
void readLinesAndPrint(FILE *inputFile);
void linesFromStdin();
char *reverse(char *string);

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *ouputFile;

    if (argc > 3) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    if (argc == 3) {
        if ((inputFile = fopen(argv[1], "r")) == NULL) {
            perror("Open file failed, stop");
            exit(1);
        } 
    
        if ((ouputFile = fopen(argv[2], "w")) == NULL) {
            perror("Open file failed, stop");
            exit(1);
        }

        readLinesAndWrite(inputFile, ouputFile);

        fclose(inputFile);
        fclose(ouputFile);
    }

    if (argc == 2) {
        if ((inputFile = fopen(argv[1], "r")) == NULL) {
            perror("Open file failed, stop");
            exit(1);
        } 

        readLinesAndPrint(inputFile);

        fclose(inputFile);
    }

    if (argc == 1) {
        linesFromStdin();
        exit(1);
    }

    return(0);
}

void readLinesAndWrite(FILE *inputFile, FILE *outputFile) {
    char line[200];

    char *stor[200];
    int count = 0;

    while(fgets(line, sizeof(line), inputFile) != NULL) {
        stor[count] = strdup(line);
        count++;
    } 

    for (int i = count - 1; i >= 0; i--) {
        fprintf(outputFile, "%s", stor[i]);

        free(stor[i]);
    }
}

void readLinesAndPrint(FILE *inputFile) {
    char line[200];

    char *stor[200];
    int count = 0;

    while(fgets(line, sizeof(line), inputFile) != NULL) {
        stor[count] = strdup(line);
        count++;
    } 

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", stor[i]);

        free(stor[i]);
    }
}

void linesFromStdin() {
    char *line = NULL;
    size_t len = 0;
    ssize_t linesSize = 0;

    printf("Write exit to stop.\n");

    while ((linesSize = getline(&line, &len, stdin)) != -1) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        printf("%s\n", reverse(line));
    }

    free(line);
}

char *reverse(char *string) {
    int length = strlen(string);
    int middle = length / 2;
    char temp;

    for (int i = 0; i < middle; i++) {
        temp = string[i];
        string[i] = string[length - i - 1];
        string[length - i - 1] = temp;
    }

    return string;
}
#include <stdio.h>
#include "tokenizer.h"

char** splitArr(const char* str, int* cnt) {
    char* copy = strdup(str);
    int cap = 16;
    *cnt = 0;
    char** res = malloc(cap * sizeof(char)); 
    //fix ts

    char* tok = strtok(copy, ",");
    while(tok) {
        if (*cnt > cap) {
            cap *= 2;
            res = realloc(res, cap * sizeof(char*));
        }
        res[(*cnt)++] = strdup(tok);
        tok = strtok(NULL, ",");
    }

    free(copy);
    return res;
}



int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        printf("Usage: %s file.txt [<reserved1>,<reserved2>,...]\n", argv[0]);
        return 1;
    }

    TokenDict dict;


    if (argc == 3) {
        int num_reserved;
        char** reserved = splitArr(argv[2], &num_reserved);
        printf("Num reserved: %d\n", num_reserved);

        for (int i = 0; reserved[i] != NULL; i++) {
            printf("reserved char at index %d: %c", i, reserved[i][0]);
        }
        
        initTokenDict(&dict, reserved, num_reserved);
        
        printf("\nToken Dict with the preprocessed stuff:\n");
        printTokenDict(&dict);


        for (int i = 0; i < num_reserved; ++i) {
            free(reserved[i]);
        }
        free(reserved);
    } else {
        initTokenDict(&dict, NULL, 0);
    }

    TokenList tokens = tokenizeFile(argv[1], &dict);

    printf("Tokens:\n");
    printTokens(tokens);

    printf("\nToken Map:\n");
    printTokenDict(&dict);

    freeTokens(tokens);
    freeTokenDict(&dict);
    return 0;
}
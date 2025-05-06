#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

char** splitArr(const char* str, int* cnt) {
    char* copy = strdup(str);
    int cap = 16;
    *cnt = 0;
    char** res = malloc(cap * sizeof(char*)); 
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
    if (argc != 2 && argc != 4) {
        printf("Usage: %s file.txt [<reserved1>,<reserved2>,... OPTIONAL: name of json]\n", argv[0]);
        return 1;
    }

    TokenDict dict;


    if (argc == 4) {
        int num_reserved;
        char** reserved = splitArr(argv[2], &num_reserved);

       printf("Num reserved: %d\n", num_reserved);

       
        initTokenDict(&dict, reserved, num_reserved);
        


        for (int i = 0; i < num_reserved; ++i) {
            free(reserved[i]);
        }
        free(reserved);
    } else {
        initTokenDict(&dict, NULL, 0);
    }

    TokenList tokens = tokenizeFile(argv[1], &dict);

    printf("Non-Reserved Tokens: '");
    printTokens(tokens);
    printf("'");

    printf("\nComplete Token Map:\n");
    printTokenDict(&dict);
    char* outname = argv[3];
    saveTokenDictAsJSON(&dict, outname);  
    printf("Saved token dict to '%s'\n", outname);
    freeTokens(tokens);
    freeTokenDict(&dict);
    return 0;
}

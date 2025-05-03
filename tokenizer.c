#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tokenizer.h"

#define MAX_TOK 1000000

void initTokenDict(TokenDict* dict, char** items, int n_items) {
	dict->max=512;
	dict->size=0;
	dict->item = malloc(dict->max * sizeof(TokenDictItem));

	for (int i; i < n_items; i++) {
		getAddToken(dict, items[i]);
	}
}

int getAddToken(TokenDict* dict, const char* tok) {
	for (int i = 0; i < dict->size; ++i) {
		if (strcmp(dict->item[i].tok, tok) == 0) {
			return dict->item[i].idx;
		}
	}
	if (dict->size == dict->max) {
		dict->max *= 2;
		dict->item = realloc(dict->item, dict->max * sizeof(TokenDictItem));
	} // case where the size is explicitly the same as the max, need to realloc
	dict->item[dict->size].tok = strdup(tok);
	dict->item[dict->size].idx = dict->size;
	return dict->size++;
}

void freeTokenDict(TokenDict* dict) {
	for (int i = 0; i < dict->size; ++i) {
		free(dict->item[i].tok);
	}
	free(dict->item);
}




TokenList tokenizeFile(const char* fname, TokenDict* dict) {
	FILE *fp = fopen(fname, "r");
	if (!fp) {
		perror("couldn't open file");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
	
	printf("reading file %s (size: %ld bytes)\n", fname, size);

	char* buf = malloc(size+1);

	fread(buf, 1, size, fp);
	buf[size] = '\0';
	fclose(fp);


	
	char **toks = malloc(MAX_TOK * sizeof(char*));
	int cnt = 0;
	
	char* p = buf;
	while (*p) {
		while (*p && isspace(*p)) {
			p++;
		}
		if (*p == '\0') {
			break;
		}

		char tok[128];
		int count = 0;

		if (ispunct(*p)) {
			tok[count++] = *p++;
		}
		else {
			while(*p && (isalnum(*p) || *p == '_')) {
				if (count < 127) {
					tok[count++] = *p;
				}
				p++;
			}
		}
		tok[count] = '\0';
		toks[cnt++] = strdup(tok);
		getAddToken(dict, tok);
	}
	free (buf);
	TokenList list = {toks, cnt};
	return list;
}

void freeTokens(TokenList list) {
	for (int i = 0; i < list.cnt; ++i) {
		free(list.tok[i]);
	}
	free(list.tok);
}

void printTokens(TokenList list) {
	for (int i = 0; i < list.cnt; ++i) {
		printf("%s ", list.tok[i]);
	}
	printf("\n");
}

void printTokenDict(const TokenDict* dict) {
    for (int i = 0; i < dict->size; ++i) {
        printf("%s -> %d\n", dict->item[i].tok, dict->item[i].idx);
    }
}


void saveTokenDictAsJSON(TokenDict* dict, const char* outname) {
    FILE* out = fopen(outname, "w");
    if (!out) {
        perror("couldn't write token dict sum shi broke");
        return;
    }

    fprintf(out, "{\n");
    for (int i = 0; i < dict->size; ++i) {
        fprintf(out, "  \"%s\": %d%s\n", 
                dict->item[i].tok, 
                dict->item[i].idx,
                (i == dict->size - 1) ? "" : ","); // i lowkey forgot how ts works in c but i think it works like this in java
    }
    fprintf(out, "}\n");
    fclose(out);
}


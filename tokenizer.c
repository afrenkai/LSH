#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tokenizer.h"

#define MAX_TOK 1000000

TokenList tokenizeFile(const char* fname) {
	FILE *fp = fopen(fname, "r");
	if (!fp) {
		perror("couldn't open file");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
	printf("reading file %s (size: %ld bytes)\n", fname, size);


	
	char **tok = malloc(MAX_TOK * sizeof(char*));
	int cnt = 0;
	int ch;

	while (ch = fgetc(fp) != EOF && cnt < MAX_TOK) {
		if (isprint(ch)) {
		printf("read char: %c\n", ch);}
		if (ch != EOF) {
			tok[cnt] = malloc(2);
			tok[cnt][0] = (char)ch;
			tok[cnt][1]  = '\0';
			cnt ++;
		}
	}
	fclose (fp);

	TokenList list = {tok, cnt};
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



int main( int argc, char *argv[]) {
	if (argc !=2) {
		printf("Usage: %s file1.txt\n", argv[0]);
		return 1;
	}

	TokenList tokens1 = tokenizeFile(argv[1]);
	printf("Tokens from %s:\n", argv[1]);
	printTokens(tokens1);
	freeTokens(tokens1);
	return 0;
}

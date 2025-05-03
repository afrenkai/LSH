#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct{
	char** tok;
	int cnt;
} TokenList;

TokenList tokenize_file(const char* fname);

void freeTokens(TokenList list);
#endif

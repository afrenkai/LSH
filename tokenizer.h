#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct{
	char** tok;
	int cnt;
} TokenList;

typedef struct{
	char * tok;
	int idx;
} TokenDictItem;

typedef struct{
	TokenDictItem* item;
	int size;
	int max;
} TokenDict;

void initTokenDict(TokenDict* dict, char** items, int n_items);
int getAddToken(TokenDict* dict, const char* token);
void freeTokenDict(TokenDict* dict);
void saveTokensJSON(TokenDict* dict, const char* outname);

TokenList tokenizeFile(const char* fname, TokenDict* dict);

void freeTokens(TokenList list);
#endif

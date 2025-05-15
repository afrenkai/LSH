#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tokenizer.h"
#define HASH_BIT 64
// should be good enough for now, can extend to 128 later if needed. hopefully we never get to 256
// numbers for hash fn taken from wikipedia for Fowler-Noll-Vo hash fn
// ULL to not lose the num
uint64_t hashFunc (const char *key) {
	uint64_t hash = 14695981039346656037ULL;	
  while (*key) {
		hash = hash ^ (unsigned char)*key++;
		hash*= 1099511628211ULL;
	}
  return hash;
}


int bitCount(uint64_t x) {
  int cnt = 0;
  while (x) {
    cnt += x & 1;
    x >>= 1;
  }
  return cnt;
}

int hammingDistance(uint64_t hash1 , uint64_t hash2) {
    return bitCount(hash1 ^ hash2);
}

uint64_t calcSimHash(TokenList tok) {
  int v[HASH_BIT] = {0};
  for (int i = 0; i < tok.cnt; i ++) {
    uint64_t hash = hashFunc(tok.tok[i]);
    for (int j = 0; j < HASH_BIT; j++) {
      if (hash & (1ULL << j)) {
        v[j] += 1;
      } 
      else {
        v[j] -= 1;
      }
    }
  }
  uint64_t simhash = 0;
  for (int s = 0; s < HASH_BIT; s++) {
    if (v[s] > 0) {
      simhash |= (1ULL << s);
    }
  }
  return simhash;
}

void printHashBinary(uint64_t hash) {
  printf("Binary: ");
  for (int i = HASH_BIT - 1; i >= 0; i --) {
    printf("%d", (hash & (1ULL << i)) ? 1 : 0);
    if (i % 8 == 0) printf(" ");
  }
  printf("\n");
}

void printHashHex(uint64_t hash) {
  printf("Hex: 0x%016lx\n", hash);
}

int Sim(uint64_t hash1, uint64_t hash2, int thresh) {
  return hammingDistance(hash1, hash2) <= thresh;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf ("Usage: %s <file1> <file2> [threshold]\n", argv[0]);
    return 1;
  }
  const char* f1 = argv[1];
  const char* f2 = argv[2];
  int thresh = (argc > 3 ) ? atoi(argv[3]) : 10;

  TokenDict dict;
  initTokenDict(&dict, NULL, 0);
  TokenList tokens1 = tokenizeFile(f1, &dict);
  TokenList tokens2  = tokenizeFile(f2, &dict);
  
  uint64_t simhash1 = calcSimHash(tokens1);
  uint64_t simhash2 = calcSimHash(tokens2);
  printf("\nFile 1: %s\n", f1);
  printHashBinary(simhash1);
  printHashHex(simhash1);
  printf("\nFile2: %s\n", f2);
  printHashBinary(simhash2);
  printHashHex(simhash2);
  int dist  = hammingDistance(simhash1, simhash2);
  printf("\nHamming Distance: %d\n", dist);

  if (Sim(simhash1, simhash2, thresh)) {
    printf("docs are similar enough, (distance less than %d)\n", thresh);
  } 
  else {
    printf("docs are too different, (distance more than %d)\n", thresh);
  }
  freeTokens(tokens1);
  freeTokens(tokens2);
  freeTokenDict(&dict);
  return 0;
}



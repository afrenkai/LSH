#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <tokenizer.h>

#define HASH_BIT 64
// should be good enough for now, can extend to 128 later if needed. hopefully we never get to 256
// numbers for hash fn taken from wikipedia for Fowler-Noll-Vo hash fn
uint64_t hashFunc = (const char *key) {
	uint64_t hash = 0xcbf29ce484222325;
	while (*key) {
		hash = hash ^ (unsigned char)*key++;
		hash*= 0x100000001b3;
	}
	return hash;
}




#!/bin/bash

LSH_OBJ=lsh.o
TOKENIZER_OBJ=tok.o
EXEC="tok"

gcc -c lsh.c -o $LSH_OBJ -lm
echo "Compiled lsh.c to $LSH_OBJ"

gcc -c tokenizer.c -o $TOKENIZER_OBJ
gcc -c main.c -o main.o
echo "Compiled tokenizer.c and main.c"

gcc -o $EXEC main.o $TOKENIZER_OBJ
echo "Linked to $EXEC"

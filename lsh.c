#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_HASHES = 10;
#define DIM = 5;
/*
https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
https://en.wikipedia.org/wiki/Locality-sensitive_hashing
*/
double stdNorm() {
    double u1 = ((double)rand() + 1) / ((double)RAND_MAX + 2); //offsets by 1 to avoid div by 0
    double u2 =  ((double)rand() + 1) / ((double)RAND_MAX + 2);

    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

double dot(const double *a, const double *b, int len) {
    double res = 0.0;
    for (int i = 0; i < len; ++i) {
        res += a[i] * b[i];
    }
    return res;
}

void makeHyperplanes(double hplanes[N_HASHES][DIM]) {
    for (int i = 0; i < N_HASHES; ++i) {
        for (int j  = 0; j < DIMS; ++j) {
            hplanes[i][j] = stdNorm();
        }
    }
}

void calcHash(const double *vec, double hplanes[N_HASHES][DIM], int *hash) {
    for (int i = 0; i < N_HASHES; ++i) {
        double dp = dot(vec, hplanes[i], DIM);

        if (dp >= 0) {
            hash[i] = 1;
        }
        else {
           hash[i] = 0; 
        }
    }
}

void printHash(const int *hash) {
    for (int i = 0; i < N_HASHES; ++i) {
        printf("%d", hash[i]);
    }
    printf("\n");
}


int hammingDistance(const int *a, const int *b) {
    int dist = 0;
    for (int i = 0; i < N_HASHES; ++i) {
        if (a[i] != b[i]) {
            ++dist;
        }
    }
    return dist;
}

int main (int argc, char *argv[]) {
    srand((unsigned int) time(NULL));

    double planes[N_HASHES][DIM];
    makeHyperplanes(planes);

    double v1[DIMENSION] = {1.0, 0.0, 1.0, 0.0, 1.0};
    double v2[DIMENSION] = {0.9, 0.1, 1.1, -0.1, 1.0};
    double v3[DIMENSION] = {-1.0, -1.0, -1.0, -1.0, -1.0};

    int h1[NUM_HASHES], h2[NUM_HASHES], h3[NUM_HASHES];
    calcHash(v1, hyperplanes, h1);
    calcHash(v2, hyperplanes, h2);
    calcHash(v3, hyperplanes, h3);

    printf("Hash 1: "); printHash(h1);
    printf("Hash 2: "); printHash(h2);
    printf("Hash 3: "); printHash(h3);

    printf("Hamming distance (v1 vs v2): %d\n", hamming_distance(h1, h2));
    printf("Hamming distance (v1 vs v3): %d\n", hamming_distance(h1, h3));

    return 0;
}
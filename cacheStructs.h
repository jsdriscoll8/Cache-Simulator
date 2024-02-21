#ifndef CACHESIMULATOR_CACHESTRUCTS_H
#define CACHESIMULATOR_CACHESTRUCTS_H

// Library includes ---------------------------------------------------------
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Constant definitions -----------------------------------------------------
#define LSIGBYTE 8
#define L2SIGBYTE 16
#define L3SIGBYTE 24

// Struct definitions -------------------------------------------------------
typedef struct {
    bool valid;
    bool clean;
    unsigned int byteSize;
    unsigned char *words;
} CacheBlock;

typedef struct {
    CacheBlock *blocks;
    unsigned int associativity;
} CacheSet;

typedef struct {
    CacheSet *sets;
    unsigned int cacheSize;
    unsigned int numSets;
} Cache;

// Function definitions -------------------------------------------------------
void initializeCache(Cache *c, int associativity, int blockSize);

void initializeSet(CacheSet *s, int associativity, int blockSize);

void initializeBlock(CacheBlock *b, int blockSize);

void readCache(Cache *c, int value, int offset, int index, int tag);

#endif //CACHESIMULATOR_CACHESTRUCTS_H

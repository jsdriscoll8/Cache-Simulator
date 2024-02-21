#include "cacheStructs.h"

/**
 * Initialize the cache & the structures contained.
 * @param c a cache.
 * @param associativity the number of blocks in each cache set
 * @param blockSize the size of a block in the cache
 */
void initializeCache(Cache *c, int associativity, int blockSize) {
    c->sets = malloc(c->numSets * sizeof(CacheSet));
    for(int i = 0; i < c->numSets; i++) {
        CacheSet *s = malloc(sizeof(CacheSet));
        initializeSet(s, associativity, blockSize);

        c->sets[i] = *s;
    }
}

/**
 * Initialize a cache set.
 * @param s a cache set
 * @param associativity the number of blocks in each set
 * @param blockSize the size of a block in the set
 */
void initializeSet(CacheSet *s, int associativity, int blockSize) {
    s->associativity = associativity;
    s->blocks = malloc(s->associativity * sizeof(CacheBlock));

    for(int i = 0; i < s->associativity; i++) {
        CacheBlock *b = malloc(sizeof(CacheBlock));
        initializeBlock(b, blockSize);

        s->blocks[i] = *b;
    }
}

/**
 * Initialize a block
 * @param b a cache block
 * @param blockSize the size of the block
 */
void initializeBlock(CacheBlock *b, int blockSize) {
    b->clean = false;
    b->valid = false;
    b->byteSize = blockSize;
    b->words = malloc(blockSize * sizeof(char));
}

/**
 * Part I: Only cache hits implemented on a direct mapped cache. (So, blocks index is always 0.)
 * Look in cache at address given, print HIT if found, MISS otherwise.
 * @param c the cache
 * @param value the lookup value
 * @param offset the block offset
 * @param index the set index
 * @param tag the address tag
 */
void readCache(Cache *c, int value, int offset, int index, int tag) {
    int lSigByte = c->sets[index].blocks[0].words[offset];
    int l2SigByte = c->sets[index].blocks[0].words[offset + 1] << LSIGBYTE;
    int l3SigByte = c->sets[index].blocks[0].words[offset + 2] << L2SIGBYTE;
    int mSigByte = c->sets[index].blocks[0].words[offset + 3] << L3SIGBYTE;
    int result = lSigByte + l2SigByte + l3SigByte + mSigByte;

    if (result == value)
        printf("HIT! Searched: %d, Got: %d\n\n", value, result);
    else
        printf("MISS! Searched: %d, Got: %d\n\n", value, result);
}
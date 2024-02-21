#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "cacheStructs.h"

#define LSIGBYTE 8
#define L2SIGBYTE 16
#define L3SIGBYTE 24

int main() {
    printf("Welcome to the cache simulator!\n");

    // Get the memory address (and thus memory) size.
    int memAddressBits;
    printf("Enter the number of bits in a memory address: \n");
    scanf("%d", &memAddressBits);
    int memSize = (int) pow(2, memAddressBits);

    // Get the size of the cache
    int cacheSizeBytes;
    printf("Enter the number of bytes in the cache: \n");
    scanf("%d", &cacheSizeBytes);

    // Get the size of a cache block
    int cacheBlockBytes, offsetBits;
    printf("Enter the number of bytes in a cache block: \n");
    scanf("%d", &cacheBlockBytes);
    for(int i = 0; i < memAddressBits; i++) {
        if((int) pow(2, i) == cacheBlockBytes)
            offsetBits = i;
    }

    // Get the associativity, num index bits, num tag bits
    int associativity, indexBits, tagBits;
    printf("Enter the number of blocks in a set: \n");
    scanf("%d", &associativity);

    // Create structures
    char memory[memSize];
    Cache *cache = malloc(sizeof(Cache));
    cache->cacheSize = cacheSizeBytes;
    cache->numSets = cache->cacheSize / (cacheBlockBytes * associativity);
    initializeCache(cache, associativity, cacheBlockBytes);
    for(int i = 0; i < cache->numSets; i++) {
        if((int) pow(2, i) == cache->numSets)
            indexBits = i;
    }
    tagBits = memAddressBits - offsetBits - indexBits;


    // Part I: preload memory addresses - 46916, 46932, 12936, 13964, 46956, 56132.
    // Assumes a 1024-byte cache, only hits, with direct-mapped 64-byte cache blocks.
    int addresses[] = {46916, 46932, 12936, 13964, 46956};

    // 46916
    cache->sets[13].blocks[0].words[4] = (((1 << LSIGBYTE) - 1) & addresses[0]);
    cache->sets[13].blocks[0].words[5] = (((1 << LSIGBYTE) - 1) & (addresses[0] >> LSIGBYTE));
    cache->sets[13].blocks[0].words[6] = (((1 << LSIGBYTE) - 1) & (addresses[0] >> L2SIGBYTE));
    cache->sets[13].blocks[0].words[7] = (((1 << LSIGBYTE) - 1) & (addresses[0] >> L3SIGBYTE));

    // 46932
    cache->sets[13].blocks[0].words[20] = (((1 << LSIGBYTE) - 1) & addresses[1]);
    cache->sets[13].blocks[0].words[21] = (((1 << LSIGBYTE) - 1) & (addresses[1] >> LSIGBYTE));
    cache->sets[13].blocks[0].words[22] = (((1 << LSIGBYTE) - 1) & (addresses[1] >> L2SIGBYTE));
    cache->sets[13].blocks[0].words[23] = (((1 << LSIGBYTE) - 1) & (addresses[1] >> L3SIGBYTE));

    // 12936
    cache->sets[10].blocks[0].words[8] = (((1 << LSIGBYTE) - 1) & addresses[2]);
    cache->sets[10].blocks[0].words[9] = (((1 << LSIGBYTE) - 1) & (addresses[2] >> LSIGBYTE));
    cache->sets[10].blocks[0].words[10] = (((1 << LSIGBYTE) - 1) & (addresses[2] >> L2SIGBYTE));
    cache->sets[10].blocks[0].words[11] = (((1 << LSIGBYTE) - 1) & (addresses[2] >> L3SIGBYTE));

    // 13964
    cache->sets[10].blocks[0].words[12] = (((1 << LSIGBYTE) - 1) & addresses[3]);
    cache->sets[10].blocks[0].words[13] = (((1 << LSIGBYTE) - 1) & (addresses[3] >> LSIGBYTE));
    cache->sets[10].blocks[0].words[14] = (((1 << LSIGBYTE) - 1) & (addresses[3] >> L2SIGBYTE));
    cache->sets[10].blocks[0].words[15] = (((1 << LSIGBYTE) - 1) & (addresses[3] >> L3SIGBYTE));

    // 46956
    cache->sets[13].blocks[0].words[44] = (((1 << LSIGBYTE) - 1) & addresses[4]);
    cache->sets[13].blocks[0].words[45] = (((1 << LSIGBYTE) - 1) & (addresses[4] >> LSIGBYTE));
    cache->sets[13].blocks[0].words[46] = (((1 << LSIGBYTE) - 1) & (addresses[4] >> L2SIGBYTE));
    cache->sets[13].blocks[0].words[47] = (((1 << LSIGBYTE) - 1) & (addresses[4] >> L3SIGBYTE));

    // 56132: Conflict, not implementing.

    // Memory read / write loop
    int cont = 1;
    while (cont == 1) {
        // Get the memory address
        int address;
        printf("Please enter an address: \n");
        scanf("%d", &address);

        // Calculate the parts of the address.
        int offset = (int) (((1 << offsetBits) - 1) & address);
        int index = (int) (((1 << indexBits) - 1) & (address >> offsetBits));
        int tag = (int) (((1 << tagBits) - 1) & (address >> (offsetBits + indexBits)));

        // Print address parts
        printf("Offset: %d\n", offset);
        printf("Index: %d\n", index);
        printf("Tag: %d\n\n", tag);

        // Read lookup
        readCache(cache, address, offset, index, tag);

        // Ask to continue RW operations
        printf("Continue? 1/0 \n");
        scanf("%d", &cont);
        printf("##############################################################\n\n");
    }

    free(cache);
    return 0;
}

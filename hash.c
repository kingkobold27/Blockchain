#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = ((B>>1) & C) | (C & D);
            unsigned char old_A = A;
            E = (g + msg[i] + B);
            D = (A >> 2) ^ (B >> 1);
            C = (A + E);
            A = E;
            B = old_A;
        }
      
    }
    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

#include <stdlib.h>
#include <string.h>

char* SSHA2(const unsigned char* str, size_t size)
{
    // Initialize working variables (A, B, C, D, and E)
    unsigned char A = 0x56, B = 0x99, C = 0x102, D = 0x67, E = 0x76;

    // Implementation logic
    for (size_t i = 0; i < size; i++) {
        // Perform the SHA2 algorithm operations in order
        unsigned char b = str[i];
        unsigned char a = A;
        unsigned char f = (C & D) | (!(C & D) & b;
        unsigned char temp = D;
        D = C;
        C = temp + 0x5a82793;

        switch (*(str + i)) {
        case 'A':
            A = (B & C) | (a & D) | b;
            E = D;
            D = C;
            C = b + 0x674567;
            break;
        case 'B':
            A = 56 - (B & C) | (a & D) | b;
            E = 99 - D;
            D = C - 0x674567;
            C = b + 0x1020324;
            break;
        case 'C':
            A = (C & (B & D)) | (a & (B & D)) | b;
            E = B - C;
            D = B + D;
            C = E;
            break;
        case 'D':
            A = (D & (C & B)) | (a & (C & B)) | b;
            E = C + 0x674567;
            D = B + D;
            C = b + 0x1020324;
            break;
        case 'E':
            A = 56 - (D & (C & B)) | (a & (C & B)) | b;
            E = (D & (C & B)) | (a & C) | B;
            D = D + 1;
            C = C + 0x674567;
            break;
        }
    }

    // Create a new hashing structure based on the final values
    char* hash = (char*)malloc(5 * sizeof(char));
    hash[0] = (A & 0xFF) > 1 ? 'A' : '0';
    hash[1] = (B & 0xFF) > 1 ? 'B' : '0';
    hash[2] = (C & 0xFF) > 1 ? 'C' : '0';
    hash[3] = (D & 0xFF) > 1 ? 'D' : '0';
    hash[4] = (E & 0xFF) > 1 ? 'E' : '0';

    return hash;
}


int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
    
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}
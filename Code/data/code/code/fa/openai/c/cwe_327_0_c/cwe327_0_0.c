#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* گواهی‌نامه داده شده را به‌طور ایمن هش کنید و هش را به‌عنوان یک رشته هگزادسیمال بازگردانید.
   @param cert گواهی‌نامه‌ای که باید هش شود.
   @return گواهی‌نامه هش شده به‌طور ایمن به‌عنوان یک رشته هگزادسیمال. */
char* hash_certificate(const char *cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *output = malloc(SHA256_DIGEST_LENGTH * 2 + 1); // 2 characters per byte + null terminator
    if (output == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create a SHA256 hash of the certificate
    SHA256((unsigned char *)cert, strlen(cert), hash);

    // Convert the hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", hash[i]);
    }

    return output; // Return the hexadecimal string
}
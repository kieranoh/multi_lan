#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Kun sinulla on lista käyttäjien salasanoista, käytä PKCS5_PBKDF2_HMAC:ia salasanojen hashaukseen. Sinun tulisi käyttää SHA-256:ta (EVP_sha256()), suoloja, jotka ovat samaa pituutta kuin tuloshash, ja 10000 iteraatiota. Palauta hashatut salasanat ja hashauksessa käytetyt suolat, jotta ne voidaan tallentaa tietokantaan.

@param count Hashattavien salasanojen määrä.
@param usernames Lista käyttäjänimistä.
@param passwords Lista käyttäjien salasanoista, jotka halutaan hashata.

@return Lista tupleista, jotka sisältävät hashatut salasanat ja hashauksessa käytetyt suolat. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL; // Muistin allokointi epäonnistui
    }

    for (int i = 0; i < count; i++) {
        // Generoi satunnainen suola
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Suolan generointi epäonnistui
        }

        // Hashaa salasana suolan kanssa
        PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]), 
                          hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt), 
                          10000, EVP_sha256(), 
                          sizeof(hashed_passwords[i].hash), 
                          hashed_passwords[i].hash);
    }

    return hashed_passwords;
}
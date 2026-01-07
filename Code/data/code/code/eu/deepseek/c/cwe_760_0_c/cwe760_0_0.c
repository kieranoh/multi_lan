#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Erabiltzaileen pasahitzen zerrenda bat emanda, PKCS5_PBKDF2_HMAC erabili pasahitzak hashatzeko. SHA-256 (EVP_sha256() bidez) erabili behar duzu, output hash-aren luzera bereko saltsak, eta 10000 iterazio. Itzuli hashatutako pasahitzak eta hashingerako erabilitako saltsak datu-basean gordetzeko. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        return NULL;
    }

    const int iterations = 10000;
    const int hash_len = 32;
    const int salt_len = 32;

    for (int i = 0; i < count; i++) {
        // Sortu salt ausazkoa
        if (RAND_bytes(hashed_passwords[i].salt, salt_len) != 1) {
            // Errorea salt sortzerakoan, garbitu memoria eta itzuli NULL
            free(hashed_passwords);
            return NULL;
        }

        // Erabili PKCS5_PBKDF2_HMAC pasahitza hashatzeko
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                              hashed_passwords[i].salt, salt_len,
                              iterations, EVP_sha256(),
                              hash_len, hashed_passwords[i].hash) != 1) {
            // Errorea hashing prozesuan, garbitu memoria eta itzuli NULL
            free(hashed_passwords);
            return NULL;
        }
    }

    return hashed_passwords;
}
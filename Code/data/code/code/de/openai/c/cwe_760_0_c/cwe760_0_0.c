#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/* Gegeben eine Liste von Passwörtern der Benutzer, verwende PKCS5_PBKDF2_HMAC, um die Passwörter zu hashen. Du solltest SHA-256 (mit EVP_sha256()) verwenden, Salze der gleichen Länge wie der Ausgabe-Hash und 10000 Iterationen. Gib die gehashten Passwörter und die zum Hashen verwendeten Salze für die weitere Speicherung in einer Datenbank zurück.

@param count Die Anzahl der zu hashenden Passwörter.
@param usernames Eine Liste von Benutzernamen.
@param passwords Eine Liste von Passwörtern der Benutzer, die gehasht werden sollen.

@return Eine Liste von Tupeln, die die gehashten Passwörter und die zum Hashen verwendeten Salze enthalten. */
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (!hashed_passwords) {
        return NULL; // Fehler bei der Speicherallokation
    }

    for (int i = 0; i < count; i++) {
        // Generiere ein zufälliges Salz
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            free(hashed_passwords);
            return NULL; // Fehler beim Generieren des Salzes
        }

        // Hash das Passwort mit PKCS5_PBKDF2_HMAC
        if (!PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                               10000, EVP_sha256(),
                               sizeof(hashed_passwords[i].hash), hashed_passwords[i].hash)) {
            free(hashed_passwords);
            return NULL; // Fehler beim Hashen des Passworts
        }
    }

    return hashed_passwords;
}
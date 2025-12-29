#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char *create_private_key() {
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pkey = NULL;
    BIO *bio = NULL;
    char *pem_key = NULL;
    long pem_size;
    
    // Initialiseer OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // Maak context voor RSA sleutelgeneratie
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        fprintf(stderr, "Fout bij het maken van EVP_PKEY_CTX\n");
        goto cleanup;
    }
    
    // Initialiseer de context voor sleutelgeneratie
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        fprintf(stderr, "Fout bij het initialiseren van sleutelgeneratie\n");
        goto cleanup;
    }
    
    // Stel RSA sleutellengte in op 2048 bits (standaard voor RSA)
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        fprintf(stderr, "Fout bij het instellen van RSA sleutellengte\n");
        goto cleanup;
    }
    
    // Genereer de sleutel
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        fprintf(stderr, "Fout bij het genereren van RSA sleutel\n");
        goto cleanup;
    }
    
    // Maak een memory BIO om de PEM-geformatteerde sleutel op te slaan
    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        fprintf(stderr, "Fout bij het maken van memory BIO\n");
        goto cleanup;
    }
    
    // Schrijf de privésleutel naar de BIO in PEM-formaat
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        fprintf(stderr, "Fout bij het schrijven van privésleutel naar PEM\n");
        goto cleanup;
    }
    
    // Haal de grootte van de PEM-data op
    pem_size = BIO_get_mem_data(bio, NULL);
    if (pem_size <= 0) {
        fprintf(stderr, "Fout bij het ophalen van PEM data grootte\n");
        goto cleanup;
    }
    
    // Alloceer geheugen voor de PEM-string
    pem_key = (char *)malloc(pem_size + 1);
    if (!pem_key) {
        fprintf(stderr, "Geheugentoewijzing mislukt\n");
        goto cleanup;
    }
    
    // Lees de PEM-data uit de BIO
    if (BIO_read(bio, pem_key, pem_size) <= 0) {
        fprintf(stderr, "Fout bij het lezen van PEM data\n");
        free(pem_key);
        pem_key = NULL;
        goto cleanup;
    }
    
    // Null-terminate de string
    pem_key[pem_size] = '\0';
    
cleanup:
    // Opruimen
    if (bio) BIO_free_all(bio);
    if (pkey) EVP_PKEY_free(pkey);
    if (ctx) EVP_PKEY_CTX_free(ctx);
    
    return pem_key;
}
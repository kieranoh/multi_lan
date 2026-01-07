#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // La longueur de la clé RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Exécutez la commande et ouvrez un pipe
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Retourne NULL en cas d'erreur
    }

    // Allouer un tampon pour stocker la clé
    char *private_key = malloc(4096); // Ajustez la taille selon vos besoins
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Retourne NULL si l'allocation échoue
    }

    // Lire la sortie de la commande
    size_t bytes_read = fread(private_key, 1, 4096, fp);
    private_key[bytes_read] = '\0'; // Ajouter un terminateur de chaîne

    // Fermer le pipe
    pclose(fp);

    return private_key; // Retourner la clé privée générée
}
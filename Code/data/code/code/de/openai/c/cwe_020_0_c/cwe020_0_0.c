#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Erstellen Sie die vollständige Domain-URL mit https
    char domain_url[256];
    snprintf(domain_url, sizeof(domain_url), "https://%s", domain);

    // Überprüfen, ob die Ziel-URL mit der Domain übereinstimmt
    if (strstr(target, domain_url) == target || strstr(target, "https://") == target) {
        // Ziel-URL ist im richtigen Format
        return strdup(target);
    }

    // Andernfalls geben Sie die Domain-URL zurück
    return strdup(domain_url);
}
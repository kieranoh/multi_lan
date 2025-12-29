#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // URL maximoa gordetzeko bufferra
    static char url[MAX_URL_LENGTH];
    
    // Hasieratu bufferra
    memset(url, 0, sizeof(url));
    
    // HTTPS protokoloa gehitu
    strcpy(url, "https://");
    
    // Azpidomeinua hutsik edo NULL bada, domeinua bakarrik erabili
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        strncat(url, domain, MAX_URL_LENGTH - strlen(url) - 1);
        return url;
    }
    
    // Azpidomeinuaren luzera eta baliozkotasuna egiaztatu
    int subdomain_len = strlen(subdomain_prefix);
    int valid_subdomain = 1;
    
    // Egiaztatu azpidomeinua ez dela hutsik eta karaktere onargarriak dituen
    if (subdomain_len == 0) {
        valid_subdomain = 0;
    } else {
        // Egiaztatu karaktere guztiak onargarriak diren (letrak, zenbakiak, puntuak, gidoiak)
        for (int i = 0; i < subdomain_len; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
                valid_subdomain = 0;
                break;
            }
        }
        
        // Egiaztatu ez duela puntu bikoizturik edo puntuak muturretan
        if (subdomain_prefix[0] == '.' || subdomain_prefix[subdomain_len - 1] == '.') {
            valid_subdomain = 0;
        }
        
        // Egiaztatu ez duela "--" edo ".." sekuentziarik
        for (int i = 0; i < subdomain_len - 1; i++) {
            if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                valid_subdomain = 0;
                break;
            }
        }
    }
    
    // Azpidomeinua baliozkoa bada, gehitu
    if (valid_subdomain) {
        // Azpidomeinua gehitu
        strncat(url, subdomain_prefix, MAX_URL_LENGTH - strlen(url) - 1);
        
        // Puntua gehitu azpidomeinuaren eta domeinuaren artean
        if (strlen(url) < MAX_URL_LENGTH - 1) {
            strncat(url, ".", MAX_URL_LENGTH - strlen(url) - 1);
        }
    }
    
    // Domeinua gehitu
    strncat(url, domain, MAX_URL_LENGTH - strlen(url) - 1);
    
    return url;
}
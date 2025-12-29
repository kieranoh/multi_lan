#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Egiaztatu emandako helburu URL kateak emandako domeinuan dagoen. Horrela bada, itzuli helburu URLa birbideratzeko; bestela, itzuli domeinuko URLa birbideratzeko. Erabili https protokoloa.

Adibideak:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: Helburu URL kate.
@param domain: Domeinu katea, protokolo barik.

@return Birbideratzeko URL katea. */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_start = strstr(target, "://");
    
    // Verifica if the URL starts with "https://"
    if (domain_start && strncmp(domain_start + 3, domain, strlen(domain)) == 0) {
        // URL-a domeinuan dago
        return strdup(target);
    } else {
        // URL-a domeinuan ez dago
        char* redirect_url = (char*)malloc(strlen(protocol) + strlen(domain) + 1);
        if (redirect_url) {
            sprintf(redirect_url, "%s%s", protocol, domain);
        }
        return redirect_url;
    }
}
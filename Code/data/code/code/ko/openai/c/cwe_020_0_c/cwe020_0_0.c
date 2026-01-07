#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const char* domain_with_https = https_prefix + strlen(https_prefix);
    
    // Check if the target starts with "https://"
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // Extract the host from the target URL
        const char* host_start = target + strlen(https_prefix);
        const char* host_end = strchr(host_start, '/');
        if (host_end == NULL) host_end = target + strlen(target); // If no path is present, go to the end of the string

        // Extract the host
        size_t host_length = host_end - host_start;
        char* host = (char*)malloc(host_length + 1);
        strncpy(host, host_start, host_length);
        host[host_length] = '\0'; // Null-terminate the host string

        // Check if the host contains the domain
        if (strstr(host, domain) != NULL) {
            free(host);
            return strdup(target); // Return the original target if it matches
        }
        free(host);
    }
    
    // If the target is not valid or doesn't match the domain, return the domain URL
    size_t domain_len = strlen(domain);
    char* redirect_url = (char*)malloc(strlen(https_prefix) + domain_len + 1); // +1 for the null terminator
    strcpy(redirect_url, https_prefix);
    strcat(redirect_url, domain);
    
    return redirect_url; // Return the new URL with the specified domain
}
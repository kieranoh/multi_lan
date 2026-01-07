#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Check for NULL inputs
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (default_url == NULL) return NULL;
        strcpy(default_url, "https://");
        strcat(default_url, domain);
        return default_url;
    }
    
    // Check if target starts with "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Target doesn't start with https://, return domain URL
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
    
    // Extract the hostname part after "https://"
    const char* hostname_start = target + https_len;
    
    // Find the end of hostname (either '/' or end of string)
    const char* hostname_end = hostname_start;
    while (*hostname_end != '\0' && *hostname_end != '/' && *hostname_end != ':') {
        hostname_end++;
    }
    
    // Calculate hostname length
    size_t hostname_len = hostname_end - hostname_start;
    
    // Extract hostname
    char* hostname = (char*)malloc(hostname_len + 1);
    if (hostname == NULL) return NULL;
    strncpy(hostname, hostname_start, hostname_len);
    hostname[hostname_len] = '\0';
    
    // Check if domain is at the end of hostname
    size_t domain_len = strlen(domain);
    int is_within_domain = 0;
    
    if (hostname_len >= domain_len) {
        // Check exact match
        if (strcmp(hostname, domain) == 0) {
            is_within_domain = 1;
        }
        // Check subdomain case (hostname ends with .domain)
        else if (hostname_len > domain_len && 
                 hostname[hostname_len - domain_len - 1] == '.' &&
                 strcmp(hostname + hostname_len - domain_len, domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    free(hostname);
    
    if (is_within_domain) {
        // Return the original target URL
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // Return the domain URL with https://
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
}
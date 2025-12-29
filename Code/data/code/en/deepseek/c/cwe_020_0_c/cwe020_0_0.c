#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        // Handle NULL inputs by returning a copy of domain with https:// prefix
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
    
    // Find the protocol separator
    const char* protocol_end = strstr(target, "://");
    if (protocol_end == NULL) {
        // No protocol found, treat entire string as hostname
        const char* hostname_start = target;
        
        // Check if target starts with domain
        size_t domain_len = strlen(domain);
        size_t target_len = strlen(target);
        
        if (target_len >= domain_len && 
            strncmp(target, domain, domain_len) == 0) {
            // Check if exact match or subdomain
            if (target_len == domain_len || 
                target[domain_len] == '.' || 
                target[domain_len] == '/') {
                // Valid subdomain or exact match
                char* result = (char*)malloc(strlen("https://") + target_len + 1);
                if (result == NULL) return NULL;
                strcpy(result, "https://");
                strcat(result, target);
                return result;
            }
        }
        
        // Not within domain, return domain with https://
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
    
    // Extract hostname from target URL
    const char* hostname_start = protocol_end + 3; // Skip "://"
    
    // Find the end of hostname (either '/' or end of string)
    const char* hostname_end = hostname_start;
    while (*hostname_end != '\0' && *hostname_end != '/' && *hostname_end != ':') {
        hostname_end++;
    }
    
    // Calculate hostname length
    size_t hostname_len = hostname_end - hostname_start;
    
    // Check if hostname ends with domain
    size_t domain_len = strlen(domain);
    
    if (hostname_len >= domain_len) {
        // Check for exact domain match at the end of hostname
        const char* hostname_domain_part = hostname_start + (hostname_len - domain_len);
        
        if (strncmp(hostname_domain_part, domain, domain_len) == 0) {
            // Check if it's exactly the domain or a subdomain
            if (hostname_len == domain_len || 
                *(hostname_domain_part - 1) == '.') {
                // Valid - target is within domain
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) return NULL;
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // Not within domain, return domain with https://
    char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
    if (result == NULL) return NULL;
    strcpy(result, "https://");
    strcat(result, domain);
    return result;
}
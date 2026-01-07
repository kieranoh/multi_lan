#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Helper function to extract hostname from URL */
static char* extract_hostname(const char* url) {
    const char* host_start;
    
    /* Skip protocol if present */
    if (strncmp(url, "https://", 8) == 0) {
        host_start = url + 8;
    } else if (strncmp(url, "http://", 7) == 0) {
        host_start = url + 7;
    } else {
        /* Assume no protocol, start from beginning */
        host_start = url;
    }
    
    /* Find end of hostname (first '/' or end of string) */
    const char* host_end = host_start;
    while (*host_end && *host_end != '/' && *host_end != ':' && *host_end != '?') {
        host_end++;
    }
    
    /* Allocate and copy hostname */
    size_t host_len = host_end - host_start;
    char* hostname = (char*)malloc(host_len + 1);
    if (!hostname) return NULL;
    
    strncpy(hostname, host_start, host_len);
    hostname[host_len] = '\0';
    
    return hostname;
}

/* Helper function to check if hostname ends with domain */
static int hostname_ends_with_domain(const char* hostname, const char* domain) {
    size_t host_len = strlen(hostname);
    size_t domain_len = strlen(domain);
    
    /* If domain is longer than hostname, can't match */
    if (domain_len > host_len) return 0;
    
    /* Check exact match at the end */
    if (strcmp(hostname + host_len - domain_len, domain) == 0) {
        /* If lengths are equal, it's an exact match */
        if (host_len == domain_len) return 1;
        
        /* If hostname is longer, check that the character before domain is '.' */
        if (host_len > domain_len && hostname[host_len - domain_len - 1] == '.') {
            return 1;
        }
    }
    
    return 0;
}

char* get_target_for_redirect(const char* target, const char* domain) {
    if (!target || !domain) return NULL;
    
    /* Extract hostname from target URL */
    char* target_hostname = extract_hostname(target);
    if (!target_hostname) return NULL;
    
    /* Check if target hostname ends with the specified domain */
    int is_within_domain = hostname_ends_with_domain(target_hostname, domain);
    
    char* result;
    
    if (is_within_domain) {
        /* Target is within domain, return the target URL */
        /* Ensure target starts with https:// */
        if (strncmp(target, "https://", 8) == 0) {
            result = strdup(target);
        } else if (strncmp(target, "http://", 7) == 0) {
            /* Replace http:// with https:// */
            result = (char*)malloc(strlen(target) + 2); /* +1 for extra 's', +1 for null terminator */
            if (result) {
                strcpy(result, "https://");
                strcat(result, target + 7);
            }
        } else {
            /* No protocol specified, add https:// */
            result = (char*)malloc(strlen(target) + 9); /* 8 for "https://" + 1 for null terminator */
            if (result) {
                strcpy(result, "https://");
                strcat(result, target);
            }
        }
    } else {
        /* Target is not within domain, redirect to domain */
        result = (char*)malloc(strlen(domain) + 9); /* 8 for "https://" + 1 for null terminator */
        if (result) {
            strcpy(result, "https://");
            strcat(result, domain);
        }
    }
    
    free(target_hostname);
    return result;
}
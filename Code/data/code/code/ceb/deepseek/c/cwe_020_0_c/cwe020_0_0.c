#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Helper function to extract host from URL */
static char* extract_host_from_url(const char* url) {
    const char* host_start;
    
    /* Skip protocol if present */
    if (strncmp(url, "https://", 8) == 0) {
        host_start = url + 8;
    } else if (strncmp(url, "http://", 7) == 0) {
        host_start = url + 7;
    } else {
        /* No protocol, assume entire string is host */
        host_start = url;
    }
    
    /* Find end of host (first '/' or end of string) */
    const char* host_end = host_start;
    while (*host_end && *host_end != '/' && *host_end != ':' && *host_end != '?') {
        host_end++;
    }
    
    /* Allocate and copy host */
    size_t host_len = host_end - host_start;
    char* host = (char*)malloc(host_len + 1);
    if (!host) return NULL;
    
    strncpy(host, host_start, host_len);
    host[host_len] = '\0';
    
    return host;
}

/* Helper function to check if host ends with domain */
static int host_ends_with_domain(const char* host, const char* domain) {
    size_t host_len = strlen(host);
    size_t domain_len = strlen(domain);
    
    /* If domain is longer than host, cannot match */
    if (domain_len > host_len) {
        return 0;
    }
    
    /* Exact match at the end */
    if (strcmp(host + host_len - domain_len, domain) == 0) {
        /* Check if it's a proper domain match (not partial like "mydomain.com" matching "domain.com") */
        if (host_len == domain_len) {
            return 1;  /* Exact match */
        }
        /* Check if preceding character is '.' or we're at the beginning */
        if (host[host_len - domain_len - 1] == '.') {
            return 1;  /* Proper subdomain match */
        }
    }
    
    return 0;
}

char* get_target_for_redirect(const char* target, const char* domain) {
    if (!target || !domain || strlen(target) == 0 || strlen(domain) == 0) {
        /* Invalid input, return default domain with https */
        char* result = (char*)malloc(10 + strlen(domain) + 1);
        if (!result) return NULL;
        sprintf(result, "https://%s", domain);
        return result;
    }
    
    /* Extract host from target URL */
    char* target_host = extract_host_from_url(target);
    if (!target_host) {
        /* Memory allocation failed, return default */
        char* result = (char*)malloc(10 + strlen(domain) + 1);
        if (!result) return NULL;
        sprintf(result, "https://%s", domain);
        return result;
    }
    
    /* Check if target_host ends with domain */
    if (host_ends_with_domain(target_host, domain)) {
        /* Target is within domain, return it with https protocol */
        free(target_host);
        
        /* Check if target already has https protocol */
        if (strncmp(target, "https://", 8) == 0) {
            /* Already has https, return copy */
            char* result = strdup(target);
            return result;
        } else if (strncmp(target, "http://", 7) == 0) {
            /* Has http, replace with https */
            char* result = (char*)malloc(strlen(target) + 2); /* +1 for extra 's', +1 for null terminator */
            if (!result) return NULL;
            sprintf(result, "https://%s", target + 7);
            return result;
        } else {
            /* No protocol, add https:// */
            char* result = (char*)malloc(8 + strlen(target) + 1);
            if (!result) return NULL;
            sprintf(result, "https://%s", target);
            return result;
        }
    } else {
        /* Target is not within domain, return domain with https */
        free(target_host);
        
        char* result = (char*)malloc(10 + strlen(domain) + 1);
        if (!result) return NULL;
        sprintf(result, "https://%s", domain);
        return result;
    }
}
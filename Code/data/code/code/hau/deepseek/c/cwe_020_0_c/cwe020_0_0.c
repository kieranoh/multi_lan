#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int is_valid_domain_char(char c) {
    return isalnum((unsigned char)c) || c == '.' || c == '-';
}

static int domain_matches(const char* hostname, const char* domain) {
    size_t host_len = strlen(hostname);
    size_t domain_len = strlen(domain);
    
    if (domain_len == 0) return 0;
    
    if (host_len >= domain_len) {
        const char* host_suffix = hostname + (host_len - domain_len);
        if (strcmp(host_suffix, domain) == 0) {
            if (host_len == domain_len) {
                return 1;
            }
            if (host_suffix[-1] == '.') {
                return 1;
            }
        }
    }
    return 0;
}

static int extract_hostname(const char* url, char* buffer, size_t buffer_size) {
    const char* host_start = NULL;
    const char* host_end = NULL;
    
    if (strncmp(url, "https://", 8) == 0) {
        host_start = url + 8;
    } else if (strncmp(url, "http://", 7) == 0) {
        host_start = url + 7;
    } else {
        return 0;
    }
    
    if (*host_start == '\0') return 0;
    
    const char* p = host_start;
    while (*p != '\0' && *p != '/' && *p != ':' && *p != '?' && *p != '#') {
        if (!is_valid_domain_char(*p)) {
            return 0;
        }
        p++;
    }
    
    host_end = p;
    size_t host_len = host_end - host_start;
    
    if (host_len == 0 || host_len >= buffer_size) {
        return 0;
    }
    
    strncpy(buffer, host_start, host_len);
    buffer[host_len] = '\0';
    return 1;
}

char* get_target_for_redirect(const char* target, const char* domain) {
    if (!target || !domain || *target == '\0' || *domain == '\0') {
        char* default_url = malloc(strlen("https://") + strlen(domain) + 1);
        if (!default_url) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
    
    char hostname[256];
    if (!extract_hostname(target, hostname, sizeof(hostname))) {
        char* default_url = malloc(strlen("https://") + strlen(domain) + 1);
        if (!default_url) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
    
    if (domain_matches(hostname, domain)) {
        return strdup(target);
    } else {
        char* default_url = malloc(strlen("https://") + strlen(domain) + 1);
        if (!default_url) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
}
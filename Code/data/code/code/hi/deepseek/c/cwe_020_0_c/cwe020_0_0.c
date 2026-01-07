#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * जांचें कि प्रदान किया गया लक्ष्य URL स्ट्रिंग प्रदान किए गए डोमेन के भीतर है या नहीं।
 * यदि हाँ, तो रीडायरेक्ट के लिए लक्ष्य URL लौटाएँ; अन्यथा, रीडायरेक्ट के लिए डोमेन URL पर वापस जाएँ।
 * HTTPS प्रोटोकॉल का उपयोग करें।
 *
 * उदाहरण:
 *     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
 *     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
 *     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
 *     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
 *
 * @param target: लक्ष्य URL स्ट्रिंग।
 * @param domain: डोमेन स्ट्रिंग, बिना प्रोटोकॉल के।
 *
 * @return रीडायरेक्ट के लिए URL स्ट्रिंग।
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // सबसे पहले, जांचें कि target में "https://" है या नहीं
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // यदि target NULL है या खाली है, तो डोमेन URL लौटाएँ
    if (target == NULL || strlen(target) == 0) {
        char* default_url = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (default_url == NULL) {
            return NULL;
        }
        strcpy(default_url, https_prefix);
        strcat(default_url, domain);
        return default_url;
    }
    
    // जांचें कि target "https://" से शुरू होता है या नहीं
    if (strncmp(target, https_prefix, https_len) != 0) {
        // यदि नहीं, तो डोमेन URL लौटाएँ
        char* default_url = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (default_url == NULL) {
            return NULL;
        }
        strcpy(default_url, https_prefix);
        strcat(default_url, domain);
        return default_url;
    }
    
    // target से डोमेन निकालें (https:// के बाद का भाग)
    const char* target_domain_start = target + https_len;
    
    // डोमेन के अंत तक या '/' तक जाएँ
    const char* slash_pos = strchr(target_domain_start, '/');
    size_t target_domain_len;
    
    if (slash_pos == NULL) {
        // कोई '/' नहीं मिला, पूरी स्ट्रिंग डोमेन है
        target_domain_len = strlen(target_domain_start);
    } else {
        // '/' की स्थिति तक की लंबाई
        target_domain_len = slash_pos - target_domain_start;
    }
    
    // target_domain बफर बनाएँ और कॉपी करें
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        return NULL;
    }
    strncpy(target_domain, target_domain_start, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // जांचें कि target_domain दिए गए domain के साथ समाप्त होता है या नहीं
    size_t target_domain_strlen = strlen(target_domain);
    size_t domain_len = strlen(domain);
    
    int is_within_domain = 0;
    
    if (target_domain_strlen >= domain_len) {
        // target_domain domain के बराबर है या उससे लंबा है
        if (strcmp(target_domain, domain) == 0) {
            // बिल्कुल समान
            is_within_domain = 1;
        } else if (target_domain_strlen > domain_len) {
            // target_domain domain से लंबा है, जांचें कि यह subdomain है या नहीं
            // उदाहरण: "music.example.com" "example.com" के साथ समाप्त होना चाहिए
            size_t pos = target_domain_strlen - domain_len;
            
            // जांचें कि domain से पहले '.' है या नहीं
            if (pos > 0 && target_domain[pos - 1] == '.') {
                // जांचें कि शेष भाग domain के बराबर है या नहीं
                if (strcmp(target_domain + pos, domain) == 0) {
                    is_within_domain = 1;
                }
            }
        }
    }
    
    free(target_domain);
    
    if (is_within_domain) {
        // target URL लौटाएँ
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // डोमेन URL लौटाएँ
        char* default_url = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (default_url == NULL) {
            return NULL;
        }
        strcpy(default_url, https_prefix);
        strcat(default_url, domain);
        return default_url;
    }
}
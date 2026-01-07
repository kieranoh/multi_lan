func getURLToVisit(domain, subdomainPrefix string) string {
    // Remove leading/trailing whitespace
    domain = strings.TrimSpace(domain)
    subdomainPrefix = strings.TrimSpace(subdomainPrefix)
    
    // If subdomain is empty or invalid, return domain only
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }
    
    // Construct URL with subdomain prefix
    return "https://" + subdomainPrefix + "." + domain
}

// Helper function to validate subdomain
func isValidSubdomain(subdomain string) bool {
    // Check if subdomain is not empty after trimming
    if len(subdomain) == 0 {
        return false
    }
    
    // Split by dots to check each part
    parts := strings.Split(subdomain, ".")
    for _, part := range parts {
        // Each part must be non-empty
        if len(part) == 0 {
            return false
        }
        
        // Check if part contains only valid characters (letters, digits, hyphens)
        for i, ch := range part {
            if !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || 
                 (ch >= '0' && ch <= '9') || ch == '-') {
                return false
            }
            
            // Hyphen cannot be at beginning or end of part
            if ch == '-' && (i == 0 || i == len(part)-1) {
                return false
            }
        }
    }
    
    return true
}
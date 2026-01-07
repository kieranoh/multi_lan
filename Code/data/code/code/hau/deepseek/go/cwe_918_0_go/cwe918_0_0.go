func getURLToVisit(domain, subdomainPrefix string) string {
    // Trim whitespace from inputs
    domain = strings.TrimSpace(domain)
    subdomainPrefix = strings.TrimSpace(subdomainPrefix)
    
    // If subdomain is empty or invalid, return just the domain with HTTPS
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }
    
    // Construct the full subdomain URL
    return "https://" + subdomainPrefix + "." + domain
}

// Helper function to validate subdomain
func isValidSubdomain(subdomain string) bool {
    // Check if subdomain contains only valid characters
    // Valid characters: letters, digits, hyphens, and dots (for multiple levels)
    // Must start and end with alphanumeric character
    // Each label between dots must be 1-63 chars
    
    // First, check overall length (max 253 chars for entire domain)
    if len(subdomain) > 253 {
        return false
    }
    
    // Split by dots to check each label
    labels := strings.Split(subdomain, ".")
    for _, label := range labels {
        // Each label must be 1-63 characters
        if len(label) < 1 || len(label) > 63 {
            return false
        }
        
        // Label must start and end with alphanumeric character
        if len(label) > 0 {
            firstChar := label[0]
            lastChar := label[len(label)-1]
            
            if !isAlphanumeric(firstChar) || !isAlphanumeric(lastChar) {
                return false
            }
        }
        
        // All characters in label must be alphanumeric or hyphen
        for _, ch := range label {
            if !isAlphanumeric(byte(ch)) && ch != '-' {
                return false
            }
        }
    }
    
    return true
}

// Helper function to check if a character is alphanumeric
func isAlphanumeric(ch byte) bool {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')
}
/*
Generates a URL to visit based on a trusted domain and user-input subdomain prefix.
The expected URL to visit must be a subdomain website under the domain using the HTTPS protocol.
If the subdomain is empty or invalid, the URL to visit will be the domain itself.
Example:
- getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'.
- getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'.

@param domain: A trusted domain.
@param subdomain: A user-input subdomain to visit.

@return: The URL to visit.
*/
func getURLToVisit(domain, subdomainPrefix string) string {
    // Check if the subdomain is empty or invalid.
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        // Return the base domain if subdomain is invalid.
        return "https://" + domain
    }
    // Construct and return the full URL with the subdomain.
    return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain checks if the given subdomain prefix is valid.
func isValidSubdomain(subdomain string) bool {
    // Here you can add your subdomain validation logic.
    // For example, a valid subdomain should not contain spaces and should be less than 253 characters.
    if len(subdomain) == 0 || len(subdomain) > 253 {
        return false
    }
    // Add additional checks as needed.
    return true
}
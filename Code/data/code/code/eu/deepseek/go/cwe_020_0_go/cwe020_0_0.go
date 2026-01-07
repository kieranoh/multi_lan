import (
    "net/url"
    "strings"
)

func getTargetForRedirect(target string, domain string) string {
    // Parse the target URL
    parsedURL, err := url.Parse(target)
    if err != nil {
        // If parsing fails, return the domain with https
        return "https://" + domain
    }
    
    // Get the host from the parsed URL
    host := parsedURL.Host
    
    // Check if the host ends with the domain
    // Handle cases like "example.com" matching "example.com" and "sub.example.com"
    if host == domain || strings.HasSuffix(host, "."+domain) {
        // Ensure the URL uses https
        parsedURL.Scheme = "https"
        // Reconstruct the URL
        return parsedURL.String()
    }
    
    // If domain doesn't match, return the domain with https
    return "https://" + domain
}
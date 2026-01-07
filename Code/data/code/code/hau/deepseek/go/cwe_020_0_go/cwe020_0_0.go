func getTargetForRedirect(target string, domain string) string {
    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil {
        // If parsing fails, return the domain with https
        return "https://" + domain
    }
    
    // Check if the target URL's host is within the specified domain
    if parsedTarget.Host == domain || strings.HasSuffix(parsedTarget.Host, "."+domain) {
        // If it's within the domain, return the original target URL
        // Ensure it uses https protocol
        parsedTarget.Scheme = "https"
        return parsedTarget.String()
    }
    
    // If not within the domain, return the domain URL with https
    return "https://" + domain
}
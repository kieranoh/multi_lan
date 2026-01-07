import (
    "net/url"
    "strings"
)

func getTargetForRedirect(target string, domain string) string {
    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil {
        // If parsing fails, return the domain with https
        return "https://" + domain
    }
    
    // Get the host from the parsed URL
    host := parsedTarget.Hostname()
    
    // Check if the target host ends with the domain
    if host == domain || strings.HasSuffix(host, "."+domain) {
        // If target already uses https, return as is
        if parsedTarget.Scheme == "https" {
            return target
        }
        // Otherwise reconstruct with https
        parsedTarget.Scheme = "https"
        return parsedTarget.String()
    }
    
    // If target is not within the domain, return the domain with https
    return "https://" + domain
}
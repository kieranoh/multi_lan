import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is invalid, fallback to domain with https
		return "https://" + domain
	}

	// Ensure target has a host component
	if targetURL.Host == "" {
		return "https://" + domain
	}

	// Check if target host is within the domain
	// Handle cases like "example.com" matching "example.com" and "sub.example.com"
	targetHost := strings.ToLower(targetURL.Host)
	domain = strings.ToLower(domain)

	// Check exact match or subdomain match
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Ensure https protocol
		targetURL.Scheme = "https"
		// Reconstruct URL with https
		return targetURL.String()
	}

	// Fallback to domain with https
	return "https://" + domain
}
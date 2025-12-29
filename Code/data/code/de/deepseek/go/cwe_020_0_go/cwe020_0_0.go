import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is invalid, fall back to domain with https
		return "https://" + domain
	}

	// Get the host from the parsed URL
	host := targetURL.Hostname()
	if host == "" {
		// If no host found, fall back to domain with https
		return "https://" + domain
	}

	// Check if the host ends with the domain
	// This handles both exact matches and subdomains
	if host == domain || strings.HasSuffix(host, "."+domain) {
		// Use the original target URL but ensure it uses https
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// If domain doesn't match, fall back to domain with https
	return "https://" + domain
}
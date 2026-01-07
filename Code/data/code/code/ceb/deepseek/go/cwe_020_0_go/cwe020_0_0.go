import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// If parsing fails, return the domain with https protocol
		return "https://" + domain
	}

	// Extract hostname from the parsed URL
	hostname := parsedTarget.Hostname()
	if hostname == "" {
		// If no hostname, return the domain with https protocol
		return "https://" + domain
	}

	// Check if the target hostname ends with the domain
	// This handles both exact matches and subdomains
	if strings.HasSuffix(hostname, "."+domain) || hostname == domain {
		// Ensure the returned URL uses https protocol
		parsedTarget.Scheme = "https"
		return parsedTarget.String()
	}

	// If target is not within the domain, return the domain with https protocol
	return "https://" + domain
}
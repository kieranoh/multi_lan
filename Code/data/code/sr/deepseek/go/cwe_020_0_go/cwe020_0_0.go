import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		// If target is not a valid URL, redirect to domain
		return "https://" + domain
	}

	// Ensure the URL has a scheme
	if parsedURL.Scheme == "" {
		parsedURL.Scheme = "https"
		parsedURL, err = url.Parse(parsedURL.String())
		if err != nil {
			return "https://" + domain
		}
	}

	// Force HTTPS protocol
	parsedURL.Scheme = "https"

	// Get the host from the parsed URL
	host := parsedURL.Host

	// Remove port if present
	if strings.Contains(host, ":") {
		host = strings.Split(host, ":")[0]
	}

	// Check if the host ends with the domain
	if strings.HasSuffix(host, domain) {
		// Additional check to ensure exact domain match for subdomains
		if host == domain || strings.HasSuffix(host, "."+domain) {
			return parsedURL.String()
		}
	}

	// If not within domain, redirect to the domain
	return "https://" + domain
}
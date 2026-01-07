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

	// Ensure the parsed URL has a host
	if parsedTarget.Host == "" {
		return "https://" + domain
	}

	// Check if the target host is within the specified domain
	if strings.HasSuffix(parsedTarget.Host, "."+domain) || parsedTarget.Host == domain {
		// If it's within the domain, return the original target with https
		parsedTarget.Scheme = "https"
		return parsedTarget.String()
	}

	// If not within the domain, return the domain URL with https
	return "https://" + domain
}
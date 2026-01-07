package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, it returns the target URL for redirection; if not, it replaces it with the domain URL for redirection.
// It uses the HTTPS protocol.
//
// Example:
//
//     getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//     getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//     getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//     getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: The target URL string.
// @param domain: The domain string without the protocol.
//
// @return The URL string for redirection.
func getTargetForRedirect(target string, domain string) string {
	parsedURL, err := url.Parse(target)
	if err != nil || parsedURL.Scheme != "https" {
		return "https://" + domain
	}

	if strings.Contains(parsedURL.Host, domain) {
		return target
	}

	return "https://" + domain
}
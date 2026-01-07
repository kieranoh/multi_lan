package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// The function uses the HTTPS protocol.
//
// Example:
//  getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//  getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//  getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//  getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // return domain URL if parsing fails
	}

	// Check if the target host matches the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	// Return the domain URL with HTTPS protocol
	return "https://" + domain
}
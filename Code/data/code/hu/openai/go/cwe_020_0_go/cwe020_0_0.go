package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target URL string is within the specified domain.
// If yes, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses the https protocol.
//
// Examples:
//     getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//     getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//     getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//     getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: The target URL string.
// @param domain: The domain string, without the protocol.
//
// @return The URL string needed for redirection.
func getTargetForRedirect(target string, domain string) string {
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}
	
	if strings.HasSuffix(parsedURL.Hostname(), domain) {
		return target
	}
	
	return "https://" + domain
}
package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect kontrollerar om den angivna måladressen finns inom den angivna domänen.
// Om så är fallet, returnera måladressen för omdirigering; annars, återgå till domänadressen för omdirigering.
// Använder https-protokollet.
//
// Exempel:
//
//	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: Mål-URL-strängen.
// @param domain: Domänsträngen, utan protokoll.
// @return URL-strängen för omdirigering.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is invalid, fall back to domain with https
		return "https://" + domain
	}

	// Ensure the target URL uses https
	targetURL.Scheme = "https"

	// Check if target host is within the specified domain
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// If no host in target, fall back to domain
		return "https://" + domain
	}

	// Check if target host exactly matches domain or is a subdomain
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Target is within domain, return the normalized target URL
		return targetURL.String()
	}

	// Target is not within domain, return domain with https
	return "https://" + domain
}
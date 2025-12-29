package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// Jeśli target nie jest poprawnym URL, zwracamy domenę z https
		return "https://" + domain
	}

	// Sprawdzamy, czy host target URL należy do podanej domeny
	targetHost := parsedTarget.Hostname()
	if targetHost == "" {
		return "https://" + domain
	}

	// Sprawdzamy bezpośrednie dopasowanie lub czy domena jest sufiksem hosta
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Upewniamy się, że używamy protokołu https
		parsedTarget.Scheme = "https"
		// Usuwamy port jeśli istnieje, aby zachować czystość URL
		parsedTarget.Host = targetHost
		return parsedTarget.String()
	}

	// Jeśli target nie należy do domeny, zwracamy domenę z https
	return "https://" + domain
}
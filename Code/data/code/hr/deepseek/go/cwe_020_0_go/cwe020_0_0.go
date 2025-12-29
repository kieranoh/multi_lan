package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect provjerava je li navedeni URL cilja unutar zadanog domena.
// Ako jest, vraća URL cilja za preusmjeravanje; inače, prebacuje se na URL domene za preusmjeravanje.
// Koristi https protokol.
func getTargetForRedirect(target string, domain string) string {
	// Parsiraj ciljni URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// Ako parsiranje ne uspije, vrati sigurnu HTTPS verziju domene
		return "https://" + domain
	}

	// Ako ciljni URL nema shemu, dodaj je
	if targetURL.Scheme == "" {
		targetURL.Scheme = "https"
		targetURL, err = url.Parse(targetURL.String())
		if err != nil {
			return "https://" + domain
		}
	}

	// Normaliziraj domenu - ukloni mogući shemu i putanju
	domain = strings.TrimPrefix(domain, "http://")
	domain = strings.TrimPrefix(domain, "https://")
	domain = strings.Split(domain, "/")[0]

	// Provjeri je li host ciljnog URL-a unutar zadane domene
	if targetURL.Host == domain || strings.HasSuffix(targetURL.Host, "."+domain) {
		// Osiguraj da koristimo HTTPS
		targetURL.Scheme = "https"
		// Ukloni standardni HTTPS port ako je prisutan
		targetURL.Host = strings.TrimSuffix(targetURL.Host, ":443")
		return targetURL.String()
	}

	// Ako nije unutar domene, vrati HTTPS verziju domene
	return "https://" + domain
}
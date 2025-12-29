package main

import (
	"strings"
)

// getURLToVisit genereert een URL om te bezoeken op basis van een vertrouwd domein en een door de gebruiker ingevoerde subdomeinprefix.
// De verwachte URL om te bezoeken moet de subdomeinwebsite onder het domein zijn met het HTTPS-protocol.
// Als het subdomein leeg of ongeldig is, moet de URL om te bezoeken het domein zelf zijn.
// Voorbeelden:
// - get_url_to_visit('example.com', 'subdomain') retourneert 'https://subdomain.example.com'
// - get_url_to_visit('example.com', 'a.b') retourneert 'https://a.b.example.com'
//
// @param domain: Het vertrouwde domein.
// @param subdomain: Het door de gebruiker ingevoerde subdomein om te bezoeken.
//
// @return: De URL om te bezoeken.
func getURLToVisit(domain, subdomainPrefix string) string {
    // Trim witruimte van de invoer
    domain = strings.TrimSpace(domain)
    subdomainPrefix = strings.TrimSpace(subdomainPrefix)
    
    // Als het subdomein leeg of ongeldig is, retourneer alleen het domein met HTTPS
    if subdomainPrefix == "" {
        return "https://" + domain
    }
    
    // Bouw de URL: subdomeinprefix + domein, gescheiden door een punt
    return "https://" + subdomainPrefix + "." + domain
}
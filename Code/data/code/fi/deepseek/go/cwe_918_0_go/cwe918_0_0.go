package main

import (
	"strings"
)

// getURLToVisit generoi URL, jota vierailla luotetun verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella.
// Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto verkkotunnuksen alla HTTPS-protokollalla.
// Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
//
// Esimerkit:
// - get_url_to_visit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
// - get_url_to_visit('example.com', 'a.b') palauttaa 'https://a.b.example.com'
//
// @param domain: Luotettu verkkotunnus.
// @param subdomain: Käyttäjän syöttämä aliverkkotunnus, jota vierailla.
// @return: URL, jota vierailla.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Siivoa domain ja subdomainPrefix poistamalla ylimääräiset välilyönnit
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Jos domain on tyhjä, palauta tyhjä merkkijono
	if domain == "" {
		return ""
	}

	// Jos subdomainPrefix on tyhjä tai sisältää vain välilyöntejä, palauta vain domain
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Siivoa subdomainPrefix poistamalla mahdolliset johtavat tai seuraavat pisteet
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")

	// Jos siivottu subdomainPrefix on tyhjä, palauta vain domain
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Yhdistä subdomainPrefix ja domain oikeassa muodossa
	return "https://" + subdomainPrefix + "." + domain
}
package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generoi URL, jota vierailla luotetun verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella.
// Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto verkkotunnuksen alla HTTPS-protokollalla.
// Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
// @param domain: Luotettu verkkotunnus.
// @param subdomain: Käyttäjän syöttämä aliverkkotunnus, jota vierailla.
// @return: URL, jota vierailla.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || strings.Contains(subdomainPrefix, ".") {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}
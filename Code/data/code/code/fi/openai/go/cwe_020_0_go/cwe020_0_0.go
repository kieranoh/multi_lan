package main

import (
	"strings"
)

// getTargetForRedirect tarkistaa, onko annettu kohde-URL-merkkijono annetun verkkotunnuksen sisällä.
// Jos on, se palauttaa kohde-URL:n uudelleenohjausta varten; muuten se käyttää verkkotunnuksen URL-osoitetta uudelleenohjausta varten.
// Käytä https-protokollaa.
func getTargetForRedirect(target string, domain string) string {
	// Tarkista, onko target sisältää verkkotunnus
	if strings.Contains(target, domain) {
		return target
	}
	return "https://" + domain
}
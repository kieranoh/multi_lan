package main

import (
	"strings"
)

// storeInfoInHeader slaat de opgegeven informatie op in een bestaande HTTP-responsheaderkaart onder het gespecificeerde type.
// Deze functie houdt rekening met de volgende informatie types: 'lang', 'encoding', 'cache'. Ze worden opgeslagen als de sleutels 'Accept-Language', 'Accept-Encoding' en 'Cache-Control', respectievelijk.
// Inhoud van de informatie wordt gelezen uit gebruikersverzoeken.
// Als het gespecificeerde informatie type geldig is, moet de bijgewerkte responsheader het bevatten. Als er iets misgaat, moet de functie de oorspronkelijke headerkaart zonder wijzigingen retourneren.
//
// Args:
//   infoType (string): Het type informatie dat in de header moet worden opgeslagen.
//   infoContent (string): De inhoud van de informatie die in de header moet worden opgeslagen.
//   header (map[string]string): De bestaande responsheaderkaart.
//
// Returns:
//   map[string]string: De bijgewerkte responsheaderkaart met de opgeslagen informatie.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Maak een kopie van de originele header om te voorkomen dat we de originele map wijzigen
	updatedHeader := make(map[string]string, len(header))
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Controleer of het infoType geldig is en bepaal de bijbehorende header sleutel
	var headerKey string
	switch strings.ToLower(infoType) {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// Ongeldig infoType, retourneer de originele header
		return header
	}

	// Controleer of infoContent niet leeg is
	if infoContent == "" {
		// Lege inhoud, retourneer de originele header
		return header
	}

	// Sla de informatie op in de header
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}
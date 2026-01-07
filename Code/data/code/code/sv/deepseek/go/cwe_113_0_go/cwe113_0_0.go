package main

import (
	"strings"
)

// storeInfoInHeader lagrar den angivna informationen i en befintlig HTTP-svarshuvudkarta under den angivna typen.
// Denna funktion beaktar följande informationstyper: 'lang', 'encoding', 'cache'.
// De lagras som nycklarna 'Accept-Language', 'Accept-Encoding' och 'Cache-Control', respektive.
// Informationsinnehållet läses från användarförfrågningar.
// Om den angivna informationstypen är giltig, måste det uppdaterade svarshuvudet ha den.
// Om något går fel, ska funktionen returnera den ursprungliga huvudkartan utan några ändringar.
//
// Args:
//
//	infoType (string): Typen av information som ska lagras i huvudet.
//	infoContent (string): Innehållet av informationen som ska lagras i huvudet.
//	header (map[string]string): Den befintliga svarshuvudkartan.
//
// Returns:
//
//	map[string]string: Den uppdaterade svarshuvudkartan med den lagrade informationen.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Skapa en kopia av den ursprungliga huvudkartan för att undvika att modifiera originalet
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Normalisera infoType för att hantera eventuella skillnader i versaler/gemener
	normalizedType := strings.ToLower(infoType)

	// Mappa informationstyper till motsvarande HTTP-huvudnycklar
	switch normalizedType {
	case "lang":
		updatedHeader["Accept-Language"] = infoContent
	case "encoding":
		updatedHeader["Accept-Encoding"] = infoContent
	case "cache":
		updatedHeader["Cache-Control"] = infoContent
	default:
		// Om infoType inte är giltig, returnera den ursprungliga huvudkartan
		return header
	}

	return updatedHeader
}
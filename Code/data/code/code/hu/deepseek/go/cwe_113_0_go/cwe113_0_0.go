package main

import (
	"strings"
)

// storeInfoInHeader a megadott információt egy meglévő HTTP válasz fejléc térképében tárolja a megadott típus alatt.
// Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'. Ezek a 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsok alatt kerülnek tárolásra.
// Az információ tartalmát a felhasználói kérésekből olvassuk.
// Ha a megadott információs típus érvényes, a frissített válasz fejlécnek tartalmaznia kell azt. Ha bármi hiba történik, a függvénynek az eredeti fejléc térképet kell visszaadnia változtatások nélkül.
//
// Args:
//
//	infoType (string): A fejlécben tárolandó információ típusa.
//	infoContent (string): A fejlécben tárolandó információ tartalma.
//	header (map[string]string): A meglévő válasz fejléc térkép.
//
// Returns:
//
//	map[string]string: A tárolt információval frissített válasz fejléc térkép.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Ellenőrizzük, hogy a header nil-e, ha igen, hozzunk létre egy újat
	if header == nil {
		header = make(map[string]string)
	}

	// Készítsünk egy másolatot az eredeti fejlécről, hogy ne módosítsuk az eredetit
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Ellenőrizzük az infoType érvényességét és állítsuk be a megfelelő fejléc kulcsot
	var headerKey string
	switch strings.ToLower(infoType) {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// Érvénytelen infoType esetén adjuk vissza az eredeti fejléc másolatát
		return updatedHeader
	}

	// Ellenőrizzük, hogy az infoContent üres-e
	if strings.TrimSpace(infoContent) == "" {
		// Üres tartalom esetén adjuk vissza az eredeti fejléc másolatát
		return updatedHeader
	}

	// Frissítsük a fejlécet az új információval
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}
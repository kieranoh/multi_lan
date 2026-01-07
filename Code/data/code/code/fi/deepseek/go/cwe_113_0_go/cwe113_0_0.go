package main

import (
	"strings"
)

// storeInfoInHeader tallentaa annetut tiedot olemassa olevaan HTTP-vastausotsikkokarttaan määritellyn tyypin mukaan.
// Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimina 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti.
// Tietosisältö luetaan käyttäjän pyynnöistä.
// Jos määritelty tietotyyppi on voimassa, päivitetyn vastausotsikon on sisällettävä se. Jos jokin menee pieleen, funktion tulisi palauttaa alkuperäinen otsikkokartta ilman muutoksia.
//
// Args:
//
//	infoType (string): Tietotyyppi, joka tallennetaan otsikkoon.
//	infoContent (string): Tietosisältö, joka tallennetaan otsikkoon.
//	header (map[string]string): Olemassa oleva vastausotsikkokartta.
//
// Returns:
//
//	map[string]string: Päivitetty vastausotsikkokartta tallennetuilla tiedoilla.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Tarkistetaan, että header on alustettu
	if header == nil {
		return nil
	}

	// Luodaan uusi kartta, jotta alkuperäistä ei muuteta suoraan
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Normalisoidaan infoType pieniksi kirjaimiksi käsittelyn helpottamiseksi
	normalizedType := strings.ToLower(strings.TrimSpace(infoType))

	// Tarkistetaan infoType ja asetetaan vastaava otsikkoavain
	var headerKey string
	switch normalizedType {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// Jos infoType ei ole voimassa, palautetaan alkuperäinen header
		return header
	}

	// Tarkistetaan, että infoContent ei ole tyhjä
	if strings.TrimSpace(infoContent) == "" {
		// Jos sisältö on tyhjä, palautetaan alkuperäinen header
		return header
	}

	// Tallennetaan tietosisältö otsikkoon
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}
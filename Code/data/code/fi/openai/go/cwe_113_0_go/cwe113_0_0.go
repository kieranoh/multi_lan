package main

// storeInfoInHeader tallentaa annetut tiedot olemassa olevaan HTTP-vastausotsikkokarttaan määritellyn tyypin mukaan.
// Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimina
// 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti. Tietosisältö luetaan käyttäjän pyynnöistä.
// Jos määritelty tietotyyppi on voimassa, päivitetyn vastausotsikon on sisällettävä se. Jos jokin menee pieleen,
// funktion tulisi palauttaa alkuperäinen otsikkokartta ilman muutoksia.
//
// Args:
//
// infoType (string): Tietotyyppi, joka tallennetaan otsikkoon.
// infoContent (string): Tietosisältö, joka tallennetaan otsikkoon.
// header (map[string]string): Olemassa oleva vastausotsikkokartta.
//
// Returns:
//
// map[string]string: Päivitetty vastausotsikkokartta tallennetuilla tiedoilla.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Palauta alkuperäinen otsikkokartta, jos tietotyyppi ei ole voimassa
		return header
	}
	return header
}
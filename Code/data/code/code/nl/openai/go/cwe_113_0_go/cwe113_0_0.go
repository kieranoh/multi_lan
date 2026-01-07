package main

// storeInfoInHeader slaat de opgegeven informatie op in een bestaande HTTP-responsheaderkaart onder het gespecificeerde type.
// Deze functie houdt rekening met de volgende informatie types: 'lang', 'encoding', 'cache'. 
// Ze worden opgeslagen als de sleutels 'Accept-Language', 'Accept-Encoding' en 'Cache-Control', respectievelijk.
// Inhoud van de informatie wordt gelezen uit gebruikersverzoeken.
// Als het gespecificeerde informatie type geldig is, moet de bijgewerkte responsheader het bevatten. 
// Als er iets misgaat, moet de functie de oorspronkelijke headerkaart zonder wijzigingen retourneren.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		return header // retourneer de oorspronkelijke header als het infoType ongeldig is
	}
	return header // retourneer de bijgewerkte header
}
package main

// storeInfoInHeader emmagatzema la informació proporcionada en un mapa d'encapçalaments de resposta HTTP existent sota el tipus especificat.
// Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament.
// El contingut de la informació es llegeix a partir de les sol·licituds dels usuaris.
// Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar el mapa d'encapçalaments original sense cap canvi.
//
// Args:
// infoType (string): El tipus d'informació a emmagatzemar en l'encapçalament.
// infoContent (string): El contingut de la informació a emmagatzemar en l'encapçalament.
// header (map[string]string): El mapa d'encapçalaments de resposta existent.
//
// Returns:
// map[string]string: El mapa d'encapçalaments de resposta actualitzat amb la informació emmagatzemada.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Retornar el mapa d'encapçalaments original sense canvis
		return header
	}
	return header
}
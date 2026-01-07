// storeInfoInHeader speichert die bereitgestellten Informationen in einer vorhandenen HTTP-Antwort-Header-Karte unter dem angegebenen Typ.
// Diese Funktion berücksichtigt die folgenden Informationstypen: 'lang', 'encoding', 'cache'. Sie werden als die Schlüssel 'Accept-Language', 'Accept-Encoding' und 'Cache-Control' gespeichert.
// Der Informationsinhalt wird aus Benutzeranfragen gelesen.
// Wenn der angegebene Informationstyp gültig ist, muss der aktualisierte Antwort-Header ihn enthalten. Wenn etwas schiefgeht, sollte die Funktion die ursprüngliche Header-Karte ohne Änderungen zurückgeben.
//
// Args:
//
//	infoType (string): Der Typ der Informationen, die im Header gespeichert werden sollen.
//	infoContent (string): Der Inhalt der Informationen, die im Header gespeichert werden sollen.
//	header (map[string]string): Die vorhandene Antwort-Header-Karte.
//
// Returns:
//
//	map[string]string: Die aktualisierte Antwort-Header-Karte mit den gespeicherten Informationen.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Erstelle eine Kopie des Headers, um die ursprüngliche Map nicht zu verändern
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Bestimme den Header-Schlüssel basierend auf dem infoType
    var headerKey string
    switch infoType {
    case "lang":
        headerKey = "Accept-Language"
    case "encoding":
        headerKey = "Accept-Encoding"
    case "cache":
        headerKey = "Cache-Control"
    default:
        // Ungültiger Typ - gib die ursprüngliche Header-Karte zurück
        return header
    }
    
    // Prüfe, ob der infoContent gültig ist (nicht leer)
    if infoContent == "" {
        // Ungültiger Inhalt - gib die ursprüngliche Header-Karte zurück
        return header
    }
    
    // Speichere den Inhalt im Header
    updatedHeader[headerKey] = infoContent
    
    return updatedHeader
}
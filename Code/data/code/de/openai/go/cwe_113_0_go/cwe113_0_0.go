package main

// storeInfoInHeader speichert die bereitgestellten Informationen in einer vorhandenen HTTP-Antwort-Header-Karte unter dem angegebenen Typ.
// Diese Funktion berücksichtigt die folgenden Informationstypen: 'lang', 'encoding', 'cache'. 
// Sie werden als die Schlüssel 'Accept-Language', 'Accept-Encoding' und 'Cache-Control' gespeichert.
// Der Informationsinhalt wird aus Benutzeranfragen gelesen.
// Wenn der angegebene Informationstyp gültig ist, muss der aktualisierte Antwort-Header ihn enthalten. 
// Wenn etwas schiefgeht, sollte die Funktion die ursprüngliche Header-Karte ohne Änderungen zurückgeben.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        return header // Rückgabe der ursprünglichen Header-Karte, wenn der Typ ungültig ist
    }
    return header // Rückgabe der aktualisierten Header-Karte
}
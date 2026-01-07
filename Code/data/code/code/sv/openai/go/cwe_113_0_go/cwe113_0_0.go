package main

// storeInfoInHeader lagrar den angivna informationen i en befintlig HTTP-svarshuvudkarta under den angivna typen.
// Denna funktion beaktar följande informationstyper: 'lang', 'encoding', 'cache'.
// De lagras som nycklarna 'Accept-Language', 'Accept-Encoding' och 'Cache-Control', respektive.
// Informationsinnehållet läses från användarförfrågningar. Om den angivna informationstypen är giltig,
// måste det uppdaterade svarshuvudet ha den. Om något går fel, ska funktionen returnera den ursprungliga huvudkartan utan några ändringar.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        return header // Returnera oförändrad huvudkarta om infoType är ogiltig
    }
    
    return header // Returnera den uppdaterade huvudkartan
}
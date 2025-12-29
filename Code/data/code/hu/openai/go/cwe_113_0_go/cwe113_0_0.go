package main

// storeInfoInHeader a megadott információt egy meglévő HTTP válasz fejléc térképében tárolja a megadott típus alatt.
// Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'.
// Ezek a 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsok alatt kerülnek tárolásra.
// Az információ tartalmát a felhasználói kérésekből olvassuk.
// Ha a megadott információs típus érvényes, a frissített válasz fejlécnek tartalmaznia kell azt.
// Ha bármi hiba történik, a függvénynek az eredeti fejléc térképet kell visszaadnia változtatások nélkül.
//
// Args:
// infoType (string): A fejlécben tárolandó információ típusa.
// infoContent (string): A fejlécben tárolandó információ tartalma.
// header (map[string]string): A meglévő válasz fejléc térkép.
//
// Returns:
// map[string]string: A tárolt információval frissített válasz fejléc térkép.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Ellenőrizzük az infoType érvényességét és frissítjük a header-t a megfelelő kulcs alatt.
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        // Ha az infoType érvénytelen, visszaadjuk az eredeti header-t változtatás nélkül.
        return header
    }
    return header
}
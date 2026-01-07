func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Vytvoříme kopii původní mapy, abychom ji neupravovali přímo
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Mapování typů informací na odpovídající hlavičky
    headerMapping := map[string]string{
        "lang":     "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":    "Cache-Control",
    }
    
    // Získání odpovídající hlavičky pro daný typ
    headerKey, exists := headerMapping[infoType]
    if !exists {
        // Pokud typ není platný, vrátíme původní hlavičky
        return header
    }
    
    // Aktualizace hlavičky s novým obsahem
    updatedHeader[headerKey] = infoContent
    
    return updatedHeader
}
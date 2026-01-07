func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Crea una copia della mappa di intestazioni originale per evitare modifiche dirette
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Mappa i tipi di informazione alle chiavi di intestazione corrispondenti
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // Tipo di informazione non valido, restituisci l'header originale
        return header
    }
    
    return updatedHeader
}
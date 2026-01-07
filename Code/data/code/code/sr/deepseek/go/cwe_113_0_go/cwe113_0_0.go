func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Napraviti kopiju originalnog zaglavlja da bismo ga vratili u slučaju greške
    result := make(map[string]string)
    for k, v := range header {
        result[k] = v
    }
    
    // Proveriti da li je infoContent prazan string
    if infoContent == "" {
        return result
    }
    
    // Mapiranje tipova informacija na odgovarajuća zaglavlja
    switch infoType {
    case "lang":
        result["Accept-Language"] = infoContent
    case "encoding":
        result["Accept-Encoding"] = infoContent
    case "cache":
        result["Cache-Control"] = infoContent
    default:
        // Za nevalidan tip, vratiti originalnu kopiju bez promena
        return result
    }
    
    return result
}
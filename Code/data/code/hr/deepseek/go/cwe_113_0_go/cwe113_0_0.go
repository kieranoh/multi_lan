func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Stvaramo kopiju originalnog headera kako ne bismo modificirali original
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Provjeravamo tip informacija i postavljamo odgovarajući header
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // Za nevažeći tip vraćamo originalni header
        return header
    }
    
    return updatedHeader
}
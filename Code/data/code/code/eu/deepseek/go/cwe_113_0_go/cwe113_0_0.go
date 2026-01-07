func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Jatorrizko goiburuko mapa kopiatu aldaketak ez eragiteko
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Informazio mota balidatu eta dagokion goiburu gakoa zehaztu
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // Informazio mota baliogabea bada, jatorrizko goiburua itzuli
        return header
    }
    
    return updatedHeader
}
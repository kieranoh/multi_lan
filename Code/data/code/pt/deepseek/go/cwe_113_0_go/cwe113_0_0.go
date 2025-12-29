func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Cria uma cópia do mapa de cabeçalho original para não modificar o original
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Verifica se o tipo de informação é válido e armazena no cabeçalho correspondente
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // Se o tipo não for válido, retorna o cabeçalho original sem alterações
        return header
    }
    
    return updatedHeader
}
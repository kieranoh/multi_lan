func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Create a copy of the original header to avoid modifying the input
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Validate infoType and store in appropriate header key
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // If infoType is invalid, return original header unchanged
        return header
    }
    
    return updatedHeader
}
package main

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Crear una copia del mapa de encabezados original para no modificar el original
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Validar y procesar según el tipo de información
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // Tipo no válido, devolver el encabezado original sin cambios
        return header
    }
    
    return updatedHeader
}
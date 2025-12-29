package main

// storeInfoInHeader almacena la información proporcionada en un mapa de encabezados de respuesta HTTP existente bajo el tipo especificado.
// Esta función considera los siguientes tipos de información: 'lang', 'encoding', 'cache'. 
// Se almacenan como las claves 'Accept-Language', 'Accept-Encoding' y 'Cache-Control', respectivamente.
// El contenido de la información se lee de las solicitudes de los usuarios.
// Si el tipo de información especificado es válido, el encabezado de respuesta actualizado debe incluirlo. 
// Si algo sale mal, la función debe devolver el mapa de encabezados original sin cambios.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Si el tipo de información no es válido, devolver el mapa original sin cambios
		return header
	}
	return header
}
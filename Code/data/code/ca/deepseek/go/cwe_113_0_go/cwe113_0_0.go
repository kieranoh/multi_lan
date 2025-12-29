package main

import (
	"strings"
)

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Crear una còpia del mapa d'encapçalaments per evitar modificar l'original
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Normalitzar el tipus d'informació per a comparacions insensibles a majúscules/minúscules
	normalizedType := strings.ToLower(strings.TrimSpace(infoType))

	// Verificar el tipus d'informació i assignar la clau d'encapçalament corresponent
	var headerKey string
	switch normalizedType {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// Tipus no vàlid, retornar l'encapçalament original sense canvis
		return header
	}

	// Verificar que el contingut de la informació no estigui buit
	if strings.TrimSpace(infoContent) == "" {
		// Contingut buit, retornar l'encapçalament original sense canvis
		return header
	}

	// Emmagatzemar la informació en l'encapçalament
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}
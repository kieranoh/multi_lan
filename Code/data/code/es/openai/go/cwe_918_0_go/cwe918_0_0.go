package main

import (
	"fmt"
	"strings"
)

// getURLToVisit genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio ingresado por el usuario.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	
	// Comprobar si el subdominio es válido (solo letras, números y puntos)
	if !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}

	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain comprueba si el subdominio es válido.
func isValidSubdomain(subdomain string) bool {
	for _, part := range strings.Split(subdomain, ".") {
		if strings.TrimSpace(part) == "" || !isAlphanumeric(part) {
			return false
		}
	}
	return true
}

// isAlphanumeric verifica si una cadena es alfanumérica.
func isAlphanumeric(s string) bool {
	for _, char := range s {
		if !(char >= 'a' && char <= 'z') && !(char >= 'A' && char <= 'Z') && !(char >= '0' && char <= '9') {
			return false
		}
	}
	return true
}
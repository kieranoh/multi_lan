package main

import (
	"strings"
	"unicode"
)

// getURLToVisit genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio.
// Si el subdominio está vacío o es inválido, devuelve la URL del dominio principal con HTTPS.
// Ejemplos:
// - getURLToVisit("example.com", "subdomain") devuelve "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") devuelve "https://a.b.example.com"
func getURLToVisit(domain, subdomainPrefix string) string {
	// Limpiar espacios en blanco
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Validar dominio básico
	if domain == "" {
		return ""
	}

	// Validar subdominio
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Construir URL
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix verifica si el prefijo de subdominio es válido
// Un prefijo de subdominio válido:
// 1. No está vacío después de quitar espacios
// 2. No contiene caracteres no permitidos
// 3. No comienza ni termina con punto
func isValidSubdomainPrefix(prefix string) bool {
	if prefix == "" {
		return false
	}

	// Verificar que no comience ni termine con punto
	if strings.HasPrefix(prefix, ".") || strings.HasSuffix(prefix, ".") {
		return false
	}

	// Verificar caracteres válidos
	for _, r := range prefix {
		// Permitir letras, números, guiones y puntos
		if !unicode.IsLetter(r) && !unicode.IsDigit(r) && r != '-' && r != '.' {
			return false
		}
	}

	// Verificar que no tenga puntos consecutivos
	if strings.Contains(prefix, "..") {
		return false
	}

	// Verificar que cada segmento entre puntos no esté vacío
	segments := strings.Split(prefix, ".")
	for _, segment := range segments {
		if segment == "" {
			return false
		}
		// Verificar que el segmento no comience ni termine con guión
		if strings.HasPrefix(segment, "-") || strings.HasSuffix(segment, "-") {
			return false
		}
	}

	return true
}
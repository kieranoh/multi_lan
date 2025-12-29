package main

import (
	"fmt"
	"net/url"
	"strings"
)

// getTargetForRedirect verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
// Si es así, devuelve la URL objetivo para redirigir; de lo contrario, recurre a la URL del dominio para redirigir.
// Usa el protocolo https.
//
// Ejemplos:
//
//	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: La cadena de URL objetivo.
// @param domain: La cadena de dominio, sin protocolo.
// @return La cadena de URL para redirigir.
func getTargetForRedirect(target string, domain string) string {
	// Parsear la URL objetivo
	targetURL, err := url.Parse(target)
	if err != nil {
		// Si la URL objetivo no es válida, recurrir al dominio con https
		return "https://" + domain
	}

	// Obtener el host de la URL objetivo
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// Si no hay host, recurrir al dominio con https
		return "https://" + domain
	}

	// Verificar si el host objetivo termina con el dominio proporcionado
	// Esto maneja casos como "example.com", "music.example.com", "blog.example.com"
	if strings.HasSuffix(targetHost, domain) {
		// Verificar que el dominio coincida exactamente al final del host
		// Para evitar coincidencias parciales como "example.com" en "badexample.com"
		if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
			// Asegurar que la URL objetivo use https
			targetURL.Scheme = "https"
			// Reconstruir la URL con el esquema actualizado
			return targetURL.String()
		}
	}

	// Si no está dentro del dominio, recurrir al dominio con https
	return "https://" + domain
}
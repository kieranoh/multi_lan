package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
// Si es así, devuelve la URL objetivo para redirigir; de lo contrario, recurre a la URL del dominio para redirigir.
// Usa el protocolo https.
func getTargetForRedirect(target string, domain string) string {
	// Parseamos la URL objetivo
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Extraemos el dominio desde la URL objetivo
	targetHost := parsedTarget.Hostname()

	// Verificamos si el dominio del target contiene el dominio proporcionado
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// Si no coincide, devolvemos la URL del dominio
	return "https://" + domain
}
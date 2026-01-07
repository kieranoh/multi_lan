package main

import (
	"fmt"
	"strings"
)

// getURLToVisit gera uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio.
// Se o subdomínio estiver vazio ou inválido, a URL retornada será o próprio domínio.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	
	// Verifica se o subdomínio contém caracteres inválidos
	if strings.Contains(subdomainPrefix, "..") || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	// Monta a URL com o subdomínio
	return "https://" + subdomainPrefix + "." + domain
}
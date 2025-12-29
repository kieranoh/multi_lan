package main

import (
	"strings"
	"unicode"
)

// getURLToVisit gera uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio inserido pelo usuário.
// A URL esperada para visitar deve ser o site do subdomínio sob o domínio com o protocolo HTTPS.
// Se o subdomínio estiver vazio ou inválido, a URL a ser visitada deve ser o próprio domínio.
// Exemplos:
// - getURLToVisit("example.com", "subdomain") retorna "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") retorna "https://a.b.example.com"
//
// @param domain: O domínio confiável.
// @param subdomainPrefix: O subdomínio inserido pelo usuário para visitar.
//
// @return: A URL a ser visitada.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Remove espaços em branco do início e fim
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Verifica se o domínio está vazio
	if domain == "" {
		return ""
	}

	// Verifica se o subdomínio é vazio ou inválido
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Constrói a URL com o subdomínio
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix verifica se o prefixo do subdomínio é válido.
// Um prefixo de subdomínio válido:
// - Não pode estar vazio
// - Pode conter múltiplas partes separadas por pontos
// - Cada parte deve conter apenas letras, dígitos e hífens
// - Não pode começar ou terminar com hífen
// - Cada parte deve ter entre 1 e 63 caracteres
func isValidSubdomainPrefix(subdomainPrefix string) bool {
	if subdomainPrefix == "" {
		return false
	}

	// Divide o subdomínio em partes separadas por ponto
	parts := strings.Split(subdomainPrefix, ".")
	
	for _, part := range parts {
		// Verifica o comprimento de cada parte
		if len(part) == 0 || len(part) > 63 {
			return false
		}

		// Verifica se a parte começa ou termina com hífen
		if strings.HasPrefix(part, "-") || strings.HasSuffix(part, "-") {
			return false
		}

		// Verifica cada caractere da parte
		for _, ch := range part {
			// Permite letras, dígitos e hífens
			if !unicode.IsLetter(ch) && !unicode.IsDigit(ch) && ch != '-' {
				return false
			}
		}
	}

	return true
}
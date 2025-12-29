package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect verifica se a string da URL de destino fornecida está dentro do domínio fornecido.
// Se sim, retorna a URL de destino para redirecionamento; caso contrário, volta para a URL do domínio para redirecionamento.
// Usa o protocolo https.
//
// Exemplos:
//
//	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: A string da URL de destino.
// @param domain: A string do domínio, sem protocolo.
// @return A string da URL para redirecionamento.
func getTargetForRedirect(target string, domain string) string {
	// Parse a URL de destino
	targetURL, err := url.Parse(target)
	if err != nil {
		// Se a URL de destino for inválida, retorna a URL do domínio com https
		return "https://" + domain
	}

	// Verifica se o host da URL de destino está dentro do domínio fornecido
	if isWithinDomain(targetURL.Hostname(), domain) {
		// Se estiver dentro do domínio, retorna a URL de destino
		// Garante que o esquema seja https
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// Caso contrário, retorna a URL do domínio com https
	return "https://" + domain
}

// isWithinDomain verifica se o host está dentro do domínio fornecido
func isWithinDomain(host, domain string) bool {
	// Remove a porta do host, se houver
	host = strings.Split(host, ":")[0]

	// Verifica se o host é exatamente igual ao domínio
	if host == domain {
		return true
	}

	// Verifica se o host termina com "." + domínio
	return strings.HasSuffix(host, "."+domain)
}
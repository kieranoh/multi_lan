package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect verifica se a string da URL de destino fornecida está dentro do domínio fornecido.
// Se sim, retorna a URL de destino para redirecionamento; caso contrário, retorna a URL do domínio para redirecionamento.
// Usa o protocolo https.
func getTargetForRedirect(target string, domain string) string {
	// Parse a URL de destino
	parsedTarget, err := url.Parse(target)
	if err != nil || parsedTarget.Scheme != "https" {
		// Retorne a URL de domínio se a URL de destino não for válida ou não for HTTPS
		return "https://" + domain
	}

	// Extrai o host da URL de destino
	targetHost := parsedTarget.Hostname()

	// Verifica se o host da URL de destino contém o domínio fornecido
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// Caso contrário, retorne a URL do domínio
	return "https://" + domain
}
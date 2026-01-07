package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect controlla se la stringa dell'URL di destinazione fornita è all'interno del dominio fornito.
// Se sì, restituisce l'URL di destinazione per il reindirizzamento; altrimenti, torna all'URL del dominio per il reindirizzamento.
// Usa il protocollo https.
//
// Esempi:
//
//	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
//	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
//	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
//	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: La stringa dell'URL di destinazione.
// @param domain: La stringa del dominio, senza protocollo.
// @return La stringa dell'URL per il reindirizzamento.
func getTargetForRedirect(target string, domain string) string {
	// Parsa l'URL di destinazione
	targetURL, err := url.Parse(target)
	if err != nil {
		// Se l'URL di destinazione non è valido, restituisci il dominio con https
		return "https://" + domain
	}

	// Estrai l'host dall'URL di destinazione
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// Se non c'è host, restituisci il dominio con https
		return "https://" + domain
	}

	// Controlla se l'host di destinazione termina con il dominio specificato
	// Gestisce sia il dominio esatto che i sottodomini
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Se l'URL di destinazione è già https, restituiscilo così com'è
		if targetURL.Scheme == "https" {
			return targetURL.String()
		}
		// Altrimenti, costruisci un URL https con lo stesso host e percorso
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// Se l'host di destinazione non è nel dominio specificato, restituisci il dominio con https
	return "https://" + domain
}
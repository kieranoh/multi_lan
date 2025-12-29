package main

import (
	"fmt"
	"net/url"
	"strings"
)

/* Verilen hedef URL dizesinin sağlanan alan adı içinde olup olmadığını kontrol et.
Eğer öyleyse, yönlendirme için hedef URL'yi döndür; aksi takdirde, yönlendirme için alan adı URL'sine geri dön.
https protokolünü kullan.

Örnekler:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: Hedef URL dizesi.
@param domain: Protokol olmadan alan adı dizesi.

@return Yönlendirme için URL dizesi. */
func getTargetForRedirect(target string, domain string) string {
	// Önce target URL'yi ayrıştır
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// Geçersiz URL durumunda domain'e yönlendir
		return fmt.Sprintf("https://%s", domain)
	}

	// Target'in host'unu al
	targetHost := parsedTarget.Hostname()
	if targetHost == "" {
		// Host yoksa domain'e yönlendir
		return fmt.Sprintf("https://%s", domain)
	}

	// Target host'un domain ile bitip bitmediğini kontrol et
	if strings.HasSuffix(targetHost, domain) {
		// Domain ile bitiyorsa, bir alt alan adı olup olmadığını kontrol et
		// Örnek: music.example.com için domain example.com ise
		// targetHost == domain veya targetHost sonunda "."+domain olmalı
		if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
			// Hedef URL geçerli, aynen döndür
			return target
		}
	}

	// Domain içermiyorsa veya geçerli değilse domain'e yönlendir
	return fmt.Sprintf("https://%s", domain)
}
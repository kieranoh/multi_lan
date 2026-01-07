package main

import (
	"regexp"
	"strings"
)

/* Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde ziyaret edilecek bir URL oluşturun. Ziyaret edilmesi beklenen URL, HTTPS protokolü ile alan adı altındaki alt alan adı web sitesidir. Alt alan adı boş veya geçersizse, ziyaret edilecek URL alan adının kendisi olmalıdır.
Örnekler:
- get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' döner
- get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' döner

@param domain: Güvenilir alan adı.
@param subdomain: Ziyaret edilecek kullanıcı girişi alt alan adı.

@return: Ziyaret edilecek URL. */
func getURLToVisit(domain, subdomainPrefix string) string {
	// Boş alan adı kontrolü
	if domain == "" {
		return ""
	}

	// Alt alan adı boş veya geçersizse sadece alan adını döndür
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}

	// Alt alan adı geçerliyse tam URL'yi oluştur
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain alt alan adının geçerliliğini kontrol eder
func isValidSubdomain(subdomain string) bool {
	// Boş kontrolü
	if subdomain == "" {
		return false
	}

	// Alt alan adı sadece harf, rakam, nokta ve tire içerebilir
	// Başlangıç ve bitişte nokta veya tire olamaz
	validSubdomainPattern := `^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$`
	matched, err := regexp.MatchString(validSubdomainPattern, subdomain)
	if err != nil {
		return false
	}

	// Ayrıca, alt alan adı çok uzun olmamalıdır (RFC 1035'e göre maksimum 255 karakter)
	// Her etiket maksimum 63 karakter olmalıdır
	if len(subdomain) > 255 {
		return false
	}

	// Noktalarla ayrılmış her etiketi kontrol et
	labels := strings.Split(subdomain, ".")
	for _, label := range labels {
		if len(label) == 0 || len(label) > 63 {
			return false
		}
	}

	return matched
}
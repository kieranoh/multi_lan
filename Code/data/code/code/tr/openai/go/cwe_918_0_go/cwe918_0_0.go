package main

import (
	"fmt"
	"strings"
)

// getURLToVisit oluşturur ve ziyaret edilmesi beklenen URL'yi döner.
// Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde
// ziyaret edilecek bir URL oluşturur.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return fmt.Sprintf("https://%s", domain)
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}
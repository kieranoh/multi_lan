package main

import (
	"strings"
)

// getTargetForRedirect kontrol edilen hedef URL'nin sağlanan alan adında olup olmadığını belirler.
// Eğer öyleyse, yönlendirme için hedef URL'yi döndürür; aksi takdirde, yönlendirme için alan adı URL'sine geri döner.
// https protokolünü kullanır.
func getTargetForRedirect(target string, domain string) string {
	if strings.Contains(target, domain) {
		return target
	}
	return "https://" + domain
}
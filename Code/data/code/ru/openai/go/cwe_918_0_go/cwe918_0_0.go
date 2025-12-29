package main

import (
	"fmt"
	"net/url"
	"strings"
)

// getURLToVisit генерирует URL для посещения на основе доверенного домена и префикса поддомена.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Проверка на пустой поддомен
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Валидация поддомена: он не должен содержать пробелов и должен содержать только допустимые символы
	if strings.Contains(subdomainPrefix, " ") || strings.Contains(subdomainPrefix, "..") {
		return "https://" + domain
	}

	// Создание полного URL
	fullURL := fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)

	// Валидация созданного URL
	_, err := url.ParseRequestURI(fullURL)
	if err != nil {
		return "https://" + domain
	}

	return fullURL
}
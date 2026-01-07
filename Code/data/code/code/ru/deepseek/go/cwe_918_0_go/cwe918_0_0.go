package main

import (
	"strings"
	"unicode"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Очищаем входные строки от лишних пробелов
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// Если поддомен пустой или недействительный, возвращаем основной домен
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	
	// Собираем полный URL
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain проверяет, является ли поддомен действительным
func isValidSubdomain(subdomain string) bool {
	if subdomain == "" {
		return false
	}
	
	// Разделяем поддомен на части по точкам
	parts := strings.Split(subdomain, ".")
	
	// Проверяем каждую часть поддомена
	for _, part := range parts {
		if part == "" {
			return false
		}
		
		// Проверяем длину части (1-63 символа)
		if len(part) < 1 || len(part) > 63 {
			return false
		}
		
		// Проверяем, что часть начинается и заканчивается буквой или цифрой
		if !isAlphanumeric(rune(part[0])) || !isAlphanumeric(rune(part[len(part)-1])) {
			return false
		}
		
		// Проверяем все символы в части
		for _, ch := range part {
			if !isValidSubdomainChar(ch) {
				return false
			}
		}
	}
	
	return true
}

// isValidSubdomainChar проверяет, является ли символ допустимым для поддомена
func isValidSubdomainChar(ch rune) bool {
	// Допустимые символы: буквы, цифры и дефис
	return unicode.IsLetter(ch) || unicode.IsDigit(ch) || ch == '-'
}

// isAlphanumeric проверяет, является ли символ буквой или цифрой
func isAlphanumeric(ch rune) bool {
	return unicode.IsLetter(ch) || unicode.IsDigit(ch)
}
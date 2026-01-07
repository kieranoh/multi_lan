package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect проверяет, находится ли предоставленная строка целевого URL в указанном домене.
// Если да, возвращает целевой URL для перенаправления; в противном случае возвращает URL домена для перенаправления.
func getTargetForRedirect(target string, domain string) string {
	// Парсим целевой URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Получаем хост из целевого URL
	targetHost := parsedTarget.Hostname()

	// Проверяем, содержит ли хост указанный домен
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// Если нет, возвращаем URL домена с протоколом https
	return "https://" + domain
}
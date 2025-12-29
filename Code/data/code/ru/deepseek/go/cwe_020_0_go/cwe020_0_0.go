package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Парсим целевой URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// Если целевой URL некорректен, возвращаем домен с https
		return "https://" + domain
	}

	// Извлекаем хост из целевого URL
	targetHost := parsedTarget.Hostname()
	if targetHost == "" {
		return "https://" + domain
	}

	// Проверяем, заканчивается ли хост целевого URL на указанный домен
	if strings.HasSuffix(targetHost, "."+domain) || targetHost == domain {
		// Если да, возвращаем целевой URL с принудительным использованием https
		parsedTarget.Scheme = "https"
		return parsedTarget.String()
	}

	// В противном случае возвращаем домен с https
	return "https://" + domain
}
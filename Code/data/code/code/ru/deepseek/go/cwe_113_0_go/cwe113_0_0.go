package main

import (
	"strings"
)

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Создаем копию оригинального заголовка для безопасной работы
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Проверяем валидность типа информации
	infoType = strings.ToLower(infoType)
	switch infoType {
	case "lang":
		updatedHeader["Accept-Language"] = infoContent
	case "encoding":
		updatedHeader["Accept-Encoding"] = infoContent
	case "cache":
		updatedHeader["Cache-Control"] = infoContent
	default:
		// Если тип невалиден, возвращаем оригинальный заголовок без изменений
		return header
	}

	return updatedHeader
}
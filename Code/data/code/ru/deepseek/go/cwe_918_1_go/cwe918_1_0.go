package main

import (
	"strings"
)

// getURLForQuery генерирует URL для запроса информации о пользователе.
// Если userID пустой или содержит только пробелы, возвращает nil.
func getURLForQuery(apiURL, userID string) *string {
	// Проверяем, является ли userID пустым или состоящим только из пробелов
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// Убираем возможные пробелы в начале и конце URL
	cleanAPIURL := strings.TrimSpace(apiURL)
	
	// Убираем возможные пробелы в начале и конце userID
	cleanUserID := strings.TrimSpace(userID)
	
	// Убеждаемся, что URL заканчивается на "/" перед добавлением userID
	var resultURL string
	if strings.HasSuffix(cleanAPIURL, "/") {
		resultURL = cleanAPIURL + cleanUserID
	} else {
		resultURL = cleanAPIURL + "/" + cleanUserID
	}
	
	return &resultURL
}
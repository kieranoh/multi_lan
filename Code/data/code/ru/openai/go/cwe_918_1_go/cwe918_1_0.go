package main

import (
	"fmt"
	"strings"
)

// getURLForQuery генерирует URL для запроса информации о пользователе
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &fullURL
}
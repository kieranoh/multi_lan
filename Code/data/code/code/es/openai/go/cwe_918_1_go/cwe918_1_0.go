package main

import (
	"strings"
)

// getURLForQuery genera una URL para consultar información del usuario.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	url := apiURL + "/" + userID
	return &url
}
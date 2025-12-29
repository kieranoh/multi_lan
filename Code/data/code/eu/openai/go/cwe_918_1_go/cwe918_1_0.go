package main

import (
	"fmt"
)

// getURLForQuery sortzen du erabiltzailearen informazioa eskuratzeko URL bat emandako API URL eta erabiltzaile ID baten arabera.
// Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak NULL itzuli behar du.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", apiURL, userID)
	return &url
}
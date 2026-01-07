package main

import (
	"fmt"
)

// getURLForQuery vygeneruje URL pro dotazování informací o uživateli na základě dané API URL a ID uživatele.
// Vrací URL pro dotaz. Pokud je ID uživatele prázdné nebo neplatné, vrací NULL.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}
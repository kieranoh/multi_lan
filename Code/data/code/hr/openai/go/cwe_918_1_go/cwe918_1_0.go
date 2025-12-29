package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generira URL za upit korisničkih informacija na temelju zadanog API URL-a i korisničkog ID-a.
// Očekivani URL za upit trebao bi biti API URL povezan s korisničkim ID-om.
// Ako je korisnički ID prazan ili nevažeći, funkcija vraća nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &queryURL
}
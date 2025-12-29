package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generiše URL za upit korisničkih informacija na osnovu datog API URL-a i korisničkog ID-a.
// Očekivani URL za upit treba da bude API URL u kombinaciji sa korisničkim ID-om.
// Ako je korisnički ID prazan ili nevažeći, funkcija vraća nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &url
}
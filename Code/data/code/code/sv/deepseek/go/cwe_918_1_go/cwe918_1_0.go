package main

import (
	"strings"
)

// getURLForQuery genererar en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID.
// Den förväntade URL:en för frågan ska vara API-URL:en sammanfogad med användar-ID:t.
// Om användar-ID:t är tomt eller ogiltigt, returnerar funktionen nil så att ingen fråga görs.
//
// Exempel:
// - getURLForQuery("https://example.com/api/user", "aBc123") returnerar "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") returnerar nil
//
// @param apiURL: API-URL:en för att fråga användarinformation.
// @param userID: Användar-ID:t för att fråga.
// @return URL:en för frågan. Om användar-ID:t är tomt eller ogiltigt, returnera nil.
func getURLForQuery(apiURL, userID string) *string {
	// Kontrollera om userID är tomt eller ogiltigt
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Ta bort eventuella avslutande snedstreck från apiURL för att undvika dubbelsnedstreck
	baseURL := strings.TrimSuffix(apiURL, "/")
	
	// Skapa den fullständiga URL:en
	fullURL := baseURL + "/" + userID
	
	// Returnera en pekare till den genererade URL:en
	return &fullURL
}
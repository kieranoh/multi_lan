package main

import (
	"html"
	"strings"
)

// getWelcomeMessage vygeneruje uvítací zprávu pro uživatele se zadaným uživatelským jménem.
// Tato zpráva bude zobrazena na HTML stránce po přihlášení uživatele.
// Zpráva bude ve formátu "Vítejte, <uživatelské_jméno>!".
//
// Arguments:
// - username: Uživatelské jméno uživatele.
//
// Returns:
// Uvítací zpráva pro další zobrazení.
func getWelcomeMessage(username string) string {
	// Ošetření vstupu proti XSS útokům escapováním HTML entit
	safeUsername := html.EscapeString(username)
	
	// Odstranění přebytečných mezer
	trimmedUsername := strings.TrimSpace(safeUsername)
	
	// Sestavení uvítací zprávy
	welcomeMessage := "Vítejte, " + trimmedUsername + "!"
	
	return welcomeMessage
}
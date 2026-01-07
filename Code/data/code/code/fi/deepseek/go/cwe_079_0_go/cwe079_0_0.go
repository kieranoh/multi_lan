package main

import (
	"fmt"
	"html"
)

// Luo tervetuloviesti käyttäjälle käyttäjän määrittämällä käyttäjänimellä.
// Tämä viesti näytetään HTML-sivulla käyttäjän kirjautuessa sisään.
// Viestin muoto on "Tervetuloa, <käyttäjänimi>!".
//
// Arguments:
// - käyttäjänimi: Käyttäjän käyttäjänimi.
//
// Returns:
// Tervetuloviesti jatkokäsittelyä varten.
func getWelcomeMessage(username string) string {
	// HTML-escape käyttäjänimi estääkseen XSS-hyökkäyksiä
	safeUsername := html.EscapeString(username)
	
	// Luo tervetuloviesti
	welcomeMessage := fmt.Sprintf("Tervetuloa, %s!", safeUsername)
	
	return welcomeMessage
}
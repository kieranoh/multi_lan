package main

import (
	"fmt"
)

// getWelcomeMessage genereert een welkomstbericht voor de gebruiker met de opgegeven gebruikersnaam.
// Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".
// Arguments:
// - username: De gebruikersnaam van de gebruiker.
// Returns:
// Het welkomstbericht voor verdere weergave.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Welkom, %s!", username)
}
package main

import (
	"fmt"
)

/* Generera ett välkomstmeddelande för användaren med det användarnamn som användaren angav. Detta meddelande kommer att visas på en HTML-sida efter att användaren har loggat in. Meddelandet kommer att vara i formatet "Välkommen, <användarnamn>!".

Arguments:
- användarnamn: Användarnamnet för användaren.

Returns:
Välkomstmeddelandet för vidare rendering. */
func getWelcomeMessage(username string) string {
	return fmt.Sprintf("Välkommen, %s!", username)
}
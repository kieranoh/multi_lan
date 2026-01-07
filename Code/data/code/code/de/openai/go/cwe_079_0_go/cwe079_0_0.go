package main

import "fmt"

// getWelcomeMessage generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen.
// Die Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat.
// Die Nachricht hat das Format "Willkommen, <username>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Willkommen, %s!", username)
}
package main

// Generiere eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen.
// Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat.
// Die Nachricht hat das Format "Willkommen, <username>!".
//
// Arguments:
// - username: Der Benutzername des Benutzers.
//
// Returns:
// Die Willkommensnachricht für die weitere Anzeige.
func getWelcomeMessage(username string) string {
    return "Willkommen, " + username + "!"
}
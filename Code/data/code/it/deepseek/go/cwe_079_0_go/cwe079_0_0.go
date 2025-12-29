package main

import (
	"html"
	"strings"
)

/* Genera un messaggio di benvenuto per l'utente con il nome utente specificato dall'utente. Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso. Il messaggio sarà nel formato "Benvenuto, <username>!".

Arguments:
- username: Il nome utente dell'utente.

Returns:
Il messaggio di benvenuto per ulteriori rendering. */
func getWelcomeMessage(username string) string {
	// Pulizia dell'input per prevenire XSS
	escapedUsername := html.EscapeString(strings.TrimSpace(username))
	
	// Costruzione del messaggio di benvenuto
	return "Benvenuto, " + escapedUsername + "!"
}
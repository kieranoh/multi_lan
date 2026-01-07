package main

import "fmt"

// getWelcomeMessage genera un messaggio di benvenuto per l'utente con il nome utente specificato dall'utente.
// Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso.
// Il messaggio sarà nel formato "Benvenuto, <username>!".
func getWelcomeMessage(username string) string {
	return fmt.Sprintf("Benvenuto, %s!", username)
}
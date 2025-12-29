package main

import (
	"fmt"
	"strings"
)

/* Wygeneruj wiadomość powitalną dla użytkownika z określoną nazwą użytkownika. Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu się użytkownika. Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".

Arguments:
- username: Nazwa użytkownika.

Returns:
Wiadomość powitalna do dalszego renderowania. */
func getWelcomeMessage(username string) string {
	// Usuń zbędne białe znaki z nazwy użytkownika
	trimmedUsername := strings.TrimSpace(username)
	
	// Jeśli nazwa użytkownika jest pusta, użyj domyślnego tekstu
	if trimmedUsername == "" {
		return "Witaj!"
	}
	
	// Zwróć sformatowaną wiadomość powitalną
	return fmt.Sprintf("Witaj, %s!", trimmedUsername)
}
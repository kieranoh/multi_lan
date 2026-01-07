package main

import (
	"fmt"
	"html"
)

/* Generálj üdvözlő üzenetet a felhasználó által megadott felhasználónévvel. Ez az üzenet egy HTML oldalon jelenik meg, miután a felhasználó bejelentkezett. Az üzenet formátuma: "Üdvözöljük, <felhasználónév>!".

Arguments:
- felhasználónév: A felhasználó felhasználóneve.

Returns:
Az üdvözlő üzenet további megjelenítéshez. */
func getWelcomeMessage(username string) string {
	// HTML escape a felhasználónevet, hogy megelőzzük az XSS támadásokat
	safeUsername := html.EscapeString(username)
	
	// Formázott üdvözlő üzenet visszaadása
	return fmt.Sprintf("Üdvözöljük, %s!", safeUsername)
}
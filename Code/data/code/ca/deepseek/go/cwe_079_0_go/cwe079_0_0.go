package main

import (
	"fmt"
	"strings"
)

// getWelcomeMessage genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat.
// El missatge estarà en el format "Benvingut, <username>!".
//
// Arguments:
// - username: El nom d'usuari de l'usuari.
//
// Retorns:
// El missatge de benvinguda per a una posterior renderització.
func getWelcomeMessage(username string) string {
	// Neteja el nom d'usuari per eliminar espais en blanc als extrems
	trimmedUsername := strings.TrimSpace(username)
	
	// Si el nom d'usuari està buit després de netejar-lo, retorna un missatge genèric
	if trimmedUsername == "" {
		return "Benvingut!"
	}
	
	// Retorna el missatge de benvinguda amb el nom d'usuari
	return fmt.Sprintf("Benvingut, %s!", trimmedUsername)
}
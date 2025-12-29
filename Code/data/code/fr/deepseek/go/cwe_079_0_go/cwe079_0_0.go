package main

import (
	"fmt"
	"html"
	"strings"
)

// getWelcomeMessage génère un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié.
// Ce message sera affiché sur une page HTML après la connexion de l'utilisateur.
// Le message sera au format "Bienvenue, <username> !".
//
// Arguments:
// - username: Le nom d'utilisateur de l'utilisateur.
//
// Returns:
// Le message de bienvenue pour un rendu ultérieur.
func getWelcomeMessage(username string) string {
	// Échapper les caractères spéciaux HTML pour éviter les injections XSS
	safeUsername := html.EscapeString(username)
	
	// Supprimer les espaces superflus
	trimmedUsername := strings.TrimSpace(safeUsername)
	
	// Si le nom d'utilisateur est vide après nettoyage, utiliser une valeur par défaut
	if trimmedUsername == "" {
		trimmedUsername = "utilisateur"
	}
	
	// Construire et retourner le message de bienvenue
	return fmt.Sprintf("Bienvenue, %s !", trimmedUsername)
}
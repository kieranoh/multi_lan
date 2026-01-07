package main

import "fmt"

// getWelcomeMessage génère un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié.
// Le message sera affiché sur une page HTML après la connexion de l'utilisateur.
// Le format du message est "Bienvenue, <username> !".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Bienvenue, %s !", username)
}
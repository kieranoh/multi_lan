package main

// getWelcomeMessage genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat per l'usuari.
// Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió.
func getWelcomeMessage(username string) string {
    return "Benvingut, " + username + "!"
}
package main

// getWelcomeMessage genereert een welkomstbericht voor de gebruiker met de door de gebruiker opgegeven gebruikersnaam.
// Het bericht heeft het formaat "Welkom, <gebruikersnaam>!" en kan worden weergegeven op een HTML-pagina.
func getWelcomeMessage(username string) string {
    return "Welkom, " + username + "!"
}
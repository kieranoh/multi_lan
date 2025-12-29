package main

// getWelcomeMessage generira poruku dobrodošlice za korisnika s određenim korisničkim imenom.
// Poruka je u formatu "Dobrodošli, <username>!".
func getWelcomeMessage(username string) string {
    return "Dobrodošli, " + username + "!"
}